#include <iostream>
#include "boost/asio.hpp"
using namespace std;
using namespace boost;
using namespace boost::asio;

int main(){
    io_context io;

    ip::tcp::socket sock(io);

    sock.connect(ip::tcp::endpoint(ip::address::from_string("127.0.0.1"), 6789));

    char buf[0xFF];

    string input;

    while(true){
        cin>>input;
        uint32_t l = input.size();

        std::memcpy(buf, input.c_str(), l);

        sock.send(buffer(buf, l));
        memset(buf, 0, 0xFF);
        sock.receive(buffer(buf));
        cout<<buf<<endl;

    }

    sock.close();
    return 0;   
}
