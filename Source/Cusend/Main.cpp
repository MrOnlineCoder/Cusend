#include <Cusend/Application.h>

#include <iostream>

void fileRoute(csd::Request& req, csd::Response& res) {
	csd::ResponseFactory::sendFile(res, "Static/hello.css");
}

void getFormRoute(csd::Request& req, csd::Response& res) {
	csd::ResponseFactory::sendFile(res, "Static/form.html");
}

void postFormRoute(csd::Request& req, csd::Response& res) {
	csd::ResponseFactory::text(res, req.getField("name")+", your text: "+req.getField("text"));
}

bool myMiddleware(csd::Request& req, csd::Response& res) {
	std::cout << "Middleware request: " << req.getPath() << std::endl;
	return true;
}

bool faviconRoute(csd::Request& req, csd::Response& res) {
	res.setStatus(304);

	return true;
}

int main(int argc, char* argv[]) {
	csd::Application app;

	app.use(myMiddleware);

	app.route(csd::Methods::Get, "/file", fileRoute);

	app.route(csd::Methods::Get, "/form", getFormRoute);
	app.route(csd::Methods::Post, "/form", postFormRoute);

	app.route(csd::Methods::Get, "/favicon.ico", faviconRoute);

	app.listen(1234);

	if (app.getError() != csd::Errors::None) {
		std::cout << "Cusend Error: " << app.getError() << std::endl;
		std::cout << "Network Error: " << app.getSocketError() << std::endl;
	}

	return 0;
}