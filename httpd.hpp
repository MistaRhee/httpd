/*
 *  httpd.hpp - A HTML page downloader using curl
 *
 *  Instructions
 *  ============
 *
 *  Not really that much to do, however, there is one function which may or may
 *  not be useful. The check exist function will check if the URL exists before
 *  executing the download, however, it will just "download" the URL anyway and
 *  drop it into stdout (which is silly), so if the URL exists, it will double
 *  runtime. To have this function, uncomment the stuff in httpd.cpp and the
 *  function in this file
 *
 *  Copyright/Licensing stuffs
 *  ==========================
 *
 *  Copyright (C) 2015 Justin Huang
 *  Permission is hereby granted, free of charge, to any person obtaining
 *  a copy of this software and associated documentation files (the
 *  ``Software''), to deal in the Software without restriction, including
 *  without limitation the rights to use, copy, modify, merge, publish,
 *  distribute, sublicense, and/or sell copies of the Software, and to
 *  permit persons to whom the Software is furnished to do so, subject to
 *  the following conditions:
 *         
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *            
 *  THE SOFTWARE IS PROVIDED ``AS IS'', WITHOUT WARRANTY OF ANY KIND, EXPRESS
 *  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 *  IN NO EVENT SHALL JUSTIN HUANG BE LIABLE FOR ANY CLAIM, DAMAGES OR
 *  OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 *  ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *  OTHER DEALINGS IN THE SOFTWARE.
 *
 * **********************************************************************/
#ifndef HTTPD_HPP
#define HTTPD_HPP

#include <curl/curl.h>
#include <curl/easy.h>
#include <curl/curlbuild.h>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <string>
#include <cstring>
#include <exception>

class cHttpd{
    public:
        cHttpd(); //Inits curl
        ~cHttpd(); //Kills curl
        std::string qDownload(const std::string, int); //Takes in two arguments, the URL and the length of the randomly generated file name
        std::string fixURL(const std::string); //Takes in a URL and ensures that any spaces are turned into %20s (something which I found out with my own project that broke this class)
        void download(const std::string, const std::string); //Takes in two arguments, the URL and the title of the file which the HTML page is saved to
        //bool checkExist(const std::string);
    private:
        std::string generateRandomName(int); //Randomly generates the filename. Acceptable characters can be changedwithin httpd.cpp
        void* curl;
};

#endif //HTTPD_HPP
