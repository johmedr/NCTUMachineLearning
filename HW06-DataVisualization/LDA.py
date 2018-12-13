import numpy as np 
from utils import read_csv_mnist
from matplotlib import pyplot as plt

class LDA(object): 
    def __init__(self, data, labels, kdim=2): 
        if isinstance(data, list): 
            _data = np.array(data)
        else: 
            _data = data
        self.data = _data

        if isinstance(labels, list): 
            _labels = np.array(labels)
        else: 
            _labels = labels
        self.labels = _labels

        self.n_samples = self.data.shape[0]
        self.n_dim = self.data.shape[1]
        self.kdim = kdim

        self.W, self.means = self._compute_lda(self.data, self.labels, self.kdim)

    def _compute_lda(self, data, labels, kdim): 
        means = {}
        for l in np.unique(labels): 
            means[l] = np.mean(data[labels == l], axis=0)
        total_mean = np.mean(data, axis=0)

        # Sb = sum(nj * (mj-m).(mj.m)^T)
        Sb = np.zeros((data.shape[1], data.shape[1]))
        for l in means.keys(): 
            nj = data[labels==l].shape[0]
            means_diff = means[l] - total_mean
            Sb += nj * np.outer(means_diff, means_diff.T)

        # SW = sum Sj , where Sj = sum(xi-mj)(xi-mj).T
        Sw = np.zeros((data.shape[1], data.shape[1]))
        for l in means.keys(): 
            diff = data[labels==l] - means[l]
            Sw += np.dot(diff.T, diff)

        # M = Sw^-1 * Sb
        M = np.dot(np.linalg.pinv(Sw), Sb)
        eigval, eigvec = np.linalg.eig(M)
        print(eigval)
        eigen = sorted([(eigval[i], eigvec[:,i]) for i in range(len(eigval))], key=lambda t:t[0]) 
        eigen.reverse()

        W = np.ndarray((data.shape[1], kdim))

        for k in range(kdim): 
            W[:,k] = eigen[k][1]

        return W, means

    def project(self, data): 
        return np.dot(data, self.W)

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

    cmap = ['m','b','g','c','r','k']

    lda_data = LDA(train['imgs'], train['lbls']).project(train['imgs'])

    for l in range(np.max(train['lbls'])):
        mask = np.array(train['lbls']) == l
        plt.scatter(lda_data[mask,0], lda_data[mask,1], c=cmap[l], marker='$'+str(l)+'$')
    plt.show()