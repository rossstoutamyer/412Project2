#include "WebServer.h"
#include <iostream>

/**The WebServer default constructor associates it with a balancer and gives it a name*/
WebServer::WebServer(LoadBalancer* _balancer, std::string _name) { 
    this->balancer = _balancer;
    this->endTime = 0;
    this->name = _name;
}

/**To process the request it currently has or find a new one*/
void WebServer::processRequest() { 
    if (this->endTime != 0) { /**This means the server just finished a job or was just created*/
        if (balancer->getTime() >= this->endTime) { /**If the current clock cycle is passed the expected end time of the request*/
            std::cout << "At " << balancer->getTime() << " " << this->name << " processed request from " << serverRequest.getIPIn() << " to " << serverRequest.getIPOut() << "!" << std::endl;
            this->endTime = 0; /**The request is fulfilled and output*/
            findRequest(); /**A new request is found*/
        }
    } else {
        findRequest(); /**If the endTime is ever 0, it immediately tries to find a request*/
    }
}

/**Sets the servers request to fulfill*/
void WebServer::setRequest(Request _request) {
    this->serverRequest = _request;
    this->endTime = serverRequest.getTime() + this->balancer->getTime(); /**Sets the expected endTime of the request*/
}

/**Returns information on request being fulfilled*/
Request WebServer::getRequest() {
    return this->serverRequest; 
}

/**This function forces the server to ask for a new request*/
void WebServer::findRequest() {
    if (!balancer->empty()) { /**When the balancer has requests, a new one is found and popped*/
        setRequest(balancer->pop());
    }
}