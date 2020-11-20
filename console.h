#pragma once

#include <regex>
#include <vector>
#include <stack>
#include <unordered_map>
#include <string>
#include "vector.h"
#include "complex.h"
#include "matrix.h"
#include <variant>

class console {
public:
	void operator()();
	

private:
	const std::string valid_characters_in_name = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	const std::string valid_operations = { "+-*/" };
	const std::string valid_characters_in_scalar = { "-1234567890." };
	std::unordered_map<std::string, std::variant<linear::complex, linear::vector, linear::matrix, long double>> map;

	void start();
	bool valid_name(const std::string&);
	bool valid_scalar(const std::string&);
	inline std::string replace_in_string(const std::string&, const std::regex&, const std::string&);
	std::vector<std::string> split(const std::string&, const std::string&);
	inline bool exist_name_in_map(const std::string&);
	void count(std::stack<char>& , std::stack<std::variant<linear::complex, linear::vector, linear::matrix, long double>>&, char);
	std::variant<linear::complex, linear::vector, linear::matrix, long double> zamelsonand_bauer(std::string&);
	bool create_double_function(const std::string&);
	bool create_vector_function(const std::string&);
	size_t number_of_substring_in_string(const std::string&, const std::string&);
	size_t number_of_space(const std::string&, size_t, size_t);
	std::string function_name(const std::string&);
	bool create_complex_function(const std::string&);
	void cout_value(const std::string&);
	void cout_expression(const std::variant<linear::complex, linear::vector, linear::matrix, long double>&);
	bool check_enter(const std::string&);
	bool check_error(const std::vector<std::string>&, const std::string&, std::string&);
	std::string name_help(const std::string&);
	void parser(std::string& , std::string&, std::string&, std::string&, bool&);
	linear::vector vector_help(const std::string&);
	linear::vector create_vector(const std::vector<std::string>);
	std::variant < linear::complex, linear::vector, linear::matrix, long double> execute(std::string&, const std::string&, bool);
};