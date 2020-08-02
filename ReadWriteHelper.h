#pragma once

#include <vector>
#include <string>

class CBSTree;

namespace reader_writer_helper
{
    void ReadSonnets(std::vector<std::string> &words);
    void Print66MostCommonWords(const std::vector<std::string> &words, const CBSTree &tree);
}
