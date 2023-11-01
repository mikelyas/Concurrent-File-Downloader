// Client.h
#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class Client {
public:
    Client();
    ~Client();

    void sendData(const std::string& serverAddress, int serverPort, const std::string& path);

private:
    
};

#endif // CLIENT_H
