//
// Created by tiendat on 21.05.22.
//
#pragma once
#include "CCoord.h"
#include <ostream>


/**
 * Move class to handle from and to
 */
struct Move {
    Move ( const CCoord &mFrom, const CCoord &mTo );
    Move () = default;

    CCoord m_From;
    CCoord m_To;

    bool operator == ( const Move & rhs ) const;
    friend std::ostream & operator << ( std::ostream & os, const Move & move );
};


