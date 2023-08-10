// Client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    Client();
    ~Client();

    // Function to send a file to the server
    void sendFile(const std::string& serverAddress, int serverPort, const std::string& filename);

private:
    
};

#endif // CLIENT_H
