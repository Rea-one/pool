#include "mainwindow.h"

win::win()
{
    ui.setupUi(this);
    // 在win构造函数中添加
    ui.editer->setFont(QFont("Consolas", 12));  // 设置等宽字体
    ui.editer->setAcceptRichText(false);       // 禁用富文本
    ui.editer->setLineWrapMode(QTextEdit::NoWrap); // 禁用自动换行
    connect(ui.file_tree, &QTreeView::doubleClicked, this, &win::on_file_doubleClicked);

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
    ui.sidebar->setCurrentIndex(1);

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
    
    // 判断是否是文件（过滤目录）
    if(!model.isDir(index)){
        QFile file(filePath);
        if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
            // 使用QTextStream读取确保编码正确
            QTextStream in(&file);
            ui.editer->setPlainText(in.readAll());
            file.close();
            
            // 更新状态栏显示
            ui.statusbar->showMessage("已打开: " + filePath, 3000);
        } else {
            ui.statusbar->showMessage("无法打开文件: " + filePath, 3000);
        }
    }
}