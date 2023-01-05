#ifndef LOADBALNCER_H
#define LOADBALANCER_H

#include <queue>
#include <vector>
#include "Request.h"

class WebServer;
/**The load balancer class keeps track of total servers, requests, and time*/
class LoadBalancer {
    std::queue<Request> requests;
    std::vector<WebServer> servers;
    int time;

public:
    /**Constructor initializes requests and servers*/
    LoadBalancer(int numServers, int numRequests);
    /**Returns the total time*/
    int getTime();
    /**Clock tick makes the servers work and increments time*/
    void clockTick();
    /**Checks to see if request queue is empty*/
    bool empty();
    /**Pops and returns a request from the queue*/
    Request pop();
    /**Pushes a new request to the queue*/
    void push(Request req);
    /**Returns the number of remaining requeusts*/
    int size();
    /**Gives the number of servers connected to the load balancer*/
    int serverSize();
    /**Pushes a new server to vector*/
    void serverPush(WebServer serv);
    /**Removes a server from the vector*/
    void serverPop();
};

#endif