#include "DeletionsTests.h"
#include "BSTree.h"
#include "ReadWriteHelper.h"

void deletion_test_util::TestDeletionOfArbitraryWords(CBSTree &tree, const std::vector<std::string> &words, int nCount)
{
    printf("----------------------------------------------------------\n");
    printf("After test deletion of %d first lexicographically ordered words(some repeating)\n", nCount);
    for (std::string word : words)
    {
        tree.DeleteWord(word);
        nCount--;
        if (nCount == 0) break;
    }

    reader_writer_helper::Print66MostCommonWords(words, tree);
}

void deletion_test_util::TestDeletion3MostCommon(CBSTree &tree, const std::vector<std::string> &words)
{
    printf("----------------------------------------------------------\n");
    printf("After test deletion of 3 most common words: of, my, I\n");

    tree.DeleteWord("of");
    tree.DeleteWord("my");
    tree.DeleteWord("I");

    reader_writer_helper::Print66MostCommonWords(words, tree);
}