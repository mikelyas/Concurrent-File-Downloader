#include "Client.h"
#include "FileTransfer.h"
#include <iostream>
#include <fstream>


Client::Client() {

}

Client::~Client() {
    
}

void Client::sendFile(const std::string& serverAddress, int serverPort, const std::string& filename) {
    // Check if the file exists and is valid
    if (!FileTransfer::validateFile(filename)) {
        std::cerr << "File not found or invalid: " << filename << std::endl;
        return;
    }

    try {
        boost::asio::io_context io_context;
        boost::asio::ip::tcp::socket socket(io_context);

        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::connect(socket, resolver.resolve(serverAddress, std::to_string(serverPort)));

        // Send the filename to the server
        std::string request = filename + "\n";
        boost::asio::write(socket, boost::asio::buffer(request));

        // Send the file data to the server
        if (FileTransfer::sendFileData(socket, filename)) {
            std::cout << "File sent successfully." << std::endl;
        } else {
            std::cerr << "Error occurred while sending the file." << std::endl;
        }
    } catch (std::exception& e) {
        std::cerr << "Error occurred: " << e.what() << std::endl;
    }
}
