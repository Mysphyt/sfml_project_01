@echo off

echo clearing bin/
rm bin/*.o

for %%f in (
  main
, menu
, event
, log
, program
, data
, texture_manager
, font_manager
, sprite_manager
) do (
    echo compiling %%f
    g++ -c -L.\include\SFML-3.0.2\lib -I.\include\SFML-3.0.2\include lib\%%f.cpp -DSFML_STATIC -o bin\%%f.o
)
echo Linking...
g++ bin\*.o -o main -L.\include\SFML-3.0.2\lib -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lopengl32 -lwinmm -lgdi32 -lfreetype 
