#ifndef LOGICGAMEENGINE_NOLEVELSFILEEXCEPTION_H
#define LOGICGAMEENGINE_NOLEVELSFILEEXCEPTION_H

#include <exception>

class NoLevelsFileException : public std::exception {
    [[nodiscard]] const char *what() const noexcept override {
        return "Can't find valid levels file";
    }
};

#endif //LOGICGAMEENGINE_NOLEVELSFILEEXCEPTION_H
