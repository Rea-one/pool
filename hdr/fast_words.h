#include "methods.h"

class fwnode
{
public:
    char tar{};
    bool is_end = false;
    std::unordered_map<char, fwnode*> next{};
    bool is(char c);
    bool have(char c);
};

class fwords
{
public:
    fwords();
    fwnode* root{};
    std::set<std::string> keys;
    void init(std::vector<std::string> words);
    void insert(std::string word);
    void erase(std::string word);
    void build_tree();
};