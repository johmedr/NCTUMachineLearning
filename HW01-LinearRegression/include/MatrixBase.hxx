#ifndef MATRIX_BASE_HXX
#define MATRIX_BASE_HXX

#include <cstddef> // size_t
#include <cassert>
#include <cmath>

#include <initializer_list>
#include <iostream>
#include <type_traits>

#include <MatrixExceptions.hxx>

namespace detail 
{
	template <typename Container2D, typename T, typename ConstructibleDerivedType>
	class MatrixBase; 
}

template <typename ConstructibleDerivedType>
typename std::enable_if< 
			std::is_base_of<
				typename ConstructibleDerivedType::base_type, 
				ConstructibleDerivedType 
			>::value,
		ConstructibleDerivedType >::type
eye(size_t dim);  

template <typename ConstructibleDerivedType>
typename std::enable_if< 
			std::is_base_of<
				typename ConstructibleDerivedType::base_type, 
				ConstructibleDerivedType 
			>::value,
		ConstructibleDerivedType >::type
zeros(size_t rows, size_t cols);

namespace detail
{
	template <typename Container2D, typename T, typename ConstructibleDerivedType>
	class MatrixBase
	{

	protected: 
		size_t _rows, _cols; 
		Container2D _m; 

		virtual inline void assert_valid_access(size_t i, size_t j) const;

		template <typename _Container2D, typename _T, typename _ConstructibleDerivedType>
		friend class MatrixBase;

	public: 
		using value_type = T; 
		using container_type = Container2D; 

		MatrixBase(size_t _rows, size_t cols, const Container2D & m); 

		virtual ~MatrixBase() = 0; 

		virtual inline const T& operator()(size_t i, size_t j) const; 
		virtual inline T& operator()(size_t i, size_t j); 

		virtual size_t rows() const final; 
		virtual size_t cols() const final; 

		virtual void fillWithZeros(); 

		virtual void print() const; 

		virtual MatrixBase<Container2D, T, ConstructibleDerivedType> & copy(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs); 

		virtual MatrixBase<Container2D, T, ConstructibleDerivedType> & operator+=(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs); 
		virtual MatrixBase<Container2D, T, ConstructibleDerivedType> & operator-=(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs); 
		virtual MatrixBase<Container2D, T, ConstructibleDerivedType> & operator*=(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs); 
		virtual MatrixBase<Container2D, T, ConstructibleDerivedType> & operator*=(const T & rhs); 

		/* TODO - Check if useful */ 
		virtual ConstructibleDerivedType operator+(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs) const; 
		virtual ConstructibleDerivedType operator-(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs) const; 
		virtual ConstructibleDerivedType operator*(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs) const; 
		virtual ConstructibleDerivedType operator*(const T & rhs) const; 
		
		virtual bool operator==(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs) const; 
		virtual bool operator!=(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs) const; 

		virtual ConstructibleDerivedType transpose() const;
		virtual void lu(ConstructibleDerivedType & lower, ConstructibleDerivedType & upper) const;  
		virtual ConstructibleDerivedType inverse() const;
	};
}

template <typename Container2D, typename T, typename ConstructibleDerivedType, typename TT>
inline 
typename std::enable_if< std::is_arithmetic<TT>::value, ConstructibleDerivedType >::type
operator*(const TT & lhs, const detail::MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs)
{
	return rhs * static_cast<const T &>(lhs); 
}

template <typename Container2D, typename T, typename ConstructibleDerivedType, typename TT = T>
inline 
TT norm2(const detail::MatrixBase<Container2D, T, ConstructibleDerivedType> & m); 

#include "../src/MatrixBase.tcc"

#endif