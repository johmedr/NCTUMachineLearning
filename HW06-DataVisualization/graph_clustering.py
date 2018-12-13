import numpy as np
from utils import read_csv_mnist, read_2d_csv_file
from KMean import KMeanClustering
from sklearn.cluster import KMeans
from matplotlib import pyplot as plt

import networkx as nx

def show_graph(W, D, points):
    # W = np.zeros((points.shape[0],points.shape[0]))
    # W[0,1] = 1
    edges = []
    nodes = list(range(W.shape[0]))
    nodes_pos = {i: points[i] for i in range(points.shape[0])}
    labels = {i:str(i) for i in range(points.shape[0])}
    gr = nx.Graph()
    for u in range(W.shape[0]):
        for v in range(W.shape[0]):
            if u != v: 
                edges.append((u,v,W[u,v]))
                gr.add_edge(u,v,weight=W[u,v])

    gr.add_nodes_from(nodes)
    nx.draw_networkx_nodes(gr, pos=nodes_pos)
    for (u,v,d) in gr.edges(data=True):
        nx.draw_networkx_edges(gr,pos=nodes_pos, edgelist=[(u,v)], width=d['weight'])
    plt.show()

class GraphClustering: 
    def __init__(self, data, nclusters=2, kernel=None, cut=None): 
        if isinstance(data, list): 
            _data = np.array(data, dtype=np.float64)
        elif isinstance(data, np.ndarray): 
            _data = data

        self.ndata = _data.shape[0]
        self.nclusters = nclusters
        self.data = _data.reshape((self.ndata, -1))
        self.kernel = kernel

        self.W = self._similarity_matrix(data)
        self.D = self._degree_matrix(self.W)
        self.L = self.D - self.W

    def _similarity_matrix(self, data): 
        W = np.ndarray((self.ndata, self.ndata), dtype=np.float64)

        for i in range(self.ndata): 
            for j in range(i+1): 
                W[i, j] = self.kernel(self.data[i], self.data[j])
                W[j, i] = W[i, j]
        print("Similarity matrix built")

        return W

    def _degree_matrix(self, W): 
        return np.diag(np.sum(W, axis=1) - np.diag(W)) 

    def ratio_cut(self, L=None, K=None): 
        if L is None: 
            L = self.L
        if K is None:
            K = self.nclusters

        eigval, eigvec = np.linalg.eigh(L)
        eigen = sorted([(eigval[i], eigvec[:,i]) for i in range(len(eigval))], key=lambda t:t[0]) 

        U = np.ndarray((self.ndata, K))

        for k in range(1,K+1): 
            U[:,k - 1] = eigen[k][1]

        km = KMeanClustering(U, self.nclusters).fit()
        return km.clusters

    def normalized_cut(self, D=None, L=None, K=None):
        if D is None: 
            D = self.D
        if L is None: 
            L = self.L
        if K is None:
            K = self.nclusters

        D1_2 = np.diag(np.diag(D)**-1./2)
        Lsym = D1_2.dot(L).dot(D1_2)

        eigval, eigvec = np.linalg.eigh(Lsym)
        eigen = sorted([(eigval[i], eigvec[:,i]) for i in range(len(eigval))], key=lambda t:t[0])  

        U = np.ndarray((self.ndata, K))
        for k in range(1,K+1):
            U[:,k - 1] = eigen[k][1]

        T = np.divide(U, np.repeat(np.linalg.norm(U, axis=1).reshape(self.ndata, 1), K, axis=1))
 
        km = KMeanClustering(T, self.nclusters).fit()
        return km.clusters


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

    colors = ['b','g','r','c','m','y','k','w']

    points = np.zeros((100, 2))
    points[:25] = np.random.normal([0.5,0.5],[.2,.2],(25,2))
    points[25:50] = np.random.normal([0.5,-0.5],[.2,.2],(25,2))
    points[50:75] = np.random.normal([-0.5,0.5],[.2,.2],(25,2))
    points[75:100] = np.random.normal([-0.5,-0.5],[.2,.2],(25,2))
    # points[:50] = np.random.normal([.5,.5],[.1,.1],(50,2))
    # points[50:100] = np.random.normal([-.5,-.5],[.1,.1],(50,2))
    np.random.shuffle(points)
    # points[:5] = np.random.normal([0.5,0.5],[.1,.1],(5,2))
    # points[5:10] = np.random.normal([-0.5,-0.5],[.1,.1],(5,2))

    # CIRCLE = PATH + 'circle.txt'
    # points = read_2d_csv_file(CIRCLE)

    MOON = PATH + 'moon.txt'
    points = read_2d_csv_file(MOON)
    # np.random.shuffle(points)

    points = points[:200]

    # points= train['imgs']

    gc = GraphClustering(points, 2, lambda x,y: np.exp(-50*np.linalg.norm(x-y)**2))
    # gc = GraphClustering(points, 2, lambda x1, x2: np.dot(x1, x2.T))

    # show_graph(gc.W, gc.D, points)
    plt.subplot(1, 3,1)
    plt.imshow(gc.W)
    plt.colorbar()
    plt.subplot(1, 3,2)
    plt.imshow(gc.D)
    plt.colorbar()
    plt.subplot(1, 3,3)
    plt.imshow(gc.L)
    plt.colorbar()

    plt.show()

    plt.subplot(1,2,1)
    clusters = gc.ratio_cut()
    plt.scatter(points[:,0], points[:,1], c=[colors[clus] for clus in clusters])

    plt.subplot(1,2,2)
    clusters = gc.normalized_cut() 
    plt.scatter(points[:,0], points[:,1], c=[colors[clus] for clus in clusters])
    plt.show() 


