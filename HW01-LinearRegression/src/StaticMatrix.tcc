
template <size_t Rows, size_t Cols, typename T> 
StaticMatrix<Rows, Cols, T>::StaticMatrix()
try : _m() 
{}
catch(const std::exception & e)
{
	throw; 
}

template <size_t Rows, size_t Cols, typename T> 
StaticMatrix<Rows, Cols, T>::StaticMatrix(const std::initializer_list<std::initializer_list<T>> & l)
try : _m()
{
	size_t i = 0, j; 

	assert(l.size() <= Rows); 

	for(const auto it_i : l) {
		assert(it_i.size() <= Cols); 

		j = 0;
		for(const auto it_j : it_i) {
			_m[i][j] = static_cast<const T>(it_j); 
			++j; 
		}

		++i; 
	}
}
catch(const std::exception & e)
{
	throw; 
}

template <size_t Rows, size_t Cols, typename T> 
StaticMatrix<Rows, Cols, T>::~StaticMatrix() 
{}

template <size_t Rows, size_t Cols, typename T> 
const T& StaticMatrix<Rows, Cols, T>::operator()(size_t i, size_t j) const
{
	assert(i < Rows && j < Cols);
	return _m[i][j];
}

template <size_t Rows, size_t Cols, typename T> 
T& StaticMatrix<Rows, Cols, T>::operator()(size_t i, size_t j)
{
	assert(i < Rows && j < Cols);
	return _m[i][j];
}

template <size_t Rows, size_t Cols, typename T> 
void StaticMatrix<Rows, Cols, T>::fillWithZeros()
{
	for(size_t i = 0; i < Rows; ++i) 
		for(size_t j = 0; j < Cols; ++j) 
			_m[i][j] = 0; 
}

template <size_t Rows, size_t Cols, typename T> 
void StaticMatrix<Rows, Cols, T>::print() const
{
	std::cout << "[";
	for(size_t i = 0; i < Rows; ++i) 
	{
		std::cout << "[";

		for(size_t j = 0; j < Cols - 1; ++j) 
		{
			std::cout << _m[i][j] << ", ";
		}
		std::cout << _m[i][Cols - 1];

		std::cout << "]," << std::endl; 
	}
	std::cout << "]" << std::endl; 
}

template <size_t Rows, size_t Cols, typename T> 
template <typename TT>
void StaticMatrix<Rows, Cols, T>::copy(const StaticMatrix<Rows, Cols, TT>& rhs)
{
	for(size_t i = 0; i < Rows; ++i) 
		for(size_t j = 0; j < Cols; ++j) 
			_m[i][j] = static_cast<T>(rhs._m[i][j]);
}

template <size_t Rows, size_t Cols, typename T> 
void StaticMatrix<Rows, Cols, T>::copy(const StaticMatrix<Rows, Cols, T>& rhs)
{
	std::copy(rhs._m.begin(), rhs._m.end(), _m.begin()); 
}

template <size_t Rows, size_t Cols, typename T>
template <size_t _Rows, size_t _Cols, typename _T>
typename std::enable_if< _Rows != _Cols, StaticMatrix<_Rows, _Cols, _T> >::type
StaticMatrix<Rows, Cols, T>::eye() 
{
	static_assert(Rows == Cols, "Illegal operation : cannot eye a non-square matrix !");
}

template <size_t Rows, size_t Cols, typename T>
template <size_t _Rows, size_t _Cols, typename _T>
typename std::enable_if< _Rows == _Cols, StaticMatrix<_Rows, _Cols, _T> >::type
StaticMatrix<Rows, Cols, T>::eye() 
{
	StaticMatrix<Rows, Cols, T> m; 
	for(size_t i = 0; i < Rows; ++i) 
		m(i, i) = 1; 
	return m; 
}

template <size_t Rows, size_t Cols, typename T> 
StaticMatrix<Rows, Cols, T> StaticMatrix<Rows, Cols, T>::zeros() 
{
	StaticMatrix<Rows, Cols, T> m; 
	for(auto line : m._m)
		line.fill(0);
	return m;
}

template <size_t Rows, size_t Cols, typename T> 
template <typename TT>
StaticMatrix<Rows, Cols, T>& StaticMatrix<Rows, Cols, T>::operator+=(const StaticMatrix<Rows, Cols, TT>& rhs)
{
	for(size_t i = 0; i < Rows; ++i) 
		for(size_t j = 0; j < Cols; ++j) 
			_m[i][j] += rhs._m[i][j]; 
	return *this; 
}

template <size_t Rows, size_t Cols, typename T> 
template <typename TT>
StaticMatrix<Rows, Cols, T>& StaticMatrix<Rows, Cols, T>::operator-=(const StaticMatrix<Rows, Cols, TT>& rhs) 
{
	for(size_t i = 0; i < Rows; ++i) 
		for(size_t j = 0; j < Cols; ++j) 
			_m[i][j] -= rhs._m[i][j]; 
	return *this; 
}

template <size_t Rows, size_t Cols, typename T> 	
template <typename TT> 
typename std::enable_if< std::is_arithmetic<TT>::value, StaticMatrix<Rows, Cols, T> >::type &
StaticMatrix<Rows, Cols, T>::operator*=(const TT& rhs)
{
	for(size_t i = 0; i < Rows; ++i)
		for(size_t j = 0; j < Cols; ++j) 
			_m[i][j] *= rhs; 
	return *this; 
}

template <size_t Rows, size_t Cols, typename T> 
template <typename TT>
StaticMatrix<Rows, Cols, T>& StaticMatrix<Rows, Cols, T>::operator*=(const StaticMatrix<Cols, Cols, TT>& rhs) 
{
	StaticMatrix<Rows, Cols, T> m = (*this) * rhs; 
	this->copy(m);
	return *this;
}

template <size_t Rows, size_t Cols, typename T> 
StaticMatrix<Cols, Rows, T> StaticMatrix<Rows, Cols, T>::transpose() const 
{
	StaticMatrix<Cols, Rows, T> m; 
	for(size_t i = 0; i < Rows; ++i) 
		for(size_t j = 0; j < Cols; ++j) 
			m._m[j][i] = _m[i][j];
	return m;
}

template <size_t Rows, size_t Cols, typename T> 
bool StaticMatrix<Rows, Cols, T>::operator==(const StaticMatrix<Rows, Cols, T>& rhs) const
{
	return _m == rhs._m; 
}

template <size_t Rows, size_t Cols, typename T> 
template <typename TT> 
bool StaticMatrix<Rows, Cols, T>::operator==(const StaticMatrix<Rows, Cols, TT>& rhs) const
{
	for(size_t i = 0; i < Rows; ++i)
		for(size_t j = 0; j < Cols; ++j)
			if( !(_m[i][j] == rhs._m[i][j]) ) 
				return false; 
	return true; 
}

template <size_t Rows, size_t Cols, typename T> 
bool StaticMatrix<Rows, Cols, T>::operator!=(const StaticMatrix<Rows, Cols, T>& rhs) const
{
	return _m != rhs._m; 
}

template <size_t Rows, size_t Cols, typename T> 
template <typename TT> 
bool StaticMatrix<Rows, Cols, T>::operator!=(const StaticMatrix<Rows, Cols, TT>& rhs) const
{
	for(size_t i = 0; i < Rows; ++i)
		for(size_t j = 0; j < Cols; ++j)
			if( (_m[i][j] != rhs._m[i][j]) ) 
				return true; 
	return false;  
}

template <size_t Rows, size_t Cols, size_t ColsOther, typename T, typename TT>  
StaticMatrix<Rows, ColsOther, T> operator*(const StaticMatrix<Rows, Cols, T>& lhs, const StaticMatrix<Cols, ColsOther, TT>& rhs)
{
	StaticMatrix<Rows, ColsOther, T> m; 
	for(size_t i = 0; i < Rows; ++i) 
		for(size_t j = 0; j < ColsOther; ++j) 
			for(size_t k = 0; k < Cols; ++k)
				m(i, j) += lhs(i, k) * rhs(k, j);
	return m;
}

template <size_t Rows, size_t Cols, typename T, typename TT>  
typename std::enable_if< std::is_arithmetic<TT>::value, StaticMatrix<Rows, Cols, T> >::type
operator*(const StaticMatrix<Rows, Cols, T>& lhs, const TT& rhs)
{
	StaticMatrix<Rows, Cols, T> m = lhs; 
	m *= rhs; 
	return m; 
}

template <size_t Rows, size_t Cols, typename T, typename TT>  
typename std::enable_if< std::is_arithmetic<TT>::value, StaticMatrix<Rows, Cols, T> >::type
operator*(const TT& lhs, const StaticMatrix<Rows, Cols, T>& rhs)
{
	return rhs * lhs; 
}

template <size_t Rows, size_t Cols, typename T, typename TT>
StaticMatrix<Rows, Cols, T> operator+(const StaticMatrix<Rows, Cols, T>& lhs, const StaticMatrix<Rows, Cols, TT>& rhs)
{
	StaticMatrix<Rows, Cols, T> m = lhs; 
	m += rhs; 
	return m; 
}

template <size_t Rows, size_t Cols, typename T, typename TT>
StaticMatrix<Rows, Cols, T> operator-(const StaticMatrix<Rows, Cols, T>& lhs, const StaticMatrix<Rows, Cols, TT>& rhs)
{
	StaticMatrix<Rows, Cols, T> m = lhs; 
	m -= rhs; 
	return m; 
}

