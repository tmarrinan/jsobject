#include <iostream>
#include "jsobject.h"

int main(int argc, char **argv) {
	jsvar obj = jsobject::parseFromFile("example.json");

	obj["name"] = "tmarrinan";
	obj["year"] = 2017;
	obj["contact"] = jsobject::parse("{'phones':[\"999-999-9999\",\"012-345-6789\"],\"email\":\"me@abc123.com\",empty:null}");
	obj["half"] = "1/2";

	jsvar phones = obj["contact"]["phones"];
	phones.append(JS_NULL);
	phones.append(false);
	obj["contact"]["phones"].append(3.14159);

	jsvar contact = obj["contact"];
	contact["other"] = "1234 Abcd St, Anywhere, USA";

	obj["nothing"] = JS_NULL;
	bool hasEmail = obj["contact"].hasProperty("email");
	bool hasFax = obj["contact"].hasProperty("fax");
	std::cout << "'contact' has email? " << hasEmail << ", has fax? " << hasFax << std::endl;
	std::cout << "'contact' number of phones? " << phones.length() << std::endl;

	std::cout << obj.stringify(true) << std::endl;

	std::cout << obj["oh"].stringify() << std::endl;

	
	return 0;
}