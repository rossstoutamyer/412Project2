#include "WebServer.h"
#include <iostream>

WebServer::WebServer(LoadBalancer* _balancer, std::string _name) { //the WebServer default constructor associates it with a balancer and gives it a name
    this->balancer = _balancer;
    this->endTime = 0;
    this->name = _name;
}

void WebServer::processRequest() { //to process the request it currently has or find a new one
    if (this->endTime != 0) { //this means the server just finished a job or was just created
        if (balancer->getTime() >= this->endTime) { //if the current clock cycle is passed the expected end time of the request
            std::cout << "At " << balancer->getTime() << " " << this->name << " processed request from " << serverRequest.getIPIn() << " to " << serverRequest.getIPOut() << "!" << std::endl;
            this->endTime = 0; //the request is fulfilled and output
            findRequest(); //a new request is found
        }
    } else {
        findRequest(); //if the endTime is ever 0, it immediately tries to find a request
    }
}

void WebServer::setRequest(Request _request) {
    this->serverRequest = _request; //sets the servers request to fulfill
    this->endTime = serverRequest.getTime() + this->balancer->getTime(); //sets the expected endTime of the request
}

Request WebServer::getRequest() {
    return this->serverRequest; //returns information on request being fulfilled
}

void WebServer::findRequest() {
    if (!balancer->empty()) { //when the balancer has requests, a new one is found and popped
        setRequest(balancer->pop());
    }
}