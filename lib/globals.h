#ifndef GLOBALS_H
#define GLOBALS_H

#include <map>
#include <SFML/Graphics.hpp>

enum class ProgramState {
    MENU,
    PROGRAM
};
extern ProgramState CURR_PROGRAM_STATE;

inline constexpr unsigned int WIN_WIDTH = 800;
inline constexpr unsigned int WIN_HEIGHT = 600;
inline constexpr unsigned int TARGET_FRAME_RATE = 60;

inline constexpr char DATA_DELIM = '|';

#endif // GLOBALS_H