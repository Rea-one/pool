#include "origin.h"
#include "QFileSystemModel"
#include "QFileDialog"
#include "QTextStream"
#include "QMessageBox"
#include "QRegularExpression"

#include "parser.h"
#include "tree_sitter/api.h"

#include "mruby.h"
#include "mruby/compile.h"

#include "methods.h"

#include "vector"
#include "string"
#include "filesystem"
#include "thread"
#include "mutex"



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
    thread_pool tasks;
    bool run_linguist();
    void ruby_task();
    bool run_mruby();
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

    void read_language_type(QString file_name);
    int declare_line;
    QList<int> ref_lines;
    QList<int> modify_lines;
    void words_distribution();
    void load_words(std::vector<QString> tar_words);
};

class block
{
    public:
    std::vector<std::pair<QString, QString>> tars;
    std::vector<QString> acts;

    void init(QString words);

};

