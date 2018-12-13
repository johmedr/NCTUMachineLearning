#ifndef MATRIX_EXCEPTIONS_HXX
#define MATRIX_EXCEPTIONS_HXX

#include <exception>

class singular_matrix_error : public std::exception 
{
public: 
	singular_matrix_error() noexcept {}
	virtual ~singular_matrix_error() noexcept {}

	virtual const char* what() const noexcept {
		return "Illegal operation on singular matrix.";  
	}
};

#endif