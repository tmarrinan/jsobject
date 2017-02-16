# jsobject
JavaScript Object Interface for C++ (Including JSON Parser / Generator)

### Features
* Flexible data types
* Easy data access using `[]`
* JSON5 parsing
| JSON5 Feature                                            | Integrated                              |
|----------------------------------------------------------|-----------------------------------------|
| quoted, single-quoted, and unquoted object names         | Yes                                     |
| trailing commas in objects and arrays                    | Yes                                     |
| single quoted strings                                    | Yes                                     |
| escape sequences in strings                              | Partial *currently only escapes quotes* |
| multiline strings (prefix each newline with a backslash) | No                                      |
| numbers can be hexadecimal (e.g. 0xA639ED01)             | Yes                                     |
| numbers can begin or end with a decimal point            | Yes                                     |
| numbers can include Infinity, -Infinity, NaN, and -NaN   | No                                      |
| numbers can begin with an explicit plus sign             | Yes                                     |
| allow inline (single-line) comments                      | No                                      |
| allow block (multi-line) comments                        | No                                      |

### Example
```
jsobject obj;
obj["name"] = "tmarrinan";
obj["year"] = 2017;
obj["contact"] = *jsobject::parse("{\"phone\":\"999-999-9999\",\"email\":\"me@abc123.com\"}");
aobj["half"] = 0.5;

std::cout << obj.stringify(true) << std::endl;

/*** PRINT *************************
{
    "contact": {
        "email": "me@abc123.com",
        "phone": "999-999-9999"
    },
    "half": 0.5,
    "name": "tmarrinan",
    "year": 2017
}
************************************/
```
