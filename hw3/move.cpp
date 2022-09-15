#include "move.h"


// Complete
Move::Move(Board* board)
{
    m.first = Vehicle::INVALID_ID;
    m.second = 0;
    b = board;
    g = 0;
    h = 0;
    prev = NULL;
}

// To be completed
Move::Move(const Board::MovePair& move, Board* b,  Move *parent)
{
    m.first = move.first;
    m.second = move.second;
    b = b;
    g = parent->g;
    h = parent->h;
    prev = parent;
}

// To be completed
Move::~Move()
{

}

// To be completed
bool Move::operator<(const Move& rhs) const
{
    // Replace this
    return false;
}

// To be completed
void Move::score(Heuristic *heur) 
{

}
