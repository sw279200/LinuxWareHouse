#include"UdpServer.hpp"
#include<memory>
#include<iostream>
#include<cstdio>
#include<vector>

void Usage(std::string proc)
{
    std::cout<<"\n\rUsage: "<<proc<<" port[1024+]\n"<<std::endl;
}

std::string Handler(const std::string& str,uint16_t & clientport,const std::string& clientip)
{
    std::cout<<"[ ip: "<< clientip<<" port: "<<clientport<<" ]# ";
    std::string res = "server get a message: ";
    res+=str;
    std::cout<<res<<std::endl;
    return res;
}

bool SafeCheck(const std::string & cmd)
{
    std::vector<std::string> key_word = 
    {
        "rm",
        "mv",
        "cp",
        "kill",
        "sudo",
        "unlink",
        "uninstall",
        "yum",
        "top"
    };

    for(auto &word:key_word)
    {
        auto pos = cmd.find(word);
        if(pos!=std::string::npos) return false;
    }

    return true;
}

std::string ExcuteCommand(const std::string & cmd)
{
    if(!SafeCheck(cmd)) return "bad man";
    FILE* fp = popen(cmd.c_str(),"r");
    if(nullptr == fp)
    {
        perror("popen error");
        return "error";
    }

    std::string result;
    char buffer[4096];
    while(true)
    {
        char * getc = fgets(buffer,sizeof(buffer),fp);
        if(nullptr == getc)
        {
            break;
        }
        result+=buffer;
    }
    pclose(fp);
    return result;

}


int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        Usage(argv[0]);
        exit(1);
    }

    uint16_t port = std::stoi(argv[1]);

    std::unique_ptr<UdpServer> svr(new UdpServer(port));
    svr->Init();
    svr->Run(Handler);    
    return 0;
}