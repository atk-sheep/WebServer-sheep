#ifndef TCPSERVER_HPP_
#define TCPSERVER_HPP_

#include "asio.hpp"
#include <iostream>
#include <functional>
#include <memory>
#include "utils.hpp"

using namespace asio::ip;

class tcpSession: public std::enable_shared_from_this<tcpSession>
{
private:
    tcp::socket m_client;

    bool m_connected{false};

    char m_dataBuffer[MAX_BUFFLENGTH]{};

    uint32_t buffLength{MAX_BUFFLENGTH};

private:
    void readData();

    void writeData(const std::string& message);

public:
    tcpSession(tcp::socket&& socket_);

    void start();

};

class tcpServer{
private:
    bool m_start{false};
    tcp::acceptor m_acceptor;

    // static tcpServer m_globalTcpserver;

private:
    tcpServer() = delete;
    explicit tcpServer(asio::io_context& io_, uint16_t port_);
    ~tcpServer();

    tcpServer(const tcpServer &) = delete;
    tcpServer(tcpServer &&) = delete;
    tcpServer& operator=(const tcpServer &) = delete;
    tcpServer& operator=(tcpServer &&) = delete;

    void accept_cbk();

    void accept_handle(asio::error_code ec_, tcp::socket clientSock);

public:
    static tcpServer& instance(asio::io_context& io_, uint16_t port_);

    void start();

};

inline tcpServer& getTcpServer(asio::io_context& io_, uint16_t port_) {return tcpServer::instance(io_, port_);}

#endif