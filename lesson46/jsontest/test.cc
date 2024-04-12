#include<iostream>
#include<jsoncpp/json/json.h>
#include<unistd.h>

int main()
{
    Json::Value root;
    root["x"] = 100;
    root["y"] = 200;
    root["op"] = '+';
    root["desc"]="this is a + oper";

    Json::FastWriter w;
    std::string res = w.write(root);
    std::cout<<res<<std::endl;

    sleep(3);

    Json::Value v;
    Json::Reader r;
    r.parse(res,v);
    int x = v["x"].asInt();
    int y = v["y"].asInt();
    char op = v["op"].asInt();
    std::string desc = v["desc"].asString();
    std::cout<<x<<std::endl;
    std::cout<<op<<std::endl;
    std::cout<<y<<std::endl;
    std::cout<<desc<<std::endl;

    return 0;
}