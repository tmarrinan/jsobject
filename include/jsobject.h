#include <iostream>
#include <map>
#include <string>
#include <vector>

#define JS_TYPE_INVALID -1
#define JS_TYPE_NULL     0
#define JS_TYPE_BOOLEAN  1
#define JS_TYPE_INTEGER  2
#define JS_TYPE_FLOAT    3
#define JS_TYPE_TEXT     4
#define JS_TYPE_ARRAY    5
#define JS_TYPE_OBJECT   6

class jsarray;
class jsobject;

class jsvar {
private:
	int type;
	bool boolean;
	long long inumber;
	double fnumber;
	std::string text;
	jsarray *array;
	jsobject *object;

public:
	jsvar();
	jsvar(bool value);
	jsvar(char value);
	jsvar(short value);
	jsvar(int value);
	jsvar(long value);
	jsvar(long long value);
	jsvar(unsigned char value);
	jsvar(unsigned short value);
	jsvar(unsigned int value);
	jsvar(unsigned long value);
	jsvar(unsigned long long value);
	jsvar(float value);
	jsvar(double value);
	jsvar(const char *value);
	jsvar(std::string value);
	jsvar(jsarray &value);
	jsvar(jsobject &value);
	jsvar(void *value);
	~jsvar() {};

	operator bool();
	operator char();
	operator short();
	operator int();
	operator long();
	operator long long();
	operator unsigned char();
	operator unsigned short();
	operator unsigned int();
	operator unsigned long();
	operator unsigned long long();
	operator float();
	operator double();
	operator std::string();
	operator jsarray&();
	operator jsobject&();

	jsvar& operator=(bool value);
	jsvar& operator=(char value);
	jsvar& operator=(short value);
	jsvar& operator=(int value);
	jsvar& operator=(long value);
	jsvar& operator=(long long value);
	jsvar& operator=(unsigned char value);
	jsvar& operator=(unsigned short value);
	jsvar& operator=(unsigned int value);
	jsvar& operator=(unsigned long value);
	jsvar& operator=(unsigned long long value);
	jsvar& operator=(float value);
	jsvar& operator=(double value);
	jsvar& operator=(const char *value);
	jsvar& operator=(std::string value);
	jsvar& operator=(jsarray &value);
	jsvar& operator=(jsobject &value);
	jsvar& operator=(void *value);

	jsvar& operator[](int index);
	jsvar& operator[](size_t index);
	jsvar& operator[](const char *key);
	jsvar& operator[](std::string key);

	int getType();
	std::string toString(bool pretty = false, int indent = 0);

	void append(jsvar &value);
	void append(bool value);
	void append(char value);
	void append(short value);
	void append(int value);
	void append(long value);
	void append(long long value);
	void append(unsigned char value);
	void append(unsigned short value);
	void append(unsigned int value);
	void append(unsigned long value);
	void append(unsigned long long value);
	void append(float value);
	void append(double value);
	void append(const char *value);
	void append(std::string value);
	void append(jsarray &value);
	void append(jsobject &value);
	void append(void *value);
	size_t length();
	std::vector<std::string> keys();
	bool hasProperty(std::string key);
	std::string stringify(bool pretty = false, int indent = 0);
};

class jsarray {
private:
	std::vector<jsvar> list;

public:
	jsarray() {};
	~jsarray() {};

	jsvar& operator[](int index);
	jsvar& operator[](size_t index);

	void append(jsvar &value);
	void append(bool value);
	void append(char value);
	void append(short value);
	void append(int value);
	void append(long value);
	void append(long long value);
	void append(unsigned char value);
	void append(unsigned short value);
	void append(unsigned int value);
	void append(unsigned long value);
	void append(unsigned long long value);
	void append(float value);
	void append(double value);
	void append(const char *value);
	void append(std::string value);
	void append(jsarray &value);
	void append(jsobject &value);
	void append(void *value);

	size_t length();
	std::string stringify(bool pretty = false, int indent = 0);

	static jsvar parse(std::string json, size_t *headPtr = NULL);
};

class jsobject {
private:
	std::map<std::string,jsvar> dict;

public:
	jsobject() {};
	~jsobject() {};

	jsvar& operator[](const char *key);
	jsvar& operator[](std::string key);

	std::vector<std::string> keys();
	bool hasProperty(std::string key);
	std::string stringify(bool pretty = false, int indent = 0);

	static jsvar parse(std::string json, size_t *headPtr = NULL);
	static jsvar parseFromFile(std::string filename);
};
