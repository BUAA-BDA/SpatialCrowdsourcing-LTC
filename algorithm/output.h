/**
	1. output data
	2. \author: Trasier
	3. \date:   2017.9.14
*/
#ifndef OUTPUT_H
#define OUTPUT_H

#include <bits/stdc++.h>
using namespace std;

#include "input.h"

#define DVEC 	5
#define SCORE	100

int calcResult(int taskN, int* compTimes);
void dumpResult(const string& execName, int ans, double usedTime=-1.0, double usedMemory=-1.0);

int calcResult(int taskN, int* compTimes) {
	int ret = 0;

	for (int i=0; i<taskN; ++i)
		ret = max(ret, compTimes[i]);
	++ret;

	return ret;
}

int calcResult(int taskN, int* compTimes, task_t* tasks) {
	int ret = 0;

	for (int i=0; i<taskN; ++i)
		ret = max(ret, compTimes[i]);
	++ret;

	if (ret >= 1000000005) {
		for (int i=0; i<taskN; ++i) {
			fprintf(stderr, "%d: %.3lf %d\n", i, tasks[i].s, compTimes[i]);
		}
	}

	return ret;
}

void dumpResult(const string& execName, int ans, double usedTime/*=-1.0*/, double usedMemory/*=-1.0*/) {
	printf("%s %d", execName.c_str(), ans);
	if (usedTime >= 0)
		printf(" %.4lf", usedTime);
	if (usedMemory >= 0)
		printf(" %.4lf", usedMemory);
	putchar('\n');
}

#endif
