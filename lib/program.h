#ifndef PROGRAM_H
#define PROGRAM_H

#include <ctime>
#include <iostream>
#include <stdio.h>
#include <thread>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "event.h"

void InitProgram();

void ProgramLoop(sf::RenderWindow& window);

void RenderProgram(sf::RenderWindow& window);

void UpdateProgram(sf::RenderWindow& window, float deltaTime);

#endif
