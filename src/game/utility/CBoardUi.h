//
// Created by tiendat on 25.05.22.
//
#pragma once
#include "../CBoard.h"

class CBoardUi {
public:
    static void printBoard ( const CBoard &currBoard );
    static void printHelpMenu();
    static void printUserMenu();

private:
    static const std::string ESCAPE;
    static const std::string RESET;
    static const std::string BRIGHT;

    static void printHead ();
    static void printSep ();
};


