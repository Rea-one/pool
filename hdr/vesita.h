#include "qt_headers.h"


#include "methods.h"

#include "ftree.h"
#include "wopol.h"
#include "cross_message.h"


class vesita: public QObject
{
    Q_OBJECT
    public:
    enum class message_tars
    {
        ftree_tar,
        wopol_tar,
        mruby_tar,
    };
    explicit vesita();
    ~vesita();

    crsm messages{};
    vth threads{};
    std::vector<std::unique_ptr<std::jthread>> stays{};

    std::shared_ptr<ftree> ftree_tar{};
    std::shared_ptr<mruby_runner> mruby_tar{};
    std::vector<std::shared_ptr<wopol>> wopol_tar{};
};
