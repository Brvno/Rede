#ifndef CLIENT_H
#define CLIENT_H

#include <bits/stdc++.h>
#include "file.h"

class Client
{
private:
    std::string serverAddress;

public:
    Client();
    void connectServer(std::string address);
};

#endif // CLIENT_H
