#include "FileSystemHandler.h"
#include <fstream>
#include <iostream>
#include <filesystem>


bool FileSystemHandler::createFolder(const std::string& folderPath) {
    if (!std::filesystem::create_directories(folderPath)) {
            std::cerr << "Error creating directory: " << folderPath << std::endl;
            return false;
    }
    return true;
}

bool FileSystemHandler::validateFile(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

bool FileSystemHandler::validatePath(const std::string& path) {
    return std::filesystem::exists(path);
}

bool FileSystemHandler::isFile(const std::string& path) {
    return std::filesystem::is_regular_file(path);
}

bool FileSystemHandler::isFile(const std::filesystem::directory_entry& entry) {
    return std::filesystem::is_regular_file(entry);
}

uint32_t FileSystemHandler::calculateNumItems(const std::string& folderPath) {
    uint32_t numItems = 0;
    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (entry.is_regular_file() || entry.is_directory()) {
            ++numItems;
        }
    }
    return numItems;
}

// Calculate the size of a file's content
size_t FileSystemHandler::calculateItemSize(const std::string& filePath) {
    try {
        std::ifstream file(filePath, std::ios::binary);
        if (!file) {
            std::cerr << "Error opening file: " << filePath << std::endl;
            return 0;
        }

        // Get the file size
        file.seekg(0, std::ios::end);
        size_t fileSize = static_cast<size_t>(file.tellg());
        file.close();

        return fileSize;
    } catch (std::exception& e) {
        std::cerr << "Error calculating item size: " << e.what() << std::endl;
        return 0;
    }
}