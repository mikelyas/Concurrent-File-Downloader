#ifndef SERVER_H
#define SERVER_H

#include <string>

class Server {
public:
    Server();
    ~Server();

    // Function to start the server and listen for incoming connections
    void start(int port);

private:

};

#endif // SERVER_H
