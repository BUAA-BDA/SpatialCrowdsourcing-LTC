/**
	1. input data
	2. \author: Trasier
	3. \date:   2017.9.14
*/
#ifndef INPUT_H
#define INPUT_H

#include <bits/stdc++.h>
using namespace std;

#define DVEC 	5
#define SCORE	100

struct location_t {
	double x, y;

	location_t(double x=0., double y=0.):
		x(x), y(y) {}
};

struct task_t {
	int id;
	location_t loc;
	double s;

	friend istream& operator>>(istream& fin, task_t& t) {
		fin >> t.loc.x >> t.loc.y;
		return fin;
	}
};

struct worker_t {
	int id;
	location_t loc;
	double p;

	friend istream& operator>>(istream& fin, worker_t& w) {
		fin >> w.loc.x >> w.loc.y >> w.p;
		return fin;
	}
};

void readInput_Tasks(istream& fin, int& taskN, task_t*& tasks);
void readInput_Tasks(const string& fileName, int& taskN, task_t*& tasks);
void readInput_Workers(istream& fin, int& workerN, worker_t*& workers);
void readInput_Workers(const string& fileName, int& workerN, worker_t*& workers);
void readInput_Worker(istream& fin, worker_t& worker, int id = 0);

void readInput_Tasks(const string& fileName, int& taskN, task_t*& tasks) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	readInput_Tasks(fin, taskN, tasks);
	fin.close();
}

void readInput_Tasks(istream& fin, int& taskN, task_t*& tasks) {
	if (taskN <= 0) {
		fin >> taskN;
		tasks = new task_t[taskN];
	}
	for (int i=0; i<taskN; ++i) {
		fin >> tasks[i];
		tasks[i].s = 0;
		tasks[i].id = i;
	}
}

void readInput_Workers(const string& fileName, int& workerN, worker_t*& workers) {
	ifstream fin(fileName.c_str(), ios::in);
	if (!fin.is_open()) {
		fprintf(stderr, "FILE %s is invalid.", fileName.c_str());
		exit(1);
	}

	readInput_Workers(fin, workerN, workers);
	fin.close();
}

void readInput_Workers(istream& fin, int& workerN, worker_t*& workers) {
	if (workerN <= 0) {
		fin >> workerN;
		workers = new worker_t[workerN];
	}
	for (int i=0; i<workerN; ++i) {
		workers[i].id = i;
		fin >> workers[i];
	}
}

void readInput_Worker(istream& fin, worker_t& worker, int id/* = 0*/) {
	worker.id = id;
	fin >> worker;
}

#endif
