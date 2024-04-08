#include"TcpServer.hpp"
#include"Protocol.hpp"

int main()
{
    Request req(123123,45612321,'+');
    std::string s;
    req.Serialize(&s);
    s = Encode(s);
    std::cout<<s;

    std::string content;
    bool r = Decode(s,&content);
    std::cout<<content<<std::endl;
    Request temp;
    temp.Deserialize(content);

    std::cout<<temp.x<<std::endl;
    std::cout<<temp.op<<std::endl;
    std::cout<<temp.y<<std::endl;

    return 0;
}
