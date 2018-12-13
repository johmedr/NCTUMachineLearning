import numpy as np
from univariate_rng import UnivariateRNG

class PolyBasisLinearModelRNG(object): 
	def __init__(self, basis, noise_amplitude, model_parameters):
		assert(isinstance(model_parameters, np.ndarray)) 
		assert(len(model_parameters.shape) == 1 and model_parameters.shape[0] >= basis)

		self.n = basis
		self.a = noise_amplitude 
		self.w = model_parameters

		self.r = UnivariateRNG()

	def setw(self,model_parameters): 
		assert(isinstance(model_parameters, np.ndarray)) 
		assert(len(model_parameters.shape) == 1 and model_parameters.shape[0] >= self.n)
		self.w = model_parameters

	def __call__(self): 
		x = 10.0
		while x >= 10.0 or x <= -10.0:
			x = self.r.rand_uniform(-10.0, 10.0)

		y = 0
		for i in range(self.n):
			y += self.w[i] * x ** i 
		y += self.r.rand_normal(0, self.a)

		return x, y

if __name__ == "__main__": 
	pr = PolyBasisLinearModelRNG(4, 2, np.array([0.3,0.5,0.9,0.1]))
	print(pr())



