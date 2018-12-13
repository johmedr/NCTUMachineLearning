#ifndef IO_HXX
#define IO_HXX
 
#include <fstream>
#include <string>
#include <regex>

#include <DynamicMatrix.hxx>

template <typename T>
void parseFile(std::string filename, Matrix<T> & x, Matrix<T> & y) 
{
	std::ifstream file(filename); 
	if(file.is_open()) 
	{ 
		std::regex pattern("[0-9]+(\\.[0-9]+)?,[0-9]+(\\.[0-9]+)?"); 

		size_t data_count = 0;
		std::string line; 
		char c; 

		while(std::getline(file, line)) 
			if(std::regex_match(line, pattern))
				++data_count; 

		x.reshape(data_count, 1); 
		y.reshape(data_count, 1); 

		file.clear(); 
		file.seekg(0, file.beg); 

		data_count = 0; 

		while(std::getline(file, line))
		{
			if(std::regex_match(line, pattern)) {
				std::istringstream ss(line); 

				ss >> x(data_count, 0) >> c >> y(data_count, 0); 
				
				++data_count; 
			}
		}
		file.close(); 
	}
	else 
		throw std::ios_base::failure("Cannot open file : " + filename);  
}

#endif