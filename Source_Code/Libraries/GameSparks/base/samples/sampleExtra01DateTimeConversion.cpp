#include <iostream>
#include <GameSparks/GSDateTime.h>


int main(int argc, const char* argv[])
{
    (void)(argc);
    (void)(argv);
	using namespace GameSparks::Core;

	GSDateTime now = GSDateTime::Now();
	GSDateTime nowLocal = now.ToLocalTime();
	GSDateTime nowGM = now.ToGMTime();

	std::cout << "now: " << now.ToString() << "hour: " << std::endl;
	std::cout << "nowLocal: " << nowLocal.ToString() << std::endl;
	std::cout << "nowGM: " << nowGM.ToString() << std::endl;

	std::cout << "conversion: " << GSDateTime(now.ToString()).ToString() << std::endl;

	std::cout << "try '2014-12-15T17:09:43.480Z'" << std::endl;
	std::cout << "ToString: " << GSDateTime("2014-12-15T17:09:43.480Z").ToString() << std::endl;
	std::cout << "ToLocalTime().ToString: " << GSDateTime("2014-12-15T17:09:43.480Z").ToLocalTime().ToString() << std::endl;
	std::cout << "ToGMTime().ToString(): " << GSDateTime("2014-12-15T17:09:43.480Z").ToGMTime().ToString() << std::endl;

	GSDateTime now2 = now;

	std::cout << now2.ToString() << std::endl;

	return 0;
}


