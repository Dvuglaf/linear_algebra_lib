// linear.cpp: определяет точку входа для приложения.
//

#include "linear.h"
#include "matrix.h"
#include <iostream>
#include "complex.h"
#include <vector>
#include "vector.h"
#include <unordered_map>
#include <variant>
#include <stack>
#include <regex>
#include <ctime>


const static std::string valid_characters_in_name = { "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ" };
const static std::string valid_operations = { "+-*/" };
const static std::string valid_characters_in_scalar = { "1234567890." };
static std::unordered_map<std::string, std::variant<linear::complex, linear::vector, linear::matrix, long double>> map;

struct user_enter {
	std::string expression;
	std::string function;
};

bool valid_name(const std::string& name) {
	for (auto& symbol : name) {
		if (valid_characters_in_name.find(symbol) == std::string::npos)
			return false;
	}
	return true;
}

bool valid_scalar(const std::string& scalar) {
	for (auto& symbol : scalar) {
		if (valid_characters_in_scalar.find(symbol) == std::string::npos) {
			return false;
		}
	}
	return true;
}

inline std::string replace_in_string(const std::string& string, const std::regex& substring, const std::string& replacement) {
	return std::regex_replace(string, substring, replacement);
}

std::vector<std::string> split(const std::string& string, const std::string& delimiter) {
	std::vector<std::string> tokens;
	size_t previous = 0, position = 0;
	do {
		position = string.find(delimiter, previous);
		if (position == std::string::npos) position = string.length();
		std::string token = string.substr(previous, position - previous);
		if (!token.empty()) tokens.push_back(token);
		previous = position + delimiter.length();
	} while (position < string.length() && previous < string.length());
	return tokens;
}


inline bool exist_name_in_map(const std::string& name) {
	return (map.find(name) == map.end()) ? false : true;
}

void count(std::stack<char>& t, std::stack<std::variant<linear::complex, linear::vector, linear::matrix, long double>>& e, const char symbol) {
	auto first = e.top();
	e.pop();
	auto second = e.top();
	e.pop();
	switch (t.top()) {
	case '+':
		if (first.index() == 0) {
			if (second.index() == 0) {
				e.push(std::get<linear::complex>(first) + std::get<linear::complex>(second));
			}
			else if (second.index() == 3) {
				e.push(std::get<linear::complex>(first) + std::get<long double>(second));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");

		}
		else if (first.index() == 1) {
			if (second.index() == 1) {
				e.push(std::get<linear::vector>(first) + std::get<linear::vector>(second));
			}
			else if (second.index() == 3) {
//				auto result = std::get<linear::vector>(first) + std::get<long double>(second);
	//			e.push(result);
			}
			else 
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first.index() == 2) {
			if (second.index() == 2) {
				e.push(std::get<linear::matrix>(first) + std::get<linear::matrix>(second));
			}
			else if (second.index() == 3) {

			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first.index() == 3) {
			if (second.index() == 0) {
				e.push(std::get<long double>(first) + std::get<linear::complex>(second));
			}
			else if (second.index() == 1) {
				//auto result = std::get<long double>(first) + std::get<linear::vector>(second);
				//e.push(result);
			}
			else if (second.index() == 2) {
				//auto result = std::get<long double>(first) + std::get<linear::matrix>(second);
				//e.push(result);
			}
			else if (second.index() == 3) {
				e.push(std::get<long double>(first) + std::get<long double>(second));
			}
		}
		break;
	case '-':
		if (first.index() == 0) {
			if (second.index() == 0) {
				e.push(std::get<linear::complex>(second) - std::get<linear::complex>(first));
			}
			else if (second.index() == 3) {
				e.push(std::get<linear::complex>(second) - std::get<long double>(first));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");

		}
		else if (first.index() == 1) {
			if (second.index() == 1) {
				e.push(std::get<linear::vector>(second) - std::get<linear::vector>(first));
			}
			else if (second.index() == 3) {
				//auto result = std::get<long double>(second) - std::get<linear::vector>(first);
				//e.push(result);
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first.index() == 2) {
			if (second.index() == 2) {
				//auto result = std::get<linear::matrix>(first) - std::get<linear::matrix>(second);
				//e.push(result);
			}
			else if (second.index() == 3) {

			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first.index() == 3) {
			if (second.index() == 0) {
				e.push(std::get<linear::complex>(second) - std::get<long double>(first));
			}
			else if (second.index() == 1) {
				//auto result = std::get<linear::vector>(second) - std::get<long double>(first);
				//e.push(result);
			}
			else if (second.index() == 2) {
				//
			}
			else if (second.index() == 3) {
				e.push(std::get<long double>(second) - std::get<long double>(first));
			}
		}
		break;
	case '*':
		if (first.index() == 0) {
			if (second.index() == 0) {
				e.push(std::get<linear::complex>(first)* std::get<linear::complex>(second));
			}
			else if (second.index() == 3) {
				e.push(std::get<linear::complex>(first)* std::get<long double>(second));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");

		}
		else if (first.index() == 1) {
			/*if (second.index() == 1) {
				auto result = std::get<linear::vector>(first) * std::get<linear::vector>(second);
				e.push(result);
			}*/
			if (second.index() == 3) {
				e.push(std::get<linear::vector>(first)* std::get<long double>(second));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first.index() == 2) {
			if (second.index() == 2) {
				e.push(std::get<linear::matrix>(first)* std::get<linear::matrix>(second));
			}
			else if (second.index() == 3) {

			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first.index() == 3) {
			if (second.index() == 0) {
				e.push(std::get<long double>(first)* std::get<linear::complex>(second));
			}
			else if (second.index() == 1) {
				e.push(std::get<long double>(first)* std::get<linear::vector>(second));
			}
			else if (second.index() == 2) {
			//
			}
			else if (second.index() == 3) {
				e.push(std::get<long double>(first)* std::get<long double>(second));
			}
		}
		break;
	case '/':
		if (first.index() == 0) {
			if (second.index() == 0) {
				e.push(std::get<linear::complex>(second) / std::get<linear::complex>(first));
			}
			else if (second.index() == 3) {
				e.push(std::get<linear::complex>(second) / std::get<long double>(first));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");

		}
		else if (first.index() == 1) {
			if (second.index() == 1) {
				//
			}
			else if (second.index() == 3) {
				e.push(std::get<long double>(second) / std::get<linear::vector>(first));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first.index() == 2) {
			if (second.index() == 2) {
				//auto result = std::get<linear::matrix>(first) + std::get<linear::matrix>(second);
				//e.push(result);
			}
			else if (second.index() == 3) {

			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first.index() == 3) {
			if (second.index() == 0) {
				e.push(std::get<linear::complex>(second) / std::get<long double>(first));
			}
			else if (second.index() == 1) {
				e.push(std::get<linear::vector>(second) / std::get<long double>(first));
			}
			else if (second.index() == 2) {
				//
			}
			else if (second.index() == 3) {
				e.push(std::get<long double>(second) / std::get<long double>(first));
			}
		}
		break;
	}
	t.pop();
	if (symbol != ' ')
		t.push(symbol);
}

std::variant<linear::complex, linear::vector, linear::matrix, long double> zamelsonand_bauer(std::string& expression) {
	expression = '(' + expression + ')';
	std::stack<std::variant<linear::complex, linear::vector, linear::matrix, long double>> e;
	std::stack<char> t;
	e.push(0);
	t.push('$');
	size_t i = 0;
	char symbol = expression[i];
	char prev = ' ';
	while(true) {
		symbol = expression[i];
		if (symbol == '\0')
			symbol = '$';
		if (prev == '(' && symbol == '+' || symbol == '-') {
			if (e.top().index() == 0) {
				e.push(linear::complex(0,0));
			}
			else if (e.top().index() == 1) {
				e.push(linear::vector(0, 0));
			}
			else if (e.top().index() == 2) {
				e.push(linear::matrix(0, 0));
			}
			else if (e.top().index() == 3) {
				e.push(0.0);
			}
		}
		if (valid_characters_in_name.find(symbol)!=std::string::npos) {
			std::string name;
			while (valid_characters_in_name.find(symbol) != std::string::npos) {
				name.push_back(symbol);
				++i;
				prev = symbol;
				symbol = expression[i];
			}
			if (symbol != '+' && symbol != '-' && symbol != '*' && symbol != '/' && symbol != ')' && symbol != ' ')
				throw std::logic_error("Error: incorrect expression!");
			
			if (!exist_name_in_map(name))
				throw std::invalid_argument("Error: unknown name!");

			e.push(map[name]);
			continue;
		}
		else if (valid_characters_in_scalar.find(symbol) != std::string::npos) {
			std::string number;
			while (valid_characters_in_scalar.find(symbol) != std::string::npos) {
				number.push_back(symbol);
				++i;
				prev = symbol;
				symbol = expression[i];
			}
			e.push(std::stod(number));
			continue;
		}
		else if (symbol == '+' || symbol == '-') {
			if (t.top() == '(')
				t.push(symbol);
			else if (t.top() == '+' || t.top() == '-')
				count(t, e, symbol);
			else if (t.top() == '*' || t.top() == '/') {
				count(t, e, ' ');
				prev = symbol;
				continue;
			}
			else if (t.top() == '(' || t.top() == '$')
				t.push(symbol);
		}
		else if (symbol == '*' || symbol == '/') {
			if (t.top() == '(' || t.top() == '+' || t.top() == '-' || t.top() == '$')
				t.push(symbol);
			else if (t.top() == '*' || t.top() == '/')
				count(t, e, symbol);
		}
		else if (symbol == '(')
			t.push(symbol);
		else if (symbol == ')') {
			if (t.top() == '$')
				throw std::logic_error("Error: wrong expression!");
			else if (t.top() == '(')
				t.pop();
			else if (t.top() == '+' || t.top() == '-' || t.top() == '*' || t.top() == '/') {
				count(t, e, ' ');//
				prev = symbol;
				continue;
			}
		}
		else if (symbol == '$') {
			if (t.top() == '(')
				throw std::logic_error("Error: wrong expression!");
			else if (t.top() == '+' || t.top() == '-' || t.top() == '*' || t.top() == '/') {//4
				count(t, e, ' ');
				prev = symbol;
				continue;
			}
			else if (t.top() == '$')
				return e.top();
		}
		else if (symbol == ' ') {
			++i;
			prev = symbol;
			continue;
		}
		else if (valid_operations.find(symbol) == std::string::npos) 
			throw std::logic_error("Error: unknown operation!");
		++i;
		prev = symbol;
	}
}

bool create_double_function(const std::string& func) {
	const std::vector<std::string> functions = { "abs", "arg" };
	for (auto& function : functions) {
		if (func == function)
			return true;
	}
	return false;
}

bool create_vector_function(const std::string& func) {
	const std::vector<std::string> functions = { "cross_product", "vector" };
	for (auto& function : functions) {
		if (func == function)
			return true;
	}
	return false;

}

size_t number_of_substring_in_string(const std::string& string, const std::string& substing) {
	size_t result = 0;
	for (std::string::size_type i = 0; i < string.length(); ++i)
		if (string[i] == substing[0])
			if (string.substr(i, substing.length()) == substing)
			{
				++result;
				i += substing.length() - 1;
			}
	return result;
}

size_t number_of_space(const std::string& expression, const size_t start, const size_t stop) {
	size_t result = 0;
	for (size_t i = start; i < stop; ++i) {
		if (expression[i] == ' ') {
			++result;
		}
	}
	return result;
}

std::string function_name(const std::string& expression) {
	const std::vector<std::string> functions = { "abs","arg","conj","exp","log","sqrt", "pow", "transpose", "complex", "vector" };
	std::string result = "";
	for (auto& it : functions) {
		if (expression.find(it) != std::string::npos) {
			result = it;
		}
		if (number_of_substring_in_string(expression, it) > 1) {
			throw std::logic_error("Error: more than one function!");
		}
	}
	return result != "" ? result : "none";
}

bool create_complex_function(const std::string& func) {
	const std::vector<std::string> functions = { "conj","exp","log","sqrt", "pow", "complex" };
	for (auto& function : functions) {
		if (func == function)
			return true;
	}
	return false;
}

void cout_value(const std::string& name) {
	if (!exist_name_in_map(name)) {
		throw std::logic_error("Error: this name does not exist!");
	}
	if (map[name].index() == 0) {
		std::cout << std::endl << " " << std::get<linear::complex>(map[name]) << std::endl;
	}
	else if (map[name].index() == 1) {
		std::cout << std::endl << " " << std::get<linear::vector>(map[name]) << std::endl;
	}
	else if (map[name].index() == 2) {
		std::cout << std::endl << " " << std::get<linear::matrix>(map[name]) << std::endl;
	}
	else if (map[name].index() == 3) {
		std::cout << std::endl << " " << std::get<long double>(map[name]) << std::endl;
	}
}

void cout_expression(const std::variant<linear::complex, linear::vector, linear::matrix, long double>& value) {
	if (value.index() == 0) {
		std::cout << std::endl << " " << std::get<linear::complex>(value) << std::endl;
	}
	else if (value.index() == 1) {
		std::cout << std::endl << " " << std::get<linear::vector>(value) << std::endl;
	}
	else if (value.index() == 2) {
		std::cout << std::endl << " " << std::get<linear::matrix>(value) << std::endl;
	}
	else if (value.index() == 3) {
		std::cout << std::endl << " " << std::get<long double>(value) << std::endl;
	}
}

bool check_enter(const std::string& user_enter) {
	if (user_enter == "exit") {
		return true;
	}
	else if (user_enter == "help") {

	}
	return false;
}

void check_error(const std::string& user_enter) {
	size_t equality_count = number_of_substring_in_string(user_enter, "=");
	if (equality_count > 1) {
		throw std::logic_error("Error: too many assignments!");
	}
	auto vector = split(user_enter, "=");
	std::string expression = user_enter;
	if (equality_count == 1) {//оператор равно.
		expression = vector[1];
		if (!valid_name(vector[0] = std::regex_replace(vector[0], std::regex("\s+\s(?!\s)"), "")))//поменять логику
			throw std::logic_error("Error: wrong name!");
	}
	else {
		//
	}
	const std::string function = function_name(expression);
	if (function != "none") {
		auto left = expression.find('(');
		auto right = expression.find_last_of(')');
		if (left == std::string::npos || right == std::string::npos)
			throw std::logic_error("Error: wrong syntax!");
		if ((left != function.size() + number_of_space(expression, 0, left)) || right != expression.size() - number_of_space(expression, right, expression.size()) - 1) {
			throw std::logic_error("Error: wrong syntax!");
		}
		auto coma_count = number_of_substring_in_string(expression, ",");
		if (coma_count > 1) {
			//throw std::string("Error: too many comas!");
		}
		else if (coma_count == 0) {
			if (function == "complex" || function == "pow")
				throw std::logic_error("Error: few parametres in function " + function);
		}
	}
}

std::string name_help(const std::string& string) {
	std::string result(string);
	for (size_t i = 0; i < result.size(); ++i) {
		if (valid_characters_in_name.find(result[i]) == std::string::npos && result[i] == ' ') {
			result.erase(i, 1);
			--i;
		}
	}
	return result;
}

void parser(std::string& user_enter, std::string& function, std::string& name, std::string& expression, bool& equality) {
	check_error(user_enter);
	function = function_name(user_enter);
	size_t equality_count = number_of_substring_in_string(user_enter, "=");
	std::string before;
	auto vector = split(user_enter, "=");
	if (equality_count == 1) { //есть присваивание
		
		name = name_help(vector[0]);
		expression = vector[1];
		equality = true;
	}
	else {
		if (function == "none") {
			name = '\0';
			expression = vector[0];
		}
		else {
			expression = vector[0];
		}
		equality = false;
	}
}

linear::vector vector_help(const std::string& expression) {
	auto vector_of_value = split(expression, " ");
	linear::vector vector(0);
	try {
		for (auto& str : vector_of_value) {
			if (!exist_name_in_map(str) && valid_scalar(str)) {
				vector.push_back(std::stod(str));
			}
			else if (exist_name_in_map(str)) {
				vector.push_back(std::get<long double>(map[str]));
			}
			else {
				throw std::string();
			}
		}
	}
	catch (...) {
		throw std::logic_error("Error: wrong expression!");
	}
	return vector;
}

linear::vector create_vector(const std::vector<std::string> splitted_expression) {
	linear::vector result(0);
	if (splitted_expression.size() > 3) {
		throw std::logic_error("Error: too many comas!");
	}
	auto start = std::stold(splitted_expression[0]);
	auto stop = std::stold(splitted_expression[1]);
	auto step = std::stold(splitted_expression[2]);
	if (start < stop) {
		if (step <= 0) {
			throw std::invalid_argument("Error: step has negative value!");
		}

		for (auto i = start; i < stop; i += step) {
			result.push_back(i);
		}
	}
	else if (start > stop) {
		if (step >= 0) {
			throw std::invalid_argument("Error: step has positive value!");
		}
		for (auto i = start; i > stop; i += step) {
			result.push_back(i);
		}
	}
	return result;


}

std::variant < linear::complex, linear::vector, linear::matrix, long double> execute(std::string& expression, const std::string& function_name, const bool function) {
	if (function) {
		expression.erase(expression.find('('), 1);
		expression.erase(expression.find_last_of(')'), 1);
		expression = std::regex_replace(expression, std::regex('(' + function_name + ')' + '+'), "");

		if (create_complex_function(function_name)) {
			auto vector = split(expression, ",");
			std::string left = vector[0], right = "none";
			linear::complex z;
			try {
				if (function_name == "pow") {
					right = vector[1];
					auto vec = split(expression, ",");
					long double pow = std::get<long double>(zamelsonand_bauer(left));
					z = std::get<linear::complex>(zamelsonand_bauer(right));
					return linear::pow(pow, z);
				}
				if (function_name == "complex") {
					right = vector[1];
					z.real(std::get<long double>(zamelsonand_bauer(left)));
					z.imag(std::get<long double>(zamelsonand_bauer(right)));
					return z;

				}
			}
			catch (...) {
				throw std::logic_error("Error: wrong expression!");
			}
			if (right != "none") {
				throw std::logic_error("Error: too many parameters in function!");
			}
			z = std::get<linear::complex>(map[left]);
			if (function_name == "conj") {
				auto value = linear::conj(z);
				return value;
			}
			else if (function_name == "exp") {
				auto value = linear::exp(z);
				return value;
			}
			else if (function_name == "log") {
				auto value = linear::log(z);
				return value;
			}
			else if (function_name == "sqrt") {
				auto value = linear::sqrt(z);
				return value;
			}
		}
		else if (create_double_function(function_name)) {
			auto vector = split(expression, ",");
			if (function_name == "none") {
				auto value = std::stod(vector[0]);
				return value;
			}
			else if (function_name == "abs") {
				auto value = linear::abs(std::get<linear::complex>(zamelsonand_bauer(vector[0])));
				return value;
			}
			else if (function_name == "arg") {
				auto value = linear::arg(std::get<linear::complex>(zamelsonand_bauer(vector[0])));
				return value;
			}
		}
		else if (create_vector_function(function_name)) {
			if (number_of_substring_in_string(expression, ",") == 2) {
				auto vector = split(expression, ",");
				return create_vector(vector);

			}
			return vector_help(expression);
		}
	}
	return zamelsonand_bauer(expression);

}

void new_cycle() {
	while (true) {
		try {
			std::string user_enter;
			while (user_enter.size() == 0) {

				std::cout << ">> ";
				std::getline(std::cin, user_enter);
			}
			if (check_enter(user_enter))
				break;
			bool equality = false;
			std::string function, expression, name;
			parser(user_enter, function, name, expression, equality);
			if (equality) {
				auto value = function == "none" ? execute(expression, function, false) : execute(expression, function, true);
				map[name] = value;
				cout_value(name);
			}
			else {
				if (function != "none") {
					cout_expression(execute(expression, function, true));
					continue;
				}
				if (!exist_name_in_map(name)) {
					cout_expression(execute(expression, function, false));
					continue;
				}
				else
					cout_value(name);
			}
		}

		catch (std::string& error) {
			std::cout << std::endl << error << std::endl;
		}
	
	}
}

//user_enter - все, что ввел пользователь
//function - название функции
//expression - выражение после названия функции в скобках или весь ввод слева.

int main()
{
	/*
		TODO: СДЕЛАТЬ ОБЩИЙ ДЛЯ complex, vector, linear::matrix НУЛЕВОЙ ЭЛЕМЕНТ!!!!!!и заменить в строке e.push(0);
	
	*/
	//to create vector: variable_name = vector(values with delimiter ' ')
	//example: vec = vector(1 3.14 2 9)
	//or variable_name = vector(start_value, stop_value, step)
	//example: vec = vector(1.1, 2, 0.2)
	//vec = (1.1, 1.3, 1.5, 1.7, 1.9)

	//to create complex: variable_name = complex(real_part, imaginary_part)
	//example: c = complex(100, 3.2)
	//new_cycle();
	using namespace linear;
	matrix m1(2,2);	
	
	is_identity(m1);
	int a = 2;
	return 0;
}
