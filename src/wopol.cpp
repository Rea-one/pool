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
    token *tar = new token();
    tar->key = key;
    tar->type = type;
    tar->index = words[line_index].size();
    words[line_index].push_back(tar);
}

wopol::wopol()
{
    parser = ts_parser_new();
}

void wopol::register_lang(std::string lang_name, const TSLanguage* lang)
{
    lang_registry[lang_name] = lang;
}
void wopol::init(std::string file_path, std::string lang)
{

    lang_map["c"] = &c_keep_keys;
    lang_map["cpp"] = &cpp_keep_keys;
    lang_map["python"] = &python_keep_keys;
    file_tar = file_path;
    keep_keys.init(*lang_map[lang]);
    keep_keys.build_tree();
    read_file();
    ts_parser_set_language(parser, lang_registry[lang]);
}

void wopol::read_file(std::string &file_path)
{
    file_tar = file_path;
    std::ifstream file(file_path);
    if (!file.is_open())
    {
        std::cout << "无法打开目标文件" << std::endl;
        return;
    }
    while (file.good())
    {
        std::string line;
        getline(file, line);
        words += line;
    }
    file.close();
}

void wopol::read_file()
{
    std::ifstream file(file_tar);
    if (!file.is_open())
    {
        std::cout << "无法打开目标文件" << std::endl;
        return;
    }
    while (file.good())
    {
        std::string line;
        getline(file, line);
        words += line;
    }
    file.close();
}

void wopol::write_file(std::string &file_path)
{
    std::ofstream file(file_path);
    if (!file.is_open())
    {
        std::cout << "无法打开目标文件" << std::endl;
        return;
    }
    for (auto &word : words)
    {
        file << word << std::endl;
    }
    file.close();
}

void wopol::write_file()
{
    std::ofstream file(file_tar);
    if (!file.is_open())
    {
        std::cout << "无法打开目标文件" << std::endl;
        return;
    }
    for (auto &word : words)
    {
        file << word << std::endl;
    }
    file.close();
}

void wopol::build_AST()
{
    std::string code = "";
    for (auto &word : words)
    {
        code += word + "\n";
    }
    tree = ts_parser_parse_string(parser, nullptr, code.c_str(), code.size());
    root_node = &ts_tree_root_node(tree);
    cursor = &ts_tree_cursor_new(*root_node);
}