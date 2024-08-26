// web_scraper.cpp
#include "web_scraper.h"
#include <iostream>
#include <sstream>
#include <libxml/HTMLparser.h>
#include <libxml/xpath.h>

WebScraper::WebScraper() {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();
}

WebScraper::~WebScraper() {
    curl_easy_cleanup(curl);
    curl_global_cleanup();
}

std::string WebScraper::fetch_url(const std::string& url) {
    if (curl) {
        std::string buffer;
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
            return "";
        }
        return buffer;
    }
    return "";
}

std::vector<std::string> WebScraper::extract_data(const std::string& html_content) {
    std::vector<std::string> extracted_data;
    htmlDocPtr doc = htmlReadMemory(html_content.c_str(), html_content.length(), nullptr, nullptr, 0);
    if (doc == nullptr) {
        std::cerr << "Failed to parse HTML" << std::endl;
        return extracted_data;
    }

    xmlXPathContextPtr xpath_ctx = xmlXPathNewContext(doc);
    if (xpath_ctx == nullptr) {
        std::cerr << "Failed to create XPath context" << std::endl;
        xmlFreeDoc(doc);
        return extracted_data;
    }

    // Example: Extract all paragraph text
    xmlXPathObjectPtr xpath_obj = xmlXPathEvalExpression(BAD_CAST "//p/text()", xpath_ctx);
    if (xpath_obj == nullptr) {
        std::cerr << "Failed to evaluate XPath expression" << std::endl;
    } else {
        xmlNodeSetPtr nodes = xpath_obj->nodesetval;
        for (int i = 0; i < nodes->nodeNr; ++i) {
            xmlNodePtr node = nodes->nodeTab[i];
            extracted_data.push_back(std::string(reinterpret_cast<const char*>(node->content)));
        }
        xmlXPathFreeObject(xpath_obj);
    }

    xmlXPathFreeContext(xpath_ctx);
    xmlFreeDoc(doc);
    return extracted_data;
}

size_t WebScraper::WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
