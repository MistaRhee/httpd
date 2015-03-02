#include "httpd.hpp"

struct mException : public std::exception {
    mException(std::string in){
        this->message = in;
    }
    std::string message;
    const char * what() const throw(){
        return message.c_str();
    }
};

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream){
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

cHttpd::cHttpd(){
    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
}

cHttpd::~cHttpd(){
    curl_easy_cleanup(curl);
}

std::string cHttpd::fixURL(const std::string incoming){
    std::string rVal;
    for(int i = 0; i < incoming.size(); i++){
        if(incoming[i] == ' '){
            rVal += "%20";
        }
        else{
            rVal += incoming[i];
        }
    }
    return rVal;
}

/*
bool cHttpd::checkExist(const std::string url){
    bool rVal = 1;
    CURL* valid;
    CURLcode res;
    valid = curl_easy_init();
    if(curl){
        curl_easy_setopt(valid, CURLOPT_URL, url.c_str());
        if((res = curl_easy_perform(valid)) != CURLE_OK) rVal = 0;
    }
    else rVal = 0;
    curl_easy_cleanup(valid);
    return rVal;
}
*/

void cHttpd::download(const std::string url, const std::string fileName){
    try{
/*
        if(!checkExist(url)){
            throw(mException("URL isn't valid or cannot be opened by curl"));
        }
*/
        FILE* fin = NULL;
        std::string newURL = fixURL(url);
        fin = fopen(fileName.c_str(), "w+");
        if(fin == NULL){
            throw(mException("File couldn't be opened!"));
        }
        curl_easy_setopt(curl, CURLOPT_URL, newURL.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        //curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fin);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::string e = "curl_easy_perform error: ";
            e += curl_easy_strerror(res);
            throw (mException(e));
        }
        fclose(fin);
    }
    catch(mException &e){
        printf("%s \n", e.what());
    }
}

std::string cHttpd::qDownload(const std::string url, int nameLen){
    try{
/*
        if(!checkExist(url)){
            throw(mException("URL isn't valid or cannot be opened by curl"));
        }
*/
        std::string fileName = generateRandomName(nameLen);
        FILE* fin = NULL;
        fin = fopen(fileName.c_str(), "w+");
        if(fin == NULL){
            throw(mException("File couldn't be opened!"));
        }
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_NOSIGNAL, 1);
        //curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, "deflate");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fin);
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::string e = "curl_easy_perform error: ";
            e += curl_easy_strerror(res);
            throw (mException(e));
        }
        fclose(fin);
        return fileName;
    }
    catch(mException &e){
        printf("%s \n", e.what());
        return NULL;
    }
}

std::string cHttpd::generateRandomName(int length){
    srand(time(NULL));
    const char aCharacters[] = "abcdefghijklmnopqrstuvwxyz1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string rVal;
    for(int i = 0, j = strlen(aCharacters); i < length; i++){
        rVal += aCharacters[rand()%j];
    }
    return rVal;
}
