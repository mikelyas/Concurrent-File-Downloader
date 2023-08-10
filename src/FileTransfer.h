#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <string>
#include <boost/asio.hpp>

class FileTransfer {
public:
    FileTransfer();
    ~FileTransfer();

    // Function to validate the file (e.g., existence, permissions, etc.)
    static bool validateFile(const std::string& filename);

    // Function to read file data and send it over the network
    static bool sendFileData(boost::asio::ip::tcp::socket& socket, const std::string& filename);

    // Function to receive file data over the network and save it to a file
    static bool receiveFileData(boost::asio::ip::tcp::socket& socket, const std::string& filename);
private:

};

#endif // FILETRANSFER_H
