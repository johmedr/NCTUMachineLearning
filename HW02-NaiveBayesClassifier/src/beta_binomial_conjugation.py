import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import beta
import time

def parse_binary_file(path): 
	with open(path) as f: 
		token_list = f.read().split('\n')
		f.close() 
		return token_list

def process_token(t):
	events = np.array([int(e) for e in t])

	success = events.sum() 
	ntrials = events.shape[0]

	return success, ntrials

def beta_binomial_estimation(binary_file, a0, b0, plot=True, step=100): 
	token_list = parse_binary_file(binary_file)
	a = a0
	b = b0

	loop = 0

	for t in token_list: 
		k, n = process_token(t)

		print("(%d/%d)[ Prior : P(x) ~ Beta(%f, %f) ]"%(loop + 1, len(token_list), a, b))
		a += k
		b += n - k 
		print("(%d/%d)[ Posterior : P(k|x) ~ Beta(%f, %f) ]"%(loop + 1, len(token_list), a, b))

		if plot and loop % step == 0: 
			x = np.linspace(0, 1, 100)
			time.sleep(0.5)
			plt.close() 
			plt.plot(x, beta.pdf(x, a, b))
			plt.show(False)
		loop += 1

if __name__ == "__main__": 
	PREFIX = "/home/yop/Programmation/Projets/NCTUMachineLearning/HW02-NaiveBayesClassifier/datasets/"
	# FILE = PREFIX + "binary_file.txt"
	FILE = PREFIX + "binary_file2.txt"

	beta_binomial_estimation(FILE, 0.5, 0.5)



