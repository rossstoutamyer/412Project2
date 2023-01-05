#include "Request.h"
#include "WebServer.h"

#include <iostream>
#include <string>
#include <random>
#include <unistd.h>

void RandomRequests(LoadBalancer &lb); /**Function to add requeust randomly each clock cycle*/
void ScaleServers(LoadBalancer &lb, int newNumRequests, int threshold); /**Function to add or remove servers when threshold is not met*/
void SimulateBurst(LoadBalancer &lb, int burstChance); /**Function to simulate a burst of access to force change in number of servers drastically*/

int main(int argc, char *argv[])
{
    int opt;
    int numServers = 10; /**Default number of servers*/
    int numTicks = 10000; /**Default number of clock cycles*/

    while((opt = getopt(argc, argv, "s:c:")) != -1) {
        switch (opt) {
            case 's': /**If the user wants a specific number of servers*/
                numServers = atoi(optarg);
                break;
            case 'c': /**If the user wants a specific number of clock cycles*/
                numTicks = atoi(optarg);
                break;
        }
    }

    int numRequests = numServers * 20; /**Default number of requests based on servers*/
    int burstChance = 1; /**I added a 1/10000 chance of a burst happening that adds 300 requests*/
    LoadBalancer lb(numServers, numRequests);
    int currRequests = numRequests; /**This will keep track of the current number of requests to see if more or less servers are needed*/

    for (int i = 0; i < numTicks; ++i) {
        if (i > 0 && i % 50 == 0) { /**Rvery 50 ticks, I decided to look at the request queue and add or subtract servers*/
            currRequests = lb.size();
            ScaleServers(lb, currRequests, numRequests * 4 / 5); /**This function scales the number of servers to try and meet a threshold of 80% of the original requests*/
        }
        SimulateBurst(lb, burstChance);
        RandomRequests(lb); /**This function has a 1/6 chance of adding a request every tick*/
        lb.clockTick(); /**The clock tick is the main function that tells all of the servers to find a job if necessary and keeps track of the clock*/
    }
    std::cout << std::endl << "Finished " << numTicks << " ticks. There are " << lb.size() << " remaining tasks of "<< numRequests << "!" << std::endl;
}

void RandomRequests(LoadBalancer &lb) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 5); /**We want to randomly add requests 1/6 of the time*/

    if(dis(gen) == 0) { /**If the number matches, the random chance is a success and a request is added*/
        Request new_req;
        lb.push(new_req);
    }
}

void ScaleServers(LoadBalancer &lb, int newNumRequests, int threshold) {
    float scaleFactor = float(newNumRequests) / threshold; /**This scale factor tells the load balancer if the work is too fast or slow*/
    if (scaleFactor > 3) { /**If the scale factor is very large (burst)*/
        int numServerAdd = int(scaleFactor * lb.serverSize()); /**This adds scale factor of the servers to the list for more work*/
        for (int i = 0; i < numServerAdd; ++i) {
            std::string name = "Server " + std::to_string(lb.serverSize());
            WebServer new_serv(&lb, name);
            lb.serverPush(new_serv); /**Here, we loop through and add all of these servers to the balancer*/
        }
    }else if (scaleFactor > 1) { /**If the scale factor is more than 1, the work is slow and more servers need to be added*/
        int numServerAdd = int(0.75 * scaleFactor * lb.serverSize()); /**This adds 75% * scale factor of the servers to the list for more work*/
        for (int i = 0; i < numServerAdd; ++i) {
            std::string name = "Server " + std::to_string(lb.serverSize());
            WebServer new_serv(&lb, name);
            lb.serverPush(new_serv); /**Here, we loop through and add all of these servers to the balancer*/
        }
    } else { /**If the scale factor is less than 1, we need to remove servers*/
        int numServerRemove = int((1.25 - scaleFactor) * lb.serverSize()); /**Removes a lot of servers if scale factor is really low*/
        for (int i = 0; i < numServerRemove; ++i) {
            lb.serverPop(); /**Removes a server from the balancer*/
        }
    }
}

void SimulateBurst(LoadBalancer &lb, int burstChance) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 99999); /**Again, we want a random chance. This time out of 100000*/

    if(dis(gen) < burstChance) { /**If the generated number is less than the input chance (1 for 1 in 10000)*/
        std::cout << "Huge Burst of Requests!!!!" << std::endl;
        for (int i = 0; i < 300; ++i) {
            Request new_req;
            lb.push(new_req); /**300 requests are added*/
        }
    }
}