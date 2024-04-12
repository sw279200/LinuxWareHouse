#include"TcpServer.hpp"
#include"Protocol.hpp"
#include"ServerCal.hpp"

static void Usage(const std::string & proc)
{
    std::cout<<"\nUsage: "<<proc<<" port\n\n"<<std::endl;
}

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        Usage(argv[0]);
        exit(0);
    }

    uint16_t port = std::stoi(argv[1]);
    ServerCal cal;
    TcpServer * tsvp = new TcpServer(8080,std::bind(&ServerCal::Calculator,&cal,std::placeholders::_1));
    tsvp->ServerInit();
    tsvp->Start();
    // Request req(123123,45612321,'+');
    // std::string s;
    // req.Serialize(&s);
    // s = Encode(s);
    // std::cout<<s;

    // std::string content;
    // bool r = Decode(s,&content);
    // std::cout<<content<<std::endl;
    // Request temp;
    // temp.Deserialize(content);

    // std::cout<<temp.x<<std::endl;
    // std::cout<<temp.op<<std::endl;
    // std::cout<<temp.y<<std::endl;

    return 0;
}
