#include <Cusend/Application.h>

#include <iostream>

bool helloRoute(csd::Request& req, csd::Response& res) {
	return csd::ResponseFactory::sendFile(res, "Static/hello.css");
}

int main(int argc, char* argv[]) {
	csd::Application app;

	app.route(csd::Methods::Get, "/hello", helloRoute);

	app.listen(3000);

	if (app.getError() != csd::Errors::None) {
		std::cout << "Cusend Error: " << app.getError() << std::endl;
		std::cout << "Network Error: " << app.getSocketError() << std::endl;
	}

	return 0;
}