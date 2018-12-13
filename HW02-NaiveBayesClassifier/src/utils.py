import numpy as np 
from matplotlib import pyplot as plt

NLABELS = 10

class log_gaussian(object): 
	def __init__(self, mu, sigma2): 
		self.mu = float(mu)
		self.sigma2 = float(sigma2)

	def __call__(self, x): 
		if self.sigma2 != 0:
			return - 1/2 * np.log(2 * np.pi) - 1/2 * np.log(self.sigma2) - 1/2. * ( (x - self.mu) ** 2 )/ self.sigma2
		elif x == self.mu: 
			return 1
		else: 
			return 0

def pltmat(mat): 
	plt.imshow(mat, interpolation='none', cmap='inferno')	
	plt.show() 

def label_frequency(labels): 
	return np.array([np.mean(labels == l) for l in range(NLABELS)])

def bins_per_label(imgs, lbls, nbins=32, maxvalue=255.):

	bins_per_label = np.ndarray((NLABELS, nbins, 28, 28), dtype=np.float)
	pixels_bin_index = np.around(np.asarray(imgs, dtype=float) * (nbins - 1) / float(maxvalue))

	for l in range(NLABELS):
		current_imgs = pixels_bin_index[:, :, lbls == l]
		for b in range(nbins): 
			for x in range(28): 
				for y in range(28): 
					bins_per_label[l, b, x, y] = current_imgs[ x, y, current_imgs[x, y] == b].shape[0]
	print(np.sum(bins_per_label))
	return bins_per_label

def gaussian_per_label(imgs, lbls): 
	gaussian_per_label = list(range(NLABELS))
	for l in range(NLABELS): 
		current_imgs = imgs[:, :, lbls == l]
		print(np.max(current_imgs))
		gaussian_per_label[l] = {
			'mean': current_imgs.mean(axis=2, dtype=np.float),
			'var': np.mean(current_imgs**2, axis=2, dtype=np.float) - np.mean(current_imgs, axis=2, dtype=np.float)**2
		}
		# pltmat(gaussian_per_label[l]['mean'])
		# pltmat(gaussian_per_label[l]['var'])
	return gaussian_per_label



# def discrete_approach(imgs, labels, nb_bins=32, max_value=255): 
# 	if imgs.shape[2] != labels.shape[0]: 
# 		raise Exception("Images and shapes have not the same length !")

# 	px_fq_per_bins = np.zeros((NLABELS, nb_bins, imgs.shape[0], imgs.shape[1]), dtype=np.float)
# 	count_per_label = np.zeros(NLABELS, dtype=np.float)

# 	index = np.around(imgs * float((nb_bins - 1.) / max_value))

# 	for x in range(imgs.shape[0]): 
# 		for y in range(imgs.shape[1]): 
# 			for i in range(imgs.shape[2]): 
# 				px_fq_per_bins[labels[i], int(index[x, y, i]), x, y] += 1.
# 				count_per_label[labels[i]] += 1.

# 	for l in range(NLABELS): 
# 		if count_per_label[l] != 0:
# 			px_fq_per_bins[l] /= count_per_label[l]

# 	logpx_fq_per_bins = np.log(px_fq_per_bins)

# 	bin_index = lambda v:  int(round(v * float((nb_bins - 1) / max_value)))

# 	logp_px_gv_label = [[[lambda v: logpx_fq_per_bins[l, bin_index(v), x, y]\
# 		for y in range(imgs.shape[1]) ]\
# 			for x in range(imgs.shape[0]) ]\
# 				for l in range(NLABELS)]\

# 	return logp_px_gv_label 

# def continuous_approach(imgs, labels): 
# 	if imgs.shape[2] != labels.shape[0]: 
# 		raise Exception("Images and shapes have not the same length !")

# 	ndata = imgs.shape[2]

# 	count_per_label = np.zeros(NLABELS)
# 	mean_per_label = np.zeros((NLABELS, 28, 28), dtype=np.float)

# 	for i in range(ndata): 
# 		count_per_label[labels[i]] += 1
# 		mean_per_label[labels[i]] = mean_per_label[labels[i]] + imgs[:, :, i]

# 	for l in range(NLABELS):
# 		mean_per_label[l] /= float(count_per_label[l])

# 	var_per_label = np.zeros((NLABELS, 28, 28), dtype=np.float)

# 	for i in range(ndata):
# 		l = labels[i]
# 		var_per_label[l] += np.power( (imgs[:, :, i] - mean_per_label[l]), 2 )

# 	for l in range(NLABELS):
# 		var_per_label[l] /= float(count_per_label[l])

# 	logp_px_gv_label = [[[log_gaussian(mean_per_label[l, x, y], var_per_label[l, x, y])\
# 		for y in range(imgs.shape[1]) ] \
# 			for x in range(imgs.shape[0]) ]\
# 				for l in range(NLABELS) ] 

# 	return logp_px_gv_label

