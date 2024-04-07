#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

void Usage(const std::string proc)
{
    std::cout << "Usage: " << proc << "serverip  serverport[1024+]" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(0);
    }

    std::string serverip = argv[1];
    uint16_t serverport = std::stoi(argv[2]);

    struct sockaddr_in server;
    socklen_t len = sizeof(server);
    server.sin_family = AF_INET;
    inet_pton(AF_INET, serverip.c_str(), &server.sin_addr);
    server.sin_port = htons(serverport);

    while (true)
    {
        int cnt = 5;
        bool isreconnect = false;
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            std::cout << "create socket error" << std::endl;
            exit(1);
        }

        do
        {
            int n = connect(sockfd, (struct sockaddr *)&server, len);
            if (n < 0)
            {
                std::cout << "reconnect "<<cnt<<"..." << std::endl;
                sleep(2);
                cnt--;
                isreconnect = true;
            }
            else
            {
                break;
            }

        } while (cnt && isreconnect);

        if(cnt == 0)
        {
            std::cerr<<"user offline ..."<<std::endl;
            break;
        }
        
        std::string message;
        std::cout<<"Please Enter# "; 
        std::getline(std::cin,message);
        int w = write(sockfd,message.c_str(),message.size());
        if(w<0)
        {
            std::cerr<<"write error"<<std::endl;
        }   

        char inbuffer[4096];
        int r = read(sockfd,inbuffer,sizeof(inbuffer));
        if(r>0)
        {
            inbuffer[r] = 0;
            std::cout<<inbuffer<<std::endl;
        }
        close(sockfd);
    }
   
    return 0;
}