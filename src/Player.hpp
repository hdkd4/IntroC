#pragma once

#include "Entity.hpp"

class Player : public Entity
{
public:
    int XPTotal = 0;
    int level = 0;
    int maxHealth = 20+5*(level);
    int health = maxHealth;
    int attack = 1+level;
    int maxMana = 30+10*level;
    int mana = maxMana;
    int magicResist = 0;
    int baseAttackResist = 0;
    int attackResist = 0;
    int ironSkinTurns = 0;
    int goldCount = 0;
    int XP = 0;
    int XPThreshold = 100;
    int fireballDamageBoost = 0;
    int ironSkinPower = 0;
    int healingPower = 0;
    void Start();
    void Update();
private:
    int m_keyCount = 0;
};