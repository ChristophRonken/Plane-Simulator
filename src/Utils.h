//
// Created by oliviervh on 28.04.18.
//

#ifndef PSE_V1_UTILS_H
#define PSE_V1_UTILS_H

# include <sstream>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <cstdio>
#include <string>

using namespace std;

/**
 * Checks if a string is a number
 * @param s
 * @return bool
 */
bool isNumber(const std::string& s);

/**
 * Converts Ints to strings
 * @param int i
 * @return string
 */
string intToString(int i);

/**
 * Compares 2 files
 * @param leftFileName
 * @param rightFileName
 * @return
 */
bool FileCompare(const std::string leftFileName, const std::string rightFileName);

#endif //PSE_V1_UTILS_H

