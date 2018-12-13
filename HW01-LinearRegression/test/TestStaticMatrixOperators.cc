#include <StaticMatrix.hxx>

class TestStaticMatrixOperators 
{
	void testSelfSumSub() 
	{
		StaticMatrix<2, 3> m1 = {{4, 5, 6}, {1, 2, 3}};
		StaticMatrix<2, 3> m1origin = {{4, 5, 6}, {1, 2, 3}};
		StaticMatrix<2, 3> m2 = {{7, 8, 9}, {2, 8, 6}};

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
		StaticMatrix<2, 1> m = {{1}, {2}};

		m *= 3; 

		assert(m(0, 0) == 3); 
		assert(m(1, 0) == 6); 
	}

	void testSelfMulMat()
	{
		StaticMatrix<3, 2> m = {{3, 2}, {-2, -1}, {-5, 8}}; 
		StaticMatrix<2, 2> m2 = {{-1, 9}, {7, 2}};

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
		StaticMatrix<2, 2> m = {{1, 2}, {2, 5}};

		StaticMatrix<2, 2> m2 = m * 3; 
		StaticMatrix<2, 2> m3 = 5 * m; 

		for(size_t i = 0; i < 2; ++i) {
			for(size_t j = 0; j < 2; ++j) {
				assert(m2(i, j) == m(i, j) * 3);
				assert(m3(i, j) == m(i, j) * 5);
			}
		}
	}

	void testSumSub() 
	{
		StaticMatrix<2, 3> m1 = {{4, 5, 6}, {1, 2, 3}};
		StaticMatrix<2, 3> m1origin = {{4, 5, 6}, {1, 2, 3}};
		StaticMatrix<2, 3> m2 = {{7, 8, 9}, {2, 8, 6}};

		StaticMatrix<2, 3> m3 = m1 + m2; 

		assert(m3(0, 0) == 11); 
		assert(m3(0, 1) == 13); 
		assert(m3(0, 2) == 15); 
		assert(m3(1, 0) == 3); 
		assert(m3(1, 1) == 10); 
		assert(m3(1, 2) == 9); 

		StaticMatrix<2, 3> m4 = m3 - m2; 

		for(size_t i = 0; i < 2; ++i) 
			for(size_t j = 0; j < 3; ++j) 
				assert(m4(i, j) == m1origin(i, j));
	}

	void testMul() 
	{
		StaticMatrix<2, 4> m1 = {{4, 5, 6, 5}, {1, 2, 3, -5}};
		StaticMatrix<4, 3> m2 = {{2, 3, 1}, {3, 4, 0}, {5, 6, 7}, {-5, -2, -0.1}}; 

		StaticMatrix<2, 3> m3 = m1 * m2; 

		assert(m3(0, 0) == 28); 
		assert(m3(0, 1) == 58); 
		assert(m3(0, 2) == 45.5); 
		assert(m3(1, 0) == 48); 
		assert(m3(1, 1) == 39); 
		assert(m3(1, 2) == 22.5); 
	}

	void testTranspose() 
	{
		StaticMatrix<2, 4> m1 = {{4, 5, 6, 5}, {1, 2, 3, -5}};
		StaticMatrix<4, 2> m2 = m1.transpose(); 

		for(size_t i = 0; i < 2; ++i)
			for(size_t j = 0; j < 4; ++j)
				assert(m1(i, j) == m2(j, i));
	}

	void testEquality() 
	{
		StaticMatrix<2, 3> m1 = {{1, 2, 3}, {4, 5, 6}}; 
		StaticMatrix<2, 3> m2 = {{1, 2, 5}, {4, 5, 6}};
		StaticMatrix<2, 3> m3 = m1;
		StaticMatrix<2, 3, char> m4 = {{1, 2, 5}, {4, 5, 6}};

		assert(m1 != m2); 
		assert(m1 == m3); 
		assert(m1 == m4); 
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
		testTranspose();
	}
};

int main() 
{
	TestStaticMatrixOperators t; 
	t.runTests(); 
}