#include <iostream>
#include <cassert>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX 1024

using namespace std;

int main()
{
    // 第1步，建立管道
    int pipefd[2] = {0};
    int n = pipe(pipefd);
    assert(n == 0);
    (void)n; 
    cout << "pipefd[0]: " << pipefd[0] << ", pipefd[1]: " << pipefd[1] << endl;

    // 第2步，创建子进程
    pid_t id = fork();
    if (id < 0)
    {
        perror("fork");
        return 1;
    }
    if(id>0)
    {
          // father
        close(pipefd[0]);
        // w - 只向管道写入，没有打印
        char message[MAX];
        snprintf(message, sizeof(message), "i am father, pid: %d", getpid());
        write(pipefd[1], message, strlen(message));
        sleep(1);
        cout << "father close w piont" << endl;
        close(pipefd[1]);
       
    }
    if (id == 0)
    {
         // 子进程
        close(pipefd[1]);

        // r
        char buffer[MAX];
        while(true)
        {
            // sleep(2000);
            ssize_t n = read(pipefd[0], buffer, sizeof(buffer)-1);
            if(n > 0)
            {
                buffer[n] = 0; // '\0', 当做字符串
                cout << getpid() << ", " << "father say: " << buffer << " to me!" << endl;
            }
            else if(n == 0)
            {
                cout << "father quit, me too !" << endl;
                break;
            }
            cout << "child return val(n): " << n << endl;
            sleep(1);

            break;
        }
        cout << "read point close"<< endl;
        close(pipefd[0]);
        exit(0);
    }
   

    sleep(5);
    int status = 0;
    pid_t rid = waitpid(id, &status, 0);
    if (rid == id)
    {
        cout << "wait success, child exit sig: " << (status&0x7F) << endl;
    }
    return 0;
}