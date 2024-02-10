#ifndef ___PROJECT_3_CONVERT_HPP
#define ___PROJECT_3_CONVERT_HPP

#include <istream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>

#include "Wordset.hpp"

namespace shindler::ics46::project3 {

template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
[[nodiscard]] std::vector<std::string> convert(const std::string& start,
                                               const std::string& end,
                                               const BaseWordSet<H1, H2, EvictThreshold>& words) {
    std::queue<std::string> wordQueue;
    std::unordered_map<std::string, std::string> predecessorMap;

    wordQueue.push(start);


    while (!wordQueue.empty())
    {
        std::string currentWord = wordQueue.front();
        wordQueue.pop();

        if (currentWord == end)
        {
            std::vector<std::string> path;
            while (currentWord != start)
            {
                path.push_back(currentWord);
                currentWord = predecessorMap[currentWord];
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        // Generate all valid neighbors of the current word
        for (size_t i = 0; i < currentWord.size(); ++i)
        {
            std::string neighbor = currentWord;
            for (char c = 'a'; c <= 'z'; ++c)
            {
                if (c != currentWord[i])
                {
                    neighbor[i] = c;
                    if (words.contains(neighbor) && predecessorMap.find(neighbor) == predecessorMap.end())
                    {
                        predecessorMap[neighbor] = currentWord;
                        wordQueue.push(neighbor);
                    }
                }
            }
        }
    }

    return {};
}

// You should not need to change this function
template <unsigned int H1, unsigned int H2, unsigned int EvictThreshold>
void loadWordsIntoTable(std::istream& istream,
                        BaseWordSet<H1, H2, EvictThreshold>& words) {
    std::string word;

    while (istream >> word) {
        words.insert(word);
    }
}

}  // namespace shindler::ics46::project3

#endif
