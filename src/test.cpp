#include <iostream>
#include "jsobject.h"

int main(int argc, char **argv) {
	// load object from json file
	jsobject *objptr = jsobject::parseFromFile("input.json");
	jsobject obj = *objptr;

	printf("\noriginal:\n%s\n", obj.stringify(true).c_str());


	// change name, add to attribs inner array
	obj["name"] = -98989.98989;
	obj["attribs"][4].append(1000000);

	jsarray &a = obj["attribs"][4];
	a.append(1000000);

	jsobject &o = obj["attribs"][4][2]["obj"];
	o["not_empty"] = true;

	printf("\nmodified:\n%s\n", obj.stringify(true).c_str());



	jsobject aobj;
	aobj["name"] = "tmarrinan";
	aobj["year"] = 2017;
	aobj["contact"] = *jsobject::parse("{\"phone\":\"999-999-9999\",\"email\":\"me@abc123.com\"}");
	aobj["half"] = 0.5;

	std::cout << aobj.stringify(true) << std::endl;
	
	return 0;
}