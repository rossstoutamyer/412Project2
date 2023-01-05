#ifndef REQUEST_H
#define REQUEST_H

#include <string>

class Request { /**The request class has a starting and ending ip as well as a time to complete the request*/
    std::string ipIn;
    std::string ipOut;
    int time;

public:
    Request(); /**A default constructor to initialize the private members*/
    std::string generateIP(); /**Generates random ips*/
    int getTime(); /**Returns the time of the request for the server*/
    std::string getIPIn(); /**Returns the ipIn for output*/
    std::string getIPOut(); /**Returns the ipOut for output*/
};

#endif