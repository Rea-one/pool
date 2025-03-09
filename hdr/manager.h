#include "qt_headers.h"


#include "methods.h"

#include "ftree.h"
#include "wopol.h"


class vesita: public QObject
{
    Q_OBJECT
    explicit vesita(QObject *parent);
    ~vesita();


    threads tasks;

    ftree *ftree_tar{};
    wopol *wopol_tar{};

};
