#pragma comment(linker, "/stack:200000000") // On Debug configuration stack is too small.
#include <stdio.h>
#include "ReadWriteHelper.h"
#include "BSTree.h"
#include "DeletionsTests.h"
#include <algorithm>

void buildBST(std::vector<std::string> &words)
{
    std::sort(words.begin(), words.end());
    const int nLength = words.size();
    int nStartIteration = nLength / 2;

    while (words[nStartIteration - 1] == words[nStartIteration]) nStartIteration--;
    int nLeftPointer    = nStartIteration - 1;
    int nRightPointer   = nStartIteration;
    CBSTree tree(words[nLeftPointer]);

    while (nLeftPointer >= 0 || nRightPointer < nLength) 
    {
        do
        {
            if( nLeftPointer >= 0 ) tree.AddNewWord(words[nLeftPointer]);
            nLeftPointer--;
        } while (nLeftPointer >= 0 && words[nLeftPointer + 1] == words[nLeftPointer]);

        do
        {
            if( nRightPointer < nLength) tree.AddNewWord(words[nRightPointer]);
            nRightPointer++;
        } while (nRightPointer < nLength && words[nRightPointer - 1] == words[nRightPointer]);
    }


    reader_writer_helper::Print66MostCommonWords(words, tree);

    // Can be uncommented and tested with huge number of words deletion to see that is working correctly.
    //deletion_test_util::TestDeletionOfArbitraryWords(tree, words, 16000);
    //deletion_test_util::TestDeletion3MostCommon(tree, words);
}

int main()
{
    //Author advises to use Release configuration since there are intense computations.
    std::vector<std::string> words;
    reader_writer_helper::ReadSonnets(words);
    buildBST(words);
    return 0;
}