#include "TcpServer.hpp"

// tcpsession

// ASIO 的 socket 是仅可移动（move-only）类型
tcpSession::tcpSession(tcp::socket&& socket_)
: m_client(std::forward<tcp::socket>(socket_))
{
    if(!m_client.is_open()) {
        std::cout<< "client socket invalid!!!"<<std::endl;
    }
}

void tcpSession::start(){

    m_connected = true;

    readData();
}

void tcpSession::readData() {
    // 异步读取数据，使用 shared_from_this() 保证对象存活
    auto self(shared_from_this());

    m_client.async_read_some(
        asio::buffer(m_dataBuffer, buffLength),
        [this, self](asio::error_code ec, std::size_t length) {
            std::cout<< "receive length: "<< length <<std::endl;

            if (!ec) {
                std::cout << "Received: " << std::string(self->m_dataBuffer, length) << std::endl;
                // reply
                writeData("Server reply: " + std::string(self->m_dataBuffer, length));

                readData();
            } else if (ec == asio::error::eof) {
                std::cout << "Client disconnected." << std::endl;
            } else {
                std::cerr << "read Error: " << ec.message() << std::endl;
            }
        });
}

void tcpSession::writeData(const std::string& message) {
    auto self(shared_from_this());
    
    m_client.async_send(
        asio::buffer(message),
        [this, self](asio::error_code ec, std::size_t length) {
            if (ec) {
                std::cerr << "Write failed: " << ec.message() << std::endl;
            }
        }
    );
}

// tcpserver

tcpServer& tcpServer::instance(asio::io_context& io_, uint16_t port_){
    // asio::ip::address::from_string("192.168.1.100")  specify the ip

    static tcpServer m_globalTcpserver{io_, port_};
    return m_globalTcpserver;
}

tcpServer::tcpServer(asio::io_context& io_, uint16_t port_)
: m_acceptor(io_, tcp::endpoint(tcp::v4(), port_))
{
}

tcpServer::~tcpServer(){}

void tcpServer::accept_cbk(){
    std::cout<< "accept ready"<< std::endl;

    // m_acceptor.async_accept(std::bind(&tcpServer::accept_handle, this, std::placeholders::_1, std::placeholders::_2));

    m_acceptor.async_accept(
        [this](asio::error_code ec_, tcp::socket socket_){
            if(!ec_) {
                std::cout<< "get one connection"<< std::endl;
                accept_handle(ec_, std::move(socket_));
            }
            else{
                std::cout<< "accept failed!"<< std::endl;
            }
        }
    );
    
}

void tcpServer::accept_handle(asio::error_code ec_, tcp::socket clientSock){

    // ASIO 的 socket 是仅可移动（move-only）类型
    auto session = std::make_shared<tcpSession>(std::move(clientSock));

    session->start();
}

void tcpServer::start(){
    m_start = true;
    
    std::cout<< "tcpserver started"<< std::endl;

    accept_cbk();
}