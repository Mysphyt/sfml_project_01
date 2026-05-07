#ifndef GLOBALS_H
#define GLOBALS_H

#include <SFML/Graphics.hpp>

enum class GameState {
    MENU,
    GAME
};
extern GameState CURR_GAME_STATE;

extern sf::Font DEFAULT_BUTTON_FONT;

inline constexpr unsigned int WIN_WIDTH = 800;
inline constexpr unsigned int WIN_HEIGHT = 600;
inline constexpr unsigned int TARGET_FRAME_RATE = 60;

inline constexpr char DATA_DELIM = '|';

#endif // GLOBALS_H