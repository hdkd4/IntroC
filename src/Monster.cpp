
#include "fogpi/fogpi.hpp"
#include "Monster.hpp"
#include "Room.hpp"


void Orc::Start()
{
    m_character = 'M';
    Orc monster;
}
void Orc::Update()
{
    int movement_direction = random_int(1,4);
    Vector2D direction(0.0f);
    switch (movement_direction)
    {
    case 1:
        direction = {0.0f, -1.0f};
        break;
    case 2:
        direction = {-1.0f, 0.0f};
        break;
    case 3:
        direction = {0.0f, 1.0f};
        break;
    case 4:
        direction = {1.0f, 0.0f};
        break;
    }
    Vector2D TryPos = m_position + direction;
    if (room->GetLocation(TryPos) == ' ')
    {
        m_position = TryPos;
    }
}

void Shaman::Start()
{
    m_character = 'm';
    Shaman monster;
}
void Shaman::Update()
{
    int movement_direction = random_int(1,4);
    Vector2D direction(0.0f);
    switch (movement_direction)
    {
    case 1:
        direction = {0.0f, -1.0f};
        break;
    case 2:
        direction = {-1.0f, 0.0f};
        break;
    case 3:
        direction = {0.0f, 1.0f};
        break;
    case 4:
        direction = {1.0f, 0.0f};
        break;
    }
    Vector2D TryPos = m_position + direction;
    if (room->GetLocation(TryPos) == ' ')
    {
        m_position = TryPos;
    }
}