#ifndef FILESYSTEMHANDLER_H
#define FILESYSTEMHANDLER_H

#include <string>
#include <filesystem>


class FileSystemHandler {
public:
    FileSystemHandler();
    ~FileSystemHandler();

    // Method to validate the file (e.g., existence, permissions, etc.)
    static bool validateFile(const std::string& filename);

    static bool validatePath(const std::string& path);

    static bool isFile(const std::string& path);

    static bool isFile(const std::filesystem::directory_entry& entry);

    static uint32_t calculateNumItems(const std::string& folderPath);

    static size_t calculateItemSize(const std::string& filePath);

    static bool createFolder(const std::string& folderPath);

private:

};

#endif // FILESYSTEMHANDLER_H