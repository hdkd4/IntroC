#pragma once

#include "fogpi/Math.hpp"
#include "Stats.hpp"

// forward defin
class Room;

class Entity {
public:
    Room *room;

    void Init(Vector2D _position) { m_position = _position; }

    virtual void Start() {}
    virtual void Update() {}

    char Draw() {return m_character; }
    Vector2D GetPosition() { return m_position; }
    const Stats& GetStats() {return m_stats;}
protected:
    Vector2D m_position;
    char m_character;
    Stats m_stats;
    //char m_color = '[0;31m';
};