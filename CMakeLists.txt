cmake_minimum_required(VERSION 3.27)
project(Final_C_Project C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Final_C_Project
        CelestialBody.c
        CelestialBody.h
        Location.c
        Location.h
        main.c
        main.h
        StringToolBox.h
        SpaceAgency.h
        StringToolBox.c
        SpaceAgency.c
        AgencyManager.h
        AgencyManager.c
        Expedition.h
        Expedition.c
        Date.h
        Date.c
        SpaceControlSystem.h
        SpaceControlSystem.c
        SpaceMap.h
        SpaceMap.c
        input.h
        input.c)
