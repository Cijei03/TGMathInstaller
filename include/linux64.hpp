#pragma once
#include <string_view>
#include <iostream>
#include <filesystem>

const std::string defaultDir = "/usr/local";
const std::string sourceDir = "packageDebian64";
const std::string includeDir = "/include/TGMath";
const std::string libDir = "/lib";

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
void removeExistingInstallDir()
{
	if (std::filesystem::exists(dstDir + "/include/TGMath"))
		std::filesystem::remove(dstDir + "/include/TGMath");
	if (std::filesystem::exists(dstDir + "/lib/TGMath"))
		std::filesystem::remove(dstDir + "/lib/TGMath");
}
void process()
{
	if (getUserDecision("It looks like installation directory is already exists. Overwrite it? (y/n) "))
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