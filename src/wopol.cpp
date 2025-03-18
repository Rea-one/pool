#include "wopol.h"

const enum surport_lang
{
    c,
    cpp,
    python,
};

// C语言保留字 (C11标准)
std::vector<std::string> c_keep_keys =
{
    "auto", "break", "case", "char", "const", "continue", "default",
    "do", "double", "else", "enum", "extern", "float", "for", "goto",
    "if", "inline", "int", "long", "register", "restrict", "return",
    "short", "signed", "sizeof", "static", "struct", "switch", "typedef",
    "union", "unsigned", "void", "volatile", "while", "_Alignas",
    "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary",
    "_Noreturn", "_Static_assert", "_Thread_local"
};

// C++保留字 (C++17标准)
std::vector<std::string> cpp_keep_keys =
{
    "alignas", "alignof", "and", "and_eq", "asm", "auto", "bitand",
    "bitor", "bool", "break", "case", "catch", "char", "char8_t",
    "char16_t", "char32_t", "class", "compl", "concept", "const",
    "const_cast", "consteval", "constexpr", "constinit", "continue",
    "co_await", "co_return", "co_yield", "decltype", "default", "delete",
    "do", "double", "dynamic_cast", "else", "enum", "explicit", "export",
    "extern", "false", "float", "for", "friend", "goto", "if", "inline",
    "int", "long", "mutable", "namespace", "new", "noexcept", "not",
    "not_eq", "nullptr", "operator", "or", "or_eq", "private", "protected",
    "public", "register", "reinterpret_cast", "requires", "return", "short",
    "signed", "sizeof", "static", "static_assert", "static_cast", "struct",
    "switch", "template", "this", "thread_local", "throw", "true", "try",
    "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual",
    "void", "volatile", "wchar_t", "while", "xor", "xor_eq"
};

// Python保留字 (Python 3.10)
std::vector<std::string> python_keep_keys =
{
    "False", "None", "True", "and", "as", "assert", "async", "await",
    "break", "class", "continue", "def", "del", "elif", "else", "except",
    "finally", "for", "from", "global", "if", "import", "in", "is",
    "lambda", "nonlocal", "not", "or", "pass", "raise", "return", "try",
    "while", "with", "yield"
};

int token_line::size()
{
    return tokens.size();
}

void token_line::push_back(token* tar)
{
    tokens.push_back(tar);
}

void editor::add_token(std::string key, std::string type, int line_index)
{
    auto tar = std::make_unique<token>{};
    tar->key = key;
    tar->type = type;
    tar->index = words[line_index].size();
    words[line_index].push_back(tar);
}

wopol::wopol()
{
    parser = ts_parser_new();
    lang_map["c"] = &c_keep_keys;
    lang_map["cpp"] = &cpp_keep_keys;
    lang_map["python"] = &python_keep_keys;
}

void wopol::register_lang(std::string lang_name, const TSLanguage* lang)
{
    lang_registry[lang_name] = lang;
}
void wopol::init(std::string file_path, std::string lang)
{
    file_tar = file_path;
    keep_keys.init(*lang_map[lang]);
    keep_keys.build_tree();
    read_file();
    ts_parser_set_language(parser, lang_registry[lang]);
}

void wopol::read_file(std::string &file_path)
{
    file_tar = file_path;
    read_file();
}

void wopol::read_file()
{
    std::ifstream file(file_tar);
    if (!file.is_open())
    {
        std::cout << "无法打开目标文件" << std::endl;
        return;
    }
    threads.enqueue([this]()
    {
        while (file.good())
        {
            std::unique_lock<std::mutex> lock(mutex);
            std::string line;
            getline(file, line);
            words += line;
        }
        file.close();
    });
}

void wopol::write_file(std::string &file_path)
{
    file_tar = file_path;
    write_file();
}

void wopol::write_file()
{
    std::ofstream file(file_tar);
    if (!file.is_open())
    {
        std::cout << "无法打开目标文件" << std::endl;
        return;
    }
    threads.enqueue([this]()
    {
        for (auto &word : words)
        {
            file << word << std::endl;
        }
        file.close();
    });
}

void wopol::build_AST()
{
    threads.enqueue([this]()
    {
        std::string code = "";
        for (auto &word : words)
        {
            code += word + "\n";
        }
        tree.reset(ts_parser_parse_string(parser, nullptr, code.c_str(), code.size()));
        root_node = &ts_tree_root_node(tree);
        cursor = &ts_tree_cursor_new(*root_node);
    });
}

void wopol::generate_tokens()
{
    // 遍历语法树节点（简化示例）
    TSNode node = *root_node;
    TSTreeCursor cursor = ts_tree_cursor_new(node);
    
    do {
        TSNode current = ts_tree_cursor_current_node(&cursor);
        
        // 获取 token 信息
        std::string type = ts_node_type(current);
        std::string text = ts_node_string(current); // 获取节点对应源码文本
        TSPoint start = ts_node_start_point(current);
        TSPoint end = ts_node_end_point(current);
        
        // 判断是否为保留字（结合你的 lang_map）
        if (type == "identifier" && keep_keys.contains(text)) {
            type = "keyword"; // 标记为关键字类型
        }
        
        // 添加到你的 token 系统（修改你的 add_token 方法）
        add_token(text, type, start.row);
        
    } while (ts_tree_cursor_goto_next_sibling(&cursor));
    
    ts_tree_cursor_delete(&cursor);
}

void wopol::key_link()
{
    
}