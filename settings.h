#ifndef SETTINGS
#define SETTINGS

#include <iostream>
#include <limits>
#include <fstream>

struct Settings
{
  int length;
  std::string mode;
  std::string system;
  int retries;
};

std::string settings(void);

Settings parse_settings(std::string settings);

void print_settings(Settings settings);

std::string select_mode(void);
std::string select_system(void);


#endif