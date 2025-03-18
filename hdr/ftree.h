#include "qt_headers.h"


class ftree: public QObject
{
    Q_OBJECT
public:
    explicit ftree(QObject *parent);
    ~ftree();

    QFileSystemModel model;

    void init();
    std::string get_path();
};