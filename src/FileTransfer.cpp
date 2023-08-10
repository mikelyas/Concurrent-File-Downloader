#include "FileTransfer.h"
#include <fstream>
#include <iostream>


bool FileTransfer::validateFile(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

bool FileTransfer::sendFileData(boost::asio::ip::tcp::socket& socket, const std::string& filename) {
     try {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return false;
        }

        boost::asio::streambuf response;
        while (!file.eof()) {
            file.read(boost::asio::buffer_cast<char*>(response.prepare(512)), 512);
            response.commit(file.gcount());
            boost::asio::write(socket, response);
            response.consume(response.size());
        }

        return true;
    } catch (std::exception& e) {
        std::cerr << "Error occurred while sending file: " << e.what() << std::endl;
        return false;
    }
}

bool FileTransfer::receiveFileData(boost::asio::ip::tcp::socket& socket, const std::string& filename) {
    try {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error creating file: " << filename << std::endl;
            return false;
        }

        boost::asio::streambuf response;
        boost::system::error_code error;
        while (boost::asio::read(socket, response, boost::asio::transfer_at_least(1), error)) {
            const char* data = boost::asio::buffer_cast<const char*>(response.data());
            std::size_t size = response.size();
            file.write(data, size);

            response.consume(size); // Consume the data that was written
        }

        if (error != boost::asio::error::eof) {
            std::cerr << "Error occurred while receiving file: " << error.message() << std::endl;
            return false;
        }

        return true;
    } catch (std::exception& e) {
        std::cerr << "Error occurred while receiving file: " << e.what() << std::endl;
        return false;
    }
}