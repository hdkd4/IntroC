#pragma once
#include "Entity.hpp"
#include "fogpi/fogpi.hpp"
#include <iostream>
#include "Player.hpp"

class Orc: public Entity
{
    public:
    int level = 0;
    int maxHealth = random_int(20,30);
    int health = maxHealth;
    int attack = random_int(0,4);
    int attackBoost = 0;
    int attackResist = 0;
    void Start();
    void Update();
};

class Shaman: public Entity
{
    public:
    int level = 0;
    int maxHealth = random_int(10,20);
    int health = maxHealth;
    int maxMana = random_int(20,70);
    int manaRemainder = maxMana%5;
    int mana = maxMana-manaRemainder;
    int ironSkinTurns = 0;
    int attack = random_int(0,1);
    int attackResist = 0;
    void Start();
    void Update();
};