#if defined(__linux__)

#include "unistd.h"
#include "signal.h"

#endif

#include <iostream>
#include "asio.hpp"

#include "threadPool.hpp"

using namespace std;
using namespace asio::ip;

static void SigHandler(int32_t sigNum){
    cout<< "receieve signal: "<< sigNum <<endl;

    //deinit

}

static void SigSetup(){
    struct sigaction action;
    std::ignore = sigemptyset(&action.sa_mask);
    action.sa_handler = &SigHandler;
    action.sa_flags = 0;

    std::ignore = sigaction(SIGINT, &action, nullptr);
    std::ignore = sigaction(SIGTERM, &action, nullptr);
    std::ignore = sigaction(SIGQUIT, &action, nullptr);
    std::ignore = sigaction(SIGHUP, &action, nullptr);

}

static void handle_for_sigpipe()
{
    struct sigaction sa;
    memset(&sa, '\0', sizeof(sa));
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    if(sigaction(SIGPIPE, &sa, NULL))
        return;
}

int main(){
    SigSetup();

    handle_for_sigpipe();

    if(!getThreadPool().threadCreate()) {
        return -1;
    }

    asio::io_context io;

    

    asio::post(io, [](){
        cout<< "asio post" << endl; 
    });

    io.run();

    return 0;
}