#ifndef GLOBALS_H
#define GLOBALS_H

#include <map>
#include <SFML/Graphics.hpp>

enum class ProgramState {
    MENU,
    MODULE
};
extern ProgramState CURR_PROGRAM_STATE;
extern sf::Vector2u WINDOW_SIZE;

inline constexpr unsigned int BASE_WIN_WIDTH = 1280;
inline constexpr unsigned int BASE_WIN_HEIGHT = 720;
inline constexpr unsigned int TARGET_FRAME_RATE = 60;

// COLORS_
inline constexpr sf::Color TRANSPARENT_PINK({255, 65, 235, 155});
inline constexpr sf::Color PINK({255, 65, 235});
inline constexpr sf::Color TRANSPARENT_TEAL({65, 230, 255, 155});
inline constexpr sf::Color TRANSPARENT_GREEN({65, 255, 75, 155});

// _COLORS

inline constexpr char DATA_DELIM = '|';

#endif // GLOBALS_H