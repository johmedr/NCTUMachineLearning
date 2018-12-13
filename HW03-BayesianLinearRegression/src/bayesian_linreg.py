from linearmodel_rng import PolyBasisLinearModelRNG
from univariate_rng import UnivariateRNG
import numpy as np
import matplotlib.pyplot as plt
import time

class BayesianLinearRegression(object): 
	def __init__(self, initial_prior_precision, basis, noise_amplitude, model_parameters): 
		assert(isinstance(initial_prior_precision, np.ndarray)) 

		self.rng = UnivariateRNG()

		self.n = basis

		self.initial_precision = initial_prior_precision

		self.a = np.max(initial_prior_precision) * 1e3 / noise_amplitude
		self.y_mean = 0 
		self.step = 0
		
		self.m_prior = 0
		self.b_prior = initial_prior_precision

		self.Y_c = []
		self.X_c = []

		self.W_mean = np.zeros((n, 1))
		self.W_var = np.zeros((3, 3))

		self.W_s = np.zeros((3, 3))
		self.W_mu = np.zeros(n)

		self.Y_s = 0
		self.Y_mu = 0

		self.linear_model = PolyBasisLinearModelRNG(basis, noise_amplitude, model_parameters)

	def _make_design_matrix(self, x): 
		return np.array([x ** i for i in range(self.n)])

	def _sequential_estimation_y(self, y): 
		old_mean_est = float(self.y_mean)
		self.y_mean += (y - old_mean_est) / self.step
		self.a = ((self.step - 1) * self.a + (y - old_mean_est) * (y - self.y_mean)) / self.step

	def __call__(self): 
		self.step += 1

		x, y = self.linear_model()

		if self.step > 1:
			self._sequential_estimation_y(y)
		self.Y_c.append(y)
		Y_ = np.array(self.Y_c)
		
		X = self._make_design_matrix(x)
		self.X_c.append(X)
		X_ = np.array(self.X_c)

		# self.W_s += self.a * np.dot(X.transpose(), X)
		self.W_s = self.a * np.dot(X_.transpose(), X_) + self.b_prior
		self.W_mu = self.a * np.dot(np.linalg.inv(self.W_s), np.dot(X_.transpose(), Y_))

		Y_s = 1/self.a + np.dot(np.dot(X_, self.W_s),  X_.transpose())
		Y_mu = np.dot(X_, self.W_mu)

		return self.W_mu, self.W_s, X, y

def apply_model(w, x): 
	y = []
	for i in range(x.shape[0]):
		s = 0 
		for j in range(w.shape[0]): 
			s += w[j] * x[i] ** j
		y.append(s)
	return np.array(y)

if __name__ == "__main__": 
	n = 4
	nsteps = 750
	param_range = 10
	
	plot_interval = 1
	blocking = False

	rng = UnivariateRNG()

	initial_prior_precision = 1e12 * np.eye(n)
	noise_amplitude = 1e1
	model_parameters = np.array([rng.rand_uniform(-param_range, param_range) for i in range(n)])

	b = BayesianLinearRegression(initial_prior_precision, n, noise_amplitude, model_parameters)


	wmu_acc = []
	pred_acc = []

	mean_error = []
	mse = []

	plotting = True

	for i in range(nsteps): 

		wmu, ws, X, y = b()
		wmu_acc.append(np.abs(wmu- model_parameters))

		mean_error.append(np.linalg.norm(wmu- model_parameters))

		pred_acc.append( np.abs(np.dot(X, wmu) - y))

		x = np.linspace(-10, 10, num=100)
		mse.append(np.linalg.norm(apply_model(model_parameters, x) - apply_model(wmu, x))**2)
		print("MSE : %f"%(mse[-1]))

		if i % plot_interval == 0 and plotting and mse[-1] > 10**n: 
			plt.close()
			try: 
				x = np.linspace(-10, 10, num=100)
				l1, = plt.plot(x, apply_model(model_parameters, x), label='ground truth') 
				l2, = plt.plot(x, apply_model(wmu, x), label='mean estimate')
				plt.legend(handles=[l1, l2])
				plt.show(blocking)
				time.sleep(0.5)
			except KeyboardInterrupt:
				print("Ok, stop plotting")
				plotting = False


	try:


		plt.subplot(2, 2 ,1)

		lpred, = plt.plot(range(nsteps), pred_acc, label='target acc')
		plt.legend(handles=[lpred])
		plt.yscale('log')

		plt.subplot(2,2,2)

		lwmu = []
		for i in range(n): 
			legwmu, = plt.plot(range(nsteps), [wmu_acc[j][i] for j in range(nsteps)], label='wmu[%d]'%(i)) 
			lwmu.append(legwmu)

		plt.legend(handles=lwmu)
		plt.yscale('log')

		plt.subplot(2, 2 , 4)
		l, = plt.plot(range(nsteps), mean_error, label='wmu mean error')
		plt.legend(handles=[l])
		plt.yscale('log')

		plt.subplot(2, 2 , 3)
		l, = plt.plot(range(nsteps), mse, label='mean square error')
		plt.legend(handles=[l])
		plt.yscale('log')
		print("SNR : %d | MSE : %f"%(param_range*2 / noise_amplitude, np.mean(mse[-100:-1])))

		plt.show()

	except KeyboardInterrupt:
		print("bye")
