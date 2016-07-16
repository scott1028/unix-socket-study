#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>
using namespace std;

void *task1(void *);

static int connFd;

// 基本上如果 Client 連線後 15 秒沒反應就會被自動斷線(這邊可以驗證秒數)
static int client_idle_timeout = 15;


int main(int argc, char* argv[])
{
    int pId, portNo, listenFd;
    socklen_t len; //store size of the address
    bool loop = false;
    struct sockaddr_in svrAdd, clntAdd;
    
    pthread_t threadA[3];
    
    if (argc < 2)
    {
        cerr << "Syntam : ./server <port>" << endl;
        return 0;
    }
    
    portNo = atoi(argv[1]);
    
    if((portNo > 65535) || (portNo < 2000))
    {
        cerr << "Please enter a port number between 2000 - 65535" << endl;
        return 0;
    }
    
    //create socket
    listenFd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(listenFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }
    
    bzero((char*) &svrAdd, sizeof(svrAdd));
    
    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(portNo);
    
    //bind socket
    if(bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0)
    {
        cerr << "Cannot bind" << endl;
        return 0;
    }
    
    listen(listenFd, 5);
    
    len = sizeof(clntAdd);
    
    int noThread = 0;

    while (noThread < 3)
    {
        cout << "Listening" << endl;

        //this is where client connects. svr will hang in this mode until client conn
        connFd = accept(listenFd, (struct sockaddr *)&clntAdd, &len);


        // 1. 讓 client socket fd recv( ... ) 資料最多等待 15 秒如果超過就當作 Client 離線釋放 Connection！
        // 2. server fd 會收到跟 Client 送斷線訊號一樣的 0 Byte 資料！
        struct timeval tv;
        tv.tv_sec = client_idle_timeout;  /* 30 Secs Timeout */
        tv.tv_usec = 0;  // Not init'ing this can cause strange errors
        setsockopt(connFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&tv,sizeof(struct timeval));


        if (connFd < 0)
        {
            cerr << "Cannot accept connection" << endl;
            return 0;
        }
        else
        {
            cout << "Connection successful" << endl;
        }
        
        pthread_create(&threadA[noThread], NULL, task1, NULL); 
        
        noThread++;
    }
    
    for(int i = 0; i < 3; i++)
    {
        pthread_join(threadA[i], NULL);
    }
    
    
}

void *task1 (void *dummyPt)
{
    cout << "Thread No: " << pthread_self() << endl;
    char test[300];
    bzero(test, 301);
    bool loop = false;
    while(!loop)
    {    
        bzero(test, 301);
        
        // 基本上如果 Client 連線後 15 秒沒反應就會被自動斷線(這邊可以驗證秒數)
        time_t  timev;
        cout << "[before recv]=" << time(&timev) << endl;
        read(connFd, test, 300);
        cout << "[after recv]=" << time(&timev) << endl;
        
        string tester (test);
        cout << "[data][start]" << endl;
        cout << (tester == "") << endl;  // 0: False, 1: True
        cout << tester << endl;
        cout << "[data][end]" << endl;
        
        if(tester == ""){
            cout << "[exit]=" << time(&timev) << endl;
            cout << "client exit#1" << endl;
            break;  // recv zero bytes, client close or exit program
        }
        
        if(tester == "exit"){
            cout << "[exit]=" << time(&timev) << endl;
            cout << "client exit#2" << endl;
            break;  // special keyword for close or exit
        }
    }

    // avoid memory leak if cleint no response make recv timeout and run here code.
    cout << "\nClosing thread and conn" << endl;
    close(connFd);
}