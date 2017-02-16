#include "jsobject.h"


/***************************************************************
 *  public methods: jsvar                                      *
 ***************************************************************/
jsvar::jsvar() {
	type = JS_TYPE_INVALID;
}

jsvar::jsvar(bool value) {
	type = JS_TYPE_BOOLEAN;
	boolean = value;
}

jsvar::jsvar(char value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
}

jsvar::jsvar(short value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
}

jsvar::jsvar(int value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
}

jsvar::jsvar(long value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
}

jsvar::jsvar(long long value) {
	type = JS_TYPE_INTEGER;
	inumber = value;
}

jsvar::jsvar(unsigned char value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
}

jsvar::jsvar(unsigned short value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
}

jsvar::jsvar(unsigned int value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
}

jsvar::jsvar(unsigned long value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
}

jsvar::jsvar(unsigned long long value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
}

jsvar::jsvar(float value) {
	type = JS_TYPE_FLOAT;
	fnumber = (double)value;
}

jsvar::jsvar(double value) {
	type = JS_TYPE_FLOAT;
	fnumber = value;
}

jsvar::jsvar(const char *value) {
	type = JS_TYPE_TEXT;
	text = std::string(value);
}

jsvar::jsvar(std::string value) {
	type = JS_TYPE_TEXT;
	text = value;
}

jsvar::jsvar(jsarray &value) {
	type = JS_TYPE_ARRAY;
	array = &value;
}

jsvar::jsvar(jsobject &value) {
	type = JS_TYPE_OBJECT;
	object = &value;
}

jsvar::jsvar(void *value) {
	if (value != NULL) {
		fprintf(stderr, "Invalid access of jsvar type null\n");
		exit(1);
	}
	type = JS_TYPE_NULL;
}

jsvar::operator bool() {
	if (type != JS_TYPE_BOOLEAN) {
		fprintf(stderr, "Invalid access of jsvar type boolean\n");
		exit(1);
	}
	return boolean;
}

jsvar::operator char() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return (char)inumber;
	return (char)fnumber;
}

jsvar::operator short() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return (short)inumber;
	return (short)fnumber;
}

jsvar::operator int() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return (int)inumber;
	return (int)fnumber;
}

jsvar::operator long() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return (long)inumber;
	return (long)fnumber;
}

jsvar::operator long long() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return inumber;
	return (long long)fnumber;
}

jsvar::operator unsigned char() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return (unsigned char)inumber;
	return (unsigned char)fnumber;
}

jsvar::operator unsigned short() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return (unsigned short)inumber;
	return (unsigned short)fnumber;
}

jsvar::operator unsigned int() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return (unsigned int)inumber;
	return (unsigned int)fnumber;
}

jsvar::operator unsigned long() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return (unsigned long)inumber;
	return (unsigned long)fnumber;
}

jsvar::operator unsigned long long() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return (unsigned long long)inumber;
	return (unsigned long long)fnumber;
}

jsvar::operator float() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return (float)inumber;
	printf("conversion to float: %.6f\n", (float)fnumber);
	return (float)fnumber;
}

jsvar::operator double() {
	if (type != JS_TYPE_INTEGER && type != JS_TYPE_FLOAT) {
		fprintf(stderr, "Invalid access of jsvar type number\n");
		exit(1);
	}
	if (type == JS_TYPE_INTEGER)
		return (double)inumber;
	return fnumber;
}

jsvar::operator std::string() {
	if (type != JS_TYPE_TEXT) {
		fprintf(stderr, "Invalid access of jsvar type text\n");
		exit(1);
	}
	return text;
}

jsvar::operator jsarray&() {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	return *array;
}

jsvar::operator jsobject&() {
	if (type != JS_TYPE_OBJECT) {
		fprintf(stderr, "Invalid access of jsvar type object\n");
		exit(1);
	}
	return *object;
}

jsvar& jsvar::operator=(bool value) {
	type = JS_TYPE_BOOLEAN;
	boolean = value;
	return *this;
}

jsvar& jsvar::operator=(char value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
	return *this;
}

jsvar& jsvar::operator=(short value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
	return *this;
}

jsvar& jsvar::operator=(int value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
	return *this;
}

jsvar& jsvar::operator=(long value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
	return *this;
}

jsvar& jsvar::operator=(long long value) {
	type = JS_TYPE_INTEGER;
	inumber = value;
	return *this;
}

jsvar& jsvar::operator=(unsigned char value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
	return *this;
}

jsvar& jsvar::operator=(unsigned short value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
	return *this;
}

jsvar& jsvar::operator=(unsigned int value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
	return *this;
}

jsvar& jsvar::operator=(unsigned long value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
	return *this;
}

jsvar& jsvar::operator=(unsigned long long value) {
	type = JS_TYPE_INTEGER;
	inumber = (long long)value;
	return *this;
}

jsvar& jsvar::operator=(float value) {
	type = JS_TYPE_FLOAT;
	fnumber = (double)value;
	return *this;
}

jsvar& jsvar::operator=(double value) {
	type = JS_TYPE_FLOAT;
	fnumber = value;
	return *this;
}

jsvar& jsvar::operator=(const char *value) {
	type = JS_TYPE_TEXT;
	text = std::string(value);
	return *this;
}

jsvar& jsvar::operator=(std::string value) {
	type = JS_TYPE_TEXT;
	text = value;
	return *this;
}

jsvar& jsvar::operator=(jsarray &value) {
	type = JS_TYPE_ARRAY;
	array = &value;
	return *this;
}

jsvar& jsvar::operator=(jsobject &value) {
	type = JS_TYPE_OBJECT;
	object = &value;
	return *this;
}

jsvar& jsvar::operator=(void *value) {
	if (value != NULL) {
		fprintf(stderr, "Invalid access of jsvar type null\n");
		exit(1);
	}
	type = JS_TYPE_NULL;
	return *this;
}

jsvar& jsvar::operator[](int index) {
	return (*this)[(size_t)index];
}

jsvar& jsvar::operator[](size_t index) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	return (*array)[index];
}

jsvar& jsvar::operator[](const char *key) {
	return (*this)[std::string(key)];
}

jsvar& jsvar::operator[](std::string key) {
	if (type != JS_TYPE_OBJECT) {
		fprintf(stderr, "Invalid access of jsvar type object\n");
		exit(1);
	}
	return (*object)[key];
}

int jsvar::getType() {
	return type;
}

std::string jsvar::toString(bool pretty, int indent) {
	size_t pos, start, escape;
	char canum[64];
	std::string esctext;
	std::string result = "";

	switch (type) {
		case JS_TYPE_NULL:
			result = "null";
			break;
		case JS_TYPE_BOOLEAN:
			if (boolean == true)
				result = "true";
			else
				result = "false";
			break;
		case JS_TYPE_INTEGER:
			sprintf(canum, "%lld", inumber);
			result = std::string(canum);
			break;
		case JS_TYPE_FLOAT:
			sprintf(canum, "%.14lf", fnumber);
			result = std::string(canum);
			pos = result.find_last_not_of("0");
			if (pos != std::string::npos)
				result = result.substr(0, pos+1);
			if (result[result.length()-1] == '.')
				result += "0";
			break;
		case JS_TYPE_TEXT:
			esctext = text;
			start = 0;
			escape = esctext.find_first_of("\"\'");
			while (escape != std::string::npos) {
				esctext = esctext.substr(0, escape) + "\\" + esctext.substr(escape);
				start = escape + 2;
				escape = esctext.find_first_of("\"\'", start);
			}
			result += "\"" + esctext + "\"";
			break;
		case JS_TYPE_ARRAY:
			result = array->stringify(pretty, indent);
			break;
		case JS_TYPE_OBJECT:
			result = object->stringify(pretty, indent);
			break;
	}
	return result;
}

void jsvar::append(jsvar &value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(bool value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(char value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(short value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(int value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(long value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(long long value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(unsigned char value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(unsigned short value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(unsigned int value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(unsigned long value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(unsigned long long value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(float value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(double value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(const char *value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(std::string value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(jsarray &value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(jsobject &value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

void jsvar::append(void *value) {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	array->append(value);
}

size_t jsvar::length() {
	if (type != JS_TYPE_ARRAY) {
		fprintf(stderr, "Invalid access of jsvar type array\n");
		exit(1);
	}
	return array->length();
}

std::vector<std::string> jsvar::keys() {
	if (type != JS_TYPE_OBJECT) {
		fprintf(stderr, "Invalid access of jsvar type object\n");
		exit(1);
	}
	return object->keys();
}

bool jsvar::hasProperty(std::string key) {
	if (type != JS_TYPE_OBJECT) {
		fprintf(stderr, "Invalid access of jsvar type object\n");
		exit(1);
	}
	return object->hasProperty(key);
}

std::string jsvar::stringify(bool pretty, int indent) {
	if (type != JS_TYPE_ARRAY && type != JS_TYPE_OBJECT) {
		fprintf(stderr, "Invalid access of jsvar type array/object\n");
		exit(1);
	}
	if (type == JS_TYPE_ARRAY)
		return array->stringify(pretty, indent);
	return object->stringify(pretty, indent);
}


/***************************************************************
 *  public methods: jsarray                                    *
 ***************************************************************/

jsvar& jsarray::operator[](int index) {
	return (*this)[(size_t)index];
}

jsvar& jsarray::operator[](size_t index) {
	if (index >= list.size()) {
		fprintf(stderr, "Invalid access of jsarray: index out of bounds\n");
		exit(1);
	}
	return list[index];
}

void jsarray::append(jsvar &value) {
	list.push_back(value);
}

void jsarray::append(bool value) {
	list.push_back(jsvar(value));
}

void jsarray::append(char value) {
	list.push_back(jsvar(value));
}

void jsarray::append(short value) {
	list.push_back(jsvar(value));
}

void jsarray::append(int value) {
	list.push_back(jsvar(value));
}

void jsarray::append(long value) {
	list.push_back(jsvar(value));
}

void jsarray::append(long long value) {
	list.push_back(jsvar(value));
}

void jsarray::append(unsigned char value) {
	list.push_back(jsvar(value));
}

void jsarray::append(unsigned short value) {
	list.push_back(jsvar(value));
}

void jsarray::append(unsigned int value) {
	list.push_back(jsvar(value));
}

void jsarray::append(unsigned long value) {
	list.push_back(jsvar(value));
}

void jsarray::append(unsigned long long value) {
	list.push_back(jsvar(value));
}

void jsarray::append(float value) {
	list.push_back(jsvar(value));
}

void jsarray::append(double value) {
	list.push_back(jsvar(value));
}

void jsarray::append(const char *value) {
	list.push_back(jsvar(value));
}

void jsarray::append(std::string value) {
	list.push_back(jsvar(value));
}

void jsarray::append(jsarray &value) {
	list.push_back(jsvar(value));
}

void jsarray::append(jsobject &value) {
	list.push_back(jsvar(value));
}

void jsarray::append(void *value) {
	list.push_back(jsvar(value));
}

size_t jsarray::length() {
	return list.size();
}

std::string jsarray::stringify(bool pretty, int indent) {
	int i;
	char pad[128];
	std::string padding = "";
	std::string ipadding = "";
	std::string result = "[";

	if (pretty) {
		sprintf(pad, "%*s", 4*indent, "");
		padding = std::string(pad);
		ipadding = padding + "    ";
	}

	for (i=0; i<list.size(); i++) {
		if (pretty)
			result += "\n" + ipadding;
		result += list[i].toString(pretty, indent + 1) + ",";
	}

	if (list.size() > 0) {
		if (pretty) {
			result[result.length()-1] = '\n';
			result += padding + "]";
		}
		else {
			result[result.length()-1] = ']';
		}
	}
	else
		result += "]";

	return result;
}

jsarray* jsarray::parse(std::string json, size_t *headPtr) {
	size_t begin = (headPtr == NULL) ? 0 : *headPtr;
	size_t head = json.find_first_not_of(" \t\r\n", begin);

	std::string comment = json.substr(head, 2);
	while (comment == "//" || comment == "/*") {
		if (comment == "//")
			head = json.find("\n", head) + 1;
		else
			head = json.find("*/", head) + 2;
		if (head == std::string::npos) {
			fprintf(stderr, "Error parsing JSON\n");
			return NULL;
		}
		head = json.find_first_not_of(" \t\r\n", head);
		comment = json.substr(head, 2);
	}

	if (json[head] != '[') {
		fprintf(stderr, "Error parsing JSON\n");
		return NULL;
	}

	jsarray* arrptr = new jsarray();
	head = json.find_first_not_of(" \t\r\n", head+1);

	std::string value;
	long long hnum;
	size_t pos, start, dot, hex, escape;
	while (json[head] != ']') {
		// ignore comments
		comment = json.substr(head, 2);
		while (comment == "//" || comment == "/*") {
			if (comment == "//")
				head = json.find("\n", head) + 1;
			else
				head = json.find("*/", head) + 2;
			if (head == std::string::npos) {
				fprintf(stderr, "Error parsing JSON\n");
				return NULL;
			}
			head = json.find_first_not_of(" \t\r\n", head);
			comment = json.substr(head, 2);
		}

		// determine value type
		// null
		if (json[head] == 'n') {
			if (json.substr(head, 4) == "null") {
				arrptr->append((void*)NULL);
				head += 4;
			}
			else {
				fprintf(stderr, "Error parsing JSON\n");
				delete arrptr;
				return NULL;
			}
		}
		// boolean
		if (json[head] == 't' || json[head] == 'f') {
			if (json.substr(head, 4) == "true") {
				arrptr->append(true);
				head += 4;
			}
			else if (json.substr(head, 5) == "false") {
				arrptr->append(false);
				head += 5;
			}
			else {
				fprintf(stderr, "Error parsing JSON\n");
				delete arrptr;
				return NULL;
			}
		}
		// number
		else if (json[head] == '-' || json[head] == '+' || json[head] == '.' || isdigit(json[head])) {
			pos = json.find_first_not_of(".x0123456789ABCDEFabcdef", head+1);
			if (pos == std::string::npos) {
				fprintf(stderr, "Error parsing JSON\n");
				delete arrptr;
				return NULL;
			}
			value = json.substr(head, pos-head);
			hex = value.find("x");
			if (hex != std::string::npos) {
				if ((value.substr(0,2) != "0x" && value.substr(0,3) != "-0x" && value.substr(0,3) != "+0x") || value.find_first_of(".x", hex+1) != std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete arrptr;
					return NULL;
				}
				sscanf(value.substr(hex+1).c_str(), "%llx", &hnum);
				if (value[0] == '-')
					hnum *= -1;
				arrptr->append(hnum);
			}
			else {
				if (value.find_first_of("ABCDEFabcdef") != std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete arrptr;
					return NULL;
				}
				dot = value.find(".");
				if (dot == std::string::npos) {
					arrptr->append(atoll(value.c_str()));
				}
				else {
					if (value.find(".", dot + 1) != std::string::npos) {
						fprintf(stderr, "Error parsing JSON\n");
						delete arrptr;
						return NULL;
					}
					arrptr->append(atof(value.c_str()));
				}
			}
			head = pos;
		}
		// text
		else if (json[head] == '\"' || json[head] == '\'') {
			start = 1;
			do {
				pos = json.find(json[head], head+start);
				if (pos == std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete arrptr;
					return NULL;
				}
				start = pos - head + 1;
			} while(json[pos-1] == '\\');
			start = 1;
			value = json.substr(head+start, pos-(head+start));
			escape = value.find("\\");
			while (escape != std::string::npos) {
				if (value[escape+1] == '\"' || value[escape+1] == '\'')
					value.erase(escape, 1);
				escape = value.find("\\");
			}
			arrptr->append(value);
			head = pos + start;
		}
		// array
		else if (json[head] == '[') {
			jsarray *narr = parse(json, &head);
			arrptr->append(*narr);
		}
		// object
		else if (json[head] == '{') {
			jsobject *nobj = jsobject::parse(json, &head);
			arrptr->append(*nobj);
		}

		// ignore comments
		head = json.find_first_not_of(" \t\r\n", head);
		comment = json.substr(head, 2);
		while (comment == "//" || comment == "/*") {
			if (comment == "//")
				head = json.find("\n", head) + 1;
			else
				head = json.find("*/", head) + 2;
			if (head == std::string::npos) {
				fprintf(stderr, "Error parsing JSON\n");
				return NULL;
			}
			head = json.find_first_not_of(" \t\r\n", head);
			comment = json.substr(head, 2);
		}

		head = json.find_first_not_of(", \t\r\n", head);
	}

	if (headPtr != NULL)
		*headPtr = head + 1;

	return arrptr;
}


/***************************************************************
 *  public methods: jsobject                                   *
 ***************************************************************/

jsvar& jsobject::operator[](const char *key) {
	return (*this)[std::string(key)];
}

jsvar& jsobject::operator[](std::string key) {
	if (dict.count(key) <= 0)
		dict[key] = jsvar();
	return dict[key];
}

std::vector<std::string> jsobject::keys() {
	std::map<std::string,jsvar>::iterator it;
	std::vector<std::string> result;

	for (it = dict.begin(); it != dict.end(); it++) {
		if (it->second.getType() != JS_TYPE_INVALID)
			result.push_back(it->first);
	}
	return result;
}

bool jsobject::hasProperty(std::string key) {
	if (dict.count(key) > 0)
		return true;
	return false;
}

std::string jsobject::stringify(bool pretty, int indent) {
	std::map<std::string,jsvar>::iterator it;
	char pad[128];
	size_t start, escape;
	std::string esckey;
	std::string padding = "";
	std::string ipadding = "";
	std::string result = "{";

	if (pretty) {
		sprintf(pad, "%*s", 4*indent, "");
		padding = std::string(pad);
		ipadding = padding + "    ";
	}

	for (it = dict.begin(); it != dict.end(); it++) {
		if (it->second.getType() != JS_TYPE_INVALID) {
			if (pretty)
				result += "\n" + ipadding;
			esckey = it->first;
			start = 0;
			escape = esckey.find_first_of("\"\'");
			while (escape != std::string::npos) {
				esckey = esckey.substr(0, escape) + "\\" + esckey.substr(escape);
				start = escape + 2;
				escape = esckey.find_first_of("\"\'", start);
			}
			result += "\"" + esckey + "\":";
			if (pretty)
				result += " ";
			result += it->second.toString(pretty, indent + 1) + ",";
		}
	}

	if (dict.size() > 0) {
		if (pretty) {
			result[result.length()-1] = '\n';
			result += padding + "}";
		}
		else {
			result[result.length()-1] = '}';
		}
	}
	else
		result += "}";

	return result;
}

jsobject* jsobject::parse(std::string json, size_t *headPtr) {
	size_t begin = (headPtr == NULL) ? 0 : *headPtr;
	size_t head = json.find_first_not_of(" \t\r\n", begin);

	std::string comment = json.substr(head, 2);
	while (comment == "//" || comment == "/*") {
		if (comment == "//")
			head = json.find("\n", head) + 1;
		else
			head = json.find("*/", head) + 2;
		if (head == std::string::npos) {
			fprintf(stderr, "Error parsing JSON\n");
			return NULL;
		}
		head = json.find_first_not_of(" \t\r\n", head);
		comment = json.substr(head, 2);
	}

	if (json[head] != '{') {
		fprintf(stderr, "Error parsing JSON\n");
		return NULL;
	}

	jsobject* objptr = new jsobject();
	head = json.find_first_not_of(" \t\r\n", head+1);

	std::string key, value;
	long long hnum;
	size_t pos, start, dot, hex, escape;
	while (json[head] != '}') {
		// ignore comments
		comment = json.substr(head, 2);
		while (comment == "//" || comment == "/*") {
			if (comment == "//")
				head = json.find("\n", head) + 1;
			else
				head = json.find("*/", head) + 2;
			if (head == std::string::npos) {
				fprintf(stderr, "Error parsing JSON\n");
				return NULL;
			}
			head = json.find_first_not_of(" \t\r\n", head);
			comment = json.substr(head, 2);
		}

		// get key
		if (json[head] == '\"' || json[head] == '\'') {
			start = 1;
			do {
				pos = json.find(json[head], head+start);
				if (pos == std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete objptr;
					return NULL;
				}
				start = pos - head + 1;
			} while(json[pos-1] == '\\');
			start = 1;
		}
		else {
			start = 0;
			pos = json.find_first_not_of("_$1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", head);
		}
		key = json.substr(head+start, pos-(head+start));
		escape = key.find("\\");
		while (escape != std::string::npos) {
			if (key[escape+1] == '\"' || key[escape+1] == '\'')
				key.erase(escape, 1);
			escape = key.find("\\");
		}
		
		head = json.find_first_not_of(" \t\r\n", pos+start);
		if (json[head] != ':') {
			fprintf(stderr, "Error parsing JSON\n");
			delete objptr;
			return NULL;
		}
		// determine value type
		head = json.find_first_not_of(" \t\r\n", head+1);
		// null
		if (json[head] == 'n') {
			if (json.substr(head, 4) == "null") {
				(*objptr)[key] = (void*)NULL;
				head += 4;
			}
			else {
				fprintf(stderr, "Error parsing JSON\n");
				delete objptr;
				return NULL;
			}
		}
		// boolean
		if (json[head] == 't' || json[head] == 'f') {
			if (json.substr(head, 4) == "true") {
				(*objptr)[key] = true;
				head += 4;
			}
			else if (json.substr(head, 5) == "false") {
				(*objptr)[key] = false;
				head += 5;
			}
			else {
				fprintf(stderr, "Error parsing JSON\n");
				delete objptr;
				return NULL;
			}
		}
		// number
		else if (json[head] == '-' || json[head] == '+' || json[head] == '.' || isdigit(json[head])) {
			pos = json.find_first_not_of(".x0123456789ABCDEFabcdef", head+1);
			if (pos == std::string::npos) {
				fprintf(stderr, "Error parsing JSON\n");
				delete objptr;
				return NULL;
			}
			value = json.substr(head, pos-head);
			hex = value.find("x");
			if (hex != std::string::npos) {
				if ((value.substr(0,2) != "0x" && value.substr(0,3) != "-0x" && value.substr(0,3) != "+0x") || value.find_first_of(".x", hex+1) != std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete objptr;
					return NULL;
				}
				sscanf(value.substr(hex+1).c_str(), "%llx", &hnum);
				if (value[0] == '-')
					hnum *= -1;
				(*objptr)[key] = hnum;
			}
			else {
				if (value.find_first_of("ABCDEFabcdef") != std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete objptr;
					return NULL;
				}
				dot = value.find(".");
				if (dot == std::string::npos) {
					(*objptr)[key] = atoll(value.c_str());
				}
				else {
					if (value.find(".", dot + 1) != std::string::npos) {
						fprintf(stderr, "Error parsing JSON\n");
						delete objptr;
						return NULL;
					}
					(*objptr)[key] = atof(value.c_str());
				}
			}
			head = pos;
		}
		// text
		else if (json[head] == '\"' || json[head] == '\'') {
			start = 1;
			do {
				pos = json.find(json[head], head+start);
				if (pos == std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete objptr;
					return NULL;
				}
				start = pos - head + 1;
			} while(json[pos-1] == '\\');
			start = 1;
			value = json.substr(head+start, pos-(head+start));
			escape = value.find("\\");
			while (escape != std::string::npos) {
				if (value[escape+1] == '\"' || value[escape+1] == '\'')
					value.erase(escape, 1);
				escape = value.find("\\");
			}
			(*objptr)[key] = value;
			head = pos + start;
		}
		// array
		else if (json[head] == '[') {
			jsarray *narr = jsarray::parse(json, &head);
			(*objptr)[key] = *narr;
		}
		// object
		else if (json[head] == '{') {
			jsobject *nobj = parse(json, &head);
			(*objptr)[key] = *nobj;
		}

		// ignore comments
		head = json.find_first_not_of(" \t\r\n", head);
		comment = json.substr(head, 2);
		while (comment == "//" || comment == "/*") {
			if (comment == "//")
				head = json.find("\n", head) + 1;
			else
				head = json.find("*/", head) + 2;
			if (head == std::string::npos) {
				fprintf(stderr, "Error parsing JSON\n");
				return NULL;
			}
			head = json.find_first_not_of(" \t\r\n", head);
			comment = json.substr(head, 2);
		}

		head = json.find_first_not_of(", \t\r\n", head);
	}

	if (headPtr != NULL)
		*headPtr = head + 1;

	return objptr;
}

jsobject* jsobject::parseFromFile(std::string filename) {
	FILE *f = fopen(filename.c_str(), "rb");
	if (f == NULL) {
		fprintf(stderr, "Error opening file %s\n", filename.c_str());
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	char *text = (char*)malloc(fsize * sizeof(char));
	if (fread(text, fsize, 1, f) != 1) {
		fprintf(stderr, "Error reading file %s\n", filename.c_str());
		return NULL;
	}
	fclose(f);

	return parse(text);
}
