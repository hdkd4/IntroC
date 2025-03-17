#pragma once
#include "fogpi/Math.hpp"

#include <string>
#include <vector>

#include "Entity.hpp"
#include "Door.hpp"

class Room {
public:
    void Load(std::string _path);
    void Draw();
    void Update();

    bool StillPlaying() { return true; }
    int monsterPile=0;

    Entity& GetPlayer() { return *m_player; }
    std::vector<Entity*>& GetMonsters() { return m_monsters; }
    const std::vector<std::vector<char>>& GetMap() { return m_map; }
    char GetLocation(Vector2D _pos);
    void SetLocation(Vector2D _pos, char _char);
    void ClearLocation(Vector2D _pos);
    void OpenDoor(Vector2D _pos);
private:
    Entity *m_player = nullptr;
    std::vector<Entity*> m_monsters;
    std::vector<std::vector<char>> m_map;
    std::vector<Door> m_doors;
};