#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request {
    std::string ipIn;
    std::string ipOut;
    int time;

public:
    Request();
    std::string generateIP();
    int getTime();
    std::string getIPIn();
    std::string getIPOut();
};

#endif