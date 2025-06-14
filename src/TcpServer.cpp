#include "TcpServer.hpp"

tcpServer tcpServer::m_globalTcpserver{};

tcpServer& tcpServer::instance(){
    return m_globalTcpserver;
}