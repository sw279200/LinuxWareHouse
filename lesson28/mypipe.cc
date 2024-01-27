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
    (void)n; // 防止编译器告警，意料之中，用assert，意料之外，用if
    cout << "pipefd[0]: " << pipefd[0] << ", pipefd[1]: " << pipefd[1] << endl;

    // 第2步，创建子进程
    pid_t id = fork();
    if (id < 0)
    {
        perror("fork");
        return 1;
    }
    // 子写，父读
    // 第3步，父子关闭不需要的fd，形成单向通信的管道
    if (id == 0)
    {
        // if(fork() > 0) exit(0); //
        // child
        close(pipefd[0]);
        // w - 只向管道写入，没有打印
        int cnt = 0;
        while(true)
        {
            // char c = 'a';
            // write(pipefd[1], &c, 1);
            // cnt++;
            // cout << "write ....: " << cnt << endl; // 课堂上我们的机器的pipe空间大小是64KB
            
            char message[MAX];
            snprintf(message, sizeof(message), "hello father, I am child, pid: %d, cnt: %d", getpid(), cnt);
            cnt++;
            write(pipefd[1], message, strlen(message));
            sleep(1);

            // if(cnt > 3) break;
        }
        cout << "child close w piont" << endl;
        // close(pipefd[1]);
        exit(0);
    }
    // 父进程
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
            cout << getpid() << ", " << "child say: " << buffer << " to me!" << endl;
        }
        else if(n == 0)
        {
            cout << "child quit, me too !" << endl;
            break;
        }
        cout << "father return val(n): " << n << endl;
        sleep(1);

        break;
    }
    cout << "read point close"<< endl;
    close(pipefd[0]);

    sleep(5);
    int status = 0;
    pid_t rid = waitpid(id, &status, 0);
    if (rid == id)
    {
        cout << "wait success, child exit sig: " << (status&0x7F) << endl;
    }
    return 0;
}