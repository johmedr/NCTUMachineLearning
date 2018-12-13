namespace detail 
{
	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	MatrixBase<Container2D, T, ConstructibleDerivedType>::MatrixBase(size_t rows_, size_t cols_, const Container2D & m) : 
		_rows(rows_), _cols(cols_), _m(m)
	{}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	MatrixBase<Container2D, T, ConstructibleDerivedType>::~MatrixBase() 
	{} 

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	void MatrixBase<Container2D, T, ConstructibleDerivedType>::assert_valid_access(size_t i, size_t j) const
	{
		assert(i < _rows && j < _cols); 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	const T& MatrixBase<Container2D, T, ConstructibleDerivedType>::operator()(size_t i, size_t j) const
	{
		assert_valid_access(i, j);
		return _m[i][j];
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	T& MatrixBase<Container2D, T, ConstructibleDerivedType>::operator()(size_t i, size_t j) 
	{
		assert_valid_access(i, j);
		return _m[i][j];
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	size_t MatrixBase<Container2D, T, ConstructibleDerivedType>::rows() const
	{
		return _rows; 
	}
	
	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	size_t MatrixBase<Container2D, T, ConstructibleDerivedType>::cols() const
	{
		return _cols;
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	void MatrixBase<Container2D, T, ConstructibleDerivedType>::fillWithZeros()
	{
		for(size_t i = 0; i < _rows; ++i) 
			for(size_t j = 0; j < _cols; ++j) 
				_m[i][j] = 0; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	void MatrixBase<Container2D, T, ConstructibleDerivedType>::print() const
	{
		std::cout << "[";
		for(size_t i = 0; i < _rows; ++i) 
		{
			std::cout << "[";

			for(size_t j = 0; j < _cols - 1; ++j) 
			{
				std::cout << _m[i][j] << ", ";
			}
			std::cout << _m[i][_cols - 1];

			std::cout << "]," << std::endl; 
		}
		std::cout << "]" << std::endl; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	MatrixBase<Container2D, T, ConstructibleDerivedType> & MatrixBase<Container2D, T, ConstructibleDerivedType>::copy(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs)
	{
		assert(rhs.rows() == _rows && rhs.cols() == _cols);

		for(size_t i = 0; i < _rows; ++i) 
			for(size_t j = 0; j < _cols; ++j) 
				_m[i][j] = rhs(i, j);
		return (*this);
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	MatrixBase<Container2D, T, ConstructibleDerivedType> & MatrixBase<Container2D, T, ConstructibleDerivedType>::operator+=(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs) 
	{
		assert(rhs.rows() == _rows && rhs.cols() == _cols);

		for(size_t i = 0; i < _rows; ++i) 
			for(size_t j = 0; j < _cols; ++j) 
				_m[i][j] += rhs(i, j); 
		return *this; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	MatrixBase<Container2D, T, ConstructibleDerivedType> & MatrixBase<Container2D, T, ConstructibleDerivedType>::operator-=(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs)
	{
		assert(rhs.rows() == _rows && rhs.cols() == _cols);

		for(size_t i = 0; i < _rows; ++i) 
			for(size_t j = 0; j < _cols; ++j) 
				_m[i][j] -= rhs(i, j); 
		return *this; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	MatrixBase<Container2D, T, ConstructibleDerivedType> & MatrixBase<Container2D, T, ConstructibleDerivedType>::operator*=(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs)
	{
		assert(_cols == rhs.rows() && rhs.cols() == rhs.rows());

		ConstructibleDerivedType m;
		m.copy(*this); 

		for(size_t i = 0; i < _rows; ++i) 
			for(size_t j = 0; j < rhs.cols(); ++j) {
				_m[i][j] = 0; 
				for(size_t k = 0; k < _cols; ++k)
					_m[i][j] += m(i, k) * rhs(k, j);
			}

		return *this; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	MatrixBase<Container2D, T, ConstructibleDerivedType> & MatrixBase<Container2D, T, ConstructibleDerivedType>::operator*=(const T & rhs)
	{
		for(size_t i = 0; i < _rows; ++i)
			for(size_t j = 0; j < _cols; ++j) 
				_m[i][j] *= rhs; 
		return *this; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	ConstructibleDerivedType MatrixBase<Container2D, T, ConstructibleDerivedType>::operator+(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs) const
	{
		ConstructibleDerivedType m(_rows, _cols); 
		m.copy(*this); 
		m += rhs; 
		return m; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	ConstructibleDerivedType MatrixBase<Container2D, T, ConstructibleDerivedType>::operator-(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs) const
	{
		ConstructibleDerivedType m(_rows, _cols); 
		m.copy(*this); 
		m -= rhs;
		return m; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	ConstructibleDerivedType MatrixBase<Container2D, T, ConstructibleDerivedType>::operator*(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs) const
	{
		assert(_cols == rhs.rows());
		ConstructibleDerivedType m(_rows, rhs.cols()); 

		for(size_t i = 0; i < _rows; ++i) 
			for(size_t j = 0; j < rhs.cols(); ++j) {
				m(i, j) = 0;
				for(size_t k = 0; k < _cols; ++k)
					m(i, j) += _m[i][k] * rhs(k, j);
			}

		return m; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	ConstructibleDerivedType MatrixBase<Container2D, T, ConstructibleDerivedType>::operator*(const T & rhs) const
	{
		ConstructibleDerivedType m(_rows, _cols); 
		m.copy(*this); 
		m *= rhs;
		return m; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	bool MatrixBase<Container2D, T, ConstructibleDerivedType>::operator==(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs) const
	{
		assert(rhs.rows() == _rows && rhs.cols() == _cols);

		for(size_t i = 0; i < _rows; ++i)
			for(size_t j = 0; j < _cols; ++j)
				if( _m[i][j] != rhs(i, j) )
					return false; 
		return true; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	bool MatrixBase<Container2D, T, ConstructibleDerivedType>::operator!=(const MatrixBase<Container2D, T, ConstructibleDerivedType> & rhs) const
	{
		assert(rhs.rows() == _rows && rhs.cols() == _cols);

		for(size_t i = 0; i < _rows; ++i)
			for(size_t j = 0; j < _cols; ++j)
				if( _m[i][j] != rhs(i, j) ) 
					return true; 
		return false;  
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	ConstructibleDerivedType MatrixBase<Container2D, T, ConstructibleDerivedType>::transpose() const
	{
		ConstructibleDerivedType m(_cols, _rows); 
		m.fillWithZeros(); 

		for(size_t i = 0; i < _rows; ++i) 
			for(size_t j = 0; j < _cols; ++j) 
				m(j, i) = _m[i][j]; 

		return m; 
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	void MatrixBase<Container2D, T, ConstructibleDerivedType>::lu(ConstructibleDerivedType & lower, ConstructibleDerivedType & upper) const
	{
		assert(_rows == _cols); 
		size_t N = _rows; 

		if(lower.rows() != N || lower.cols() != N)
			lower.reshape(N, N); 

		if(upper.rows() != N || upper.cols() != N)
			upper.reshape(N, N); 

		lower.fillWithZeros(); 
		upper.fillWithZeros(); 

		T sum; 
		size_t i, j, k; 

		for(i = 0; i < N; ++i) 
		{
			for(j = i; j < N; ++j) 
			{
				sum = 0; 

				for(k = 0; k < i; ++k) {
					sum += lower(i, k) * upper(k, j); 
				}

				upper(i, j) = _m[i][j] - sum; 
			}

			lower(i, i) = 1; 
			for(j = i; j < N; ++j)
			{
				sum = 0; 

				for(k = 0; k < i; ++k) {
					sum += lower(j, k) * upper(k, i); 
				}

				if(upper(i, i) != 0)
					lower(j, i) = (_m[j][i] - sum) / upper(i, i); 
				else 
					throw singular_matrix_error(); 
			}
		}
	}

	template <typename Container2D, typename T, typename ConstructibleDerivedType> 
	ConstructibleDerivedType MatrixBase<Container2D, T, ConstructibleDerivedType>::inverse() const
	{		
		assert(_rows == _cols); 
		size_t N = _rows; 

		ConstructibleDerivedType l(N, N), u(N, N); 

		try {
			lu(l, u);
		} catch(const std::exception & e) {
			throw; 
		}

		size_t i, j, k; 
		auto eyen = ::eye<ConstructibleDerivedType>(N); 
		ConstructibleDerivedType z(N, N), matinv(N, N); 
		T sum; 

		for(i = 0; i < N; ++i) 
		{
			for(j = 0; j < N; ++j)
			{
				sum = 0; 

				for(k = 0; k < i; ++k) {
					sum += l(i, k) * z(k, j);  
				}

				z(i, j) = eyen(i, j) - sum; 
			}
		}

		// As i is size_t, i < 0 has no meaning
		// but if i = 0 then ( (--i) > N is true ) - the loop stops  
		for(i = N - 1; i < N; --i) 
		{
			for(j = 0; j < N; ++j)
			{
				sum = 0; 

				for(k = i; k < N; ++k) {
					sum += u(i, k) * matinv(k, j);
				}

				if(u(i, i) == 0) 
					throw singular_matrix_error(); 
				else
					matinv(i, j) = (z(i, j) - sum) / u(i, i);
			}
		}

		return matinv;
	}
} 

template <typename ConstructibleDerivedType>
typename std::enable_if< 
			std::is_base_of<
				typename ConstructibleDerivedType::base_type, 
				ConstructibleDerivedType 
			>::value,
		ConstructibleDerivedType >::type
eye(size_t dim) 
{
	ConstructibleDerivedType m(dim, dim); 
	m.fillWithZeros(); 

	for(size_t i = 0; i < dim; ++i) 
		m(i, i) = 1; 

	return m;
}

template <typename ConstructibleDerivedType>
typename std::enable_if< 
			std::is_base_of<
				typename ConstructibleDerivedType::base_type, 
				ConstructibleDerivedType 
			>::value,
		ConstructibleDerivedType >::type
zeros(size_t rows, size_t cols) 
{
	ConstructibleDerivedType m(rows, cols); 
	m.fillWithZeros(); 
	return m;
}

template <typename Container2D, typename T, typename ConstructibleDerivedType, typename TT = T>
inline 
TT norm2(const detail::MatrixBase<Container2D, T, ConstructibleDerivedType> & m) 
{
	TT sum = 0; 

	for(size_t i = 0; i < m.rows(); ++i) 
		for(size_t j = 0; j < m.cols(); ++j)
			sum += m(i, j) * m(i, j); 

	return sqrt(sum);
}