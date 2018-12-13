import numpy as np
from utils import *
from datasets import *
from mpl_toolkits.mplot3d import Axes3D

class mnist_naive_bayes_classifier(object): 
	def __init__(self, train_imgs_path, train_lbls_path, mode=1):
		print("... [ Extracting data ] ...")

		train_imgs, train_lbls = parse_mnist_dataset(TRAIN_IMGS, TRAIN_LBLS)

		print("... [ Building model ] ...")

		self.img_shape = train_imgs.shape[0:2]

		self.prior = np.array([np.mean(train_lbls == l) for l in range(NLABELS)])

		if mode == 0:
			self.bins_per_label = bins_per_label(train_imgs, train_lbls, maxvalue=1.)
		elif mode == 1: 
			self.gaussian_per_label = gaussian_per_label(train_imgs, train_lbls)
		else: 
			raise Exception("Try to instanciate Naive Bayes Classifier with an invalid mode (" + str(mode) + ")")

		self.mode = mode

		# self.logp_px_gv_label = None
		
		# if mode == 0: 
		# 	self.logp_px_gv_label = discrete_approach(train_imgs, train_lbls)
		# elif mode == 1: 
		# 	self.logp_px_gv_label = continuous_approach(train_imgs, train_lbls) 
		# else: 
		# 	raise Exception("Try to instanciate Naive Bayes Classifier with an invalid mode (" + str(mode) + ")")

		print("... [ Naive Bayes Classifier successfully initialized ] ...")

	def _find_posterior_discrete(self, imgs, nbins=32, maxvalue=1.): 
		pixels_bin_index = np.around(imgs * (nbins - 1) / float(maxvalue))
		
		count_per_label = np.zeros((NLABELS, 28, 28), dtype=np.float)
		log_likelihood = np.zeros((NLABELS), dtype=np.float)

		total_per_label = np.asarray(self.bins_per_label.sum(axis=1), dtype=np.float) 

		'''
		select bins from index 
		build matrix with probas
		use sum op to compress x and y dimensions 
		'''
		for l in range(NLABELS): 
			for x in range(28):
				for y in range(28): 
					for b in range(nbins): 
						if b == pixels_bin_index[x, y]: 
							count_per_label[l, x, y] = self.bins_per_label[l, b, x, y]
							break
		log_likelihood = (np.log(count_per_label) - np.log(total_per_label)).sum(axis=(1,2))

		log_posterior = log_likelihood + np.log(self.prior)
		return log_posterior			

	def _find_posterior_continuous(self, img): 
		log_posterior = np.zeros(NLABELS, dtype=np.float)
		log_likelihood = np.zeros(NLABELS, dtype=np.float)

		ln_gaussian = log_gaussian(0,0)

		for l in range(NLABELS):
			for x in range(28): 	
				for y in range(28): 
					ln_gaussian.mu = self.gaussian_per_label[l]['mean'][x, y]
					ln_gaussian.sigma2 = self.gaussian_per_label[l]['var'][x, y]
					log_likelihood[l] += ln_gaussian(img[x, y])

			# fig = plt.figure()
			# ax = fig.add_subplot(111, projection='3d')
			# X, Y = np.meshgrid(range(28), range(28)) 
			# ax.plot_surface(X, Y, plot)
			# plt.show()

		log_posterior = log_likelihood + np.log(self.prior)
		return log_posterior	

	def __call__(self, img): 
		if self.mode == 0:
			return np.argmax(self._find_posterior_discrete(img))
		elif self.mode == 1: 
			return np.argmax(self._find_posterior_continuous(img))

	def perform_test(self, test_imgs_path, test_lbls_path):
		test_imgs, test_lbls = parse_mnist_dataset(TRAIN_IMGS, TRAIN_LBLS)

		correct_answers = 0

		acc = []

		for i in range(test_lbls.shape[0]): 
			if self.__call__(test_imgs[:,:,i]) == test_lbls[i]: 
				correct_answers += 1
			acc.append(correct_answers / (i+1))
			if i%100 == 0: 
				print("[%d] Live accuracy -> %f"%(i, correct_answers / (i+1)))
				plt.close()
				plt.plot(range(i + 1), acc)
				plt.show(False)

		return correct_answers, float(correct_answers / test_lbls.shape[0])


if __name__=="__main__": 
	PREFIX = "/home/yop/Programmation/Projets/NCTUMachineLearning/HW02-NaiveBayesClassifier/datasets/"
	TRAIN_IMGS = PREFIX + "train-images-idx3-ubyte"
	TRAIN_LBLS = PREFIX + "train-labels-idx1-ubyte"
	TEST_IMGS = PREFIX + "test-images-idx3-ubyte"
	TEST_LBLS = PREFIX + "test-labels-idx1-ubyte"

	# imgs, lbls = parse_mnist_dataset(TRAIN_IMGS, TRAIN_LBLS)

	# label_fq = label_frequency(lbls)

	# px_discr = discrete_approach(imgs, lbls)
	# px_conti = continuous_approach(imgs, lbls)

	nbc = mnist_naive_bayes_classifier(TRAIN_IMGS, TRAIN_LBLS, 1) 
	correct, accuracy = nbc.perform_test(TEST_IMGS, TEST_LBLS)

	print("Got %d correct answers ! (%f)"%(correct, accuracy))





