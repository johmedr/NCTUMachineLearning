template <size_t N, typename T, typename TLU>
void LUdecomp(const StaticMatrix<N, N, T> & mat, StaticMatrix<N, N, TLU> & lower, StaticMatrix<N, N, TLU> & upper)
{
	lower = upper = StaticMatrix<N, N, TLU>::zeros(); 
	TLU sum; 
	size_t i, j, k; 

	for(i = 0; i < N; ++i) 
	{
		for(j = i; j < N; ++j) 
		{
			sum = 0; 

			for(k = 0; k < i; ++k) {
				sum += lower(i, k) * upper(k, j); 
			}

			upper(i, j) = static_cast<TLU>(mat(i, j)) - sum; 
		}

		lower(i, i) = 1; 
		for(j = i; j < N; ++j)
		{
			sum = 0; 

			for(k = 0; k < i; ++k) {
				sum += lower(j, k) * upper(k, i); 
			}

			if(upper(i, i) != 0)
				lower(j, i) = (static_cast<TLU>(mat(j, i)) - sum) / upper(i, i); 
			else 
				throw singular_matrix_error(); 
		}
	}
}

template <size_t N, typename T, typename TT> 
StaticMatrix<N, N, TT> inverse(const StaticMatrix<N, N, T> & mat)
{

	StaticMatrix<N, N, TT> l, u; 

	try {
		LUdecomp(mat, l, u); 
	} catch(const std::exception & e) {
		throw; 
	}

	size_t i, j, k; 
	StaticMatrix<N, N, TT> eyen = StaticMatrix<N, N, TT>::eye(); 
	StaticMatrix<N, N, TT> z, matinv; 
	TT sum; 

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

// template <size_t N_DATAS, size_t N_FEATURES, typename T, typename TT>
// StaticMatrix<N_FEATURES, 1, TT> linearRegression(const StaticMatrix<N_DATAS, N_FEATURES, T> & a, const StaticMatrix<N_DATAS, 1, T> & b, double lambda_l2)
// {
// 	StaticMatrix<N_FEATURES, 1, TT> x; 
// 	try 
// 	{
// 		x = inverse(a.transpose() * a + lambda_l2 * StaticMatrix<N_FEATURES, N_FEATURES>::eye()) * a.transpose() * b; 
// 	} 
// 	catch(const std::exception & e) 
// 	{
// 		throw; 
// 	}
// 	return x; 
// }