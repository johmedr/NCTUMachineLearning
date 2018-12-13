import numpy as np
from matplotlib import pyplot as plt

from svmutil import *
from svm import *

from utils import read_csv_mnist
from PCA import PCA

from sklearn import svm

def sparse_to_dense_array(array, dim):
    if isinstance(array, dict):
        dense = array[-1] * np.ones((dim,))
        for k in array: 
            if k != -1:
                dense[k] = array[k]
        return dense
    elif isinstance(array, list): 
        dense_list = []
        for a in array:
            dense_list.append(sparse_to_dense_array(a, dim)) 
        return dense_list

PATH = '/home/yop/Programmation/Projets/NCTUMachineLearning/HW05-Clustering/homework#1-2018Spring/'

X_TRAIN = PATH + 'X_train.csv'
T_TRAIN = PATH + 'T_train.csv'
X_TEST = PATH + 'X_test.csv'
T_TEST = PATH + 'T_test.csv'

train = {'imgs':[], 'lbls':[]}
test = {'imgs':[], 'lbls':[]}



train['imgs'], train['lbls'] = read_csv_mnist(X_TRAIN, T_TRAIN)
test['imgs'], test['lbls'] = read_csv_mnist(X_TEST, T_TEST)

# np.random.shuffle(train['imgs'])

data = np.asarray(train['imgs'])
labels =  train['lbls']

def make_kmat(kernel, data):
    if isinstance(data, list): 
        data = np.asarray(data)
    n_samples = len(data)
    gram = np.zeros((n_samples, n_samples))
    for i in range(n_samples): 
        for j in range(i+1): 
            gram[i, j] = kernel(data[i], data[j])
            gram[j,i] = gram[i,j]
    return gram

best_params = (0,0)
best_acc = 0
gamma = 0.1
C = 0.021544
# for C in np.linspace(0.021544,50,5): 
#     for gamma in np.logspace(-7,2,10):
#         print("gamma : %f, C : %f"%(gamma, C))
def kernel(x,y): 
    term = np.dot(x, y.T)
    for i in range(term.shape[0]):
        for j in range(i+1): 
            k = np.exp(- gamma * np.linalg.norm(x[i]-y[j], ord=2)**2)
            term[i,j] += k
            term[j,i] += k
    return term
# m = svm_train(labels , data,'-s 0 -t 1 -c 5 -g 0.05 -q')
# clf = svm.SVC(kernel='rbf', C=5, gamma=0.05)
# clf.fit(data, labels)
# print("accuracy : %f"%(np.mean(clf.predict(test['imgs'])==test['lbls'])))

clf = svm.SVC(C=C, kernel=kernel)
clf.fit(data, labels)
# print("accuracy : %f"%(np.mean(clf.predict(make_kmat(lambda x, y: np.dot(x, y.T) + np.exp(- 0.05 * np.linalg.norm(x-y, ord=2)**2), test['imgs']))==test['lbls'])))
# sv = clf.support_vectors_
acc = np.mean(clf.predict(test["imgs"])==test['lbls'])
print("accuracy : %f"%(acc))
if acc > best_acc: 
    best_acc = acc
    best_params = (gamma, C)
    print('new best : ' + str(best_params))


# sv = sparse_to_dense_array(m.get_SV(), 784)
# sv = np.asarray(sv)

mnist_2d = PCA(data, 2)

sp_points = mnist_2d[clf.support_]

not_sp_points =  np.delete(mnist_2d, clf.support_,axis=0)

# mask = mnist_2d[:,0] == mnist_2d[:,0]
# for i in range(mnist_2d.shape[0]): 
#     if np.isclose(mnist_2d[i,0], sv_2d[:,0], atol=1e-2).any() or np.isclose(mnist_2d[i,0],sv_2d[:,0], atol=1e-2).any():
#         mask[i] = False

# mnist_2d = mnist_2d[mask]
# for i in range(sv_2d.shape[0]): 
#     mask = (mnist_2d[:,0] != sv_2d[i, 0]) 
#     print(mask.shape)
#     mnist_2d = mnist_2d[mnist_2d != sv_2d[i]]


plt.scatter(sp_points[:,0], sp_points[:,1], marker='o')
plt.scatter(not_sp_points[:,0], not_sp_points[:,1], marker='x')
plt.show()
