#include"Add.h"
#include"Sub.h"
#include"Mul.h"
#include"Div.h"


int main()
{
    int x = 10,y = 20,code = 0;

    printf("%d+%d=%d\n",x,y,Add(x,y));
    printf("%d-%d=%d\n",x,y,Sub(x,y));
    printf("%d*%d=%d\n",x,y,Mul(x,y));
    printf("%d/%d=%d\n",x,y,Div(x,y,&code));

    return 0;
}
