import numpy as np

def read_2d_csv_file(filename): 
	vals = []

	with open(filename, 'r') as f:
		for l in f: 
			vals.append([float(t) for t in l.split(',')])

	return np.array(vals)

def read_csv_mnist(imgs_filename, lbls_filename): 
	imgs = []
	lbls = []

	with open(imgs_filename, 'r') as f: 
		for l in f: 
			imgs.append([float(t) for t in l.split(',')])

	with open(lbls_filename, 'r') as f: 
		for l in f: 
			lbls.append(int(l))

	assert(len(imgs) == len(lbls))

	return imgs, lbls 
