#include <Cusend/Application.h>

#include <iostream>

bool helloRoute(csd::Request& req, csd::Response& res) {
	if (req.getField("name") != "") {
		return csd::ResponseFactory::text(res, "Hello, "+req.getField("name"));
	}

	return csd::ResponseFactory::sendFile(res, "Static/hello.css");
}

bool faviconRoute(csd::Request& req, csd::Response& res) {
	res.setStatus(304);

	return true;
}

int main(int argc, char* argv[]) {
	csd::Application app;

	app.route(csd::Methods::Get, "/hello", helloRoute);
	app.route(csd::Methods::Get, "/favicon.ico", faviconRoute);

	app.listen(3000);

	if (app.getError() != csd::Errors::None) {
		std::cout << "Cusend Error: " << app.getError() << std::endl;
		std::cout << "Network Error: " << app.getSocketError() << std::endl;
	}

	return 0;
}