#pragma once

const int defaultvalue = 0;
enum
{
    ok = 0,
    div_zero,
    mod_zero,
    unknow
};

const std::string opers = "+-*/%&()";
class Task
{
public:
    Task(){}
    Task(int x, int y, char op, int result=defaultvalue, int code=ok)
        : _data_x(x), _data_y(y), _oper(op)
    {
    }

    std::string PrintTask()
    {
        std::string s;
        s= std::to_string(_data_x);
        s+=_oper;
        s+=std::to_string(_data_y);
        s+="=?";

        return s;
    }

    std::string PrintResult()
    {
        std::string s;
        s= std::to_string(_data_x);
        s+=_oper;
        s+=std::to_string(_data_y);
        s+="=";
        s+=std::to_string(_result);
        s+=" [";
        s+=std::to_string(_code);
        s+="]";

        return s;
    }

    void Run()
    {
        switch (_oper)
        {
        case '+':
            _result = _data_x + _data_y;
            break;
        case '-':
            _result = _data_x - _data_y;
            break;
        case '*':
            _result = _data_x * _data_y;
            break;
        case '/':
        {
            if (_data_y == 0)
            {
                _code = div_zero;
            }
            else _result = _data_x / _data_y;
        }
        break;
        case '%':
        {
            if (_data_y == 0)
            {
                _code = mod_zero;
            }
            else _result = _data_x % _data_y;
        }
        break;
        default:
            _code = unknow;
            break;
        }
    }

    ~Task() {}

private:
    int _data_x; // 操作数
    int _data_y; // 操作数
    char _oper;  // 运算符
    int _result; // 结果
    int _code;   // 结果码 0:可信  !0：不可信
};
