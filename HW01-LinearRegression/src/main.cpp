#include <iostream>
#include <iomanip>
#include <fstream> 
#include <LinearRegression.hxx>
#include <IO.hxx>

#include <stdio.h>
#include <unistd.h>

template <typename T> 
void beautifulPrint(std::string methodName, const Matrix<T> & a, const Matrix<T> & b, const Matrix<T> & x)
{
	std::cout << std::setfill(' ');
	
	std::cout.setf(std::ios::scientific, std::ios::floatfield);
	std::cout << std::setprecision(2); 

	std::cout << "Results with " << methodName << std::endl;
	std::cout << "LSE : " << leastSquareError(a, x, b) << std::endl; 
	std::cout << std::left << "Best fitting equation : "  << std::endl; 
	std::cout <<  "y = ";
	std::cout << x(0, 0);

	int width = static_cast<int>(100- 11); 

	if(x.rows() > 1) 
	{
		for(size_t i = 1; i < x.rows(); ++i) {
			if (width - static_cast<int>(17 + i/10) < 0){
				std::cout << std::endl; 
				std::cout <<" "; 
				width = static_cast<int>(100 - 2); 
			}
			width -= static_cast<int>(17 + i/10); 

			if (x(i, 0) < 0) 
				std::cout << " - " << -x(i, 0); 
			else 
				std::cout << " + " << x(i, 0); 
			std::cout << "*x^" << i; 
		}
	}
	std::cout << std::endl; 
}


int main(int argc, char *argv[])
{
	assert(argc < 8); 

	extern char * optarg; 

	std::string filename; 
	size_t order_n = 1; 
	double lambda = 0; 

	char c;

	while( (c = getopt(argc, argv, "f:n:l:")) != -1 )
	{
		switch(c)
		{
			case 'f': 
				filename = static_cast<std::string>(optarg); 
				break;

			case 'n': 
				order_n = static_cast<size_t>(std::stoi(optarg)); 
				break; 

			case 'l': 
				lambda = static_cast<double>(std::stod(optarg));
				break;

		}
	}

	Matrix<double> data_x, data_y; 

	parseFile(filename, data_x, data_y); 


	auto A = polynomialDesignMatrix(data_x, order_n);

	std::cout << std::setw(100) << std::setfill('-') << std::left << "" << std::endl; 
	try {
		auto x_linreg = linearRegression(A, data_y, lambda); 
		beautifulPrint("Direct LSE solving", A, data_y, x_linreg); 
	} 
	catch(const std::exception & e) 
	{
		std::cout << "Cannot solve this problem using linear regression. Raise singular matrix exception" << std::endl; 
		std::cout << "Try to influence the conditioning of the design matrix, or reduce the order n." << std::endl; 
	}
	std::cout << std::endl; 
	std::cout << std::setw(50) << std::setfill('*') << std::left << "" << std::endl; 
	std::cout << std::endl; 

	try {
		auto x_newton = newtonDescent(A, data_y); 
		beautifulPrint("Newton descent", A, data_y, x_newton); 
	} 
	catch(const std::exception & e) 
	{
		std::cout << "Cannot solve this problem using Newton descent. Raise singular matrix exception" << std::endl; 
		std::cout << "Try to influence the conditioning of the design matrix, or reduce the order n." << std::endl; 
	}
	std::cout << std::setw(100) << std::setfill('-') << std::left << "" << std::endl; 

}