#include <iostream>
#include <map>
#include <string>
#include <vector>

#define JSON_BOOLEAN 0
#define JSON_INTEGER 1
#define JSON_FLOAT   2
#define JSON_TEXT    3
#define JSON_ARRAY   4
#define JSON_OBJECT  5

#define JSON_MODE_INIT 0
#define JSON_MODE_ARRAY 1
#define JSON_MODE_OBJECT 2

class jsarray;
class jsobject;

class jsarray {
private:
	std::vector<std::pair<int,int> > list;

	std::vector<bool>        boolean;
	std::vector<long long>   inumber;
	std::vector<double>      fnumber;
	std::vector<std::string> text;
	std::vector<jsarray*>    array;
	std::vector<jsobject*>   object;

public:
	jsarray() {};
	~jsarray() {};

	void addBooleanToArray(bool value);
	void addIntegerToArray(long long value);
	void addFloatToArray(double value);
	void addTextToArray(std::string value);
	void addArrayToArray(jsarray* value);
	void addObjectToArray(jsobject* value);

	size_t length();
	int getElementType(size_t index);
	bool getElementAsBoolean(size_t index, bool *err = NULL);
	long long getElementAsInteger(size_t index, bool *err = NULL);
	double getElementAsFloat(size_t index, bool *err = NULL);
	std::string getElementAsText(size_t index, bool *err = NULL);
	jsarray* getElementAsArray(size_t index, bool *err = NULL);
	jsobject* getElementAsObject(size_t index, bool *err = NULL);
	
	std::string stringify(bool pretty = false, int indent = 0);

	static jsarray* parseArray(std::string json, size_t *headPtr = NULL);
};

class jsobject {
private:
	std::map<std::string,bool>        boolean;
	std::map<std::string,long long>   inumber;
	std::map<std::string,double>      fnumber;
	std::map<std::string,std::string> text;
	std::map<std::string,jsarray*>    array;
	std::map<std::string,jsobject*>   object;

public:
	jsobject() {};
	~jsobject() {};

	void addBooleanToObject(std::string key, bool value);
	void addIntegerToObject(std::string key, long long value);
	void addFloatToObject(std::string key, double value);
	void addTextToObject(std::string key, std::string value);
	void addArrayToObject(std::string key, jsarray* value);
	void addObjectToObject(std::string key, jsobject* value);

	int getItemType(std::string key);
	bool getItemAsBoolean(std::string key, bool *err = NULL);
	long long getItemAsInteger(std::string key, bool *err = NULL);
	double getItemAsFloat(std::string key, bool *err = NULL);
	std::string getItemAsText(std::string key, bool *err = NULL);
	jsarray* getItemAsArray(std::string key, bool *err = NULL);
	jsobject* getItemAsObject(std::string key, bool *err = NULL);
	
	std::string stringify(bool pretty = false, int indent = 0);

	static jsobject* parse(std::string json, size_t *headPtr = NULL);
	static jsobject* parseFromFile(std::string filename);
};