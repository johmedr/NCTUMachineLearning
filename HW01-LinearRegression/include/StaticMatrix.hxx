#ifndef STATIC_MATRIX_HXX
#define STATIC_MATRIX_HXX

#include <cassert>
#include <initializer_list>
#include <iostream>
#include <array>
#include <algorithm>
#include <type_traits>

#include <MatrixExceptions.hxx>

template <size_t Rows, size_t Cols, typename T = float> 
class StaticMatrix
{
private: 
	std::array<std::array<T, Cols>, Rows> _m; 

public: 
	static const size_t rows = Rows; 
	static const size_t cols = Cols; 
	using dtype = T; 

public: 
	StaticMatrix();
	StaticMatrix(const std::initializer_list<std::initializer_list<T>> & l); 

	virtual ~StaticMatrix(); 

	inline const T& operator()(size_t i, size_t j) const; 
	inline T& operator()(size_t i, size_t j); 

	void fillWithZeros(); 

	void print() const; 

	template <typename TT>
	void copy(const StaticMatrix<Rows, Cols, TT>& rhs); 

	void copy(const StaticMatrix<Rows, Cols, T>& rhs); 

	template <typename TT = T>
	StaticMatrix<Rows, Cols, T>& operator+=(const StaticMatrix<Rows, Cols, TT>& rhs); 

	template <typename TT = T>
	StaticMatrix<Rows, Cols, T>& operator-=(const StaticMatrix<Rows, Cols, TT>& rhs); 

	template <typename TT = T> 
	typename std::enable_if< std::is_arithmetic<TT>::value, StaticMatrix<Rows, Cols, T> >::type &
	operator*=(const TT& rhs); 

	template <typename TT = T>
	StaticMatrix<Rows, Cols, T>& operator*=(const StaticMatrix<Cols, Cols, TT>& rhs); 

	StaticMatrix<Cols, Rows, T> transpose() const; 

	bool operator==(const StaticMatrix<Rows, Cols, T>& rhs) const;

	template <typename TT> 
	bool operator==(const StaticMatrix<Rows, Cols, TT>& rhs) const; 

	bool operator!=(const StaticMatrix<Rows, Cols, T>& rhs) const;

	template <typename TT> 
	bool operator!=(const StaticMatrix<Rows, Cols, TT>& rhs) const; 

	template <size_t _Rows = Rows, size_t _Cols = Cols, typename _T = T>
	static
	typename std::enable_if< _Rows != _Cols, StaticMatrix<_Rows, _Cols, _T> >::type
	eye(); 

	template <size_t _Rows = Rows, size_t _Cols = Cols, typename _T = T>
	static
	typename std::enable_if< _Rows == _Cols, StaticMatrix<_Rows, _Cols, _T> >::type
	eye(); 

	static StaticMatrix<Rows, Cols, T> zeros();

private:
	template <size_t _Rows, size_t _Cols, typename _TT>
	friend class StaticMatrix;
};

template <size_t Rows, size_t Cols, size_t ColsOther, typename T, typename TT>  
StaticMatrix<Rows, ColsOther, T> operator*(const StaticMatrix<Rows, Cols, T>& lhs, const StaticMatrix<Cols, ColsOther, TT>& rhs); 

template <size_t Rows, size_t Cols, typename T, typename TT>
inline 
typename std::enable_if< std::is_arithmetic<TT>::value, StaticMatrix<Rows, Cols, T> >::type
operator*(const StaticMatrix<Rows, Cols, T>& lhs, const TT& rhs); 

template <size_t Rows, size_t Cols, typename T, typename TT>
inline 
typename std::enable_if< std::is_arithmetic<TT>::value, StaticMatrix<Rows, Cols, T> >::type
operator*(const TT& lhs, const StaticMatrix<Rows, Cols, T>& rhs); 

template <size_t Rows, size_t Cols, typename T, typename TT>
inline
StaticMatrix<Rows, Cols, T> operator+(const StaticMatrix<Rows, Cols, T>&, const StaticMatrix<Rows, Cols, TT>& rhs); 

template <size_t Rows, size_t Cols, typename T, typename TT>
inline
StaticMatrix<Rows, Cols, T> operator-(const StaticMatrix<Rows, Cols, T>&, const StaticMatrix<Rows, Cols, TT>& rhs); 


#include <../src/StaticMatrix.tcc>

#endif