#include <iostream>
#include "jsobject.hpp"

std::string getExePath(std::string exe);

int main(int argc, char **argv) {
	std::string exePath = getExePath(argv[0]);

	// read json from file
	jsvar readObj = jsobject::parseFromFile(exePath + "../resrc/json5_eg.json");
	std::cout << std::endl << "--------------------------------" << std::endl;
	std::cout << "JSON5 parsed from file:" << std::endl;
	std::cout << readObj.stringify(true) << std::endl;

	// parse json from string
	jsvar strObj = jsobject::parse("{'phones':[\"999-999-9999\",\"012-345-6789\"],\"email\":\"me@abc123.com\",empty:null}");
	std::cout << std::endl << "--------------------------------" << std::endl;
	std::cout << "JSON5 parsed from string:" << std::endl;
	std::cout << strObj.stringify(true) << std::endl;

	// create object
	jsvar newObj;
	newObj["name"] = "tmarrinan";
	newObj["year"] = 2017;
	jsvar todo;
	todo.append("task1");
	todo.append("task2");
	todo.append(3);
	todo.append(-12.5);
	todo.append(JS_NULL);
	newObj["todo"] = todo;
	std::cout << std::endl << "--------------------------------" << std::endl;
	std::cout << "JS object created from scratch:" << std::endl;
	std::cout << newObj.stringify(true) << std::endl;

	// modify an object
	newObj["todo"][3] = "task4";
	newObj["todo"][4] = 5;
	newObj.remove("year");
	std::cout << std::endl << "--------------------------------" << std::endl;
	std::cout << "JS object modification (w/ variable type changes):" << std::endl;
	std::cout << newObj.stringify(true) << std::endl;

	// checking existance
	bool hasEmail = strObj.hasProperty("email");
	bool hasFax = strObj.hasProperty("fax");
	std::cout << std::endl << "--------------------------------" << std::endl;
	std::cout << "Checking existance of items:" << std::endl;
	std::cout << "object has email? " << hasEmail << ", has fax? " << hasFax << std::endl;
	std::cout << "number of phones? " << strObj["phones"].length() << std::endl;

	std::cout << std::endl;

	return 0;
}

std::string getExePath(std::string exe) {
	size_t pos = exe.rfind("/");
	if (pos == std::string::npos)
		return std::string("./");
	return exe.substr(0, pos+1);
}
