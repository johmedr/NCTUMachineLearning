#ifndef LINALG_COMMON_H
#define LINALG_COMMON_H

#include <StaticMatrix.hxx>

// template <size_t Rows, size_t Cols, typename TA, typename TLU>
// void LUdecomp(const StaticMatrix<Rows, Cols, TA> & A, StaticMatrix<Rows, Cols, TLU> & L, StaticMatrix<Rows, Cols, TLU> & U);
template <size_t N, typename T, typename TLU = T>
void LUdecomp(const StaticMatrix<N, N, T> & mat, StaticMatrix<N, N, TLU> & lower, StaticMatrix<N, N, TLU> & upper); 

template <size_t N, typename T, typename TT = T> 
StaticMatrix<N, N, TT> inverse(const StaticMatrix<N, N, T> & mat); 

// template <size_t N_DATAS, size_t N_FEATURES, typename T, typename TT = T>
// StaticMatrix<N_FEATURES, 1, TT> linearRegression(const StaticMatrix<N_DATAS, N_FEATURES, T> & a, const StaticMatrix<N_DATAS, 1, T> & b, double lambda_l2); 

#include "../src/StaticLinAlgCommon.tcc"

#endif