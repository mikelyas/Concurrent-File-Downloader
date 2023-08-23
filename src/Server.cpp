#include "Server.h"
#include "FileTransfer.h"
#include <iostream>
#include <fstream>


Server::Server() {

}
    
Server::~Server() {

}

void Server::start(int port) {
       try {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::acceptor acceptor(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port));

        while (true) {
            boost::asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);

            if (FileTransfer::receiveData(socket)) {
                std::cout << "Data received and saved." << std::endl;
            } else {
                std::cerr << "Error occurred while receiving data." << std::endl;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
}
