#include <StaticMatrix.hxx>
#include <cassert>

class TestStaticMatrix 
{
	void testCreation() 
	{
		StaticMatrix<3, 5> m1; 
		StaticMatrix<1, 1, int> m2;
		StaticMatrix<3, 2> m3 = {{2, 5}, {6, 9}, {-1, 0.5}}; 
	}

	void testElementAccess()
	{
		StaticMatrix<2, 3> m1 = {{1, 5, 0}, {9, 8, 0}};

		assert(m1(0, 1) == 5); 
		assert(m1(1, 1) == 8); 

		m1(1, 2) = 9; 
		assert(m1(1, 2) == 9);
	}

	void testFillWithZeros() 
	{
		StaticMatrix<3, 4> m = {{5, 3, 8}, {9, 2, 5}};

		m.fillWithZeros(); 

		for(size_t i = 0; i < 3; ++i) 
			for(size_t j = 0; j < 4; ++j) 
				assert(m(i, j) == 0); 
	}

	void testCopy() 
	{
		StaticMatrix<2, 3> m1 = {{1, 5, 0}, {9, 8, 0}};
		StaticMatrix<2, 3> m2; 
		StaticMatrix<2, 3, char> m3; 

		m2.copy(m1); 

		for(size_t i = 0; i < 2; ++i) 
			for(size_t j = 0; j < 3; ++j)
				assert(m2(i, j) == m1(i, j));

		m3.copy(m1); 

		for(size_t i = 0; i < 2; ++i) 
			for(size_t j = 0; j < 3; ++j)
				assert(m3(i, j) == m1(i, j)); 
	}

	void testEye() 
	{
		StaticMatrix<3, 3> m = StaticMatrix<3, 3>::eye(); 
		StaticMatrix<3, 3> mexpected = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; 
		assert(m == mexpected);
	}


public: 
	void runTests() 
	{
		testCreation(); 
		testElementAccess();
		testFillWithZeros();  
		testCopy();
		testEye(); 
	}
};

int main() 
{
	TestStaticMatrix tm; 
	tm.runTests(); 
}