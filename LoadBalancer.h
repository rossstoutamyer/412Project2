#ifndef LOADBALNCER_H
#define LOADBALANCER_H

#include <queue>
#include <vector>
#include "Request.h"

class WebServer;
class LoadBalancer {
    std::queue<Request> requests;
    std::vector<WebServer> servers;
    int time;

public:
    LoadBalancer(int numServers, int numRequests);
    int getTime();
    void clockTick();
    bool empty();
    Request pop();
    void push(Request req);
    int size();
    int serverSize();
    void serverPush(WebServer serv);
    void serverPop();
};

#endif