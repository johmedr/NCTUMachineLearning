#include <DynamicMatrix.hxx>

class TestDynamicMatrix 
{
	void testCreation() 
	{
		Matrix<> m1; 
		Matrix<int> m2;
		Matrix<> m3 = {{2, 5}, {6, 9}, {-1, 0.5}}; 
	}

	void testElementAccess()
	{
		Matrix<> m1 = {{1, 5, 0}, {9, 8, 0}};

		assert(m1(0, 1) == 5); 
		assert(m1(1, 1) == 8); 

		m1(1, 2) = 9; 
		assert(m1(1, 2) == 9);
	}

	void testFillWithZeros() 
	{
		Matrix<> m = {{5, 3, 8}, {9, 2, 5}};

		m.fillWithZeros(); 

		for(size_t i = 0; i < 2; ++i) 
			for(size_t j = 0; j < 3; ++j) 
				assert(m(i, j) == 0); 
	}

	void testReshape() 
	{
		Matrix<> m(2, 3); 

		m.reshape(5, 4); 

		m(4, 3) = 12; 

		assert(m(4, 3) == 12); 
	}

	void testCopy() 
	{
		Matrix<> m1 = {{1, 5, 0}, {9, 8, 0}};
		Matrix<> m2(2, 3); 
		Matrix<> m3(2, 3); 

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
		auto m = eye<Matrix<>>(3); 
		Matrix<> mexpected = {{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}; 
		assert(m == mexpected);
	}

	void testZeros()
	{
		auto m = zeros<Matrix<>>(2, 1); 
		Matrix<> mexpected = {{0}, {0}}; 
		assert(m == mexpected);
	}


public: 
	void runTests() 
	{
		testCreation(); 
		testElementAccess();
		testFillWithZeros();  
		testReshape();
		testCopy();
		testEye(); 
		testZeros();
	}
};

int main() 
{
	TestDynamicMatrix tm; 
	tm.runTests(); 
}