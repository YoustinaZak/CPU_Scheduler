// backend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <vector>
#include <tuple>
using namespace std;
class process {
    string name;
    bool finished;
    float arrival_time;
    float burst_time;
    float remaining_time;
    vector<tuple<float, float>> schedule; // each tuple has a start and an endtime

public:
    process(string name, float arrival_time, float burst_time) {
        this->name = name;
        this->arrival_time = arrival_time;
        this->burst_time = burst_time;
    }
};

class algorithm {
    bool preemptive;
    bool priority;
    virtual void updateProcesses(vector<process>& proc_vec) {} //to be overridden
    virtual void updateReadyQ(vector<process>& ready_vec) {}  //to be overridden
};
class scheduler {
    string ID;
    vector <process> processes; // vector of all process objects
    vector <process> ready_queue;// 1st element gets CPU
public:
    void inProgress(algorithm algo) {
        int time = 0;
        while (ready_queue.size()) {
       
            //update processes
            //update their time left
            Sleep(1000); //wait 1 sec
        }

    }
    process getRunningProcess() {
        return ready_queue[0];
    }
};

class FCFS : public algorithm {
public:


};

class SJF : public algorithm {
};

class Priority : public algorithm {
};

class RR : public algorithm {

};
int main()
{
    scheduler sched;
    int in;
    cout << "Please Enter the Algo";
    cin >> in;
    FCFS fcfs;
    switch (in) {
    case 0: sched.inProgress(fcfs);
        break;

    }
    return 0;
}
