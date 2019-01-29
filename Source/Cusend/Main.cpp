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

void getLoginPage(csd::Request& req, csd::Response& res) {
	csd::ResponseFactory::sendFile(res, "Static/login.html");
}

void postLoginPage(csd::Request& req, csd::Response& res) {
	std::string pass = req.getField("pass");

	if (pass != "2019") {
		res.setStatus(403);
		csd::ResponseFactory::text(res, "Access denied - invalid password!");
		return;
	}

	res.setCookie("loggedIn", "yes");
	csd::ResponseFactory::redirect(res, "/profile");
}

void profilePage(csd::Request& req, csd::Response& res) {
	if (req.getCookie("loggedIn") != "yes") {
		csd::ResponseFactory::redirect(res, "/login");
		return;
	}

	csd::ResponseFactory::text(res, "You are logged in! This is your profile.");
}

void indexPage(csd::Request& req, csd::Response& res) {
	csd::ResponseFactory::sendFile(res, "Static/index.html");
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

	app.route(csd::Methods::Get, "/", indexPage);

	app.route(csd::Methods::Get, "/file", fileRoute);

	app.route(csd::Methods::Get, "/form", getFormRoute);
	app.route(csd::Methods::Post, "/form", postFormRoute);

	app.route(csd::Methods::Get, "/login", getLoginPage);
	app.route(csd::Methods::Post, "/login", postLoginPage);

	app.route(csd::Methods::Get, "/profile", profilePage);

	app.route(csd::Methods::Get, "/favicon.ico", faviconRoute);

	app.listen(1234);

	if (app.getError() != csd::Errors::None) {
		std::cout << "Cusend Error: " << app.getError() << std::endl;
		std::cout << "Network Error: " << app.getSocketError() << std::endl;
	}

	return 0;
}