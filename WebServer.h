#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "LoadBalancer.h"
#include <string>

class LoadBalancer;
class WebServer { /**The webserver is connected to a load balancer, has a request and name, and a time when it completes the request*/
    LoadBalancer* balancer;
    Request serverRequest;
    int endTime;
    std::string name;
public:
    WebServer(LoadBalancer* _balancer, std::string _name); /**A constructor that names the server and connects the load balancer*/
    void processRequest(); /**The main function that works on requests*/
    void setRequest(Request _request); /**Called in find request to set the serverRequest private member to get details*/
    Request getRequest(); /**Returns the actual requests information for output*/
    void findRequest(); /**Asks load balancer for a new request if the queue is not empty*/
};

#endif