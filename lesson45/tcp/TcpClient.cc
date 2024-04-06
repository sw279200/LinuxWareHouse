#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

void Usage(std::string proc)
{
    std::cout << "\n\rUsage: " << proc << " serverip  serverport[1024+]" << std::endl;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        Usage(argv[0]);
        exit(1);
    }
    std::string serverip = argv[1];
    uint16_t serverport = std::stoi(argv[2]);

    struct sockaddr_in server;
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    inet_pton(AF_INET, serverip.c_str(), &(server.sin_addr));
    server.sin_port = htons(serverport);

    while (true)
    {
        int cnt = 5;
        bool isreconnect = false;
        int sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0)
        {
            std::cerr << "socket error" << std::endl;
            return 1;
        }

        // tcp要不要bind? 要bind 要不要显示的bind? 不用显示的bind 系统进行bind，随机端口
        // 客户端发起connect的时候,进行自动随机bind.
        do
        {
            int n = connect(sockfd, (struct sockaddr *)&server, sizeof(server));
            if (n < 0)
            {
                isreconnect = true;
                cnt--;
                std::cerr << "connect error, reconnect: %d" << cnt << std::endl;
                sleep(2);
            }
            else
            {
                break;
            }

        } while (cnt && isreconnect);

        if(cnt == 0)
        {
            std::cerr<<"user offline..."<<std::endl;
            break;
        }

        std::string message;
        std::cout << "please Enter# ";
        std::getline(std::cin, message);
        int w = write(sockfd, message.c_str(), message.size());
        if(w<0)
        {
            std::cerr<<"write error"<<std::endl;
        }
        char inbuffer[4096];
        int r = read(sockfd, inbuffer, sizeof(inbuffer));
        if (r > 0)
        {
            inbuffer[r] = 0;
            std::cout << inbuffer << std::endl;
        }
        close(sockfd);
    }
    std::cout << "Connection closed by foreign host" << std::endl;
    return 0;
}