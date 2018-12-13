import numpy as np

class KMeanClustering(object): 
	def __init__(self, points, K, centroids=None): 
		self.points = points
		self.N = self.points.shape[0]
		self.K = K

		if centroids is None: 
			centroids = points[np.random.randint(0, self.N, self.K)]
		self.centroids = centroids

		self.distances = self._dist_points_centroids(self.centroids) 
		self.clusters = self._assign(self.distances)
		self.groups = self._group(self.clusters)
		self.converged = False

	def _dist_points_centroids(self, centroids):
		return np.array([
			[np.linalg.norm((self.points[i] - c),ord=2) for c in centroids] 
				for i in range(self.N)]) 

	def _assign(self, distances): 
		return np.argmin(distances, axis=1)

	def _compute_centroids(self, clusters):
		return np.array([
			np.mean(self.points[clusters == i], axis=0) if self.points[clusters == i].shape[0] > 0 
				else self.centroids[i] for i in range(self.K)])

	def _group(self, clusters):
		return set([frozenset(np.arange(self.N)[clusters == c]) for c in range(self.K)])

	def iterate(self): 
		if not self.converged: 
			centroids = self._compute_centroids(self.clusters) 
			distances = self._dist_points_centroids(centroids)
			clusters = self._assign(distances)
			groups = self._group(clusters)

			if groups != self.groups: 
				self.centroids = centroids
				self.distances = distances
				self.clusters = clusters
				self.groups = groups
			else: 
				self.converged = True
		else: 
			print('Tried to iterate but algorithm as already converged !')

