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
    std::string current_file_path{};
    std::string language_type{};
    bool language_type_detected=false;
    bool language_detect_requirment=true;
    mrb_state* mrb=nullptr;
    
    threads tasks;
    
    void linguist_task();
    bool close_mruby();
    std::string langua_feedback(std::string file_name);
    

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

