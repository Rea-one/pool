#include "qt_headers.h"


class ftree: public QObject
{
    Q_OBJECT
    explicit ftree(QObject *parent);
    ~ftree();

    std::string state_message;
    QFileSystemModel model;
};