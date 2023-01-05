#include "WebServer.h"
#include <iostream>

LoadBalancer::LoadBalancer(int numServers, int numRequests) {
    this->time = 0;

    for (int i = 0; i < numRequests; ++i) {
        Request new_req;
        this->push(new_req);
    }

    for (int i = 0; i < numServers; ++i) {
        std::string name = "Server " + std::to_string(i + 1);
        WebServer currServer(this, name);
        if (!empty()) {
            currServer.setRequest(this->pop());
        }
        this->serverPush(currServer);
    }
}

int LoadBalancer::getTime() {
    return this->time;
}

bool LoadBalancer::empty() {
    return requests.empty();
}

void LoadBalancer::clockTick() {
    for (std::size_t i = 0; i < this->servers.size(); ++i) {
        this->servers[i].processRequest();
    }
    this->time++;
}

Request LoadBalancer::pop() {
    Request currRequest = this->requests.front();
    this->requests.pop();
    return currRequest;
}

int LoadBalancer::size() {
    return this->requests.size();
}

void LoadBalancer::push(Request req) {
    requests.push(req);
}

int LoadBalancer::serverSize() {
    return this->servers.size();
}

void LoadBalancer::serverPush(WebServer serv) {
    this->servers.push_back(serv);
}

void LoadBalancer::serverPop() {
    if(!this->servers.empty()) {
        this->servers.pop_back();
    }
}