template <size_t N_DATAS, size_t N_FEATURES, typename T, typename TT>
StaticMatrix<N_FEATURES, 1, TT> linearRegression(const StaticMatrix<N_DATAS, N_FEATURES, T> & a, const StaticMatrix<N_DATAS, 1, T> & b, double lambda_l2)
{
	StaticMatrix<N_FEATURES, 1, TT> x; 
	try 
	{
		x = inverse(a.transpose() * a + lambda_l2 * StaticMatrix<N_FEATURES, N_FEATURES>::eye()) * a.transpose() * b; 
	} 
	catch(const std::exception & e) 
	{
		throw; 
	}
	return x; 
}

template <typename T, typename LT>
Matrix<T> linearRegression(const Matrix<T> & a, const Matrix<T> & b, LT lambda_l2) 
{
	assert(a.rows() == b.rows()); 
	assert(b.cols() == 1); 

	Matrix<T> x(a.cols(), 1); 

	try 
	{
		x = ( a.transpose() * a + static_cast<T>(lambda_l2) * eye<Matrix<T>>(a.cols()) ).inverse() * a.transpose() * b; 
	} 
	catch(const std::exception & e) 
	{
		throw; 
	}
	return x; 
}

template <typename T, typename NT = size_t> 
Matrix<T> polynomialDesignMatrix(const Matrix<T> & data, NT order_n)
{
	assert(order_n > 0); 
	assert(data.cols() == 1); 
	Matrix<T> design_matrix(data.rows(), order_n);

	for(size_t i = 0; i < design_matrix.rows(); ++i) {
		design_matrix(i, 0) = 1; 
		for(size_t j = 1; j < design_matrix.cols(); ++j) 
			design_matrix(i, j) = design_matrix(i, j - 1) * data(i, 0); 
	}
	return design_matrix; 
}


template <typename T, typename TT = T>
TT leastSquareError(const Matrix<T> & a, const Matrix<T> & x, const Matrix<T> & b)
{
	assert(b.cols() == 1); 

	return ((a * x - b).transpose() * (a * x - b))(0,0); 
}

template <typename T>
Matrix<T> newtonDescent(const Matrix<T> & a, const Matrix<T> & b)
{
	assert(a.rows() == b.rows()); 

	auto grad = [=](Matrix<T> x)->Matrix<T> { return 2 * a.transpose() * a * x - 2 * a.transpose() * b; };
	auto hessian = 2 * a.transpose() * a; 

	Matrix<T> x(a.cols(), 1); 

	x.fillWithZeros(); 
	x = x - hessian.inverse() * grad(x); 

	return x; 
}