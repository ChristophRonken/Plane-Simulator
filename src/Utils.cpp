//
// Created by oliviervh on 28.04.18.
//

# include <iostream>

using namespace std;

bool is_number(const std::string& s) {
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();

}