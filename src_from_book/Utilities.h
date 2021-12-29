#ifndef LOGICGAMEENGINE_UTILITIES_H
#define LOGICGAMEENGINE_UTILITIES_H

#include <sstream>
#include <string>
#include <algorithm>

inline void ReadQuotedString(std::stringstream &stream,
                             std::string &string) {
    stream >> string;
    if (string.at(0) == '"') {
        while (string.at(string.length() - 1) != '"' || !stream.eof()) {
            std::string str;
            stream >> str;
            string.append(" " + str);
        }
    }
    string.erase(std::remove(string.begin(), string.end(), '"'), string.end());
}

#endif //LOGICGAMEENGINE_UTILITIES_H
