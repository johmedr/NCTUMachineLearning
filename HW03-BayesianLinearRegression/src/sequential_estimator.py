from univariate_rng import UnivariateRNG
import matplotlib.pyplot as plt
import numpy as np

class SequentialEstimator(object): 
	def __init__(self, mean, var): 
		self.mean = mean
		self.var = var

		self.mean_est = 0
		self.var_est = 0

		self.n = 0

		self.M2 = 0

		self.r = UnivariateRNG()

	def __call__(self): 

		x = self.r.rand_normal(self.mean, self.var) 

		self.n += 1

		old_mean_est = float(self.mean_est)
		self.mean_est += (x - old_mean_est) / self.n

		self.M2 = self.M2 + (x - self.mean_est) * (x - old_mean_est)

		# self.var_est = ((self.n - 1) * self.var_est + (x - old_mean_est) * (x - self.mean_est)) / self.n
		self.var_est = self.M2 / self.n


		return self.mean_est, self.var_est, x, self.n


if __name__ == "__main__": 
	mean = 2
	var = 5 

	acc = 1e-5

	s = SequentialEstimator(mean, var)

	mean_est = 0
	var_est = 0
	count = 100

	mean_acc = []
	var_acc = []

	n = 0
	while (mean_est - mean)**2 > acc or (var_est - var)**2 > acc or count != 0: 

		mean_est, var_est, x, n = s() 

		mean_acc.append((mean_est - mean)**2)
		var_acc.append((var_est - var)**2)

		print("(%d) : seen %f - new mean : %f, new var : %f"%(n, x, mean_est, var_est))

		if mean_acc[-1] < acc and var_acc[-1] < acc: 
			count -= 1
		else: 
			count = 100


	lmean, = plt.plot(range(n), mean_acc, label='mean acc') 
	lvar, = plt.plot(range(n), var_acc, label='var acc')
	ltar, = plt.plot(range(n), [acc for i in range(n)], label='target acc')
	plt.legend(handles=[lmean, lvar, ltar])
	plt.yscale('log')
	plt.show()

