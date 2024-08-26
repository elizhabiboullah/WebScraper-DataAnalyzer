// main.cpp
#include <iostream>
#include <string>
#include "web_scraper.h"
#include "data_analyzer.h"

int main() {
    std::string url;
    std::cout << "Enter the URL to scrape: ";
    std::cin >> url;

    WebScraper scraper;
    std::string html_content = scraper.fetch_url(url);

    if (html_content.empty()) {
        std::cerr << "Failed to fetch URL content." << std::endl;
        return 1;
    }

    std::vector<std::string> extracted_data = scraper.extract_data(html_content);

    DataAnalyzer analyzer;
    analyzer.analyze(extracted_data);
    analyzer.print_results();

    return 0;
}
