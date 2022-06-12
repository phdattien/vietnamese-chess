#pragma once
#include <set>
#include <string>
#include <memory>
#include <vector>
#include "CCoord.h"
#include "Constants.h"

/*
 * enum for two board sides
 */
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
    /*
     * Constructor takes whick side and on what coord is troop is on Board
     *
     * @param side on
     * @param coord on what coord
     */
    CTroop ( SIDE side, CCoord coord ) :
            m_Side (side),
            m_Coord ( coord ) {};
    virtual ~CTroop() noexcept = default;
    /**
     * Virtual method to get all Possible moves from troops position
     * @param currBoard on Play
     * @return set of Coordinates of possibleMoves
     */
    virtual std::set<CCoord> getPossibleMoves ( const Board & currBoard ) const = 0;
    /**
     * Every troop has his own default unique name - can't be chanche
     * @return his name as char
     */
    virtual char getName () const = 0;
    // get side of a troop
    const SIDE & getSide  () const { return m_Side; };
    // setter for a newCoordinate
    void setCoord ( const CCoord & newCoord ) { m_Coord = newCoord; };
    const CCoord & getCoord () const { return m_Coord; };

protected:
    SIDE m_Side;
    /** @var Troop current position */
    CCoord m_Coord;
};

