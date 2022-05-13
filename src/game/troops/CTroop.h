#pragma once
#include "CCoord.h"
#include <set>
#include <string>
#include <memory>
#include "CCoord.h"

enum class SIDE {
    BLACK,
    RED
};

class CTroop {
public:
    CTroop ( std::string name, SIDE side, CCoord coord ) :
            m_Name ( move ( name ) ),
            m_Side (side),
            m_Coord ( coord ) {};
    virtual ~CTroop() noexcept = default;
    virtual std::set<CCoord> getPossibleMoves ( const std::unique_ptr<CTroop> currBoard[10][9] ) const = 0;
    const CCoord & getCoord () const { return m_Coord; };
    const std::string & getName  () const { return m_Name; };
    const SIDE & getSide  () const { return m_Side; };

protected:
    std::string m_Name;
    SIDE m_Side;
    // where the troop is currently on the board
    CCoord m_Coord;
};

