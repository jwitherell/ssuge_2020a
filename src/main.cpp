#include <application.h>

int main(int argc, char ** argv)
{
	ssuge::Application app;
	app.initApp();
	app.run();
	app.closeApp();
	return 0;
}