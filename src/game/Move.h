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
    /**
     * Construct a Method
     * @param mFrom  from coord
     * @param mTo  to coord
     */
    Move ( const CCoord &mFrom, const CCoord &mTo );
    Move () = default;

    CCoord m_From;
    CCoord m_To;
    /*
     * Score for Ordering better moves
     */
    int m_Score = 0;

    bool operator == ( const Move & rhs ) const;
    bool operator < ( const Move & rhs ) const;
    friend std::ostream & operator << ( std::ostream & os, const Move & move );
};


