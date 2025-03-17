#include "fast_words.h"


bool fwnode::is(char c)
{
    return tar == c;
}

bool fwnode::have(char c)
{
    return next.find(c) != next.end();
}

fwords::fwords()
{
    root = new fwnode();
    root -> tar = ' ';
}


void fwords::init(std::vector<std::string> words)
{
    for (const auto& word : words)
    {
        keys.insert(word);
    }
}


void fwords::insert(std::string word)
{
    keys.insert(word);
}

void fwords::erase(std::string word)
{
    keys.erase(word);
}

void fwords::build_tree()
{
    for (auto word : keys)
    {
        if (word.empty())
        {
            erase(word);
            continue;
        }
        fwnode* attention = root;
        for (auto c : word)
        {
            if (!attention -> have(c))
            {
                attention -> next[c] = new fwnode();
                attention -> next[c] -> tar = c;
            }
            attention = attention -> next[c];
        }
        attention -> is_end = true;
    }
}