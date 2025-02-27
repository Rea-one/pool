#include "origin.h"
#include "QFileSystemModel"
#include "QFileDialog"
#include "QTextStream"

#include "vector"


class win: public QMainWindow
{
    Q_OBJECT
    Ui_MainWindow ui{};
    QFileSystemModel model{};

    private:
    bool file_filter(const QString &name);
    void on_file_doubleClicked(const QModelIndex &index);
    
    public:
    win();
    ~win();
    

    public slots:
    bool enter();
    bool to_file_tree();
    bool to_logics();
    bool open_file();
    bool save_file();
    void select_directory();
};
