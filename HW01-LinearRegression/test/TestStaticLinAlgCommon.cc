#include <StaticMatrix.hxx>
#include <StaticLinAlgCommon.hxx>

class TestStaticLinAlgCommon 
{

	void testLUdecomp()
	{
		StaticMatrix<3, 3> A, L, U, Lexpected, Uexpected;  

		A = {{2, -1, -2}, {-4, 6, 3}, {-4, -2, 8}}; 
		Lexpected = {{1, 0, 0}, {-2, 1, 0}, {-2, -1, 1}}; 
		Uexpected = {{2, -1, -2}, {0, 4, -1}, {0, 0, 3}}; 

		LUdecomp(A, L, U); 

		assert(L == Lexpected);
		assert(U == Uexpected); 

		try {
		LUdecomp(StaticMatrix<3, 3>::zeros(), L, U); // ERROR !!!
		} catch(...) 
		{
			
		} 
		// LUdecomp(A.fillWithZeros(), L, U); // ERROR !! 
		A.fillWithZeros(); 

		bool throws = false; 
		try 
		{
			LUdecomp(A, L, U); 
		} catch(const std::exception & e) {
			throws = true; 
		}

		assert(throws);
	}

	void testInverse() 
	{
		StaticMatrix<2, 2> m1 = {{2, 4}, {6, 8}};
		StaticMatrix<2, 2> m1inv = {{-1, 0.5}, {0.75, -0.25}}; 

		StaticMatrix<2, 2> m = inverse(m1); 

		assert(m == m1inv); 

		m.fillWithZeros() ;

		bool throws = false; 
		try 
		{
			inverse(m); 
		} catch(const std::exception & e) {
			throws = true; 
		}

		assert(throws);

		StaticMatrix<128, 128> m2 = StaticMatrix<128, 128>::eye();
		auto m2inv = inverse(m2);  
		assert( m2 == m2inv );
	}

public: 
	void runTests() 
	{
		testLUdecomp(); 
		testInverse();
	}
};

int main()
{
	TestStaticLinAlgCommon t; 
	t.runTests();
}