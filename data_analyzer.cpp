
#include "data_analyzer.h"
#include <iostream>
#include <sstream>
#include <algorithm>

void DataAnalyzer::analyze(const std::vector<std::string>& data) {
    for (const auto& line : data) {
        std::istringstream iss(line);
        std::string word;
        while (iss >> word) {
            // Convert to lowercase for case-insensitive comparison
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);
            // Remove punctuation
            word.erase(std::remove_if(word.begin(), word.end(), ::ispunct), word.end());
            if (!word.empty()) {
                word_frequency[word]++;
            }
        }
    }
}

void DataAnalyzer::print_results() {
    std::cout << "Word Frequency Analysis:" << std::endl;
    for (const auto& pair : word_frequency) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}
