/**
	1. online version - AAM
	2. \author: Trasier
	3. \date:   2017.9.14
*/
#include <bits/stdc++.h>
using namespace std;

#include "input.h"
#include "output.h"
#include "global.h"

#ifdef WATCH_MEM
#include "monitor.h"
int usedMemory = 0;
#endif

const int inf = 1<<30;
int K;
int* compTime;
task_t* tasks;
worker_t* workers;
int taskN = 0;
int workerN = 0;
double delta, epsilon;

void readInput(istream& fin) {
	fin >> K >> epsilon >> dmax;
	delta = calcDelta(epsilon);
	readInput_Tasks(fin, taskN, tasks);
	readInput_Workers(fin, workerN, workers);
	compTime = new int[taskN];

	for (int i=0; i<taskN; ++i) {
		compTime[i] = inf;
	}
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif
}

void FreeMem() {
	delete[] compTime;
	delete[] tasks;
	delete[] workers;
}

pdd calcValue2() {
	int c = 0;
	double sum = 0, mx = -inf;

	for (int i=0; i<taskN; ++i) {
		if (tasks[i].s == 0)
			continue;
		++c;
		mx = max(mx, tasks[i].s);
		sum += tasks[i].s;
	}

	return (c==0) ? make_pair(0.,0.) : make_pair(sum/c, mx);
}

void calcValue2(double& maxRemain, double& avg) {
	maxRemain = -inf;
	avg = 0;

	for (int j=0; j<taskN; ++j) {
		if (tasks[j].s >= delta)
			continue;
		avg += delta - tasks[j].s;
		maxRemain = max(maxRemain, delta - tasks[j].s);
	}
	avg /= K;
}

void Schedule() {
	int leftNum = taskN, cid = 0;
	double maxRemain, avg;
	priority_queue<pdi, vector<pdi>, greater<pdi> > Q;

	for (int i=0; leftNum>0&&i<workerN; ++i) {
		worker_t& worker = workers[i];
		calcValue2(maxRemain, avg);
		for (int j=0; j<taskN; ++j) {
			if (tasks[j].s >= delta)
				continue;
			double tmp;
			if (avg >= maxRemain) {
				double ut = calcUtility(tasks[j], worker), tmp = min(delta-tasks[j].s, ut);
				Q.push(make_pair(tmp, j));
				if (Q.size() > K) Q.pop();
			} else {
				Q.push(make_pair(delta-tasks[j].s, j));
				if (Q.size() > K) Q.pop();
			}
		}

		while (!Q.empty()) {
			pdi tmp = Q.top();
			Q.pop();
			int taskId = tmp.second;
			double ut = calcUtility(tasks[taskId], worker);
			tasks[taskId].s += ut;
			if (tasks[taskId].s >= delta) {
				compTime[taskId] = i;
				--leftNum;
			}
		}
		
#ifdef WATCH_MEM
		if (i%1000 == 0)
			watchSolutionOnce(getpid(), usedMemory);
#endif
	}

#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
#endif
}

int main(int argc, char **argv) {
	string execName("AAM");

	string srcFileName;
	if (argc > 1) {
		srcFileName = string(argv[1]);
	}
	if (argc > 2)
		freopen(argv[2], "w", stdout);

	// step1: read Input
	if (srcFileName.empty()) {
		readInput(cin);
	} else {
		ifstream fin(srcFileName.c_str(), ios::in);
		if (!fin.is_open()) {
			fprintf(stderr, "FILE %s is invalid.", srcFileName.c_str());
			exit(1);
		}

		readInput(fin);
		fin.close();
	}

	// step2: online execute
	clock_t begTime, endTime;
	begTime = clock();
	Schedule();
	endTime = clock();
	
	#ifdef WATCH_MEM
	watchSolutionOnce(getpid(), usedMemory);
	#endif
	
	// step3: output result
	int ans = calcResult(taskN, compTime);
	double usedTime = (endTime - begTime)*1.0 / CLOCKS_PER_SEC;
	#ifdef WATCH_MEM
	dumpResult(execName, ans, usedTime, usedMemory/1024.0);
	#else
	dumpResult(execName, ans, usedTime);
	#endif

	// step4: free memory
	FreeMem();

	fflush(stdout);

	return 0;
}
