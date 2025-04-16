#include "header.h"

// Process class implementation
void myprocess::setRemainingTime(float remaining_time) {
    this->remaining_time = remaining_time;
}

void myprocess::setFinished(bool TF) {
    this->finished = TF;
}

void myprocess::setStartTime(float start_time) {
    this->start_time = start_time;
}

void myprocess::addIntervalOfTime(float start_time, float end_time) {
    tuple<float, float> interval = make_tuple(start_time, end_time);
    schedule.push_back(interval);
}

void myprocess::showIntervals() {
    if (!schedule.empty()) {
        for (int i = 0; i < schedule.size(); i++) {
            cout << "Start: " << get<0>(schedule[i]) << endl;
            cout << "End: " << get<1>(schedule[i]) << endl;
        }
    }
}

float myprocess::getArrivalTime() {
    return arrival_time;
}

float myprocess::getBurstTime() {
    return burst_time;
}

float myprocess::getRemainingTime() {
    return remaining_time;
}

float myprocess::getStartTime() {
    return start_time;
}

bool myprocess::getFinished() {
    return finished;
}

string myprocess::getName() {
    return name;
}

// Scheduler class implementation
void scheduler::inProgress(algorithm& algo) {
    int time = 0;
    algo.initReadyQ(ready_queue);
    ready_queue[0].setStartTime(0);

    while (time < 7) {
        cout << "Time is: " << time << endl;
        if (!ready_queue.empty()) {
            cout << "heere " << endl; 
            algo.updateProcesses(ready_queue[0], time);
            //algo.sortReadyQ(ready_queue, time);

            cout << ready_queue[0].getName() << endl;
            algo.updateReadyQ(ready_queue, time);

            Sleep(1000); //wait 1 sec 
            time++;
        }
    }
}

myprocess scheduler::getRunningProcess() {
    return ready_queue[0];
}

void scheduler::addProcess(myprocess p) {
    processes.push_back(p);
    ready_queue.push_back(p);
}

// FCFS algorithm implementation
void FCFS::updateProcesses(myprocess& proc, int time) {
    float start = proc.getStartTime();
    float burst = proc.getBurstTime();
    proc.setRemainingTime(proc.getRemainingTime() - 1);

    cout << "rem: " << proc.getRemainingTime() << endl;
    if (proc.getRemainingTime() == 0) {
        proc.setFinished(true);
    }
}

void FCFS::updateReadyQ(vector<myprocess>& ready_vec, int time) {
    float start = ready_vec[0].getStartTime();
    float burst = ready_vec[0].getBurstTime();
    if (!ready_vec.empty()) {

        if (ready_vec[0].getFinished()) {
            ready_vec[0].addIntervalOfTime(start, start + burst);
            ready_vec[0].showIntervals();
            ready_vec.erase(ready_vec.begin());

            if (!ready_vec.empty()) {
                ready_vec[0].setStartTime(time + 1);
            }
        }
    }
}

void FCFS::initReadyQ(vector<myprocess>& ready_vec) {
    sort(ready_vec.begin(), ready_vec.end(), [](myprocess& a, myprocess& b) {
        return a.getArrivalTime() < b.getArrivalTime();
        });
}

void FCFS::sortReadyQ(vector<myprocess>& ready_vec, int time) {
    myprocess* before = &ready_vec[0];
    sort(ready_vec.begin(), ready_vec.end(), [](myprocess& a, myprocess& b) {
        return a.getArrivalTime() < b.getArrivalTime();
        });
    myprocess* after = &ready_vec[0];
    if (before != after) {
    }
    else {
        cout << "Not Sorted" << endl;
    }
}

// SJF algorithm implementation
void SJF::initReadyQ(vector<myprocess>& ready_vec) {
    sort(ready_vec.begin(), ready_vec.end(), [](myprocess& a, myprocess& b) {
        if (a.getArrivalTime() != b.getArrivalTime()) {
            return a.getArrivalTime() < b.getArrivalTime();
        }
        else {
            return a.getRemainingTime() < b.getRemainingTime();
        }
        });
}

void SJF::sortReadyQ(vector<myprocess>& ready_vec, int time) {
    // Sorting logic can be added here if needed
}

void SJF::updateProcesses(myprocess& proc, int time) {
    float start = proc.getStartTime();
    float burst = proc.getBurstTime();
    proc.setRemainingTime(proc.getRemainingTime() - 1);
    if (proc.getRemainingTime() == 0) {
        proc.setFinished(true);
    }
}

void SJF::updateReadyQ(vector<myprocess>& ready_vec, int time) {
    float start = ready_vec[0].getStartTime();
    float burst = ready_vec[0].getBurstTime();
    if (ready_vec[0].getFinished()) {
        ready_vec[0].addIntervalOfTime(start, start + burst);
        ready_vec.erase(ready_vec.begin());

        if (!ready_vec.empty()) {
            ready_vec[0].setStartTime(time);
        }
    }
}

int main() {
    myprocess p1 = myprocess("p1", 0, 2, 0);
    myprocess p2 = myprocess("p2", 0, 4, 0);
    myprocess p3 = myprocess("p3", 1, 1, 0);
    scheduler sched;
    sched.addProcess(p1);
    sched.addProcess(p2);
    sched.addProcess(p3);
    int in;
    cout << "Please Enter the Algo";
    cin >> in;
    FCFS fcfs;
    SJF sjf;

    switch (in) {
    case 0: sched.inProgress(fcfs);
        break;
    case 1: sched.inProgress(sjf);
        break;
    }
    //cout << get<0>(p1.schedule[0]) << " " << get<1>(p1.schedule[0]);
    return 0;
}