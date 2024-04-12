#pragma once

#include<iostream>
#include"Protocol.hpp"

enum
{
    Div_ZERO = 1,
    Model_ZERO,
    Other_Oper
};

class ServerCal
{
public:
    ServerCal(){}

    Response CalculatorHelper(const Request & req)
    {
        Response resp(0,0);
        switch (req.op)
        {
        case '+':
            resp.result = req.x + req.y;
            break;
        case '-':
            resp.result = req.x - req.y;
            break;
        case '*':
            resp.result = req.x * req.y;
            break;
        case '/':
            {
                if(req.y == 0)resp.code = Div_ZERO;
                else resp.result = req.x / req.y;
            }
            break;
        case '%':
            {
                if(req.y == 0)resp.code = Model_ZERO;
                else resp.result = req.x % req.y;
            }
            break;
        default:
            resp.code = Other_Oper;
            break;
        }
        return resp;
    }

    std::string Calculator(std::string & package)
    {
        std::string content;
        bool r = Decode(package,&content);
        if(!r) return "";
        Request req;
        r = req.Deserialize(content);
        if(!r) return "";

        content = "";

        Response resp = CalculatorHelper(req);
        resp.Serialize(&content);
        content = Encode(content);
        return content;
    }

    ~ServerCal(){}
};