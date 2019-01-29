# Cusend

Cusend (*C plUS plUS back-END*) is a lightweight C++ library for building Web APIs. The idea is inspired by [crow](https://github.com/ipkn/crow) and the API style is inspired by [express](https://github.com/expressjs/express).

## Hello World example
```cpp
#include <Cusend/Application.h>

void helloRoute(csd::Request& req, csd::Response& res) {
	csd::ResponseFactory::text(res, "Hello World!");
}

int main(int argc, char* argv[]) {
	csd::Application app;
	
	app.route(csd::Methods::Get, "/hello", helloRoute);
	app.listen(3000);
	return 0;
}
```

Browsing to localhost:3000/hello in your favourite browser will show "Hello World!" text.

## Features
* Designed to be cross-platform
* API is easy-to-use and easy-to-understand
* Uses multi-threading for handling connections

## TODO
* ~~GET params parsing~~
* ~~POST params parsing~~
* ~~URL encoding/decoding~~
* multipart/form-data POST body parsing
* URI params parsing (e.g. GET /article/:articleID)
* Cookie management
* Cache
* ~~Add documentation and doxygen~~
* Support as many MIME-types as possible
* ~~Middleware routing~~
* Error-prone request parser
* Implement platform-specifc functions for Unix/Linux
* Create makefiles for different platforms
* Provide precompiled binaries for Windows

## Contributing
Contributions are welcomed. If you found a bug or want to add a feature - open an issue. You can also create a pull request which fixes the bug or adds the feature respectively. Please, try to follow same code style as in the whole project. Use *express* API docs for reference.

## Authors
* MrOnlineCoder (creator and maintainer)

## License
MIT
see LICENSE file