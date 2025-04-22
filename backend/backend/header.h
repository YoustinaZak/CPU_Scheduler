#pragma once
#include <iostream>
#include <windows.h>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;
class process {
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
      process(string name, float arrival_time, float burst_time, int priority) {
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
  
public:
   bool preemptive;

    virtual void updateProcesses(process * proc, int time) = 0; //to be overridden
    virtual void updateReadyQ(vector<process *> &ready_vec, int time) = 0;  //to be overridden
	virtual void initReadyQ(vector<process *>& ready_vec)=0 ; //to be overridden
};
class scheduler {
protected:
    string ID;
    vector <process*> ready_queue;// 1st element gets CPU
public:
    bool live;
    vector <process*> processes; // vector of all process objects
    void inProgress(algorithm& algo);
    process* getRunningProcess();
    void addProcess(process* p);
};

class FCFS : public algorithm {
public:
    void updateProcesses(process* proc, int time);
    void updateReadyQ(vector<process* >& ready_vec, int time);
    void initReadyQ(vector<process*>& ready_vec);
   

};

class SJF : public algorithm {
public:
    void updateProcesses(process* proc, int time);
    void updateReadyQ(vector<process* >& ready_vec, int time);
    void initReadyQ(vector<process*>& ready_vec);

};

class Priority : public algorithm {
public:
    void updateProcesses(process* proc, int time);
    void updateReadyQ(vector<process* >& ready_vec, int time);
    void initReadyQ(vector<process*>& ready_vec);
};

class RR : public algorithm {
public:
    int quantum = 2;
    int rem_q = quantum;
    void updateProcesses(process* proc, int time);
    void updateReadyQ(vector<process* >& ready_vec, int time);
    void initReadyQ(vector<process*>& ready_vec);
};

