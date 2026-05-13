#ifndef GAME_H
#define GAME_H

#include <ctime>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <thread>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "event.h"

void InitGame();

void GameLoop(sf::RenderWindow& window);

void RenderGame(sf::RenderWindow& window);

void UpdateGame();

#endif