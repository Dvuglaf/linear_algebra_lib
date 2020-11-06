#include <string>
class var {
	std::string name;
	std::string type;

public:
	var(std::string, std::string);
};

inline var::var(std::string n, std::string type)
{
	name = n;
	type = typeid(type).name();
}
