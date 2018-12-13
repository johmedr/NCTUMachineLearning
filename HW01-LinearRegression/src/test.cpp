#include <iostream>

template <int A = 0, class B = float>
class Base;

template <int A, class B> 
class Base
{}; 

template <class B>
class Base<0, B> 
{}; 

template <int A = 0, class B = float>
class Son; 

template <int A, class B>
class Son : public Base<A, B>
{
public: 
	Son(){
		std::cout << "son1 !" << std::endl;
	}
} ;

template <class B>
class Son<0, B> : public Base<B>
{ 
public: 
	Son(int a_){
		std::cout << "son2 !" << std::endl; 
	}	
};

template <class >
static constexpr make_obj()


int main() 
{

	Son o1; 
	Son o2(1); 
}