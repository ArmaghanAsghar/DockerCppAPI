//
// Created by dev on 9/28/20.
//

#include "DockerAPI.h"


#include <iostream>
#include <string>

using namespace std;

static size_t write_function(void *data, size_t size, size_t nmemb, void *buffer) {


    ((std::string *)buffer)->assign((char*)data, size*nmemb);

    return size*nmemb;



}

DockerAPI::DockerAPI(string _ver, string option){

    version = _ver;
    int ver_len = version.size();

    if (ver_len < 5) {
        std::cout << "WARNING: version malformed." << std::endl;
    }
    prefix_query = "http://"+version+"/containers/";


}

HttpResponse DockerAPI::exec_post(string url){

    HttpResponse res;
    initCurl();

    CURLcode response;
    long http_code{0};
    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");


    curl_easy_setopt(_curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(_curl, CURLOPT_POSTFIELDS, "");
    curl_easy_setopt(_curl, CURLOPT_URL, const_cast<char*>(url.c_str()));

    res.curl_code = curl_easy_perform(_curl);

    curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &res.http_code);

    res.msg = this->getResData();

    curl_easy_reset(_curl);
    curl_slist_free_all(headers);

    return res;
}

HttpResponse  DockerAPI::exec_get(string url){

    HttpResponse res;
    initCurl();
    curl_easy_setopt(_curl, CURLOPT_URL, const_cast<char *>(url.c_str()));

    res.curl_code = curl_easy_perform(_curl);
    curl_easy_getinfo(_curl, CURLINFO_RESPONSE_CODE, &res.http_code);

    res.msg = this->getResData();
    curl_easy_reset(_curl);


    return res;
}

DockerAPI::~DockerAPI(){
    curl_easy_cleanup(_curl);
}

void DockerAPI::initCurl(){

    _curl = curl_easy_init();

    curl_easy_setopt(_curl, CURLOPT_UNIX_SOCKET_PATH, "/var/run/docker.sock");
    curl_easy_setopt(_curl, CURLOPT_WRITEFUNCTION, write_function);
    curl_easy_setopt(_curl, CURLOPT_WRITEDATA, &buffer);

}

char * DockerAPI::getResData(){

    return const_cast<char*>(buffer.c_str());

}



string DockerAPI::getPrefixQ(){
    return prefix_query;
}
