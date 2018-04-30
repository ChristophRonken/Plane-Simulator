//
// Created by oliviervh on 28.04.18.
//

#include "Utils.h"

bool isNumber(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();

}

string intToString(int i){

    stringstream ss;
    ss << i;
    string str = ss.str();
    return str;

};
