template <typename T>
Matrix<T>::Matrix(size_t rows, size_t cols) : 
	base_type(rows, cols, container_type(rows, std::vector<T>(cols)))
{}

template <typename T>
Matrix<T>::Matrix(const std::initializer_list<std::initializer_list<T>> & l) : 
	base_type(l.size(), l.begin()->size(), container_type(l.size(), std::vector<T>(l.begin()->size())))
{
	size_t i = 0, j; 

	assert(l.size() <= _rows); 

	for(const auto it_i : l) {
		assert(it_i.size() <= _cols); 

		j = 0;
		for(const auto it_j : it_i) {
			_m[i][j] = static_cast<const T>(it_j); 
			++j; 
		}

		++i; 
	}
}

template <typename T>
Matrix<T>::~Matrix(){}

template <typename T>
Matrix<T> & Matrix<T>::reshape(size_t rows, size_t cols)
{
	_m.clear(); 
	_m.resize(rows, std::vector<T>(cols)); 
	_rows = rows; 
	_cols = cols; 
	return (*this);
}

template <typename T>
Matrix<T> & Matrix<T>::copy(const base_type & rhs)
{
	reshape(rhs.rows(), rhs.cols());
	for(size_t i = 0; i < _rows; ++i) 
		for(size_t j = 0; j < _cols; ++j) 
			_m[i][j] = rhs(i, j);
	return (*this);
}
