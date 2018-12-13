#include <iostream>
#include <type_traits>

using namespace std;

template <int i> 
struct Obj {} 

template <int V, class A, template <int V> class B>
struct condit_t
{
	using type = B<V>; 
};

template <class A, template <int V> class  B>
struct condit_t<0, A, B>
{
	using type = A;
};

int dim(short a) 
{
	return 0; 
}

constexpr int dim(int a) 
{
	return a; 
}

template <class R = int, T v = 1, R = typename condit_t<dim(v), void, Obj>::type>
R make_obj() {
	return R();
}

template <class T = int, T v = 1, class ...Ts>
B<float> make_obj(Ts ...) {
	return objb::B<float>(); 
}

int main() 
{
	int n = 5; 
	int * n2 = new int(n - n *2); 
	branch(n); 
	n = *((n2 + 2)); 
	branch(n);
}