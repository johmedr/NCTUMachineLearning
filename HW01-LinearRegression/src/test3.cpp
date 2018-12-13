#include <iostream>
using namespace std;

struct Base { 
	virtual ~Base(){} 

	virtual void foo() = 0; 
};


namespace objb
{
	template <class> 
	struct B 
	{
		B() {
			cout << "B::B()" << endl; 
		}


		virtual void foo()
		{
						cout << "B::B" << endl; 

		}
	};
}

using objb::B; 

namespace obja
{
	template <int> 
	struct A : public B<float>
	{
		A() {
			cout << "A::A()" << endl; 
		}

		virtual void foo() 
		{
			cout << "A::A" << endl; 

		}
	};
}


template<int n> struct i {}; 
int make_obj_helper(char n) {
	return 0; 
}

constexpr int make_obj_helper(int n) {
	return 'a'; 
}

template <class T = int, T v = 1, i<make_obj_helper(v)>* = nullptr>
inline constexpr obja::A<make_obj_helper(v)> make_obj(const int p) {
	const int n = p; 
	return obja::A<n>();
}

template <class T = int, T v = 1, class ...Ts>
B<float> make_obj(Ts ...) {
	return objb::B<float>(); 
}



int main() 
{
	int n; 
	n = 6; 
	n += 3 * (--n); 
	int * n2; 
	n2 = new int(n - n *2); 
	auto b = make_obj(*(&n2 + 1)); 
	auto a = make_obj(5); 

	b.foo();
	a.foo(); 

}