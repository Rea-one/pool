#include "origin.h"
#include "QFileSystemModel"
#include "QFileDialog"
#include "QTextStream"
#include "QMessageBox"
#include "QRegularExpression"

#include "tree_sitter/api.h"

#include "mruby.h"
#include "mruby/compile.h"
#include "mruby/string.h"

#include "methods.h"

#include "vector"
#include "string"
#include "filesystem"
#include "thread"
#include "mutex"
#include "chrono"
#include "unordered_map"

extern "C"
{
    const TSLanguage *tree_sitter_c();
    const TSLanguage *tree_sitter_cpp();
    const TSLanguage *tree_sitter_javascript();
    const TSLanguage *tree_sitter_python();
}


extern std::unordered_map<std::string, const TSLanguage *> language_map;

const TSLanguage *string_to_TSLanguage(const std::string &language_name);


class win: public QMainWindow
{
    Q_OBJECT
    Ui_MainWindow ui{};
    QFileSystemModel model{};

    private:
    void on_file_doubleClicked(const QModelIndex &index);
    
    public:
    win();
    ~win();
    std::mutex ruby_lock;
    std::mutex data_lock;
    std::mutex parser_lock;
    std::string current_file_path{};
    std::string language_type{};
    bool language_type_detected=false;
    bool language_detect_requirment=true;
    bool words_analysis_requirment=false;
    bool analysis_operation=false;
    mrb_state* mrb=nullptr;
    
    threads tasks;
    
    void linguist_task();
    void analysis_task();
    

    public slots:
    bool enter();
    bool to_file_tree();
    bool to_logics();
    bool open_file();
    bool save_file();
    void select_directory();
};


class words_analysis
{
    public:
    words_analysis();
    TSParser *parser;
    std::vector<int> distribution;
    std::vector<QString> words;

    std::string language_type;
    void set_language_type(std::string tar_type);
    int declare_line;
    QList<int> ref_lines;
    QList<int> modify_lines;
    void words_distribution();
    void load_words(std::vector<QString> tar_words);
};

