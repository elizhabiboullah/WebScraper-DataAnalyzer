
cmake_minimum_required(VERSION 3.10)
project(WebScraperAnalyzer)

set(CMAKE_CXX_STANDARD 14)

find_package(CURL REQUIRED)
find_package(LibXml2 REQUIRED)

include_directories(${CURL_INCLUDE_DIRS} ${LIBXML2_INCLUDE_DIRS})

add_executable(WebScraperAnalyzer
    main.cpp
    web_scraper.cpp
    data_analyzer.cpp
)

target_link_libraries(WebScraperAnalyzer ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})
