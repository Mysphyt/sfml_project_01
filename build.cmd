@echo off

for %%f in (main, menu, event, log, game, data, texture_manager, font_manager) do (
    echo compiling %%f
    g++ -c -L.\include\SFML-3.0.2\lib -I.\include\SFML-3.0.2\include lib\%%f.cpp -DSFML_STATIC -o lib\%%f.o
)
g++ lib\menu.o lib\event.o lib\log.o lib\main.o lib\game.o lib\data.o lib\texture_manager.o lib\font_manager.o -o main -L.\include\SFML-3.0.2\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype 
