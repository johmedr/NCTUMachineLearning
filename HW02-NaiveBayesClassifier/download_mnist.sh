#!/bin/bash
if [ ! -d "datasets" ]; 
then 
	mkdir datasets; 
fi 

function dl_dataset() {
	if [ ! -f datasets/$1.gz ] && [ ! -f datasets/$1 ] 
	then 
		wget -P datasets http://yann.lecun.com/exdb/mnist/$1.gz
	fi 

	if [ ! -f datasets/$1 ]
	then 
		gzip -d datasets/$1
	fi
}

dl_dataset train-images-idx3-ubyte
dl_dataset train-labels-idx1-ubyte
dl_dataset t10k-images-idx3-ubyte
dl_dataset t10k-labels-idx1-ubyte

# if [ ! -f datasets/train-images-idx3-ubyte.gz ] && [ ! -f datasets/train-images-idx3-ubyte ] 
# then 
# 	wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
# fi 

# if [ ! -f datasets/train-images-idx3-ubyte.gz ] && [ ! -f datasets/train-images-idx3-ubyte ] 
# then 
# 	wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
# fi 

# if [ ! -f datasets/train-images-idx3-ubyte.gz ] && [ ! -f datasets/train-images-idx3-ubyte ] 
# then 
# 	wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
# fi 

# if [ ! -f datasets/train-images-idx3-ubyte.gz ] && [ ! -f datasets/train-images-idx3-ubyte ] 
# then 
# 	wget http://yann.lecun.com/exdb/mnist/train-images-idx3-ubyte.gz
# fi 