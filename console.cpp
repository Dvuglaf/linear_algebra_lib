#include "console.h"
#include <exception>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <clocale>

void console::operator()(){
	start();
}

void console::start(){
	while (true) {
		try {
			std::string user_enter;
			while (user_enter.size() == 0) {

				std::cout << ">> ";
				std::getline(std::cin, user_enter);
			}
			if (check_enter(user_enter))
				continue;
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

		catch (const std::exception& e) {
			std::cout << std::endl << e.what() << std::endl;
		}

	}

}

bool console::valid_name(const std::string& name) {
	for (auto& symbol : name) {
		if (valid_characters_in_name.find(symbol) == std::string::npos)
			return false;
	}
	return true;
}

bool console::valid_scalar(const std::string& scalar) {
	for (auto& symbol : scalar) {
		if (valid_characters_in_scalar.find(symbol) == std::string::npos) {
			return false;
		}
		if (symbol == '-' && scalar.find_last_of('-') != 0) {
			return false;
		}
	}
	return true;
}

inline std::string console::replace_in_string(const std::string& string, const std::regex& substring, const std::string& replacement) {
	return std::regex_replace(string, substring, replacement);
}

std::vector<std::string> console::split(const std::string& string, const std::string& delimiter) {
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

inline bool console::exist_name_in_map(const std::string& name) {
	return (map.find(name) == map.end()) ? false : true;
}

void console::count(std::stack<char>& t, std::stack<std::variant<linear::complex, linear::vector, linear::matrix, long double>>& e, const char symbol) {
	auto first = e.top();
	e.pop();
	auto second = e.top();
	e.pop();
	auto first_index = first.index();
	auto second_index = second.index();
	switch (t.top()) {
	case '+':
		if (first_index == 0) {
			if (second_index == 0) {
				e.push(std::get<linear::complex>(first) + std::get<linear::complex>(second));
			}
			else if (second_index == 3) {
				e.push(std::get<linear::complex>(first) + std::get<long double>(second));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");

		}
		else if (first_index == 1) {
			if (second_index == 1) {
				e.push(std::get<linear::vector>(first) + std::get<linear::vector>(second));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first_index == 2) {
			if (second_index == 2) {
				e.push(std::get<linear::matrix>(first) + std::get<linear::matrix>(second));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first_index == 3) {
			if (second_index == 0) {
				e.push(std::get<long double>(first) + std::get<linear::complex>(second));
			}
			else if (second_index == 3) {
				e.push(std::get<long double>(first) + std::get<long double>(second));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");

		}
		break;
	case '-':
		if (first_index == 0) {
			if (second_index == 0) {
				e.push(std::get<linear::complex>(second) - std::get<linear::complex>(first));
			}
			else if (second_index == 3) {
				e.push(std::get<long double>(second) - std::get<linear::complex>(first));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");

		}
		else if (first_index == 1) {
			if (second_index == 1) {
				e.push(std::get<linear::vector>(second) - std::get<linear::vector>(first));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first.index() == 2) {
			if (second_index == 2) {
				auto result = std::get<linear::matrix>(first) - std::get<linear::matrix>(second);
				e.push(result);
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first_index == 3) {
			if (second_index == 0) {
				e.push(std::get<linear::complex>(second) - std::get<long double>(first));
			}
			else if (second_index == 3) {
				e.push(std::get<long double>(second) - std::get<long double>(first));
			}
		}
		break;
	case '*':
		if (first_index == 0) {
			if (second_index == 0) {
				e.push(std::get<linear::complex>(first) * std::get<linear::complex>(second));
			}
			else if (second_index == 3) {
				e.push(std::get<linear::complex>(first) * std::get<long double>(second));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");

		}
		else if (first_index == 1) {
			if (second_index == 2) {
				e.push(std::get<linear::vector>(first) * std::get<linear::matrix>(second));
			}
			else if (second_index == 3) {
				e.push(std::get<linear::vector>(first) * std::get<long double>(second));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first_index == 2) {
			if (second_index == 1) {
				e.push(std::get<linear::vector>(first) * std::get<linear::matrix>(second));
			}
			else if (second_index == 2) {
				e.push(std::get<linear::matrix>(first) * std::get<linear::matrix>(second));
			}
			else if (second_index == 3) {
				e.push(std::get<linear::matrix>(first) * std::get<long double>(second));

			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first_index == 3) {
			if (second_index == 0) {
				e.push(std::get<long double>(first) * std::get<linear::complex>(second));
			}
			else if (second_index == 1) {
				e.push(std::get<long double>(first) * std::get<linear::vector>(second));
			}
			else if (second_index == 2) {
				e.push(std::get<long double>(first) * std::get<linear::matrix>(second));

			}
			else if (second_index == 3) {
				e.push(std::get<long double>(first) * std::get<long double>(second));
			}
		}
		break;
	case '/':
		if (first_index == 0) {
			if (second_index == 0) {
				e.push(std::get<linear::complex>(second) / std::get<linear::complex>(first));
			}
			else if (second_index == 3) {
				e.push(std::get<linear::complex>(second) / std::get<long double>(first));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");

		}
		else if (first_index == 1) {
			if (second_index == 3) {
				e.push(std::get<long double>(second) / std::get<linear::vector>(first));
			}
			else
				throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first_index == 2) {
			throw std::invalid_argument("Error: no operator found for the given operand action!");
		}
		else if (first_index == 3) {
			if (second_index == 0) {
				e.push(std::get<linear::complex>(second) / std::get<long double>(first));
			}
			else if (second_index == 1) {
				e.push(std::get<linear::vector>(second) / std::get<long double>(first));
			}
			else if (second_index == 2) {
				e.push(std::get<linear::matrix>(second) / std::get<long double>(first));
			}
			else if (second_index == 3) {
				e.push(std::get<long double>(second) / std::get<long double>(first));
			}
		}
		break;
	}
	t.pop();
	if (symbol != ' ')
		t.push(symbol);
}

std::variant<linear::complex, linear::vector, linear::matrix, long double> console::zamelsonand_bauer(std::string& expression) {
	expression = '(' + expression + ')';
	std::stack<std::variant<linear::complex, linear::vector, linear::matrix, long double>> e;
	std::stack<char> t;
	e.push(0);
	t.push('$');
	size_t i = 0;
	char symbol = expression[i];
	char prev = ' ';
	while (true) {
		symbol = expression[i];
		if (symbol == '\0')
			symbol = '$';
		if (prev == '(' && (symbol == '+' || symbol == '-')) {
			throw std::logic_error("Error: unary operations don't supported!");
		}
		if (valid_characters_in_name.find(symbol) != std::string::npos) {
			std::string name;
			while (valid_characters_in_name.find(symbol) != std::string::npos) {
				name.push_back(symbol);
				++i;
				prev = symbol;
				symbol = expression[i];
			}
			if (!exist_name_in_map(name))
				throw std::invalid_argument("Error: unknown name!");

			e.push(map[name]);
			continue;
		}
		else if (valid_characters_in_scalar.find(symbol) != std::string::npos && valid_operations.find(symbol) == std::string::npos) {
			std::string number;
			while (valid_characters_in_scalar.find(symbol) != std::string::npos && valid_operations.find(symbol)==std::string::npos) {
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
			else if (valid_operations.find(prev) != std::string::npos) {
				throw std::logic_error("Error: wrong expression!");
			}
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
			throw std::logic_error("Error: expression must not contain spaces!");
		}
		else if (valid_operations.find(symbol) == std::string::npos)
			throw std::logic_error("Error: unknown operation!");
		++i;
		prev = symbol;
	}
}

bool console::create_double_function(const std::string& func) {
	const std::vector<std::string> functions = { "abs", "arg", "scalar" };
	for (auto& function : functions) {
		if (func == function)
			return true;
	}
	return false;
}

bool console::create_vector_function(const std::string& func) {
	const std::vector<std::string> functions = { "cross_product", "vector" };
	for (auto& function : functions) {
		if (func == function)
			return true;
	}
	return false;

}

size_t console::number_of_substring_in_string(const std::string& string, const std::string& substing) {
	//size_t temp = std::count
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

size_t console::number_of_space(const std::string& expression, const size_t start, const size_t stop) {
	size_t result = 0;
	for (size_t i = start; i < stop; ++i) {
		if (expression[i] == ' ') {
			++result;
		}
	}
	return result;
}

std::string console::function_name(const std::string& expression) {
	const std::vector<std::string> functions = { "abs","arg","conj","exp","log","sqrt", "pow", "transpose", "complex", "vector", "scalar" };
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

bool console::create_complex_function(const std::string& func) {
	const std::vector<std::string> functions = { "conj","exp","log","sqrt", "pow", "complex" };
	for (auto& function : functions) {
		if (func == function)
			return true;
	}
	return false;
}

void console::cout_value(const std::string& name) {
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

void console::cout_expression(const std::variant<linear::complex, linear::vector, linear::matrix, long double>& value) {
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

bool console::check_enter(const std::string& user_enter) {
	if (user_enter == "exit") {
		exit(0);
	}
	else if (user_enter == "help") {
		setlocale(LC_ALL, "rus");
		int number;
		std::string line;
		std::ifstream in;
		std::cout << "1. Комплексные числа.\n2. Вектора.\n3. Матрицы.\n4. Ввод/вывод.\n5. Выход\n>> ";
		std::cin >> number;

		if (number == 1) {
			wchar_t* Path = L".\\complex.txt";
			in.open(Path);
			if (in.is_open()) {
				while (getline(in, line)) {
					std::cout << line << std::endl;
				}
			}
		}
		else if (number == 2) {
			in.open("..\\vector.txt");
			if (in.is_open()) {
				while (getline(in, line)) {
					std::cout << line << std::endl;
				}
			}

		}
		else if (number == 3) {
			in.open("\\matrix.txt");
			if (in.is_open()) {
				while (getline(in, line)) {
					std::cout << line << std::endl;
				}
			}
		}
		else if (number == 4) {
			in.open("\\io.txt");
			if (in.is_open()) {
				while (getline(in, line)) {
					std::cout << line << std::endl;
				}
			}
		}
		else if (number == 5) {

		}
		else
			; 
		// закрываем файл
		std::cin.ignore();
		return true;
	}
	else if (user_enter == "clear") {
		system("cls");
		return true;
	}
	else if (user_enter == "var") {
		for (auto& it : map) {
			std::cout << std::endl << it.first << ":";
			cout_value(it.first);
		}
		return true;
	}
	return false;
}



bool console::check_error(const std::vector<std::string>& vector, const std::string& function, std::string& error) {
	if (vector.size() > 2) {
		error = "Error: too many assignments!";
		return false;
	}
	if (vector.size() == 2) {//оператор равно.
		std::string name = name_help(vector[0]);
		if (!valid_name(name)) {
			error = "Error: wrong name!";
			return false;
		}
	}
	else 


	if (function != "none") {
		auto comma_count = number_of_substring_in_string(vector.size() == 2 ? vector[1] : vector[0], ",");
		if (function == "complex" || function == "pow") {
			if (comma_count != 1) {
				error = "Error: one comma expected!";
				return false;
			}
		}
		else if (function == "vector") {
			if (comma_count != 0 && comma_count != 2) {
				error = "Error: zero or two commas expected!";
				return false;
			}
		}
	}
	return true;
}

std::string console::name_help(const std::string& string) {
	std::string result(string);
	for (size_t i = 0; i < result.size(); ++i) {
		if (valid_characters_in_name.find(result[i]) == std::string::npos && result[i] == ' ') {
			result.erase(i, 1);
			--i;
		}
		else
			break;
	}
	for (size_t i = result.size() - 1; i > 0; --i) {
		if (valid_characters_in_name.find(result[i]) == std::string::npos && result[i] == ' ') {
			result.erase(i, 1);
			//++i;
		}
		else
			break;
	}
	return result;
}

void console::parser(std::string& user_enter, std::string& function, std::string& name, std::string& expression, bool& equality) {
	function = function_name(user_enter);
	size_t equality_count = number_of_substring_in_string(user_enter, "=");
	auto vector = split(user_enter, "=");
	std::string error;

	if (!check_error(vector, function, error))
		throw std::logic_error(error);

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

linear::vector console::vector_help(const std::string& expression) {
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

linear::vector console::create_vector(const std::vector<std::string> splitted_expression) {
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

std::variant < linear::complex, linear::vector, linear::matrix, long double> console::execute(std::string& expression, const std::string& function_name, const bool function) {
	if (function) {
		std::regex words_regex("(^\\s+|"+ function_name + ")(\\s+|)");
		expression = std::regex_replace(expression, words_regex, "");
		expression.erase(0, 1);
		expression.erase(expression.size() - 1, 1);
		if (create_complex_function(function_name)) {
			const auto vector = split(expression, ",");
			std::string left = std::regex_replace(vector[0], std::regex("(^\\s+|\\s+$)"), ""), right = "none";
			linear::complex z;
			try {
				if (function_name == "pow") {
					right = std::regex_replace(vector[1], std::regex("(^\\s+|\\s+$)"), "");
					linear::complex pow = std::get<linear::complex>(zamelsonand_bauer(left));
					z = std::get<linear::complex>(zamelsonand_bauer(right));
					return linear::pow(pow, z);
				}
				if (function_name == "complex") {
					right = std::regex_replace(vector[1], std::regex("(^\\s+|\\s+$)"), "");
					z.real(exist_name_in_map(left) ? std::get<long double>(map[left]) : std::stold(left));
					z.imag(exist_name_in_map(right) ? std::get<long double>(map[right]) : std::stold(right));
					return z;

				}
			}
			catch (const std::exception& e) {
				throw e;
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
			else if (function_name == "scalar") {
				auto value = linear::scalar(
					std::get<linear::vector>((zamelsonand_bauer(vector[0]))),
					std::get<linear::vector>((zamelsonand_bauer(vector[1])))
				);
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
	return zamelsonand_bauer(std::regex_replace(expression, std::regex("(^\\s+|\\s+$)"), ""));

}

