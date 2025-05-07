C:\Programme\MinGW\bin\g++.exe ^
    -fdiagnostics-color=always ^
    ^
    .\source\transmitter.cpp ^
    ^
    -g ^
    -shared -o ^
    .\lib\transmitter.dll ^
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
    -l file_system ^
    ^
    -std=gnu++20 ^
    -D EEA
