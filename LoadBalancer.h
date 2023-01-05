#ifndef LOADBALNCER_H
#define LOADBALANCER_H

#include <queue>
#include <vector>
#include "Request.h"

class WebServer;
class LoadBalancer { /**The load balancer class keeps track of total servers, requests, and time*/
    std::queue<Request> requests;
    std::vector<WebServer> servers;
    int time;

public:
    LoadBalancer(int numServers, int numRequests); /**Constructor initializes requests and servers*/
    int getTime(); /**Returns the total time*/
    void clockTick(); /**Clock tick makes the servers work and increments time*/
    bool empty(); /**Checks to see if request queue is empty*/
    Request pop(); /**Pops and returns a request from the queue*/
    void push(Request req); /**Pushes a new request to the queue*/
    int size(); /**Returns the number of remaining requeusts*/
    int serverSize(); /**Gives the number of servers connected to the load balancer*/
    void serverPush(WebServer serv); /**Pushes a new server to vector*/
    void serverPop(); /**Removes a server from the vector*/
};

#endif