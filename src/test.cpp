#include <iostream>
#include "jsobject.h"

int main(int argc, char **argv) {
	jsobject obj;
	obj["name"] = "tmarrinan";
	obj["year"] = 2017;
	obj["contact"] = *jsobject::parse("{'phones':[\"999-999-9999\", \"012-345-6789\"],\"email\":\"me@abc123.com\",empty:null}");
	obj["half"] = 0.5;

	jsarray &phones = obj["contact"]["phones"];
	phones.append((void*)NULL);
	phones.append(false);
	phones.append(3.14159);

	obj["nothing"] = (void*)NULL;

	bool hasEmail = obj["contact"].hasProperty("email");
	bool hasFax = obj["contact"].hasProperty("fax");
	std::cout << "has email? " << hasEmail << ", has fax? " << hasFax << std::endl;

	std::cout << obj.stringify(true) << std::endl;
	
	return 0;
}