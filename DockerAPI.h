//
// Created by dev on 9/28/20.
//

#include <curl/curl.h>
#include <stdlib.h>
#include <string>

using namespace std;

struct HttpResponse {

    //CurlCode: https://curl.haxx.se/libcurl/c/libcurl-errors.html
    CURLcode curl_code;
    long http_code{0};
    string msg;
};


class DockerAPI {
private:

    CURL  *_curl;
    string version;
    std::string buffer;
    std::string prefix_query;

    void initCurl();
    char * getResData();

public:
    DockerAPI(string _ver, string option);
    ~DockerAPI();

    string getPrefixQ();
    HttpResponse  exec_get(string url);
    HttpResponse exec_post(string url);



};

