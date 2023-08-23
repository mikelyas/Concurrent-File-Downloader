#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <string>
#include <boost/asio.hpp>

// forward declaration
namespace std::filesystem {
    class directory_entry;
}

class FileTransfer {
public:
    FileTransfer();
    ~FileTransfer();

    // Method to send file or folder
    static bool sendData(boost::asio::ip::tcp::socket& socket, const std::string& path);

    // Method to receive file or folder
    static bool receiveData(boost::asio::ip::tcp::socket& socket);

    // Method to read file data and send it over the network
    static bool sendFile(boost::asio::ip::tcp::socket& socket, const std::string& filename);

    // Method to send folder content recursivly
    static bool sendFolderData(boost::asio::ip::tcp::socket& socket, const std::string& folderPath);

    // Method to receive file data over the network and save it to a file
    static bool receiveFile(boost::asio::ip::tcp::socket& socket, const std::string& filename);

    // Method to receive folder content recursivly
    static bool receiveFolder(boost::asio::ip::tcp::socket& socket, const std::string& folderPath);

    static bool sendIsFile(boost::asio::ip::tcp::socket& socket, const bool& isFile);

    static bool receiveIsFile(boost::asio::ip::tcp::socket& socket, bool& isFile);
private:
    static bool sendFileSize(boost::asio::ip::tcp::socket& socket, const std::string& filename);

    static bool receiveFileSize(boost::asio::ip::tcp::socket& socket, size_t &fileSize);

    static bool sendFileData(boost::asio::ip::tcp::socket& socket, std::ifstream& file);

    static bool receiveFileData(boost::asio::ip::tcp::socket& socket, std::ofstream& file, size_t fileSize);

    static bool sendNumItems(boost::asio::ip::tcp::socket& socket, const std::string& folderPath);

    static bool receiveNumItems(boost::asio::ip::tcp::socket& socket, uint32_t& numItems);

    static bool sendItemName(boost::asio::ip::tcp::socket& socket, const std::string& itemName);

    static bool receiveItemName(boost::asio::ip::tcp::socket& socket, std::string& itemName);

    static bool sendItemNameSize(boost::asio::ip::tcp::socket& socket, const std::string& itemName);

    static bool receiveItemNameSize(boost::asio::ip::tcp::socket& socket, size_t& itemNameSize);
};

#endif // FILETRANSFER_H
