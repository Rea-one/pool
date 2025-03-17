#include "tree_sitter/api.h"

#include "qt_headers.h"

#include "methods.h"
#include "mruby_runner.h"
#include "fast_words.h"


class token: public QObject
{
    Q_OBJECT
    public:
    explicit token();
    ~token();

    std::string key{};
    std::string type{};
    int index{};
};

class token_line: public QObject
{
    Q_OBJECT
    public:
    explicit token_line();
    ~token_line();

    std::vector<token*> tokens{};
    int index{};

    int size();
    void push_back(token* tar);
};

class editor: public QObject
{
    Q_OBJECT
    public:
    std::vector<token_line> words{};
    void add_token(std::string key, std::string type, int index);
};


class wopol: public QObject
{
    Q_OBJECT
    static std::unordered_map<std::string, const TSLanguage*> lang_registry;
    public:
    explicit wopol();

    std::string file_tar{};
    
    std::string words{};
    fwords keep_keys{};
    std::unordered_map<std::string, std::vector<std::string>*> lang_map{};
    TSParser *parser{};
    TSTree *tree{};
    TSNode *root_node{};
    TSTreeCursor *cursor{};

    void register_lang(std::string lang_name, const TSLanguage* lang);
    void init(std::string file_path, std::string lang);
    void read_file(std::string &file_path);
    void read_file();
    void write_file(std::string &file_path);
    void write_file();
    void auto_save();

    void build_AST();
};