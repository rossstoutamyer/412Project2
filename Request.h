#ifndef REQUEST_H
#define REQUEST_H

#include <string>

/**The request class has a starting and ending ip as well as a time to complete the request*/
class Request {
    std::string ipIn;
    std::string ipOut;
    int time;

public:
    /**A default constructor to initialize the private members*/
    Request();
    /**Generates random ips*/
    std::string generateIP();
    /**Returns the time of the request for the server*/
    int getTime();
    /**Returns the ipIn for output*/
    std::string getIPIn();
    /**Returns the ipOut for output*/
    std::string getIPOut();
};

#endif