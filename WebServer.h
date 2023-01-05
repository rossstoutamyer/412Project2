#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "LoadBalancer.h"
#include <string>

class LoadBalancer;
/**The webserver class is connected to a load balancer, has a request and name, and a time when it completes the request*/
class WebServer { 
    LoadBalancer* balancer;
    Request serverRequest;
    int endTime;
    std::string name;
public:
    /**A constructor that names the server and connects the load balancer*/
    WebServer(LoadBalancer* _balancer, std::string _name);
    /**The main function that works on requests*/
    void processRequest();
    /**Called in find request to set the serverRequest private member to get details*/
    void setRequest(Request _request);
    /**Returns the actual requests information for output*/
    Request getRequest();
    /**Asks load balancer for a new request if the queue is not empty*/
    void findRequest();
};

#endif