cmake_minimum_required(VERSION 3.21)
project(chess)

set(CMAKE_CXX_STANDARD 17)

include_directories(build)
include_directories(src)

add_executable(chess
        src/main.cpp
        src/game/CBoard.h
        src/game/CBoard.cpp
        src/game/CCoord.h
        src/game/CCoord.cpp
        src/game/CTroop.h
        src/game/CGeneral.h
        src/game/CGeneral.cpp
        src/game/CAdvisor.h
        src/game/CAdvisor.cpp
        src/game/CElephant.cpp
        src/game/CElephant.h
        src/game/CHorse.cpp
        src/game/CHorse.h
        src/game/CChariot.cpp
        src/game/CChariot.h
        src/game/CPawn.cpp
        src/game/CPawn.h
        src/game/CCannon.cpp
        src/game/CCannon.h
        src/game/Move.cpp
        src/game/Move.h
        src/game/CPlayer.h
        src/game/CPlayerRandomAI.cpp
        src/game/CPlayerRandomAI.h
        src/game/CFen.cpp
        src/game/CFen.h
        src/game/CPositionInf.h
        src/game/UI.cpp
        src/game/UI.h
        src/game/CGame.h
        src/game/CGame.cpp
        src/game/CPlayerHuman.cpp
        src/game/CPlayerHuman.h
        src/game/CApplication.cpp
        src/game/CApplication.h
        src/game/CQuitException.h
        src/game/Constants.h
        src/game/Draw.h src/game/CEvaluation.cpp src/game/CEvaluation.h src/game/CSearch.cpp src/game/CSearch.h src/game/CPlayerSmartAI.cpp src/game/CPlayerSmartAI.h
        src/game/Perft.cpp
        src/game/Perft.h
        src/game/PLAYER_TYPE.h )


