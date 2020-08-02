#pragma once

#include <vector>
#include <string>

class CBSTree;

namespace deletion_test_util
{
    void TestDeletionOfArbitraryWords(CBSTree &tree, const std::vector<std::string> &words, int nCount);
    void TestDeletion3MostCommon(CBSTree &tree, const std::vector<std::string> &words);
}