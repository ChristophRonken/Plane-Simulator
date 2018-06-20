//
// Created by oliviervh on 28.04.18.
//

#include "Utils.h"

bool isNumber(const std::string &s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it))
        ++it;
    return !s.empty() && it == s.end();
}

string intToString(int i)
{

    stringstream ss;
    ss << i;
    string str = ss.str();
    return str;
};

/**
Auxiliary functions for file manipulation.
*/
bool DirectoryExists(const std::string dirname)
{
    struct stat st;
    return stat(dirname.c_str(), &st) == 0;
}

bool FileExists(const std::string filename)
{
    struct stat st;
    if (stat(filename.c_str(), &st) != 0)
        return false;
    ifstream f(filename.c_str());
    if (f.good())
    {
        f.close();
        return true;
    }
    else
    {
        f.close();
        return false;
    }
}

bool FileIsEmpty(const std::string filename)
{
    struct stat st;
    if (stat(filename.c_str(), &st) != 0)
        return true; // File does not exist; thus it is empty
    return st.st_size == 0;
}

bool FileCompare(const std::string leftFileName, const std::string rightFileName)
{
    ifstream leftFile, rightFile;
    char leftRead, rightRead;
    bool result;

    // Open the two files.
    leftFile.open(leftFileName.c_str());
    if (!leftFile.is_open())
    {
        return false;
    };
    rightFile.open(rightFileName.c_str());
    if (!rightFile.is_open())
    {
        leftFile.close();
        return false;
    };

    result = true; // files exist and are open; assume equality unless a counterexamples shows up.
    while (result && leftFile.good() && rightFile.good())
    {
        leftFile.get(leftRead);
        rightFile.get(rightRead);
        result = (leftRead == rightRead);
    };
    if (result)
    {
        // last read was still equal; are we at the end of both files ?
        result = (!leftFile.good()) && (!rightFile.good());
    };

    leftFile.close();
    rightFile.close();
    return result;
}