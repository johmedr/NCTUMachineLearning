import numpy as np
from matplotlib import pyplot as plt

from svmutil import *
from svm import *

from utils import read_csv_mnist

class KFold: 
    def __init__(self, K): 
        self.K = int(K) 

    def split(self, data): 
        fold_length = len(data) / self.K
        batchs = []
        ref = set(range(len(data)))
        for k in range(self.K):
            test_index = set(range(int(k * fold_length), int((k + 1) * fold_length)))
            batchs.append((test_index,(ref - test_index)))
        return batchs


# if __name__ == '__main__': 
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

res_c = 5
res_g = 5

C = np.logspace(-5,15,res_c, base=2.)
G = np.logspace(-15,3,res_g, base=2.)
D = np.linspace(1,5,res_c)


# res_c = 5
# res_g = 5

# C = np.space(820,1680,res_c)
# G = np.space(0.27,0.49,res_g)

X, Y = np.meshgrid(C, G)
Z = np.ndarray((res_c, res_g), dtype=float)
Acc = np.ndarray((5,5,5), dtype=float)

r = 0

kfold = KFold(5)

step = 0
for train_index, test_index in kfold.split(train['imgs']): 
    step +=1
    print(step)

    train_lbls_batch = [train['lbls'][i] for i in train_index]
    train_imgs_batch = [train['imgs'][i] for i in train_index]
    test_lbls_batch =  [train['lbls'][i] for i in test_index]
    test_imgs_batch =  [train['imgs'][i] for i in test_index]

    for i in range(len(C)): 
        for j in range(len(G)):
            for k in range(len(D)):
                print((i,j,k))

                c = C[i]
                g = G[j]
                d = D[k]

                acc = 0.

                # m = svm_train(train_lbls_batch, train_imgs_batch,'-s 0 -t 0 -c %f -g %f -r %f -q'%(c,g,r))
                m = svm_train(train_lbls_batch, train_imgs_batch,'-s 0 -t 1 -c %f -g %f -r %f -d %d -q'%(c,g,r,d))
                p_label, p_acc, p_val = svm_predict(test_lbls_batch, test_imgs_batch, m)
                Acc[i,j,k] += p_acc[0]

Acc /= float(kfold.K)

Z = np.argmax(Acc, axis=2)

c = plt.contourf(X,Y,Z,cmap=plt.cm.BuPu, vmin=80, vmax=100)
plt.colorbar(c)
plt.show() 
