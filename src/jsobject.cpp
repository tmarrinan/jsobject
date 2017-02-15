#include "jsobject.h"


/***************************************************************
 *  public methods: jsarray                                    *
 ***************************************************************/

void jsarray::addBooleanToArray(bool value) {
	int idx = boolean.size();
	list.push_back(std::make_pair(JSON_BOOLEAN, idx));
	boolean.push_back(value);
}

void jsarray::addIntegerToArray(long long value) {
	int idx = inumber.size();
	list.push_back(std::make_pair(JSON_INTEGER, idx));
	inumber.push_back(value);
}

void jsarray::addFloatToArray(double value) {
	int idx = fnumber.size();
	list.push_back(std::make_pair(JSON_FLOAT, idx));
	fnumber.push_back(value);
}

void jsarray::addTextToArray(std::string value) {
	int idx = text.size();
	list.push_back(std::make_pair(JSON_TEXT, idx));
	text.push_back(value);
}

void jsarray::addArrayToArray(jsarray* value) {
	int idx = array.size();
	list.push_back(std::make_pair(JSON_ARRAY, idx));
	array.push_back(value);
}

void jsarray::addObjectToArray(jsobject* value) {
	int idx = object.size();
	list.push_back(std::make_pair(JSON_OBJECT, idx));
	object.push_back(value);
}

size_t jsarray::length() {
	return list.size();
}

int jsarray::getElementType(size_t index) {
	if (index >= list.size())
		return -1;
	return list[index].first;
}

bool jsarray::getElementAsBoolean(size_t index, bool *err) {
	if (index >= list.size() || list[index].first != JSON_BOOLEAN) {
		if (err)
			*err = true;
		return false;
	}

	if (err)
		*err = false;
	return boolean[list[index].second];
}

long long jsarray::getElementAsInteger(size_t index, bool *err) {
	if (index >= list.size() || list[index].first != JSON_INTEGER) {
		if (err)
			*err = true;
		return 0;
	}

	if (err)
		*err = false;
	return inumber[list[index].second];
}

double jsarray::getElementAsFloat(size_t index, bool *err) {
	if (index >= list.size() || list[index].first != JSON_FLOAT) {
		if (err)
			*err = true;
		return 0.0;
	}

	if (err)
		*err = false;
	return fnumber[list[index].second];
}

std::string jsarray::getElementAsText(size_t index, bool *err) {
	if (index >= list.size() || list[index].first != JSON_TEXT) {
		if (err)
			*err = true;
		return "";
	}

	if (err)
		*err = false;
	return text[list[index].second];
}

jsarray* jsarray::getElementAsArray(size_t index, bool *err) {
	if (index >= list.size() || list[index].first != JSON_ARRAY) {
		if (err)
			*err = true;
		return NULL;
	}

	if (err)
		*err = false;
	return array[list[index].second];
}

jsobject* jsarray::getElementAsObject(size_t index, bool *err) {
	if (index >= list.size() || list[index].first != JSON_OBJECT) {
		if (err)
			*err = true;
		return NULL;
	}

	if (err)
		*err = false;
	return object[list[index].second];
}

std::string jsarray::stringify(bool pretty, int indent) {
	int i, j;
	char canum[64];
	std::string snum;
	size_t pos, start, escape;
	char pad[64];
	std::string padding;
	std::string esctext;
	std::string result = "[";

	if (pretty) {
		sprintf(pad, "%*s", 4*indent, "");
		padding = std::string(pad);
	}

	for (i=0; i<list.size(); i++) {
		if (pretty)
			result += "\n" + padding + "    ";
		switch (list[i].first) {
			case JSON_BOOLEAN:
				if (boolean[list[i].second] == true)
					result += "true,";
				else
					result += "false,";
				break;
			case JSON_INTEGER:
				sprintf(canum, "%lld", inumber[list[i].second]);
				result += std::string(canum) + ",";
				break;
			case JSON_FLOAT:
				sprintf(canum, "%.14lf", fnumber[list[i].second]);
				snum = std::string(canum);
				pos = snum.find_last_not_of("0");
				if (pos != std::string::npos)
					snum = snum.substr(0, pos+1);
				if (snum[snum.length()-1] == '.')
					snum += "0";
				result += snum + ",";
				break;
			case JSON_TEXT:
				esctext = text[list[i].second];
				start = 0;
				escape = esctext.find_first_of("\"\'");
				while (escape != std::string::npos) {
					esctext = esctext.substr(0, escape) + "\\" + esctext.substr(escape);
					start = escape + 2;
					escape = esctext.find_first_of("\"\'", start);
				}
				result += "\"" + esctext + "\",";
				break;
			case JSON_ARRAY:
				result += array[list[i].second]->stringify(pretty, indent+1) + ",";
				break;
			case JSON_OBJECT:
				result += object[list[i].second]->stringify(pretty, indent+1) + ",";
				break;
		}
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

jsarray* jsarray::parseArray(std::string json, size_t *headPtr) {
	size_t begin = (headPtr == NULL) ? 0 : *headPtr;
	size_t head = json.find_first_not_of(" \t\r\n", begin);
	if (json[head] != '[') {
		fprintf(stderr, "Error parsing JSON\n");
		return NULL;
	}

	jsarray* arr = new jsarray();
	head = json.find_first_not_of(" \t\r\n", head+1);

	std::string value;
	long long hnum;
	size_t pos, start, dot, hex, escape;
	while (json[head] != ']') {
		// determine value type
		// boolean
		if (json[head] == 't' || json[head] == 'f') {
			if (json.substr(head, 4) == "true") {
				arr->addBooleanToArray(true);
				head += 4;
			}
			else if (json.substr(head, 5) == "false") {
				arr->addBooleanToArray(false);
				head += 5;
			}
			else {
				fprintf(stderr, "Error parsing JSON\n");
				delete arr;
				return NULL;
			}
		}
		// number
		else if (json[head] == '-' || json[head] == '+' || json[head] == '.' || isdigit(json[head])) {
			pos = json.find_first_not_of(".x0123456789ABCDEFabcdef", head+1);
			if (pos == std::string::npos) {
				fprintf(stderr, "Error parsing JSON\n");
				delete arr;
				return NULL;
			}
			value = json.substr(head, pos-head);
			hex = value.find("x");
			if (hex != std::string::npos) {
				if ((value.substr(0,2) != "0x" && value.substr(0,3) != "-0x" && value.substr(0,3) != "+0x") || value.find_first_of(".x", hex+1) != std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete arr;
					return NULL;
				}
				sscanf(value.substr(hex+1).c_str(), "%llx", &hnum);
				if (value[0] == '-')
					hnum *= -1;
				arr->addIntegerToArray(hnum);
			}
			else {
				if (value.find_first_of("ABCDEFabcdef") != std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete arr;
					return NULL;
				}
				dot = value.find(".");
				if (dot == std::string::npos) {
					arr->addIntegerToArray(atoll(value.c_str()));
				}
				else {
					if (value.find(".", dot + 1) != std::string::npos) {
						fprintf(stderr, "Error parsing JSON\n");
						delete arr;
						return NULL;
					}
					arr->addFloatToArray(atof(value.c_str()));
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
					delete arr;
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
			arr->addTextToArray(value);
			head = pos + start;
		}
		// array
		else if (json[head] == '[') {
			jsarray *narr = parseArray(json, &head);
			arr->addArrayToArray(narr);
		}
		// object
		else if (json[head] == '{') {
			jsobject *nobj = jsobject::parse(json, &head);
			arr->addObjectToArray(nobj);
		}

		head = json.find_first_not_of(", \t\r\n", head);
	}

	if (headPtr != NULL)
		*headPtr = head + 1;

	return arr;
}


/***************************************************************
 *  public methods: jsobject                                   *
 ***************************************************************/

void jsobject::addBooleanToObject(std::string key, bool value) {
	boolean[key] = value;
}

void jsobject::addIntegerToObject(std::string key, long long value) {
	inumber[key] = value;
}

void jsobject::addFloatToObject(std::string key, double value) {
	fnumber[key] = value;
}

void jsobject::addTextToObject(std::string key, std::string value) {
	text[key] = value;
}

void jsobject::addArrayToObject(std::string key, jsarray* value) {
	array[key] = value;
}

void jsobject::addObjectToObject(std::string key, jsobject* value) {
	object[key] = value;
}

int jsobject::getItemType(std::string key) {
	if (boolean.count(key))
		return JSON_BOOLEAN;
	if (inumber.count(key))
		return JSON_INTEGER;
	if (fnumber.count(key))
		return JSON_FLOAT;
	if (text.count(key))
		return JSON_TEXT;
	if (array.count(key))
		return JSON_ARRAY;
	if (object.count(key))
		return JSON_OBJECT;

	return -1;
}

bool jsobject::getItemAsBoolean(std::string key, bool *err) {
	if (err)
		*err = false;
	if (boolean.count(key))
		return boolean[key];
	
	if (err)
		*err = true;
	return false;
}

long long jsobject::getItemAsInteger(std::string key, bool *err) {
	if (err)
		*err = false;
	if (inumber.count(key))
		return inumber[key];
	
	if (err)
		*err = true;
	return 0;
}

double jsobject::getItemAsFloat(std::string key, bool *err) {
	if (err)
		*err = false;
	if (fnumber.count(key))
		return fnumber[key];
	
	if (err)
		*err = true;
	return 0.0;
}

std::string jsobject::getItemAsText(std::string key, bool *err) {
	if (err)
		*err = false;
	if (text.count(key))
		return text[key];
	
	if (err)
		*err = true;
	return "";
}

jsarray* jsobject::getItemAsArray(std::string key, bool *err) {
	if (err)
		*err = false;
	if (array.count(key))
		return array[key];
	
	if (err)
		*err = true;
	return NULL;
}

jsobject* jsobject::getItemAsObject(std::string key, bool *err) {
	if (err)
		*err = false;
	if (object.count(key))
		return object[key];
	
	if (err)
		*err = true;
	return NULL;
}

std::string jsobject::stringify(bool pretty, int indent) {
	std::map<std::string, bool>::iterator itB;
	std::map<std::string, long long>::iterator itI;
	std::map<std::string, double>::iterator itF;
	std::map<std::string, std::string>::iterator itT;
	std::map<std::string, jsarray*>::iterator itA;
	std::map<std::string, jsobject*>::iterator itO;

	char canum[32];
	std::string snum;
	size_t pos, start, escape;
	bool empty = true;
	char pad[64];
	std::string padding;
	std::string esctext;
	std::string result = "{";

	if (pretty) {
		sprintf(pad, "%*s", 4*indent, "");
		padding = std::string(pad);
	}

	for (itB = boolean.begin(); itB != boolean.end(); itB++) {
		if (pretty)
			result += "\n" + padding + "    ";
		result += "\"" + itB->first + "\":";
		if (pretty)
			result += " ";
		if (itB->second == true)
			result += "true,";
		else
			result += "false,";
		empty = false;
	}
	for (itI = inumber.begin(); itI != inumber.end(); itI++) {
		if (pretty)
			result += "\n" + padding + "    ";
		result += "\"" + itI->first + "\":";
		if (pretty)
			result += " ";
		sprintf(canum, "%lld", itI->second);
		result += std::string(canum) + ",";
		empty = false;
	}
	for (itF = fnumber.begin(); itF != fnumber.end(); itF++) {
		if (pretty)
			result += "\n" + padding + "    ";
		result += "\"" + itF->first + "\":";
		if (pretty)
			result += " ";
		sprintf(canum, "%.14lf", itF->second);
		snum = std::string(canum);
		pos = snum.find_last_not_of("0");
		if (pos != std::string::npos)
			snum = snum.substr(0, pos+1);
		if (snum[snum.length()-1] == '.')
			snum += "0";
		result += snum + ",";
		empty = false;
	}
	for (itT = text.begin(); itT != text.end(); itT++) {
		if (pretty)
			result += "\n" + padding + "    ";
		result += "\"" + itT->first + "\":";
		if (pretty)
			result += " ";
		esctext = itT->second;
		start = 0;
		escape = esctext.find_first_of("\"\'");
		while (escape != std::string::npos) {
			esctext = esctext.substr(0, escape) + "\\" + esctext.substr(escape);
			start = escape + 2;
			escape = esctext.find_first_of("\"\'", start);
		}
		result += "\"" + esctext + "\",";
		empty = false;
	}
	for (itA = array.begin(); itA != array.end(); itA++) {
		if (pretty)
			result += "\n" + padding + "    ";
		result += "\"" + itA->first + "\":";
		if (pretty)
			result += " ";
		result += itA->second->stringify(pretty, indent+1) + ",";
		empty = false;
	}
	for (itO = object.begin(); itO != object.end(); itO++) {
		if (pretty)
			result += "\n" + padding + "    ";
		result += "\"" + itO->first + "\":";
		if (pretty)
			result += " ";
		result += itO->second->stringify(pretty, indent+1) + ",";
		empty = false;
	}

	if (!empty) {
		if (pretty) {
			result[result.length()-1] = '\n';
			result += padding + "}";
		}
		else {
			result[result.length()-1] = '}';
		}
	}
	else {
		result += "}";
	}

	return result;
}

jsobject* jsobject::parse(std::string json, size_t *headPtr) {
	// TODO: JSON5
	//  X quoted, single-quoted, and unquoted object names
	//  X trailing commas in objects and arrays
	//  X single quoted strings
	//  \ escape sequences in strings ---> *currently only support quotes*
	//  - multiline strings (prefix each newline with a backslash)
	//  X numbers can be hexadecimal (e.g. 0xA639ED01)
	//  X numbers can begin or end with a decimal point
	//  - numbers can include Infinity, -Infinity, NaN, and -NaN
	//  X numbers can begin with an explicit plus sign
	//  - allow inline (single-line) comments
	//  - allow block (multi-line) comments

	size_t begin = (headPtr == NULL) ? 0 : *headPtr;
	size_t head = json.find_first_not_of(" \t\r\n", begin);
	if (json[head] != '{') {
		fprintf(stderr, "Error parsing JSON\n");
		return NULL;
	}

	jsobject* obj = new jsobject();
	head = json.find_first_not_of(" \t\r\n", head+1);

	std::string key, value;
	long long hnum;
	size_t pos, start, dot, hex, escape;
	while (json[head] != '}') {
		// get key
		if (json[head] == '\"' || json[head] == '\'') {
			start = 1;
			do {
				pos = json.find(json[head], head+start);
				if (pos == std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete obj;
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
			delete obj;
			return NULL;
		}
		// determine value type
		head = json.find_first_not_of(" \t\r\n", head+1);
		// boolean
		if (json[head] == 't' || json[head] == 'f') {
			if (json.substr(head, 4) == "true") {
				obj->addBooleanToObject(key, true);
				head += 4;
			}
			else if (json.substr(head, 5) == "false") {
				obj->addBooleanToObject(key, false);
				head += 5;
			}
			else {
				fprintf(stderr, "Error parsing JSON\n");
				delete obj;
				return NULL;
			}
		}
		// number
		else if (json[head] == '-' || json[head] == '+' || json[head] == '.' || isdigit(json[head])) {
			pos = json.find_first_not_of(".x0123456789ABCDEFabcdef", head+1);
			if (pos == std::string::npos) {
				fprintf(stderr, "Error parsing JSON\n");
				delete obj;
				return NULL;
			}
			value = json.substr(head, pos-head);
			hex = value.find("x");
			if (hex != std::string::npos) {
				if ((value.substr(0,2) != "0x" && value.substr(0,3) != "-0x" && value.substr(0,3) != "+0x") || value.find_first_of(".x", hex+1) != std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete obj;
					return NULL;
				}
				sscanf(value.substr(hex+1).c_str(), "%llx", &hnum);
				if (value[0] == '-')
					hnum *= -1;
				obj->addIntegerToObject(key, hnum);
			}
			else {
				if (value.find_first_of("ABCDEFabcdef") != std::string::npos) {
					fprintf(stderr, "Error parsing JSON\n");
					delete obj;
					return NULL;
				}
				dot = value.find(".");
				if (dot == std::string::npos) {
					obj->addIntegerToObject(key, atoll(value.c_str()));
				}
				else {
					if (value.find(".", dot + 1) != std::string::npos) {
						fprintf(stderr, "Error parsing JSON\n");
						delete obj;
						return NULL;
					}
					obj->addFloatToObject(key, atof(value.c_str()));
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
					delete obj;
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
			obj->addTextToObject(key, value);
			head = pos + start;
		}
		// array
		else if (json[head] == '[') {
			jsarray *narr = jsarray::parseArray(json, &head);
			obj->addArrayToObject(key, narr);
		}
		// object
		else if (json[head] == '{') {
			jsobject *nobj = parse(json, &head);
			obj->addObjectToObject(key, nobj);
		}

		head = json.find_first_not_of(", \t\r\n", head);
	}

	if (headPtr != NULL)
		*headPtr = head + 1;

	return obj;
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
