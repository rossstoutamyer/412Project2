#include "WebServer.h"
#include <iostream>

/**Load balancer constructor inititalizes the queue and the number of servers*/
LoadBalancer::LoadBalancer(int numServers, int numRequests) {
    this->time = 0; /**The time is also set to 0*/

    for (int i = 0; i < numRequests; ++i) {
        Request new_req;
        this->push(new_req); /**Each request is pushed to the queue*/
    }

    for (int i = 0; i < numServers; ++i) {
        std::string name = "Server " + std::to_string(i + 1);
        WebServer currServer(this, name);
        if (!empty()) {
            currServer.setRequest(this->pop()); /**While there are requests on the queue, each server gets one*/
        }
        this->serverPush(currServer); /**Each server is connected to the load balancer*/
    }
}

/**The function to get the time in clock cycles*/
int LoadBalancer::getTime() {
    return this->time;
}

/**Checks if there are requests on the queue*/
bool LoadBalancer::empty() {
    return requests.empty();
}

/**Simulates a clock tick*/
void LoadBalancer::clockTick() {
    for (std::size_t i = 0; i < this->servers.size(); ++i) {
        this->servers[i].processRequest(); /**Each server processes a request or finds a new one*/
    }
    this->time++; /**Time is incremented*/
}

/**Function to remove requeusts*/
Request LoadBalancer::pop() {
    Request currRequest = this->requests.front();
    this->requests.pop(); /**Pops the request on front of the queue*/
    return currRequest; /**Returns a request to be stored in the server*/
}

/**Returns the number of requests remaining*/
int LoadBalancer::size() {
    return this->requests.size();
}

/**Pushes another request to the queue*/
void LoadBalancer::push(Request req) {
    requests.push(req); 
}

/**Returns the number of servers on the load balancer as this might change*/
int LoadBalancer::serverSize() {
    return this->servers.size(); 
}

/**Pushes a new server to load balancer vector*/
void LoadBalancer::serverPush(WebServer serv) {
    this->servers.push_back(serv);
}

/**Removes a server from load balancer vector if one exists*/
void LoadBalancer::serverPop() {
    if(!this->servers.empty()) { 
        this->servers.pop_back();
    }
}