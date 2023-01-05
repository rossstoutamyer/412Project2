#include "WebServer.h"
#include <iostream>

LoadBalancer::LoadBalancer(int numServers, int numRequests) { /**Load balancer constructor inititalizes the queue and the number of servers*/
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

int LoadBalancer::getTime() { /**The function to get the time in clock cycles*/
    return this->time;
}

bool LoadBalancer::empty() { /**Checks if there are requests on the queue*/
    return requests.empty();
}

void LoadBalancer::clockTick() { /**Simulates a clock tick*/
    for (std::size_t i = 0; i < this->servers.size(); ++i) {
        this->servers[i].processRequest(); /**Each server processes a request or finds a new one*/
    }
    this->time++; /**Time is incremented*/
}

Request LoadBalancer::pop() { /**Function to remove requeusts*/
    Request currRequest = this->requests.front();
    this->requests.pop(); /**Pops the request on front of the queue*/
    return currRequest; /**Returns a request to be stored in the server*/
}

int LoadBalancer::size() {
    return this->requests.size(); /**Returns the number of requests remaining*/
}

void LoadBalancer::push(Request req) {
    requests.push(req); /**Pushes another request to the queue*/
}

int LoadBalancer::serverSize() {
    return this->servers.size(); /**Returns the number of servers on the load balancer as this might change*/
}

void LoadBalancer::serverPush(WebServer serv) {
    this->servers.push_back(serv); /**Pushes a new server to load balancer vector*/
}

void LoadBalancer::serverPop() {
    if(!this->servers.empty()) { /**Removes a server from load balancer vector if one exists*/
        this->servers.pop_back();
    }
}