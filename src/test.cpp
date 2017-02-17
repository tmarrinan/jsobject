#include <iostream>
#include "jsobject.h"

int main(int argc, char **argv) {
	jsvar obj;
	obj["name"] = "tmarrinan";
	obj["year"] = 2017;
	obj["contact"] = jsobject::parse("{'phones':[\"999-999-9999\", \"012-345-6789\"],\"email\":\"me@abc123.com\",empty:null}");
	obj["half"] = 0.5;

	jsvar phones = obj["contact"]["phones"];
	phones.append((void*)NULL);
	phones.append(false);
	obj["contact"]["phones"].append(3.14159);

	jsvar contact = obj["contact"];
	contact["other"] = "1234 Abcd St, Anywhere, USA";

	jsvar arr;
	arr.append("test");
	arr.append(12.345);
	arr.append((void*)NULL);
	arr.append(false);

	obj["test_arr"] = arr;

	obj["nothing"] = (void*)NULL;
	obj["input"] = jsobject::parseFromFile("input.json");

	bool hasEmail = obj["contact"].hasProperty("email");
	bool hasFax = obj["contact"].hasProperty("fax");
	std::cout << "'contact' has email? " << hasEmail << ", has fax? " << hasFax << std::endl;
	std::cout << "'contact' number of phones? " << phones.length() << std::endl;

	std::cout << obj.stringify(true) << std::endl;
	
	return 0;
}