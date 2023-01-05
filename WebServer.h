#ifndef WEBSERVER_H
#define WEBSERVER_H

#include "LoadBalancer.h"
#include <string>

class LoadBalancer;
class WebServer {
    LoadBalancer* balancer;
    Request serverRequest;
    int endTime;
    std::string name;
public:
    WebServer(LoadBalancer* _balancer, std::string _name);
    void processRequest();
    void setRequest(Request _request);
    Request getRequest();
    void findRequest();
};

#endif