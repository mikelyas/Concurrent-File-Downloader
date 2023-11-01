#include "Client.h"
#include "FileTransfer.h"
#include "FileSystemHandler.h"
#include <iostream>
#include <fstream>


Client::Client() {

}

Client::~Client() {
    
}

void Client::sendData(const std::string& serverAddress, int serverPort, const std::string& path) {
    if (!FileSystemHandler::validatePath(path)) {
        std::cerr << "Path doesn't exist: " << path << std::endl;
        return;
    }
    bool isFile = FileSystemHandler::isFile(path);
    if (isFile && !FileSystemHandler::validateFile(path)) {
        std::cerr << "File is invalid: " << path << std::endl;
        return;
    }


    try {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context);

        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::connect(socket, resolver.resolve(serverAddress, std::to_string(serverPort)));

        if (FileTransfer::sendData(socket, path)) {
            std::cout << "Data sent successfully." << std::endl;
        } else {
            std::cerr << "Error occurred while sending the data." << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
}