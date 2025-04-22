#include "header.h"

// Process class implementation
void process::setRemainingTime(float remaining_time) {
	this->remaining_time = remaining_time;
}

void process::setFinished(bool TF) {
	this->finished = TF;
}

void process::setStartTime(float start_time) {
	this->start_time = start_time;
}

void process::addIntervalOfTime(float start_time, float end_time) {
	tuple<float, float> interval = make_tuple(start_time, end_time);
	schedule.push_back(interval);
}

void process::showIntervals() {
	if (!schedule.empty()) {
		for (int i = 0; i < schedule.size(); i++) {
			cout << "Start: " << get<0>(schedule[i]) << endl;
			cout << "End: " << get<1>(schedule[i]) << endl;
		}
	}
}

float process::getArrivalTime() {
	return arrival_time;
}

float process::getBurstTime() {
	return burst_time;
}

float process::getRemainingTime() {
	return remaining_time;
}

float process::getStartTime() {
	return start_time;
}

bool process::getFinished() {
	return finished;
}

string process::getName() {
	return name;
}

// Scheduler class implementation
void scheduler::inProgress(algorithm& algo) {
	int time = 0;
	algo.initReadyQ(ready_queue);
	ready_queue[0]->setStartTime(0);
	time++;
	while (time < 20) {
		cout << "Time is: " << time << endl;
		if (!ready_queue.empty()) {

			if (time == 1)
			{
				process* p3 = new process("p3", time, 1, 0);
				this->addProcess(p3);
			}

			algo.updateProcesses(ready_queue[0], time);

			cout << ready_queue[0]->getName() << endl;
			algo.updateReadyQ(ready_queue, time);

			if(live)
			{
				Sleep(1000); //wait 1 sec
			}
		}  
		time++;
	}
}


process* scheduler::getRunningProcess() {
	return ready_queue[0];
}

void scheduler::addProcess(process* p) {
	processes.push_back(p);
	ready_queue.push_back(p);
}

// FCFS algorithm implementation
void FCFS::updateProcesses(process* proc, int time) {
	float start = proc->getStartTime();
	float burst = proc->getBurstTime();
	proc->setRemainingTime(proc->getRemainingTime() - 1);

	// cout << "rem: " << proc->getRemainingTime() << endl;
	if (proc->getRemainingTime() == 0) {
		proc->setFinished(true);
	}
}

void FCFS::updateReadyQ(vector<process*>& ready_vec, int time) {

	float start = ready_vec[0]->getStartTime();
	float burst = ready_vec[0]->getBurstTime();
	if (!ready_vec.empty()) {

		if (ready_vec[0]->getFinished()) {
			ready_vec[0]->addIntervalOfTime(start, start + burst);
			//  ready_vec[0]->showIntervals();
			ready_vec.erase(ready_vec.begin());

			if (!ready_vec.empty()) {
				sort(ready_vec.begin(), ready_vec.end(), [](process* a, process* b) {
					return a->getArrivalTime() < b->getArrivalTime();
					});
				ready_vec[0]->setStartTime(time);
			}
		}
	}
}

void FCFS::initReadyQ(vector<process*>& ready_vec) {
	sort(ready_vec.begin(), ready_vec.end(), [](process* a, process* b) {
		return a->getArrivalTime() < b->getArrivalTime();
		});
}

//void FCFS::sortReadyQ(vector<myprocess>& ready_vec, int time) {
//    myprocess* before = &ready_vec[0];
//    sort(ready_vec.begin(), ready_vec.end(), [](myprocess& a, myprocess& b) {
//        return a.getArrivalTime() < b.getArrivalTime();
//        });
//    myprocess* after = &ready_vec[0];
//    if (before != after) {
//    }
//    else {
//        cout << "Not Sorted" << endl;
//    }
//}

// SJF algorithm implementation
void SJF::initReadyQ(vector<process*>& ready_vec) {
	sort(ready_vec.begin(), ready_vec.end(), [](process* a, process* b) {
		return a->getRemainingTime() < b->getRemainingTime();
		}
	);

}

//void SJF::sortReadyQ(vector<myprocess>& ready_vec, int time) {
//    // Sorting logic can be added here if needed
//}

void SJF::updateProcesses(process* proc, int time) {
	float start = proc->getStartTime();
	float burst = proc->getBurstTime();
	proc->setRemainingTime(proc->getRemainingTime() - 1);
	//cout << "rem: " << proc.getRemainingTime() << endl;
	if (proc->getRemainingTime() == 0) {
		//cout << "Finished"<<endl;
		proc->setFinished(true);
		//cout <<"Finished ;"<<proc.getFinished() << endl;
	}
}

void SJF::updateReadyQ(vector<process*>& ready_vec, int time) {
	//checking finished or not
	float start = ready_vec[0]->getStartTime();
	float burst = ready_vec[0]->getBurstTime();
	bool erased = false;
	if (ready_vec[0]->getFinished()) {
		ready_vec[0]->addIntervalOfTime(start, time);
		ready_vec.erase(ready_vec.begin());
		erased = true;

		if (ready_vec.empty()) {
			return;
		}

	}
	if (this->preemptive == true) {
		process* before = ready_vec[0];

		sort(ready_vec.begin(), ready_vec.end(), [](process* a, process* b) {


			return a->getRemainingTime() < b->getRemainingTime();
			});

		process* after = ready_vec[0];
		if ((before != after) && erased == false) {

			before->addIntervalOfTime(start, time);
			after->setStartTime(time);
		}
		else
		{
			if (erased)
			{
				if (!ready_vec.empty()) {
					sort(ready_vec.begin(), ready_vec.end(), [](process* a, process* b) {
						return a->getRemainingTime() < b->getRemainingTime();
						});

					ready_vec[0]->setStartTime(time);
				}
			}
		}
	}
	else {
		if (erased)
		{
			if (!ready_vec.empty()) {
				sort(ready_vec.begin(), ready_vec.end(), [](process* a, process* b) {
					return a->getRemainingTime() < b->getRemainingTime();
					});

				ready_vec[0]->setStartTime(time);
			}
		}

	}
}
void RR::initReadyQ(vector<process*>& ready_vec) {
	sort(ready_vec.begin(), ready_vec.end(), [](process* a, process* b) {
		return a->getArrivalTime() < b->getArrivalTime();
		});
}
void RR::updateProcesses(process* proc, int time) {
	float start = proc->getStartTime();
	float burst = proc->getBurstTime();
	proc->setRemainingTime(proc->getRemainingTime() - 1);
	this->rem_q--;

	// cout << "rem: " << proc->getRemainingTime() << endl;
	if (proc->getRemainingTime() == 0) {
		//cout << "Finished"<<endl;
		proc->setFinished(true);
		//cout <<"Finished ;"<<proc.getFinished() << endl;
	}
}
void RR::updateReadyQ(vector<process*>& ready_vec, int time) {
	if (ready_vec.empty()) return;

	float start = ready_vec[0]->getStartTime();
	float burst = ready_vec[0]->getBurstTime();

	if (rem_q == 0 && ready_vec[0]->getFinished()) {
		ready_vec[0]->addIntervalOfTime(start, time);
		//ready_vec[0]->showIntervals();
		ready_vec.erase(ready_vec.begin());
		rem_q = quantum;
		if (!ready_vec.empty()) {
			ready_vec[0]->setStartTime(time);
		}
	}
	else if (rem_q == 0 && !ready_vec[0]->getFinished()) {
		ready_vec[0]->addIntervalOfTime(start, time);

		ready_vec.push_back(ready_vec[0]);
		ready_vec.erase(ready_vec.begin());
		if (!ready_vec.empty()) {
			ready_vec[0]->setStartTime(time);
		}
		rem_q = quantum;
	}
	else if (ready_vec[0]->getFinished()) {
		ready_vec[0]->addIntervalOfTime(start, time);
		//ready_vec[0]->showIntervals();
		ready_vec.erase(ready_vec.begin());
		rem_q = quantum;

		if (!ready_vec.empty()) {
			ready_vec[0]->setStartTime(time);
		}
	}

	else {
		return;
	}
}


void Priority::updateProcesses(process* proc, int time) {}
void Priority::updateReadyQ(vector<process* >& ready_vec, int time) {}
void Priority::initReadyQ(vector<process*>& ready_vec) {}



int main() {
	process* p1 = new process("p1", 0, 3, 0);
	process* p2 = new process("p2", 0, 4, 0);
	//process* p3 = new process("p3", 1, 1, 0);



	scheduler sched;
	sched.addProcess(p1);
	sched.addProcess(p2);
	//sched.addProcess(p3);

	int in;
	cout << "Live?? ";
	cin >> in;
	sched.live = in;
	cout << "Please Enter the Algo";
	cin >> in;
	
	algorithm* alg = nullptr;
	switch (in) {
	case 0:
	{
		alg = new FCFS();
		break;
	}
	case 1: {
		alg = new SJF();
		break;
	}

	case 2: {
		alg = new RR();
		break;
	}
	case 3: {
		alg = new Priority();
		break;
	}
	}

	bool preemptive;
	cout << "Preemptive?? ";
	cin >> preemptive;
	alg->preemptive = preemptive;

	sched.inProgress(*alg);

	for (int i = 0; i < sched.processes.size(); i++) {
		cout << sched.processes[i]->getName() << endl;
		cout << "Schedule: " << endl;


		for (int j = 0; j < sched.processes[i]->schedule.size(); j++) {
			cout << get<0>(sched.processes[i]->schedule[j]) << " " << get<1>(sched.processes[i]->schedule[j]) << endl;
		}
	}

	return 0;
}