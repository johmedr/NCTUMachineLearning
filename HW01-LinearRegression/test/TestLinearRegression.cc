#include <LinearRegression.hxx>

class TestLinearRegression
{
	void testStaticLinearRegression() 
	{
		StaticMatrix<5, 2> a = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}}; 
		StaticMatrix<5, 1> b = {{2}, {4.1}, {5.8}, {8.4}, {9.5}}; 
		StaticMatrix<2, 1> xexpected = {{1.93}, {0.17}};

		auto x = linearRegression(a, b, 0); 

		auto delta = x * x.transpose() - xexpected * xexpected.transpose(); 

		assert(delta(0, 0) < 1e-5);
	}

	void testDynamicLinearRegression() 
	{
		Matrix<> a = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}}; 
		Matrix<> b = {{2}, {4.1}, {5.8}, {8.4}, {9.5}}; 
		Matrix<> xexpected = {{1.93}, {0.17}};

		auto x = linearRegression(a, b, 0); 

		auto delta = x * x.transpose() - xexpected * xexpected.transpose(); 

		assert(delta(0, 0) < 1e-5);
	}

	void testPolynomialDesignMatrix() 
	{
		Matrix<> data = {{1}, {2}, {4}, {-5}}; 
		Matrix<> aexpected = {{1, 1, 1, 1}, {1, 2, 4, 8}, {1, 4, 16, 64}, {1, -5, 25, -125}};

		auto a = polynomialDesignMatrix(data, 4); 

		assert(a == aexpected); 
	}

	void testNewtonDescent() 
	{
		Matrix<> a = {{1, 1}, {2, 1}, {3, 1}, {4, 1}, {5, 1}}; 
		Matrix<> b = {{2}, {4.1}, {5.8}, {8.4}, {9.5}}; 
		Matrix<> xexpected = {{1.93}, {0.17}};

		auto x = newtonDescent(a, b); 

		auto delta = x * x.transpose() - xexpected * xexpected.transpose(); 

		assert(delta(0, 0) < 1e-5);
	}

public: 
	void runTests()
	{
		testStaticLinearRegression(); 
		testDynamicLinearRegression(); 
		testPolynomialDesignMatrix(); 
		testNewtonDescent(); 
	}
};


int main() 
{
	TestLinearRegression t; 
	t.runTests(); 
}