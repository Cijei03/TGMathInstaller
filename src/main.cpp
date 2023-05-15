#include <iostream>
#include <filesystem>
#include <string_view>


#if _WIN64
#include "../include/win64.hpp"
#elif __linux__
#include "../include/linux64.hpp"
#endif


int main()
{
	std::cout << "TGMath will be installed in: " << dstDir << std::endl;
	process();
	return 0;
	try
	{
		std::cout << "Creating directiories..." << std::endl;
		{
			std::filesystem::create_directories(dstDir + includeDir);
			std::filesystem::create_directories(dstDir + includeDir + "/vectorSIMD");
			std::filesystem::create_directories(dstDir + libDir);
		}
		std::cout << "Copying files..." << std::endl;
		{
			std::filesystem::copy(sourceDir + "/include", dstDir + includeDir);
			std::filesystem::copy(sourceDir + "/include/vector", dstDir + includeDir + "/vector");
			std::filesystem::copy(sourceDir + "/include/matrix", dstDir + includeDir + "/matrix");
			std::filesystem::copy(sourceDir + "/include/vectorSIMD", dstDir + includeDir + "/vectorSIMD");
			std::filesystem::copy(sourceDir + "/include/vectorSIMD/vec2", dstDir + includeDir + "/vectorSIMD/vec2");
			std::filesystem::copy(sourceDir + "/include/vectorSIMD/vec3", dstDir + includeDir + "/vectorSIMD/vec3");
			std::filesystem::copy(sourceDir + "/include/vectorSIMD/vec4", dstDir + includeDir + "/vectorSIMD/vec4");
			std::filesystem::copy(sourceDir + "/lib", dstDir + libDir);
		}
	}
	catch (std::exception)
	{
		std::cout << "Installer met unexpected problems, installation aborted." << std::endl;
	}
	return 0;
}