//
// Created by tiendat on 21.05.22.
//
#pragma once
#include "troops/CCoord.h"


/**
 * Move class to handle from and to
 */
struct Move {
    Move ( const CCoord &mFrom, const CCoord &mTo );

    CCoord m_From;
    CCoord m_To;
};


