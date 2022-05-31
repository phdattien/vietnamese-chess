#pragma once
#include <set>
#include <string>
#include <memory>
#include <vector>
#include "CCoord.h"
#include "troopsNames.h"

enum class SIDE {
    BLACK,
    RED
};
/**
 * Abstract class of all troops in game
 */


class CTroop {
public:
    using Board = std::vector<std::vector<std::shared_ptr<CTroop>>>;
    CTroop ( SIDE side, CCoord coord ) :
            m_Side (side),
            m_Coord ( coord ) {};
    virtual ~CTroop() noexcept = default;
    // virtual method for a troop to get all of his possible moves from the his position and boardState
    virtual std::set<CCoord> getPossibleMoves ( const Board & currBoard ) const = 0;
    // Every troop has his own default unique name - can't be chanched
    virtual char getName () const = 0;
    // get side of a troop
    const SIDE & getSide  () const { return m_Side; };
    // setter for a newCoordinate
    void setCoord ( const CCoord & newCoord ) { m_Coord = newCoord; };
    // get a current Coordinate of a troop
    const CCoord & getCoord () const { return m_Coord; };

protected:
    // which color Troop belongs to
    SIDE m_Side;
    // where the troop is currently on the board
    CCoord m_Coord;
};

