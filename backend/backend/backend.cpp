// backend.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <vector>
#include <tuple>
using namespace std;
class process {
protected:
    string name;
    bool finished= false;
    int priority;
    float arrival_time;
    float start_time;
    float burst_time;
    float remaining_time;
    vector<tuple<float, float>> schedule; // each tuple has a start and an endtime

public:
    process(string name, float arrival_time, float burst_time, int priority) {
        this->name = name;
        this->arrival_time = arrival_time;
        this->burst_time = burst_time;
        remaining_time = burst_time;
        this->priority = priority;
    }
    void setRemainingTime(float remaining_time) {
        this->remaining_time = remaining_time;
    }
    void setFinished(bool TF) {
        this->finished = TF;
    }
    void setStartTime(float start_time) {
        this->start_time = start_time;
    }
    void addIntervalOfTime(float start_time, float end_time) {
        tuple<float, float > interval= make_tuple(start_time, end_time);
        schedule.push_back(interval);
    }
    void showIntervals() {
        if (!schedule.empty()) {
            for (int i = 0; i < schedule.size(); i++) {
                cout << "Start: " <<get<0>(schedule[i])<< endl;
                cout << "End: " << get<1>(schedule[i]) << endl;
            }
        }
    }
    float getArrivalTime() {
        return arrival_time;
    };
    float getBurstTime() {
        return burst_time;
    }
    float getRemainingTime() {
        return remaining_time;
    }
    float getStartTime() {
        return start_time;
    }
    bool getFinished() {
        return finished;
    }
    string getName() {
        return name;
    }
};

class algorithm {
    bool preemptive;
    bool priority;
public:
    virtual void updateProcesses(process& proc, int time) = 0; //to be overridden
    virtual void updateReadyQ(vector<process>& ready_vec, int time) = 0;  //to be overridden
};
class scheduler {
    string ID;
    vector <process> processes; // vector of all process objects
    vector <process> ready_queue;// 1st element gets CPU
public:
    void inProgress(algorithm& algo) {
        int time = 0;
        ready_queue[0].setStartTime(0);
        while (true) {
            cout << "Time is: " << time << endl;
            if (!ready_queue.empty()) {
                algo.updateProcesses(ready_queue[0], time);
                cout << ready_queue[0].getName() << endl;
                
                algo.updateReadyQ(ready_queue, time);
                //update their time left
                //check if a new process was added
                Sleep(1000); //wait 1 sec 
            }
            time++;
        }
    }
    process getRunningProcess() {
        return ready_queue[0];
    }
    void addProcess(process p) {
        processes.push_back(p);
        ready_queue.push_back(p);
    }
};

class FCFS : public algorithm {
public:
    void updateProcesses(process& proc, int time) {
        float start = proc.getStartTime();
        float burst = proc.getBurstTime();
        proc.setRemainingTime(proc.getRemainingTime() - 1);
        
        cout << "rem: " << proc.getRemainingTime() << endl;
        if (proc.getRemainingTime() == 0) {
            //cout << "Finished"<<endl;
            proc.setFinished(true);
            //cout <<"Finished ;"<<proc.getFinished() << endl;
        }
    }
    void updateReadyQ(vector<process>& ready_vec, int time) {
        float start = ready_vec[0].getStartTime();
        float burst = ready_vec[0].getBurstTime();
        if (ready_vec[0].getFinished()) {
            ready_vec[0].addIntervalOfTime(start, start + burst);
            ready_vec[0].showIntervals();
            ready_vec.erase(ready_vec.begin());
            
            if (!ready_vec.empty()) {
                ready_vec[0].setStartTime(time+1);
            }
        }
    }

};

class SJF : public algorithm {
};

class Priority : public algorithm {
};

class RR : public algorithm {

};
int main()
{
    process p1 = process("p1", 0, 2, 0);
    process p2 = process("p2", 0, 4, 0);
    process p3 = process("p3", 1, 1, 0);
    scheduler sched;
    sched.addProcess(p1);
    sched.addProcess(p2);
    sched.addProcess(p3);
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
