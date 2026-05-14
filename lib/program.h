#ifndef PROGRAM_H
#define PROGRAM_H

#include <ctime>
#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <thread>
#include <windows.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "event.h"

void InitProgram();

void ProgramLoop(sf::RenderWindow& window);

void RenderProgram(sf::RenderWindow& window);

void UpdateProgram();

#endif