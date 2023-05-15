#include <iostream>
#include <filesystem>
#include <string_view>


#if _WIN64
const std::string defaultDir = "C:/Program Files/TGSDK";
const std::string sourceDir = "packageWin64";
const std::string includeDir = "/include/TGMath";
const std::string libDir = "/lib";
#elif __linux__
const std::string defaultDir = "/usr/local";
const std::string sourceDir = "packageDebian64";
const std::string includeDir = "/include/TGMath";
const std::string libDir = "/lib";
#endif

std::string dstDir = defaultDir;

bool getUserDecision(std::string_view message)
{
	char cache{};
	while (cache != 'y' && cache != 'n')
	{
		std::cout << message;
		std::cin >> cache;
	}
	return (cache == 'y');
}
bool checkPathIsOnlyDisk(std::string_view path)
{
#if _WIN64
	if (path.length() == 2)
	{
		return (path[1] == ':');
	}
#endif
	return false;
}

int main()
{
	std::cout << "TGMath will be installed in: " << dstDir << std::endl;
#ifdef _WIN64
	if (getUserDecision("Would you change installation destination directory? (y/n) "))
	{
		do
		{
			std::cout << "Enter it: ";
			std::cin.ignore(UINT32_MAX, '\n');
			std::getline(std::cin, dstDir, '\n');
		} while (!std::filesystem::is_directory(dstDir));
	}
	if (std::filesystem::exists(dstDir) && !checkPathIsOnlyDisk(dstDir))
	{
		if (getUserDecision("It looks like directory which you chose is already exists. Overwrite it? (y/n) "))
		{
			std::filesystem::remove_all(dstDir);
		}
	}
#endif
	if (std::filesystem::exists(dstDir + "/include/TGMath"))
		std::filesystem::remove_all(dstDir + "/include/TGMath");
	if (std::filesystem::exists(dstDir + "/lib/libTGMath.a"))
		std::filesystem::remove(dstDir + "/lib/libTGMath.a");


	try
	{
		std::cout << "Creating directiories..." << std::endl;
		{
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