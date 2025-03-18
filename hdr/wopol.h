#include "tree_sitter/api.h"

#include "qt_headers.h"

#include "methods.h"
#include "mruby_runner.h"
#include "fast_words.h"


// class token: public QObject
// {
//     Q_OBJECT
//     public:
//     explicit token();
//     ~token();

//     std::string key{};
//     std::string type{};
//     int index{};
// };

// class token_line: public QObject
// {
//     Q_OBJECT
//     public:
//     explicit token_line();
//     ~token_line();

//     std::vector<token*> tokens{};
//     int index{};

//     int size();
//     void push_back(token* tar);
// };

// class editor: public QObject
// {
//     Q_OBJECT
//     public:
//     std::vector<token_line> words{};
//     void add_token(std::string key, std::string type, int index);
// };


class wopol: public QObject
{
    Q_OBJECT
    static std::unordered_map<std::string, const TSLanguage*> lang_registry;
    public:
    std::mutex mutex;
    explicit wopol();

    std::string file_tar{};
    
    std::vector<std::string> words{};
    std::vector<std::array<int, int>> token_idx{};
    
    fwords keep_keys{};
    std::unordered_map<std::string, std::vector<std::string>*> lang_map{};
    std::unordered_map<char, std::function<void()>> key_map{};
    std::unique_ptr<TSParser, decltype(&ts_parser_delete)> parser{nullptr, ts_parser_delete};
    std::unique_ptr<TSTree, decltype(&ts_tree_delete)> tree{nullptr, ts_tree_delete};
    std::unique_ptr<TSNode, decltype(&ts_node_delete)> root_node{nullptr, ts_node_delete};
    std::unique_ptr<TSTreeCursor, decltype(&ts_tree_cursor_delete)> cursor{nullptr, ts_tree_cursor_delete};

    vth threads{};

    void register_lang(std::string lang_name, const TSLanguage* lang);
    void init(std::string file_path, std::string lang);
    void read_file(std::string &file_path);
    void read_file();
    void write_file(std::string &file_path);
    void write_file();
    void auto_save();

    void build_AST();
    void generate_tokens();
    void key_link();

    void act(auto func)
    {
        threads.enqueue(func);
    }
};