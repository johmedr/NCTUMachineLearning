#include <iostream> 
#include <type_traits>
using namespace std; 

struct Base 
{
	virtual void operator()() = 0; 
	const int m = 2; 
};

template <typename T = float>
struct A : Base
{
	virtual void operator()() override
	{
		cout << "A" << endl; 
		cout << m << endl; 
	} 

	virtual void operator()(A<>&  o) 
	{
		cout << "A o" << endl; 
	}
};

template <int p>
struct B : Base
{
	virtual void operator()() override 
	{
		cout << "B virt" << endl; 
		cout << m << endl; 
	}

	template <int i = p>	
	void operator()(int a) 
	{
		cout << "B"<< endl; 
	}

	static const int m = p; 

	// void operator()(const A<> & o)
	// {
	// 	cout << "B ao" << endl; 
	// }

	template <int i = p> 
	void operator()(const B<i> & o)
	{
		cout << "B o" << endl; 
	}
};

template <int p = 0, typename T = float>
void bar(const B<p> & b, const B<p> & b2) 
{
	cout << "bar(b)" << endl; 
}

template <int p = 0, typename T = float>
void bar(const A<T> & a, const A<T> & a2)
{
	cout << "bar(a)" << endl; 
}

template <int p = 0, typename T = float>
void bar(const Base & a, const Base & b)
{
	cout << "bar(Base)" << endl; 
}


template <int p, typename T1>
typename enable_if<is_same<B<p>, T1>::value, void>::type
foo(T1 b)
{
	cout << "foo(b)" << endl; 
}

template <int p, typename T1>
typename enable_if< !(is_same<B<p>, T1>::value), void>::type
foo(T1 a)
{
	cout << "foo(a)" << endl; 
}



// template <typename T, T V> 
// struct wrap 
// {
// 	static const T value = V; 
// };

// template <typename T, T V>
// struct make_obj 
// {
// 	static constexpr wrap<T, V> operator()(int v) 
// 	{
// 		b = (v == V); 
// 	}

// 	static const bool b; 

// 	using type = typename conditional<b, A<>, B<V>>::type; 
// };

int main() 
{
	// A<> a; 
	// a(); 
	// B<2> b; 
	// b();
	// b(3); 

	// // A<> * ab = new B<2>();

	// // (*ab)(); 

	// B<1> b2; 
	// b(b2); 

	// Base a

	// // (static_cast<A<>>(b))(*ab); 
	// // (static_cast<A<>>(b))(b2); 

	// // foo<2>(ab);

	// foo<1>(a); 


	// b(*ab);

	// (*ab)(*ab); 

	// delete ab; 

	Base * a = new A<>(); 
	Base * b = new B<12>(); 

	(*a)(); 
	(*b)(); 
	
	bar(*a, *a); 
	bar(*b, *b); 
	bar(*a, *b); 

	delete a,b;  
}