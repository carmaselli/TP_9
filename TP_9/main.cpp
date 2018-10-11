
//#include<boost/program_options/cmdline.hpp>
#include<boost/program_options.hpp>
#include<iostream>

namespace po = boost::program_options;
using namespace std;


int main(int argc, char*argv[])
{
	cout << argc ;

	// Declare the supported options.
	po::options_description desc("Allowed options");
	desc.add_options()
		("help", "produce help message")
		("compression", po::value<int>(), "set compression level")
		("nico gil", po::value<string>(), "definir si nico es puto")
		;
	desc.add_options()
		("hola", "hace esto")
		;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if (vm.count("help")) {
		cout << desc << "\n";
		getchar();
		return 1;
	}

	if (vm.count("compression")) {
		cout << "Compression level was set to "
			<< vm["compression"].as<int>() << ".\n";
	}
	else {
		cout << "Compression level was not set.\n";
	}
	getchar();
}