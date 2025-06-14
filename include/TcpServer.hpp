#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include "asio.hpp"
#include <iostream>

using namespace asio::ip;

class tcpSession{
private:



};

class tcpServer{
private:
    bool m_start{false};
    tcp::acceptor m_acceptor;

    static tcpServer m_globalTcpserver;

private:
    explicit tcpServer();
    ~tcpServer();

    tcpServer(const tcpServer &) = delete;
    tcpServer(tcpServer &&) = delete;
    tcpServer& operator=(const tcpServer &) = delete;
    tcpServer& operator=(tcpServer &&) = delete;

    void accept_cbk();

public:
    static tcpServer& instance();

};

inline tcpServer& getTcpServer() {return tcpServer::instance();}

#endif