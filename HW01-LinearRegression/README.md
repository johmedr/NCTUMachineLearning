# NCTUMachineLearningSpring2018

## Build the project : 
### 1. Clone the repository
``` 
git clone https://github.com/yop0/NCTUMachineLearningSpring2018.git
```
### 2. Generate the build tools 
```
cd /path\ to\ NCTUMachineLearningSpring2018
mkdir build && cd build
cmake ..
``` 
### 3. Make the executable
``` 
make -j4 
``` 
*Optionnal* : Run tests
``` 
make all_tests -j4
```
### 4. Use the built command line interface 
```
./path\ to\ NCTUMachineLearningSpring2018/build/bin/linreg -f <relative path to sample_filename> [-n <polynomial order>] [-l <L2 regularization term>]
``` 

## About the sample file
The file must contain a list of points (x, y). 
Each line represents a point, and x and y are separated by a comma (no space). 
For example : 
```
9.56,12.87
23.2,192.12
42.8,1087.95
```
