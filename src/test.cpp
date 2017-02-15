#include <iostream>
#include "jsobject.h"

int main(int argc, char **argv) {
	// create object manually
	jsarray *a = new jsarray();
	a->addFloatToArray(3.14159);
	a->addIntegerToArray(100);
	a->addBooleanToArray(false);
	a->addTextToArray("hello world!");

	jsobject *b = new jsobject();
	b->addBooleanToObject("is_open", true);
	b->addTextToObject("location", "here 123");
	b->addFloatToObject("temperature", -17.5);
	b->addArrayToObject("my_list", a);

	std::string bjson = b->stringify();
	printf("JSOBJECT: %s\n", bjson.c_str());


	// load object from json file
	jsobject *c = jsobject::parseFromFile("input.json");
	std::string cjson = c->stringify(true);
	printf("\nJSOBJECT:\n%s\n", cjson.c_str());

	printf("name: %s\n", c->getItemAsText("name").c_str());
	printf("picture?: %s\n", c->getItemAsArray("attribs")->getElementAsArray(4)->getElementAsText(0).c_str());
	printf("attribs size: %lu\n", c->getItemAsArray("attribs")->length());

	return 0;
}