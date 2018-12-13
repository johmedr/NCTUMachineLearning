#ifndef LINEAR_REGRESSION_HXX
#define LINEAR_REGRESSION_HXX

#include <cmath>

#include <StaticMatrix.hxx>
#include <DynamicMatrix.hxx>

#include <StaticLinAlgCommon.hxx>

template <size_t N_DATAS, size_t N_FEATURES, typename T, typename TT = T>
StaticMatrix<N_FEATURES, 1, TT> linearRegression(const StaticMatrix<N_DATAS, N_FEATURES, T> & a, const StaticMatrix<N_DATAS, 1, T> & b, double lambda_l2); 

template <typename T, typename LT = double>
Matrix<T> linearRegression(const Matrix<T> & a, const Matrix<T> & b, LT lambda_l2); 

template <typename T, typename NT = size_t> 
Matrix<T> polynomialDesignMatrix(const Matrix<T> & data, NT order_n);  

template <typename T, typename TT = T>
TT leastSquareError(const Matrix<T> & a, const Matrix<T> & x, const Matrix<T> & b);

template <typename T>
Matrix<T> newtonDescent(const Matrix<T> & a, const Matrix<T> & b); 

#include "../src/LinearRegression.tcc"

#endif