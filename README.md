# jsobject
JavaScript Object Interface for C++ (Including JSON Parser / Generator)

### Features
* Flexible data types
* Easy data access using `[]`
* JSON5 parsing

| JSON5 Feature                                            | Integrated |
|----------------------------------------------------------|------------|
| Quoted, single-quoted, and unquoted object names         | Yes        |
| Trailing commas in objects and arrays                    | Yes        |
| Single quoted strings                                    | Yes        |
| Escape sequences in strings                              | Yes        |
| Multiline strings (prefix each newline with a backslash) | Yes        |
| Numbers can be hexadecimal (e.g. 0xA639ED01)             | Yes        |
| Numbers can begin or end with a decimal point            | Yes        |
| Numbers can include Infinity, -Infinity, NaN, and -NaN   | Yes        |
| Numbers can begin with an explicit plus sign             | Yes        |
| Allow inline (single-line) comments                      | Yes        |
| Allow block (multi-line) comments                        | Yes        |

### Example
```
#include <iostream>
#include "jsobject.h"

int main(int argc, char **argv) {
    jsvar obj;
    obj["name"] = "tmarrinan";
    obj["year"] = 2017;
    obj["contact"] = jsobject::parse("{\"phone\":[\"999-999-9999\",\"012-345-6789\"],\"email\":\"me@abc123.com\"}");
    obj["empty"] = JS_NULL;
    obj["half"] = 0.5;

    jsvar phones = obj["contact"]["phone"];

    std::cout << obj.stringify(true) << std::endl;
    std::cout << "main phone number: " << phones[0] << std::endl;

    /*** PRINT *************************
    {
        "contact": {
            "email": "me@abc123.com",
            "phone": [
                "999-999-9999",
                "012-345-6789"
            ]
        },
        "empty": null,
        "half": 0.5,
        "name": "tmarrinan",
        "year": 2017
    }
    main phone number: 999-999-9999
    ************************************/

    return 0;
}
```
