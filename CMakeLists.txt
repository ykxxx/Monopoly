cmake_minimum_required(VERSION 3.8)
project(HW4)

set(GPP_ENABLE_WARNINGS "-O0 -Wall -Werror -Wno-unused-result")
set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GPP_ENABLE_WARNINGS}")
add_executable(HW4 ${SOURCE_FILES} Board.cpp
        Board.h
        CSVReader.cpp
        CSVReader.h
        DiceRoller.cpp
        DiceRoller.h
        GameState.cpp
        GameState.h
        Space.cpp
        Space.h
        Go.cpp
        Go.h
        main.cpp
        MonopolyUtility.cpp
        MonopolyUtility.h
        Move.cpp
        Move.h
        Player.cpp
        Player.h
        Property.cpp
        Property.h
        PropertyManager.cpp
        PropertyManager.h
        PropertySet.cpp
        PropertySet.h
        Rules.cpp
        Rules.h
        FreeParking.cpp FreeParking.h PayToBank.cpp PayToBank.h Jail.cpp Jail.h GoToJail.cpp GoToJail.h)