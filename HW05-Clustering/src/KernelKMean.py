import numpy as np
from matplotlib import pyplot as plt

class KernelKMeanClustering(object): 
	def __init__(self, points, K, kernel=None, gram=None): 
		self.points = points
		self.N = self.points.shape[0]
		self.K = K

		self.kernel = kernel
		if gram is None and kernel is not None: 
			self.gram = self._compute_gram_matrix()
		elif kernel is None and gram is not None:
			self.gram = gram

		# self.clusters = self._initial_clustering()
		self.clusters = np.random.randint(0, self.K, self.N)
		self.groups = self._group(self.clusters)
		self.distances = None

		self.converged = False

	def _compute_gram_matrix(self): 
		gram = np.ndarray((self.N, self.N), dtype=float)

		for i in range(self.N): 
			for j in range(i+1): 
				gram[i, j] = self.kernel(self.points[i], self.points[j])
		for i in range(self.N):
			for j in range(i+1,self.N): 
				gram[i,j] = gram[j,i]

		# plt.imshow(gram)
		# plt.colorbar()
		# plt.show()

		return gram


	def _initial_clustering(self): 
		centroids = self.points[np.random.randint(0, self.N, self.K)]
		distances = np.array([[np.linalg.norm((self.points[i] - c),ord=2) 
			for c in centroids] 
				for i in range(self.N)]) 

		return self._assign(distances)

	def _compute_distances(self, clusters): 
		distances = np.ndarray((self.N, self.K))

		for k in range(self.K): 
			mask = clusters == k

			clust_len = np.sum(mask, dtype=float)
			if clust_len == 0: 
				print("Empty cluster")
				continue

			clust_dist = np.sum(self.gram[mask][:,mask], dtype=float) / clust_len**2

			for j in range(self.N):
				dist = self.gram[j, j] + clust_dist
				dist -= 2. * np.sum(self.gram[j, mask], dtype=float) / clust_len

				distances[j,k] = dist

		return distances

	def _assign(self, distances): 
		return np.argmin(distances, axis=1)

	def _group(self, clusters):
		return set([frozenset(np.arange(self.N)[clusters == c]) for c in range(self.K)])

	def iterate(self): 
		if not self.converged: 
			distances = self._compute_distances(self.clusters)
			clusters = self._assign(distances)
			groups = self._group(clusters)

			if groups != self.groups: 
				self.distances = distances
				self.clusters = clusters
				self.groups = groups
			else: 
				self.converged = True
		else: 
			print('Tried to iterate but algorithm as already converged !')

