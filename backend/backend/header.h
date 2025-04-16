#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
class myprocess {
protected:
    string name;
    bool finished = false;
    int priority;
    float arrival_time;
    float start_time;
    float burst_time;
    float remaining_time;


public: 
      vector<tuple<float, float>> schedule; // each tuple has a start and an endtime
      myprocess(string name, float arrival_time, float burst_time, int priority) {
		  this->name = name;
		  this->arrival_time = arrival_time;
		  this->burst_time = burst_time;
		  this->remaining_time = burst_time;
		  this->priority = priority;
      }
      
void setRemainingTime(float remaining_time);
      
      void setFinished(bool TF);
      void setStartTime(float start_time);
      void addIntervalOfTime(float start_time, float end_time);
      void showIntervals();
      float getArrivalTime();
      float getBurstTime();
      float getRemainingTime();
      float getStartTime();
      bool getFinished();
      string getName();
      
};

class algorithm {
    bool preemptive;
    
public:
    virtual void updateProcesses(myprocess& proc, int time) = 0; //to be overridden
    virtual void updateReadyQ(vector<myprocess>& ready_vec, int time) = 0;  //to be overridden
    virtual void initReadyQ(vector<myprocess>& ready_vec) = 0; //to be overridden
    virtual void sortReadyQ(vector<myprocess>& ready_vec, int time) = 0; //to be overridden
};
class scheduler {
protected:
    string ID;
    vector <myprocess> processes; // vector of all process objects
    vector <myprocess> ready_queue;// 1st element gets CPU
public:
    void inProgress(algorithm& algo);
    myprocess getRunningProcess();
    
    void addProcess(myprocess p);
};

class FCFS : public algorithm {
public:
    void updateProcesses(myprocess& proc, int time);
    void updateReadyQ(vector<myprocess>& ready_vec, int time);
    void initReadyQ(vector<myprocess>& ready_vec);
    void sortReadyQ(vector<myprocess>& ready_vec, int time);

};

class SJF : public algorithm {
public:
    void initReadyQ(vector<myprocess>& ready_vec);
    void sortReadyQ(vector<myprocess>& ready_vec, int time);
    void updateProcesses(myprocess& proc, int time);
    void updateReadyQ(vector<myprocess>& ready_vec, int time);


};

class Priority : public algorithm {
};

class RR : public algorithm {

};

