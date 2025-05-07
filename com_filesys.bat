C:\Programme\MinGW\bin\g++.exe ^
    -fdiagnostics-color=always ^
    ^
    .\source\file_system.cpp ^
    ^
    -g ^
    -shared -o ^
    .\lib\file_system.dll ^
    ^
    -I C:\Programme\SFML\SFML-2.6.1\include ^
    -L .\lib ^
    -l openal32 ^
    -l sfml-audio ^
    -l sfml-graphics ^
    -l sfml-network ^
    -l sfml-system ^
    -l sfml-window ^
    -I .\include ^
    -L C:\Programme\SFML\SFML-2.6.1\lib ^
    ^
    -std=gnu++20 ^
    -D EEA
