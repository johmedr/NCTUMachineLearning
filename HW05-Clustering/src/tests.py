import time
import numpy as np
from matplotlib import pyplot as plt

from utils import read_2d_csv_file
from KMean import KMeanClustering
from KernelKMean import KernelKMeanClustering


if __name__ == "__main__":
	N = 100
	K = 4
	# points = np.random.rand(N,2)
	points = np.ndarray((N, 2))
	points[:25] = np.random.normal([0.5,0.5],[.2,.2],(25,2))
	points[25:50] = np.random.normal([0.5,-0.5],[.2,.2],(25,2))
	points[50:75] = np.random.normal([-0.5,0.5],[.2,.2],(25,2))
	points[75:100] = np.random.normal([-0.5,-0.5],[.2,.2],(25,2))

	PATH = '/home/yop/Programmation/Projets/NCTUMachineLearning/HW05-Clustering/homework#1-2018Spring/'
	CIRCLE = PATH + 'circle.txt'
	MOON = PATH + 'moon.txt'
	# points = read_2d_csv_file(CIRCLE)
	# points = read_2d_csv_file(MOON)
	colors = ['b','g','r','c','m','y','k','w']

	# res = 100
	# x = np.linspace(np.min(points[:,0]), np.max(points[:,0]), res)
	# y = np.linspace(np.min(points[:,1]), np.max(points[:,1]), res)
	# X, Y = np.meshgrid(x, y)


# for gamma in np.logspace(-15,2,15):
	# K = 5
	# km = KMeanClustering(points, K)


	# trial = 0
	# while not km.converged: 
	# 	plt.close()
	# 	f = plt.figure()
	# 	plt.scatter(points[:,0], points[:,1], c=[colors[clus] for clus in km.clusters])
	# 	# plt.show(False)
	# 	trial+=1
	# 	f.savefig('km_K%d_trial_%d.png'%(K, trial))
	# 	km.iterate() 

	# exit(0)
gamma = 2

print("gamma = " + str(gamma))

kms = [KernelKMeanClustering(points, 4, kernel=lambda x,y: np.exp(-gamma*np.linalg.norm(x-y, ord=2)**2))]
# kms = [KernelKMeanClustering(points, 2, kernel=lambda x,y:(np.dot(x.transpose(),y)**2))]

kms += [KernelKMeanClustering(points, 4, gram=kms[0].gram)
	for i in range(9)] 


s = 0
while not np.all([km.converged for km in kms]) and s < 100: 
	# print(s)
	s+=1
	plt.close()
	f = plt.figure()
	for i in range(len(kms)):
		plt.subplot(2,5,i+1)
		plt.scatter(points[:,0], points[:,1], c=[colors[clus] for clus in kms[i].clusters])
		plt.axis('off')

	f.savefig('blop_kkm_K%d_trial_%d.png'%(K, s))
	# plt.show(False)
	for i in range(len(kms)):
		if not kms[i].converged: 
			kms[i].iterate()

f = plt.figure()
for i in range(len(kms)):
	plt.subplot(2,5,i+1)
	plt.scatter(points[:,0], points[:,1], c=[colors[clus] for clus in kms[i].clusters])
f.savefig('circle_kernel_gamma_' + str(gamma) + '.png')
plt.show()
