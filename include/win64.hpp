#pragma once
#include <string_view>
#include <iostream>
#include <filesystem>

const std::string defaultDir = "C:/Program Files/TGSDK";
const std::string sourceDir = "packageWin64";
const std::string includeDir = "/include/TGMath";
const std::string libDir = "/lib";

std::string dstDir = defaultDir;

bool checkPathIsOnlyDisk(std::string_view path)
{
	if (path.length() == 2)
	{
		return (path[1] == ':');
	}
	return false;
}
void changeInstallDir()
{
	do
	{
		std::cout << "Enter new directory: ";
		std::cin.ignore(UINT32_MAX, '\n');
		std::getline(std::cin, dstDir, '\n');
	} while (!std::filesystem::is_directory(dstDir));
}
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
void removeExistingInstallDir()
{
	if (std::filesystem::exists(dstDir + "/include/TGMath"))
		std::filesystem::remove_all(dstDir + "/include/TGMath");
	if (std::filesystem::exists(dstDir + "/lib/TGMath.lib"))
		std::filesystem::remove(dstDir + "/lib/TGMath.lib");
}
bool checkIsExists()
{
	if (std::filesystem::exists(dstDir + "/include/TGMath"))
		return true;
	else if (std::filesystem::exists(dstDir + "/lib/TGMath.lib"))
		return true;
	return false;
}

void process()
{
	if (getUserDecision("Would you change installation destination directory? (y/n) "))
	{
		changeInstallDir();
	}

	if (checkIsExists() && !checkPathIsOnlyDisk(dstDir))
	{
		if (getUserDecision("It looks like directory which you chose is already exists. Overwrite it? (y/n) "))
		{
			removeExistingInstallDir(); 
		}
		else
		{
			std::cout << "Couldn't overwrite existing directories. Installator will be closed." << std::endl;
			auto x = getchar();
			exit(0);
		}
	}
}