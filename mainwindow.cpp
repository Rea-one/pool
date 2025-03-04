#include "mainwindow.h"

std::unordered_map<std::string, const TSLanguage *> language_map =
{
    {"c", tree_sitter_c()},
    {"cpp", tree_sitter_cpp()},
    {"javascript", tree_sitter_javascript()},
    {"python", tree_sitter_python()},
    // 添加更多语言...
};

win::win()
{
    ui.setupUi(this);
    // 在win构造函数中添加
    ui.editer->setFont(QFont("Consolas", 12));  // 设置等宽字体
    ui.editer->setAcceptRichText(false);       // 禁用富文本
    ui.editer->setLineWrapMode(QTextEdit::NoWrap); // 禁用自动换行
    connect(ui.file_tree, &QTreeView::doubleClicked, this, &win::on_file_doubleClicked);
    tasks.add_thread([this]()
    {
        analysis_task();
    });
}
win::~win()
{
    this->close();
}

bool win::enter()
{
    ui.steps->setCurrentIndex(1);
    return true;
}

bool win::to_file_tree()
{
    ui.file_tree->setModel(&model);
    ui.file_tree->setRootIndex(model.index(QDir::currentPath()));
    ui.wfile->setCurrentIndex(1);

    ui.file_tree->setColumnWidth(0, 250);  // 文件名列
    ui.file_tree->setColumnHidden(1, true); // 隐藏大小列
    ui.file_tree->setColumnHidden(2, true); // 隐藏类型列
    ui.file_tree->setColumnHidden(3, true); // 隐藏修改时间列

    select_directory();
    return true;
}

bool win::to_logics()
{
    ui.sidebar->setCurrentIndex(2);
    return true;
}

bool win::open_file()
{
    QString path = QFileDialog::getOpenFileName(this);
    if(path.isEmpty()) return false;
    
    QFile file(path);
    if(!file.open(QIODevice::ReadOnly)) return false;
    
    ui.editer->setPlainText(file.readAll());
    file.close();
    return true;
}

bool win::save_file()
{
    QString path = QFileDialog::getSaveFileName(this);
    if(path.isEmpty()) return false;
    
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly)) return false;
    
    file.write(ui.editer->toPlainText().toUtf8());
    file.close();
    return true;
}

void win::select_directory()
{
    QString dir = QFileDialog::getExistingDirectory(
        this, 
        "选择工作目录",
        QDir::homePath(),
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks
    );
    
    if(!dir.isEmpty()) {
        model.setRootPath(dir);
        ui.file_tree->setRootIndex(model.index(dir));
        QDir::setCurrent(dir); // 修改当前工作目录
        ui.statusbar->showMessage("当前目录：" + dir, 3000);
    }
}

void win::on_file_doubleClicked(const QModelIndex &index)
{
    // 获取完整文件路径
    QString filePath = model.filePath(index);
    current_file_path = filePath.toStdString();
    language_type_detected = false;

    // 判断是否是文件（过滤目录）
    if(!model.isDir(index))
    {
        QFile file(filePath);
        tasks.add_thread([this]()
        {
            linguist_task();
        });
        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            // 使用QTextStream读取确保编码正确
            QTextStream in(&file);
            ui.editer->setPlainText(in.readAll());
            file.close();
            // 更新状态栏显示
            ui.statusbar->showMessage("已打开: " + filePath, 3000);
        }
        else
        {
            ui.statusbar->showMessage("无法打开文件: " + filePath, 3000);
        }
    }
}

void win::linguist_task()
{
    std::unique_lock<std::mutex> lock(ruby_lock);
    mrb = mrb_open();
    
    if (mrb == NULL)
    {
        ui.statusbar->showMessage("mruby 初始化失败", 3000);
        return;
    }

    // 加载 linguist.rb 脚本
    FILE *linguist_pack = fopen("github-linguist", "r");
    if (!linguist_pack)
    {
        ui.statusbar->showMessage("无法加载linguist库", 3000);
        mrb_close(mrb);
        return;
    }
    mrb_load_file(mrb, linguist_pack);
    fclose(linguist_pack);

    while (language_detect_requirment)
    {
        if (!language_type_detected)
        {
            if (current_file_path.empty())
            {
                ui.statusbar->showMessage("请选择文件", 3000);
            }
            else
            {
                FILE *file = fopen(current_file_path.c_str(), "r");
                if (!file)
                {
                    ui.statusbar->showMessage("无法打开文件: " + QString::fromStdString(current_file_path), 3000);
                    continue;
                }

                // 执行 Ruby 脚本并获取结果
                mrb_value result = mrb_load_file(mrb, file);
                fclose(file);

                // 检查是否有异常
                if (mrb->exc)
                {
                    mrb_value exception = mrb_funcall(mrb, mrb_obj_value(mrb->exc), "inspect", 0);
                    qWarning() << "Error in linguist_task:" << QString::fromUtf8(mrb_string_value_ptr(mrb, exception));
                    mrb->exc = nullptr; // 清除异常
                    continue;
                }

                // 处理返回值
                QString language;
                if (mrb_string_p(result))
                {
                    language = QString::fromUtf8(mrb_string_value_ptr(mrb, result));
                }
                else
                {
                    language = "Unknown";
                }
                std::unique_lock<std::mutex> lock(data_lock);
                // 更新状态栏并存储检测结果
                ui.statusbar->showMessage("检测到语言: " + language, 3000);
                language_type = language.toStdString(); // 存储到成员变量
                language_type_detected = true; // 标记已检测
                analysis_operation = false; // 任务标记
            }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // 释放 mruby 资源
    mrb_close(mrb);
}

void win::analysis_task()
{
    std::unique_lock<std::mutex> lock(parser_lock);
    words_analysis *analysis = new words_analysis();

    while (words_analysis_requirment)
    {
        if (language_type_detected && !analysis_operation)
        {
            std::unique_lock<std::mutex> lock(data_lock);
            analysis->set_language_type(language_type);
        }
    }
}

words_analysis::words_analysis()
{
    distribution = std::vector<int>(256, 0);
    parser = ts_parser_new();
}

void words_analysis::set_language_type(std::string tar_type)
{
    // 根据传入的语言名称获取 Tree-sitter 语言定义
    const TSLanguage *language = string_to_TSLanguage(tar_type);
    
    if (language == nullptr)
    {
        // 如果语言未找到，可以记录错误或抛出异常
        qWarning() << "Tree-sitter language not found for:" << QString::fromStdString(tar_type);
        return;
    }

    // 设置解析器的语言类型
    ts_parser_set_language(parser, language);

    // 更新类成员变量
    language_type = tar_type;
}


void words_analysis::load_words(std::vector<QString> tar_words)
{
    words = tar_words;
}

void words_analysis::words_distribution()
{
    for (auto elem : words)
    {
        distribution[fast_index(elem.toLatin1()[0])] ++;
    }
}



const TSLanguage *string_to_TSLanguage(const std::string &language_name)
{
    auto it = language_map.find(language_name);
    if (it != language_map.end())
    {
        return it->second;
    }
    return nullptr; // 未找到对应语言
}