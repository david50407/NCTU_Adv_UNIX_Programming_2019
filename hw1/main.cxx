#include "netstat/application.hxx"

int main(int argc, char **argv) {
	Netstat::Application app;
	app.run(argc, argv);

	return 0;
}
