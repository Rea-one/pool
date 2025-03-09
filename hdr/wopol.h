#include " qt_headers.h"

class wopol: public QObject
{
    Q_OBJECT
    explicit wopol(QObject *parent = nullptr);
    ~wopol();

    std::vector<std::string> words{};
    std::string state_message{};

    void read_file(std::string file_path);
    void write_file(std::string file_path);
    
}