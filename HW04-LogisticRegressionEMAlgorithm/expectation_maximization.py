import numpy as np 
from matplotlib import pyplot as plt

from univariate_rng import UnivariateRNG
from datasets import parse_mnist_dataset

def binarize_imgs(imgs): 
	imgs_bin = np.asarray(imgs > 0.5, dtype=np.float) 
	return imgs_bin

def confusion_matrix(predicted, expected, n_classes=None): 
	if n_classes is None: 
		n_classes = int(np.amax([np.amax(expected), np.amax(predicted)]) - np.amin([np.amin(expected), np.amin(predicted)])) + 1
	m = np.zeros((n_classes, n_classes))
	for i in range(predicted.shape[0]):
		m[int(predicted[i])][int(expected[i])] += 1.
	return m

class ExpectationMaximization(object):
	def __init__(self, imgs, lbls):
		self.imgs = imgs
		self.lbls = lbls
		self.rng = UnivariateRNG() 

		self.n_classes = int(np.amax(lbls) - np.amin(lbls)) + 1
		self.n_imgs = self.imgs.shape[2]
		self.img_l = self.imgs.shape[0]

		self.mu = np.reshape(
			[self.rng.rand_uniform(0.25,0.75) 
				for i in range(self.img_l**2 * self.n_classes)], (self.img_l, self.img_l, self.n_classes))
		self.mu[:, :] /= np.sum(self.mu, axis=(0, 1))
		for i in range(10): 
			print("min %f, max %f, mean %f"%(np.min(self.mu[:,:,i]), np.max(self.mu[:,:,i]), np.mean(self.mu[:,:,i])))
			plt.imshow(self.mu[:,:,i])
			plt.colorbar()
			plt.show()

		self.pi = np.array([1/self.n_classes for i in range(self.n_classes)])

	def dumbify(self,p): 
		p[p < 0] = np.abs(p[p < 0])
		p[p > 1] = 2 - p[p > 1]
		return p

	def expectation(self, imgs): 
		E_z_nc = np.ndarray((imgs.shape[2], self.n_classes))
		for n in range(imgs.shape[2]): 
			for c in range(self.n_classes): 
				# if (self.mu <= 0.).any():
				# 	print("BAAAAAAAA")

				# E_z_nc[n, c] = np.log(self.pi[c])
				# E_z_nc[n, c] += np.sum(np.multiply(np.log(self.mu[:,:,c]), imgs[:,:, n] ))
				# E_z_nc[n, c] += np.sum(np.multiply(np.log(1 - self.mu[:,:,c]), 1 - imgs[:,:, n] ))

				E_z_nc[n, c] = np.nanprod(
						np.multiply(
							np.power( self.mu[:,:,c], imgs[:,:, n] ), 
							np.power( (1 - self.mu[:, :, c]), (1 - imgs[:,:, n]) )
							))
				# plt.imshow(np.multiply(
				# 			np.power( self.mu[:,:,c], imgs[:,:, n] ), 
				# 			np.power( (1 - self.mu[:, :, c]), (1 - imgs[:,:, n]) )
				# 			))
				# plt.colorbar()
				# print(E_z_nc[n,c])
				# plt.show()
				E_z_nc[n, c] *= self.pi[c]


		# E_z_nc = np.log(E_z_nc)

		for c in range(self.n_classes): 
			# E_z_nc[:,c] -= np.log(np.sum(np.exp(E_z_nc), axis=1))
			E_z_nc[:, c] /= np.sum(E_z_nc, axis=1)

		return np.nan_to_num(E_z_nc)


	def maximization(self, E_z_nc): 
		N_c = np.sum(E_z_nc, axis=0)
		print(N_c)

		img_mean_c = np.ndarray((self.img_l, self.img_l, self.n_classes))
		for c in range(self.n_classes):
			img_mean_c[:, :,c] = E_z_nc[0, c] * self.imgs[:, :, 0]
			for n in range(1, self.n_imgs): 
				img_mean_c[:, :,c] += E_z_nc[n, c] * self.imgs[:, :, n]
		
		img_mean_c[:, :] /= N_c[c]

		self.mu = self.dumbify(np.nan_to_num(img_mean_c))
		self.pi = self.dumbify(np.nan_to_num(N_c / self.n_imgs))
		# self.pi = np.nan_to_num(N_c / np.sum(N_c))
		print(self.pi)
		print(np.sum(N_c))

	def run_once(self): 
		E_z_nc = self.expectation(self.imgs)
		self.maximization(E_z_nc)

	def __call__(self, imgs): 
		return self.expectation(imgs)


if __name__ == "__main__": 
	PREFIX = "/home/yop/Programmation/Projets/NCTUMachineLearning/HW02-NaiveBayesClassifier/datasets/"
	TRAIN_IMGS = PREFIX + "train-images-idx3-ubyte"
	TRAIN_LBLS = PREFIX + "train-labels-idx1-ubyte"
	imgs, lbls = parse_mnist_dataset(TRAIN_IMGS, TRAIN_LBLS)
	TEST_IMGS = PREFIX + "t10k-images-idx3-ubyte"
	TEST_LBLS = PREFIX + "t10k-labels-idx1-ubyte"
	t_imgs, t_lbls = parse_mnist_dataset(TEST_IMGS, TEST_LBLS)

	imgs = binarize_imgs(imgs)
	t_imgs = binarize_imgs(imgs)

	em = ExpectationMaximization(imgs[:,:,:1500], lbls[:1500])

	n_cols = 4
	n_rows = 3

	for i in range(1000): 
		em.run_once() 

		p = np.argmax(em(t_imgs[:,:,:100]), axis=0) 
		e = lbls[:100]

		plt.close()

		plt.subplot(n_rows,n_cols,1)
		plt.imshow(confusion_matrix(p,e))
		plt.colorbar()

		for j in range(2, n_cols * n_rows): 
			plt.subplot(n_rows,n_cols,j)
			plt.imshow(em.mu[:,:,j-2])

		plt.show(False)
