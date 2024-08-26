// web_scraper.h
#ifndef WEB_SCRAPER_H
#define WEB_SCRAPER_H

#include <string>
#include <vector>
#include <curl/curl.h>

class WebScraper {
public:
    WebScraper();
    ~WebScraper();
    std::string fetch_url(const std::string& url);
    std::vector<std::string> extract_data(const std::string& html_content);

private:
    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
    CURL* curl;
};

#endif // WEB_SCRAPER_H
