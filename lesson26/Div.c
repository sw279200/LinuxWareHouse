#include"Div.h"

int Div(int x,int y,int * code)
{
    *code = 0;
    if(y==0)
    {
        *code = -1;
        return -1;
    }
    return x / y;
}
