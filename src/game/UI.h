//
// Created by tiendat on 25.05.22.
//
#pragma once
#include "CBoard.h"

/*
 * CLass Handle all static console UI
 */
class UI {
public:
    static void printBoard ( const CBoard &currBoard );
    static void printHelpMenu();
    static void printUserMenu();
    static void printChoosePlayer();

private:
    static const std::string ESCAPE;
    static const std::string RESET;
    static const std::string BRIGHT;
    static void printHead ();
    static void printSep ();
};


