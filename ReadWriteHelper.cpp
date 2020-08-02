#include "ReadWriteHelper.h"
#include "BSTree.h"
#include <stdio.h>
#include <fstream>
#include <set>
#include <algorithm>
#include <utility>

void reader_writer_helper::ReadSonnets(std::vector<std::string> &words)
{
    const int nSonnerStart = 253;
    const int nSonnetEnd = 2867;

    // Unwanted symbols left for the user to customize to its own needs
    // The assigment only said to skip numbers from the words, but since there are also other symbols which do not
    // belong to words they are also added, can be removed easily commenting out the code and seeing the new results.
    std::set<char> word_unwanted_symbols;

    for (char c = '0'; c <= '9'; ++c) {
        word_unwanted_symbols.insert(c);
    }

    word_unwanted_symbols.insert(',');
    word_unwanted_symbols.insert('.');
    word_unwanted_symbols.insert(':');
    word_unwanted_symbols.insert('?');
    word_unwanted_symbols.insert('!');
    word_unwanted_symbols.insert('(');
    word_unwanted_symbols.insert(')');
    word_unwanted_symbols.insert('\'');

    std::string cur_line;
    std::ifstream shakespeare_sonnets_file("Shakespeare.txt");

    for (int nCurrentLine = 1; std::getline(shakespeare_sonnets_file, cur_line) && 
                               nCurrentLine <= nSonnetEnd; ++nCurrentLine)
    {
        if (nCurrentLine >= nSonnerStart)
        {
            std::string word;
            for (const char letter : cur_line)
            {
                if (letter == ' ')
                {
                    if (!word.empty()) words.push_back(word);
                    word = "";
                }
                else if (word_unwanted_symbols.find(letter) == word_unwanted_symbols.end()) word += letter;
            }

            if (!word.empty()) words.push_back(word);
        }
    }

    shakespeare_sonnets_file.close();
}

void reader_writer_helper::Print66MostCommonWords(const std::vector<std::string> &words, const CBSTree &tree)
{
    std::vector<std::pair<int, std::string>> word_number_of_times_used;
    const int nLength = words.size();
    std::string first = *words.begin();
    word_number_of_times_used.emplace_back(tree.GetTotalWordCount(first), first);

    for (int i = 1; i < nLength; ++i)
    {
        // Do not check the same words
        if (words[i - 1] == words[i]) continue;
        word_number_of_times_used.emplace_back(tree.GetTotalWordCount(words[i]), words[i]);
    }

    // Sort by number of occurencies firstly
    std::sort(word_number_of_times_used.begin(), word_number_of_times_used.end());
    // reverse for descending order, also function to sort function could have been passed, but since efficiency
    // is not needed here we just reverse.
    std::reverse(word_number_of_times_used.begin(), word_number_of_times_used.end());

    std::vector<std::pair<std::string, int>> result66words;
    const int nResultLength = word_number_of_times_used.size();
    for (int i = 0; i < nResultLength; ++i)
    {
        if (word_number_of_times_used[i].second == "the" || word_number_of_times_used[i].second == "a") continue;
        if (result66words.size() != 66) {
            result66words.emplace_back(word_number_of_times_used[i].second, word_number_of_times_used[i].first);
        }
        else break;
    }

    printf("The 66 most common words are:\n");
    for (int i = 0; i < 66; ++i) {
        printf("%s which appeared: %d times\n", result66words[i].first.c_str(), result66words[i].second);
    }

    // System pause is added only if correct visual studio configuration is not enabled to pause the output
    // Generally it is not needed when launching with ctrl + F5 and subsystem is set to console.
    system("pause");
}