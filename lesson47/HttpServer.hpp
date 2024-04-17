#pragma once

#include <iostream>
#include <string>
#include <pthread.h>
#include <fstream>
#include<sstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <unordered_map>
#include "Socket.hpp"
#include<vector>

static const int defaultport = 8080;
const std::string wwwroot = "./wwwroot"; //web根目录
const std::string sep="\r\n";
const std::string homepage="index.html";

class ThreadData
{
public:
    ThreadData(int fd) : _sockfd(fd)
    {
    }

public:
    int _sockfd;
};


class HttpRequest
{
public:
    void Deserialize(std::string req)
    {
        while(true)
        {
            std::size_t pos = req.find(sep);
            if(pos==std::string::npos) break;
            std::string temp = req.substr(0,pos);
            if(temp.empty()) break;
            req_header.push_back(temp);
            req.erase(0,pos+sep.size());
        }
        text = req;
    }

    void Parse()
    {
        std::stringstream ss(req_header[0]);
        ss>>method>>url>>http_version;

        file_path = wwwroot;
        if(url == "/" || url == "/index.html")
        {
            file_path+="/";
            file_path+=homepage;
        }
        else file_path+=url;
    }

    void DebugPrint()
    {
        for(auto &line : req_header)
        {
            std::cout<<"-----------------------------"<<std::endl;
            std::cout<<line<<"\n\n";
        }
        std::cout<<"method: "<<method<<std::endl;
        std::cout<<"url: "<<url<<std::endl;
        std::cout<<"http_version: "<<http_version<<std::endl;
        std::cout<<"file_path: "<<file_path<<std::endl;

        std::cout<<text<<std::endl;
    }

public:
    std::vector<std::string> req_header;
    std::string text;

    //
    std::string method;
    std::string url;
    std::string http_version;
    std::string file_path;
};

class HttpServer
{
public:
    HttpServer(uint16_t port = defaultport) : _port(port)
    {
    }

    bool Start()
    {
        _listensock.Socket();
        _listensock.Bind(_port);
        _listensock.Listen();

        for (;;)
        {
            std::string clientip;
            uint16_t clientport;
            int sockfd = _listensock.Accept(&clientip, &clientport);
            if(sockfd<0) continue;
            log.LogMessage(INFO,"get a new line, sockfd: %d ",sockfd);
            pthread_t tid;
            ThreadData *td = new ThreadData(sockfd);
            pthread_create(&tid, nullptr, ThreadRun, td);
        }
    }

    static std::string ReadHtmlContent(const std::string & htmlpath)
    {
        std::ifstream in(htmlpath);
        if(!in.is_open()) return "404";

        std::string content;
        std::string line;
        while(std::getline(in,line))
        {
            content+=line;
        }
        in.close();

        return content;
    }

    static void HandlerHttp(int sockfd)
    {
        char buffer[10240];
        ssize_t n = recv(sockfd, buffer, sizeof(buffer) - 1, 0);
        if (n > 0)
        {
            buffer[n] = 0;
            std::cout << buffer; //假设我们读取到的就是一个完整的独立的http请求

            // 返回响应的过程
            HttpRequest req;
            req.Deserialize(buffer);
            req.Parse();
            //req.DebugPrint();

            // std::string path = wwwroot;
            // //path+=url;
            std::string text = ReadHtmlContent(req.file_path);
            std::string response_line = "HTTP/1.0 200 OK\r\n";
            std::string response_header = "Content-Length: ";
            response_header += std::to_string(text.size());
            response_header += "\r\n";
            std::string blank_line = "\r\n";

            std::string response = response_line;
            response += response_header;
            response += blank_line;
            response += text;

            send(sockfd, response.c_str(), response.size(), 0);
        }
         close(sockfd);
    }

    static void *ThreadRun(void *args)
    {
        pthread_detach(pthread_self());
        ThreadData *td = static_cast<ThreadData *>(args);
        HandlerHttp(td->_sockfd);
        delete td;
        return nullptr;
    }

    ~HttpServer() {}

private:
    Sock _listensock;
    uint16_t _port;
};