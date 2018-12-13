#ifndef DYNAMIC_MATRIX_HXX
#define DYNAMIC_MATRIX_HXX

#include <MatrixBase.hxx> 

#include <vector>
#include <initializer_list>
#include <cassert>

template <typename T = float> 
class Matrix : public detail::MatrixBase<std::vector< std::vector<T> >, T, Matrix<T>>
{
public:
	using base_type = detail::MatrixBase<std::vector< std::vector<T> >, T, Matrix<T>>;
	using value_type = typename base_type::value_type; 
	using container_type = typename base_type::container_type; 

protected : 
	using base_type::_m;
	using base_type::_rows; 
	using base_type::_cols;

public: 

	Matrix(size_t rows = 1, size_t cols = 1);
	Matrix(const std::initializer_list<std::initializer_list<T>> & l);

	virtual ~Matrix();

	virtual Matrix<T> & copy(const base_type & rhs) override; 

	virtual Matrix<T> & reshape(size_t rows, size_t cols); 
};

#include "../src/DynamicMatrix.tcc"

#endif