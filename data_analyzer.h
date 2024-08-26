
#ifndef DATA_ANALYZER_H
#define DATA_ANALYZER_H

#include <vector>
#include <string>
#include <map>

class DataAnalyzer {
public:
    void analyze(const std::vector<std::string>& data);
    void print_results();

private:
    std::map<std::string, int> word_frequency;
};

#endif // DATA_ANALYZER_H
