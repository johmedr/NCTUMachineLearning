#include <DynamicMatrix.hxx>


// [TODO] - Test more complex operations
class TestDynamicMatrixOperators 
{
	void testSelfSumSub() 
	{
		Matrix<> m1 = {{4, 5, 6}, {1, 2, 3}};
		Matrix<> m1origin = {{4, 5, 6}, {1, 2, 3}};
		Matrix<> m2 = {{7, 8, 9}, {2, 8, 6}};

		m1 += m2; 

		assert(m1(0, 0) == 11); 
		assert(m1(0, 1) == 13); 
		assert(m1(0, 2) == 15); 
		assert(m1(1, 0) == 3); 
		assert(m1(1, 1) == 10); 
		assert(m1(1, 2) == 9); 

		m1 -= m2; 

		for(size_t i = 0; i < 2; ++i) 
			for(size_t j = 0; j < 3; ++j) 
				assert(m1(i, j) == m1origin(i, j));
	}

	void testSelfMulScal() 
	{
		Matrix<> m = {{1}, {2}};

		m *= 3; 

		assert(m(0, 0) == 3); 
		assert(m(1, 0) == 6); 
	}

	void testSelfMulMat()
	{
		Matrix<> m = {{3, 2}, {-2, -1}, {-5, 8}}; 
		Matrix<> m2 = {{-1, 9}, {7, 2}};

		m *= m2; 

		assert(m(0, 0) == 11); 
		assert(m(0, 1) == 31); 
		assert(m(1, 0) == -5); 
		assert(m(1, 1) == -20); 
		assert(m(2, 0) == 61); 
		assert(m(2, 1) == -29); 
	}

	void testScalMul() 
	{
		Matrix<> m = {{1, 2}, {2, 5}};

		Matrix<> m2 = m * 3; 
		Matrix<> m3 = 5 * m; 

		for(size_t i = 0; i < 2; ++i) {
			for(size_t j = 0; j < 2; ++j) {
				assert(m2(i, j) == m(i, j) * 3);
				assert(m3(i, j) == m(i, j) * 5);
			}
		}
	}

	void testSumSub() 
	{
		Matrix<> m1 = {{4, 5, 6}, {1, 2, 3}};
		Matrix<> m1origin = {{4, 5, 6}, {1, 2, 3}};
		Matrix<> m2 = {{7, 8, 9}, {2, 8, 6}};

		Matrix<> m3 = m1 + m2; 

		assert(m3(0, 0) == 11); 
		assert(m3(0, 1) == 13); 
		assert(m3(0, 2) == 15); 
		assert(m3(1, 0) == 3); 
		assert(m3(1, 1) == 10); 
		assert(m3(1, 2) == 9); 

		Matrix<> m4 = m3 - m2; 

		for(size_t i = 0; i < 2; ++i) 
			for(size_t j = 0; j < 3; ++j) 
				assert(m4(i, j) == m1origin(i, j));
	}

	void testMul() 
	{
		Matrix<> m1 = {{4, 5, 6, 5}, {1, 2, 3, -5}};
		Matrix<> m2 = {{2, 3, 1}, {3, 4, 0}, {5, 6, 7}, {-5, -2, -0.1}}; 

		Matrix<> m3 = m1 * m2; 

		assert(m3(0, 0) == 28); 
		assert(m3(0, 1) == 58); 
		assert(m3(0, 2) == 45.5); 
		assert(m3(1, 0) == 48); 
		assert(m3(1, 1) == 39); 
		assert(m3(1, 2) == 22.5); 
	}

	void testEquality() 
	{
		Matrix<> m1 = {{1, 2, 3}, {4, 5, 6}}; 
		Matrix<> m2 = {{1, 2, 5}, {4, 5, 6}};
		Matrix<> m3 = m1;
		Matrix<> m4 = {{1, 2, 3}, {4, 5, 6}};

		assert(m1 != m2); 
		assert(m1 == m3); 
		assert(m1 == m4); 
	}

	void testTranspose() 
	{
		Matrix<> m1 = {{4, 5, 6, 5}, {1, 2, 3, -5}};
		Matrix<> m2 = m1.transpose(); 

		for(size_t i = 0; i < 2; ++i)
			for(size_t j = 0; j < 4; ++j)
				assert(m1(i, j) == m2(j, i));
	}

	void testLUdecomp()
	{
		Matrix<> A, L, U, Lexpected, Uexpected;  

		A = {{2, -1, -2}, {-4, 6, 3}, {-4, -2, 8}}; 
		Lexpected = {{1, 0, 0}, {-2, 1, 0}, {-2, -1, 1}}; 
		Uexpected = {{2, -1, -2}, {0, 4, -1}, {0, 0, 3}}; 

		A.lu(L, U);

		assert(L == Lexpected);
		assert(U == Uexpected); 
		
		Matrix<> m; 
		m.fillWithZeros(); 

		bool throws = false; 
		try 
		{
			m.lu(L, U); // ERROR !!!
		} catch(const std::exception & e) {
			throws = true; 
		}

		assert(throws);
	}

	void testInverse() 
	{
		Matrix<> m1 = {{2, 4}, {6, 8}};
		Matrix<> m1inv = {{-1, 0.5}, {0.75, -0.25}}; 

		Matrix<> m = m1.inverse(); 

		assert(m == m1inv); 

		m.fillWithZeros() ;

		bool throws = false; 
		try 
		{
			m.inverse(); 
		} catch(const std::exception & e) {
			throws = true; 
		}

		assert(throws);

		auto m2 = eye<Matrix<>>(128);
		auto m2inv = m2.inverse();  
		assert( m2 == m2inv );
	}

	void testMulTranspose() 
	{
		Matrix<> a = {{2, 3}, {4, 5}, {5, 6}}; 
		Matrix<> result = {{45, 56}, {56, 70}};

		assert(a.transpose() * a == result); 
	}

	void testNorm2() 
	{
		Matrix<> a = {{1, 3}, {1, 2}, {0, 1}}; 

		assert(norm2(a) == 4); 
	}

public:
	void runTests() 
	{
		testSelfSumSub(); 
		testSelfMulScal(); 
		testSelfMulMat();
		testScalMul(); 
		testSumSub(); 
		testMul(); 
		testEquality(); 
		testTranspose();
		testLUdecomp(); 
		testInverse(); 
		testMulTranspose(); 
		testNorm2();
	}
};

int main() 
{
	TestDynamicMatrixOperators t; 
	t.runTests(); 
}