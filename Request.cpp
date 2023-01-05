#include "Request.h"

#include <iostream>
#include <string>
#include <random>

Request::Request() { /**The default constructor generates a random ipIn, ipOut, and time between 2 and 500*/
    this->ipIn = generateIP();
    this->ipOut = generateIP();
    this->time = 2 + rand() % 499;
}

std::string Request::generateIP() { /**ChatGPT generated this to get a random ip address*/
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255); /**Ip address numbers cannot be larger than 255*/

    std::string ip = ""; /**The ip is initialized to empty*/
    for (int i = 0; i < 4; i++) {
        if (i > 0) { /**After each number, a period is added*/
            ip += ".";
        }
        ip += std::to_string(dis(gen)); /**The random number is added to the string*/
    }

    return ip;
}

int Request::getTime() {
    return this->time; /**Returns the time of a request to simulate fulfilling*/
}

std::string Request::getIPIn() {
    return this->ipIn; /**Gets ipIn to output when job is done*/
}

std::string Request::getIPOut() {
    return this->ipOut; /**Gets ipOut to output when job is done*/
}