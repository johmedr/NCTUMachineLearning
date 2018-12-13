from graph_clustering import GraphClustering
from PCA import PCA
from utils import read_csv_mnist
from sklearn.cluster import SpectralClustering 

import numpy as np
from matplotlib import pyplot as plt


if __name__ == "__main__":
	PATH = '/home/yop/Programmation/Projets/NCTUMachineLearning/HW05-Clustering/homework#1-2018Spring/'

	X_TRAIN = PATH + 'X_train.csv'
	T_TRAIN = PATH + 'T_train.csv'
	X_TEST = PATH + 'X_test.csv'
	T_TEST = PATH + 'T_test.csv'

	train = {'imgs':[], 'lbls':[]}
	test = {'imgs':[], 'lbls':[]}

	train['imgs'], train['lbls'] = read_csv_mnist(X_TRAIN, T_TRAIN)
	test['imgs'], test['lbls'] = read_csv_mnist(X_TEST, T_TEST)

	rng_state = np.random.get_state()
	np.random.shuffle(train['imgs'])
	np.random.set_state(rng_state)
	np.random.shuffle(train['lbls'])

	cmap = ['m','b','g','c','r','k']

	# new_data = PCA(data, 2)
	# print(new_data.shape)
	# plt.subplot(1,2,1)
	# plt.scatter(data[:,0], data[:,1])
	# plt.subplot(1,2,2)
	# plt.scatter(new_data[:,0], new_data[:,1])
	# plt.axis([-10,5,-10,5])
	# plt.show()
	gamma = 0.1
	print("Building graph")

	kernels = [
		lambda x,y: np.exp(- 0.1 * np.linalg.norm(x-y, ord=2)**2) + np.dot(x, y.T),
		lambda x,y: (0.35355 * np.dot(x,y.T))**2, 
		lambda x,y: np.exp(- 0.05* np.linalg.norm(x-y, ord=2)**2), 
		lambda x,y: np.dot(x, y.T), 
	]

	imgs = train['imgs'][:1000]
	
	# for k in kernels:
	k = kernels[0]
	for i in range(10):
		# gc = GraphClustering(train['imgs'], nclusters=4, kernel=lambda x,y: np.exp(- 0.05 * np.linalg.norm(x-y, ord=2)**2))
		gc = GraphClustering(imgs, nclusters=4, kernel=k)

		# fig = plt.figure()
		# plt.subplot(1,2,1)
		# print("Graph built - cutting")
		# clusters = gc.normalized_cut()
		# print("Graph cutted - extracting PCA")

		# pca_data = PCA(imgs, 2)
		# print("PCA extracted - plotting results")

		# plt.scatter(pca_data[:,0], pca_data[:,1], c=[cmap[c] for c in clusters])

		# plt.subplot(1,2,2)
		print("Graph built - cutting")
		clusters2 = gc.ratio_cut()
		print("Graph cutted - extracting PCA")

		pca_data2 = PCA(imgs, 2)
		print("PCA extracted - plotting results")

		plt.scatter(pca_data2[:,0], pca_data2[:,1], c=[cmap[c] for c in clusters2])
		plt.show()
		plt.close()