#include "FileTransfer.h"
#include "FileSystemHandler.h"
#include <fstream>
#include <iostream>
#include <algorithm>


bool FileTransfer::sendData(boost::asio::ip::tcp::socket& socket, const std::string& path) {
    bool isFile = FileSystemHandler::isFile(path);
    if (!sendIsFile(socket, isFile))
        return false;

    // Send item name
    if (!sendItemNameSize(socket, path))
        return false;
    if (!sendItemName(socket, path))
        return false;

    // Send the item data (file or directory)
    if (isFile) {
        if (!sendFile(socket, path)) {
            return false;
        }
    } else {
        if (!sendFolderData(socket, path)) {
            return false;
        }
    }
    return true;
}

bool FileTransfer::receiveData(boost::asio::ip::tcp::socket& socket) {
    bool isFile;
    if (!receiveIsFile(socket, isFile))
        return false;

    size_t itemNameSize;
    if (!receiveItemNameSize(socket, itemNameSize))
        return false;

    std::string itemName(itemNameSize, '\0');
    if (!receiveItemName(socket, itemName))
        return false;

    if (isFile) {
        // Receive and save the file
        if (!receiveFile(socket, itemName)) {
            return false;
        }
    } else {
        // Recursively receive the subdirectory's contents
        if (!receiveFolder(socket, itemName)) {
            return false;
        }
    }
    return true;
}

bool FileTransfer::sendFileData(boost::asio::ip::tcp::socket& socket, std::ifstream& file) {
    boost::system::error_code error;
    boost::asio::streambuf response;
    while (!file.eof()) {
        file.read(boost::asio::buffer_cast<char*>(response.prepare(512)), 512);
        response.commit(file.gcount());
        boost::asio::write(socket, response, error);
        if (error) {
            std::cerr << "Error occurred while sending file data: " << error.message() << std::endl;
            file.close();
            return false;
        }
        response.consume(response.size());
    }
    file.close();
    return true;
}

bool FileTransfer::receiveFileData(boost::asio::ip::tcp::socket& socket, std::ofstream& file, size_t fileSize) {
    boost::system::error_code error;
    boost::asio::streambuf response;
    // Read exactly the expected amount of data
    while (fileSize > 0) {
        size_t bytesToRead = (fileSize < response.max_size()) ? fileSize : response.max_size();
        size_t bytesRead = boost::asio::read(socket, response, boost::asio::transfer_exactly(bytesToRead), error);

        if (error) {
            std::cerr << "Error occurred while receiving item data: " << error.message() << std::endl;
            file.close();
            return false;
        }

        // Write the received data to the file
        const char* data = boost::asio::buffer_cast<const char*>(response.data());
        file.write(data, bytesRead);

        response.consume(bytesRead); // Consume the data that was written
        fileSize -= bytesRead;
    }
    file.close();
    return true;
}

bool FileTransfer::sendFileSize(boost::asio::ip::tcp::socket& socket, const std::string& filename) {
    boost::system::error_code error;
    size_t dataSize = FileSystemHandler::calculateItemSize(filename);
    boost::asio::write(socket, boost::asio::buffer(&dataSize, sizeof(dataSize)), error);
    if (error) {
        std::cerr << "Error occurred while sending file size: " << error.message() << std::endl;
        return false;
    }
    return true;
}

bool FileTransfer::receiveFileSize(boost::asio::ip::tcp::socket& socket, size_t &fileSize) {
    boost::system::error_code error;
    boost::asio::read(socket, boost::asio::buffer(&fileSize, sizeof(fileSize)), error);
        if (error) {
        std::cerr << "Error occurred while receiving file size: " << error.message() << std::endl;
        return false;
    }
    return true;
}

bool FileTransfer::sendNumItems(boost::asio::ip::tcp::socket& socket, const std::string& folderPath) {
    boost::system::error_code error;
    // Calculate the number of items in the folder
    uint32_t numItems = FileSystemHandler::calculateNumItems(folderPath);
    boost::asio::write(socket, boost::asio::buffer(&numItems, sizeof(numItems)), error);
    if (error) {
        std::cerr << "Error occurred while sending number of items: " << error.message() << std::endl;
        return false;
    }
    return true;
}

bool FileTransfer::receiveNumItems(boost::asio::ip::tcp::socket& socket, uint32_t& numItems) {
    boost::system::error_code error;
    boost::asio::read(socket, boost::asio::buffer(&numItems, sizeof(numItems)), error);
    if (error) {
        std::cerr << "Error reading number of items: " << error.message() << std::endl;
        return false;
    }
    return true;
}

bool FileTransfer::sendIsFile(boost::asio::ip::tcp::socket& socket, const bool& isFile) {
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(&isFile, sizeof(isFile)), error);
    if (error) {
        std::cerr << "Error occured while sending info if it is file or not: " << error.message() << std::endl;
        return false;
    }
    return true;
}

bool FileTransfer::receiveIsFile(boost::asio::ip::tcp::socket& socket, bool& isFile) {
    boost::system::error_code error;
    boost::asio::read(socket, boost::asio::buffer(&isFile, sizeof(isFile)), error);
    if (error) {
        std::cerr << "Error reading item type: " << error.message() << std::endl;
        return false;
    }
    return true;
}

bool FileTransfer::sendItemName(boost::asio::ip::tcp::socket& socket, const std::string& itemName) {
    boost::system::error_code error;
    boost::asio::write(socket, boost::asio::buffer(itemName), error);
    if (error) {
        std::cerr << "Error occurred while sending the name of the file: " << error.message() << std::endl;
        return false;
    }
    return true;
}

bool FileTransfer::receiveItemName(boost::asio::ip::tcp::socket& socket, std::string& itemName) {
    boost::system::error_code error;
    boost::asio::read(socket, boost::asio::buffer(itemName), error);
    if (error) {
        std::cerr << "Error reading item name: " << error.message() << std::endl;
        return false;
    }
    return true;
}

bool FileTransfer::sendItemNameSize(boost::asio::ip::tcp::socket& socket, const std::string& itemName) {
    boost::system::error_code error;
    size_t itemNameSize = itemName.size();
    boost::asio::write(socket, boost::asio::buffer(&itemNameSize, sizeof(itemNameSize)), error);
    if (error) {
        std::cerr << "Error occurred while sending the size of file name: " << error.message() << std::endl;
        return false;
    }
    return true;
}

bool FileTransfer::receiveItemNameSize(boost::asio::ip::tcp::socket& socket, size_t& itemNameSize) {
    boost::system::error_code error;
    boost::asio::read(socket, boost::asio::buffer(&itemNameSize, sizeof(itemNameSize)), error);
    if (error) {
        std::cerr << "Error reading item name size: " << error.message() << std::endl;
        return false;
    }
    return true;
}

bool FileTransfer::sendFile(boost::asio::ip::tcp::socket& socket, const std::string& filename) {
    try {
        std::ifstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error opening file: " << filename << std::endl;
            return false;
        }

        if (!sendFileSize(socket, filename))
            return false;

        return sendFileData(socket, file);
    } catch (std::exception& e) {
        std::cerr << "Error occurred while sending file: " << e.what() << std::endl;
        return false;
    }
}

bool FileTransfer::sendFolderData(boost::asio::ip::tcp::socket& socket, const std::string& folderPath) {
    try {
        if (!sendNumItems(socket, folderPath))
            return false;

        // Loop over items and send them
        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(folderPath)) {
            bool isFile = FileSystemHandler::isFile(entry);
            if (!sendIsFile(socket, isFile))
                return false;

            // Send item name
            std::string itemName = entry.path().filename().string();
            if (!sendItemNameSize(socket, itemName))
                return false;
            if (!sendItemName(socket, itemName))
                return false;

            // Send the item data (file or directory)
            if (isFile) {
                sendFile(socket, entry.path().string());
            } else {
                sendFolderData(socket, entry.path().string());
            }
        }

        // Signal end of folder transfer
        socket.shutdown(boost::asio::socket_base::shutdown_send);
        return true;
    } catch (std::exception& e) {
        std::cerr << "Error occurred while sending folder: " << e.what() << std::endl;
        return false;
    }
}

bool FileTransfer::receiveFile(boost::asio::ip::tcp::socket& socket, const std::string& filename) {
    try {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error creating file: " << filename << std::endl;
            return false;
        }

        size_t fileSize;
        if (!receiveFileSize(socket, fileSize))
            return false;

        return receiveFileData(socket, file, fileSize);
    } catch (std::exception& e) {
        std::cerr << "Error occurred while receiving file: " << e.what() << std::endl;
        return false;
    }
}

bool FileTransfer::receiveFolder(boost::asio::ip::tcp::socket& socket, const std::string& folderPath) {
    try {
        if (!FileSystemHandler::createFolder(folderPath))
            return false;
        
        uint32_t numItems;
        if (!receiveNumItems(socket, numItems))
            return false;
        for (uint32_t i = 0; i < numItems; ++i) {
            bool isFile;
            if (!receiveIsFile(socket, isFile))
                return false;

            size_t itemNameSize;
            if (!receiveItemNameSize(socket, itemNameSize))
                return false;

            std::string itemName(itemNameSize, '\0');
            if (!receiveItemName(socket, itemName))
                return false;
            // Determine the full path of the item
            std::string itemPath = folderPath + "/" + itemName;

            if (isFile) {
                // Receive and save the file
                if (!receiveFile(socket, itemPath)) {
                    return false;
                }
            } else {
                // Recursively receive the subdirectory's contents
                if (!receiveFolder(socket, itemPath)) {
                    return false;
                }
            }
        }

        return true;
    } catch (std::exception& e) {
        std::cerr << "Error occurred while receiving folder: " << e.what() << std::endl;
        return false;
    }
}
