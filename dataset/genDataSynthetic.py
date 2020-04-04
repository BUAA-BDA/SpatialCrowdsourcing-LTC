#!/usr/bin/env python

import numpy as np
from random import randint, shuffle
import sys
import os
import utm

class constForDataSet:
	locRng = [0, 500]
	taskNList = [1000, 2000, 3000, 4000, 5000]
	KList = [4,5,6,7,8]
	workerN = 80000
	epsilonList = [0.06, 0.10, 0.14, 0.18, 0.22]
	scale_taskNList = [10000, 20000, 30000, 40000, 50000, 100000]
	scale_workerN = 2000000
	dmaxList = [10, 20, 30, 40, 50]
	muList = [0.82, 0.84, 0.86, 0.88, 0.90]
	defaultValues = [
		taskNList[len(taskNList)/2],
		KList[len(KList)/2],
		epsilonList[len(epsilonList)/2],
		dmaxList[len(dmaxList)/2],
		muList[len(muList)/2],
	]
	sigma = 0.05
	dataSetN = 1

class CFDS(constForDataSet):
	pass

class baseGenerator:

	def gen(self, n):
		pass

class randomGenerator(baseGenerator):

	def __init__(self, mx):
		self.mx = mx

	def gen(self, n):
		ret = np.random.random_integers(0, mx, n)
		return ret
		
class expGenerator(baseGenerator):

	def __init__(self, mu):
		self.mu = mu

	def gen(self, n, lb = None, rb = None):
		ret = np.random.exponential(self.mu, n)
		for i in xrange(n):
			if lb is not None and ret[i]<lb:
				ret[i] = lb
			if rb is not None and ret[i]>rb:
				ret[i] = rb
		return ret

	def setMu(self, mu):
		self.mu = mu

class normalGenerator(baseGenerator):

	def __init__(self, mu, sigma):
		self.mu = mu
		self.sigma = sigma

	def gen(self, n, lb = 0.66, rb = 1.0):
		ret = np.random.normal(self.mu, self.sigma, n)
		for i in xrange(n):
			if lb is not None and ret[i]<lb:
				ret[i] = lb
			if rb is not None and ret[i]>rb:
				ret[i] = rb
		return ret

	def setMu(self, mu):
		self.mu = mu

	def setSigma(self, sigma):
		self.sigma = sigma


class uniformGenerator(baseGenerator):

	def __init__(self, low, high):
		self.low = low
		self.high = high

	def gen(self, n, lb = None, rb = None):
		ret = np.random.uniform(self.low, self.high, n)
		for i in xrange(n):
			if lb is not None and ret[i]<lb:
				ret[i] = lb
			if rb is not None and ret[i]>rb:
				ret[i] = rb
		return ret

	def setLow(self, low):
		self.low = max(low, 0.66)

	def setHigh(self, high):
		self.high = min(high, 1.0)

class locGenerator(baseGenerator):

	def __init__(self, low, high):
		self.low = low
		self.high = high

	def setLow(self, low):
		self.low = low

	def setHigh(self, high):
		self.high = high

	def gen(self, n, permitLayer = True):
		if permitLayer==False and (self.high - self.low + 1) ** 2 < n:
			raise ValueError("Not enough poi in 2D places")
		locSet = set()
		ret = []
		for i in xrange(n):
			while True:
				x = randint(self.low, self.high)
				y = randint(self.low, self.high)
				loc = (x, y)
				if permitLayer or loc not in locSet:
					break
			locSet.add(loc)
			ret.append(loc)
		return ret


def genData(desFile, tasks, workers, workerAcc, K, epsilon, dmax):
	workerNum = len(workers)
	taskNum = len(tasks)
	with open(desFile, "w") as fout:
		line = "%s %s %s\n" % (K, epsilon, dmax)
		fout.write(line)
		line = "%s\n" % (taskNum)
		fout.write(line)
		for i in xrange(taskNum):
			line = "%s %s\n" % (tasks[i][0], tasks[i][1])
			fout.write(line)
		line = "%s\n" % (workerNum)
		fout.write(line)
		for i in xrange(workerNum):
			line = "%s %s %.2f\n" % (workers[i][0], workers[i][1], workerAcc[i])
			fout.write(line)

def genTasks(taskNum):
	a, b = CFDS.locRng
	ret = map(lambda i:[randint(a,b), randint(a,b)], xrange(taskNum))
	return ret

def genWorkers(tasks, workerNum):
	ret = []
	taskNum = len(tasks)
	m = workerNum / taskNum
	dmax2 = CFDS.dmaxList[len(CFDS.dmaxList)/2]
	for i in xrange(workerNum):
		tid = i / m
		# if tid==493:
			# print m
		x = tasks[tid][0] + randint(0, dmax2/2)
		y = tasks[tid][1] + randint(0, dmax2/2)
		ret.append([x, y])
	shuffle(ret)
	return ret

def genDataSetName(taskN, K, epsilon, dmax, mu, ch='N'):
	if ch=='R':
		ret = "%d_%.2f_%d_%.2f_%s" % (K, epsilon, dmax, mu, ch)
	else:
		ret = "%d_%d_%.2f_%d_%.2f_%s" % (taskN, K, epsilon, dmax, mu, ch)
	return ret

def genDataSet(dataSetId, desFilePath):
	uniformGrt = uniformGenerator(0.0, 0.0)
	taskN, K, epsilon, dmax, mu = CFDS.defaultValues
	taskNmax = max(CFDS.taskNList)
	tasks = genTasks(taskNmax)
	workers = genWorkers(tasks, CFDS.workerN)
	normalGrt = normalGenerator(mu, CFDS.sigma)
	workerAcc = normalGrt.gen(CFDS.workerN)
	taskN, K, epsilon, dmax, mu = CFDS.defaultValues

	for taskN in CFDS.taskNList:
		tmpFilePath = genDataSetName(taskN, K, epsilon, dmax, mu)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		genData(desFileName, tasks[:taskN], workers, workerAcc, K, epsilon, dmax)
	taskN, K, epsilon, dmax, mu = CFDS.defaultValues
	 
	for K in CFDS.KList:
		tmpFilePath = genDataSetName(taskN, K, epsilon, dmax, mu)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		genData(desFileName, tasks, workers, workerAcc, K, epsilon, dmax)
	taskN, K, epsilon, dmax, mu = CFDS.defaultValues

	for epsilon in CFDS.epsilonList:
		tmpFilePath = genDataSetName(taskN, K, epsilon, dmax, mu)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		genData(desFileName, tasks, workers, workerAcc, K, epsilon, dmax)
	taskN, K, epsilon, dmax, mu = CFDS.defaultValues

	for mu in CFDS.muList:
		tmpFilePath = genDataSetName(taskN, K, epsilon, dmax, mu)
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		normalGrt.setMu(mu)
		workerAccTmp = normalGrt.gen(CFDS.workerN)
		genData(desFileName, tasks, workers, workerAccTmp, K, epsilon, dmax)
	taskN, K, epsilon, dmax, mu = CFDS.defaultValues
	
	expGrt = expGenerator(mu)
	for mu in CFDS.muList:
		tmpFilePath = genDataSetName(taskN, K, epsilon, dmax, mu, 'E')
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		expGrt.setMu(mu)
		workerAccTmp = expGrt.gen(CFDS.workerN)
		genData(desFileName, tasks, workers, workerAccTmp, K, epsilon, dmax)
	taskN, K, epsilon, dmax, mu = CFDS.defaultValues

	for mu in CFDS.muList:
		if mu>=0.83:
			high = 1.0
			low = 2*mu - high
		else:
			low = 0.66
			high = 2*mu - low
		uniformGrt.setLow(low)
		uniformGrt.setHigh(high)
		tmpFilePath = genDataSetName(taskN, K, epsilon, dmax, mu, 'U')
		tmpFilePath = os.path.join(desFilePath, tmpFilePath)
		if not os.path.exists(tmpFilePath):
			os.mkdir(tmpFilePath)
		desFileName = "data_%02d.txt" % (dataSetId)
		desFileName = os.path.join(tmpFilePath, desFileName)
		if os.path.exists(desFileName):
			continue
		workerAccTmp = uniformGrt.gen(CFDS.workerN)
		genData(desFileName, tasks, workers, workerAccTmp, K, epsilon, dmax)
	taskN, K, epsilon, dmax, mu = CFDS.defaultValues

	
def exp0(desFilePath):
	if not os.path.exists(desFilePath):
		os.mkdir(desFilePath)
	dataSetN = CFDS.dataSetN
	for i in xrange(dataSetN):
		genDataSet(i, desFilePath)

		
if __name__ == "__main__":
	desFilePath = "./synthetic"
	exp0(desFilePath)
