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

            // Receive the filename from the client
            boost::asio::streambuf request;
            boost::asio::read_until(socket, request, '\n');

            std::istream is(&request);
            std::string filename;
            std::getline(is, filename);

            // Receive the file data from the client and save it
            if (FileTransfer::receiveFileData(socket, filename)) {
                std::cout << "File received and saved: " << filename << std::endl;
            } else {
                std::cerr << "Error occurred while receiving the file." << std::endl;
            }
        }
    } catch (std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
}
