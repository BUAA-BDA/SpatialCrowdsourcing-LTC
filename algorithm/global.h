/**
	1. global
	2. \author: Trasier
	3. \date:   2017.9.14
*/
#ifndef GLOBAL_H
#define GLOBAL_H

#include "input.h"

const double eps = 1e-4;
double dmax = 30;
typedef pair<int,int> pii;
typedef pair<double,int> pdi;
typedef pair<double,double> pdd;

double hardAccArr[6][16] = {
		0.971,0.968,0.974,0.974,0.984,0.935,0.957,0.968,0.976,0.963,0.979,0.968,0.944,0.935,0.957,0.911,
		0.974,0.971,0.971,0.971,0.987,0.955,0.932,0.974,0.971,0.952,0.984,0.971,0.926,0.952,0.938,0.914,
		0.971,0.966,0.971,0.968,0.932,0.989,0.957,0.914,0.926,0.920,0.926,0.908,0.941,0.866,0.929,0.908,
		0.957,0.968,0.966,0.971,0.926,0.987,0.926,0.923,0.927,0.896,0.905,0.923,0.935,0.873,0.923,0.938,
		0.938,0.935,0.923,0.905,0.971,0.966,0.963,0.968,0.923,0.981,0.976,0.971,0.926,0.923,0.932,0.899,
		0.966,0.926,0.896,0.923,0.976,0.963,0.968,0.960,0.893,0.977,0.984,0.964,0.899,0.905,0.908,0.930
};

double Length(const location_t& a, const location_t& b) {
	return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}

inline double calcPredictAcc(const task_t& t, const worker_t& w) {
	double l = Length(t.loc, w.loc);
	double ret = w.p / (1.0 + exp(-(dmax - l)));
	return ret;
}

inline double calcUtility(const task_t& t, const worker_t& w) {
	double p = calcPredictAcc(t, w);
	double ret = (p <= 0.66) ? 1e-3 : (p*2-1.0)*(p*2-1.0);
	return ret;
}

int dcmp(double x) {
	if (fabs(x) < 1e-6)
		return 0;
	return x>0 ? 1:-1;
}

double calcDelta(double epsilon) {
	if (epsilon <= 0) epsilon = eps;
	return 2 * log(1.0 / epsilon);
}

#endif
