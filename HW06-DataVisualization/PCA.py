import numpy as np 
from utils import read_csv_mnist
from matplotlib import pyplot as plt

def PCA(data, kdim, norm=True): 
	if isinstance(data, list): 
		_data = np.asarray(data)
	elif isinstance(data, np.ndarray):
		_data = data

	x = _data.reshape((_data.shape[0],-1))
	_koriginal = x.shape[1]
	_kdim = min(kdim, _koriginal)

	S = np.cov(x, rowvar=False)
	D, V = np.linalg.eigh(S)

	W = np.ndarray((_koriginal, _kdim))

	for i in range(kdim): 
		dmax = np.argmax(D)

		W[:,i] = V[:,dmax]
		D[dmax] = -1
	return np.dot(x, W) 

if __name__ == '__main__':
	PATH = '/home/yop/Programmation/Projets/NCTUMachineLearning/HW05-Clustering/homework#1-2018Spring/'

	X_TRAIN = PATH + 'X_train.csv'
	T_TRAIN = PATH + 'T_train.csv'
	X_TEST = PATH + 'X_test.csv'
	T_TEST = PATH + 'T_test.csv'

	train = {'imgs':[], 'lbls':[]}
	test = {'imgs':[], 'lbls':[]}

	train['imgs'], train['lbls'] = read_csv_mnist(X_TRAIN, T_TRAIN)
	test['imgs'], test['lbls'] = read_csv_mnist(X_TEST, T_TEST)

	data = np.ndarray((100,2))
	data[:,0] = np.linspace(0,5,100) + np.random.normal(0,1,100)
	data[:,1] = data[:,0] * 2. + np.random.normal(0,1,100) - 1

	cmap = ['C' + str(i) for i in range(10)]

	# new_data = PCA(data, 2)
	# print(new_data.shape)
	# plt.subplot(1,2,1)
	# plt.scatter(data[:,0], data[:,1])
	# plt.subplot(1,2,2)
	# plt.scatter(new_data[:,0], new_data[:,1])
	# plt.axis([-10,5,-10,5])
	# plt.show()
	pca_data = PCA(train['imgs'], 2)
	for l in range(np.max(train['lbls'])):
		mask = np.array(train['lbls']) == l
		plt.scatter(pca_data[mask,0], pca_data[mask,1], c=cmap[l], marker='$'+str(l)+'$')
	plt.show()