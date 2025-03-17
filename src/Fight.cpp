#include "Fight.hpp"
#include "Room.hpp"
#include "Entity.hpp"
#include "Player.hpp"
#include "Monster.hpp"
#include <iostream>
#include "fogpi/fogpi.hpp"

void FightOrc(Player& player,Room& room)
{
    Orc monster;
    int numInput = 0;
    int nextAct = 0;
    int MonsterAct;
    monster.level=random_int(0,player.level);
    monster.maxHealth +=random_int(3,7)*(monster.level);
    monster.health = monster.maxHealth;
    monster.attack += random_int(1,2)*monster.level;

    printf("\nYou encountered a level %d orc!\n",monster.level);

    //Player turn starts
    while(true)
    {
        do{
            printf("\nYou:                Orc:\
                    \nHealth: %d/%d       Health %d/%d\
                    \nMana:   %d/%d\n",player.health,player.maxHealth,monster.health,monster.maxHealth,player.mana,player.maxMana);
            printf("\n1: Attack\n2: Magic\n\n");
            numInput = request_int("Enter a number to proceed");
            
        } while(numInput != 1 && numInput != 2);
        switch (numInput)
        {
            case 1: 
            {
                int attackRoll = random_int(1,6) + player.attack-monster.attackResist;
                if(attackRoll>0)
                {
                    printf("You did %d damage to the orc!\n\n",attackRoll);
                    monster.health-=attackRoll;
                }
                else
                {
                    printf("You missed!\n");
                }
                break;
            }
            case 2: 
            {
                do{
                    printf("\n1: Heal: heal yourself for %d-%d hp at the cost of 10 mana\
                        \n2: Iron Skin: increases your damage resistance by %d-%d points for 3 rounds at the cost of 15 mana\
                        \n3: Fireball: deals %d-%d damage and ignores resistances at the cost of 30 mana \n\n",
                        5+player.healingPower,10+player.healingPower,
                        1+player.ironSkinPower,5+player.ironSkinPower,
                        10+player.fireballDamageBoost,20+player.fireballDamageBoost);
                    numInput = request_int("Enter a number to proceed");
                } while(numInput != 1 && numInput != 2 && numInput != 3);

                switch (numInput)
                {
                case 1: 
                {
                if(player.mana>=10)
                {
                    player.mana -= 10;
                    int healRoll = random_int(5, 10)+player.healingPower;
                    printf("You healed yourself for %d points!\n\n",healRoll);
                    player.health += healRoll;
                    if (player.health>player.maxHealth)
                        player.health=player.maxHealth;
                    player.mana-=player.maxMana/10;
                }
                else
                {
                    printf("Not enough mana!\n\n");
                }
                break;
                }
                case 2:
                {
                    if (player.mana >= 15)
                    {
                        player.mana -= 15;
                        int ironSkinRoll = random_int(1, 5)+player.ironSkinPower;
                        printf("Your Physical Resist rose by %d points!\n\n",ironSkinRoll);
                        player.attackResist = ironSkinRoll+player.baseAttackResist;
                        player.ironSkinTurns = 4;
                        player.mana-=player.maxMana/10;
                    }
                    else
                    {
                        printf("Not enough mana!\n\n");
                    }
                break;
                }
            
            
                case 3:
                {
                    if(player.mana>=30)
                    {
                        player.mana-=30;
                        player.mana-=player.maxMana/10;
                        int attackRoll = random_int(10,20)+player.fireballDamageBoost;
                        printf("You did %d damage to the orc!\n",attackRoll);
                        monster.health-=attackRoll;
                    }
                    else
                    {
                        printf("Not enough mana!\n");
                    }
                    break;
                }

                break;
                }
            }
        }
        //End Player Turn
        
            monster.attackResist = 0;
        if (monster.health<1)
        {
            room.monsterPile-=1;
            int XP = random_int(25,50)+(random_int(15,45)*monster.level);
            player.XP+=XP;
            printf("You defeated the orc!\n");
            int gold = 0;
            for(int i=0; i<=monster.level;i++)
            {
                gold+=random_int(12,30);
            }
            player.goldCount+=gold;
            printf("You got %d Gold Pieces and %d XP\n",gold,XP);
            break;
        }
        //Monster Turn Start
        if (nextAct!=1)
            MonsterAct = random_int(1,3);
        else
        {
            MonsterAct = 1;
        }
        switch(MonsterAct)
        {
            case 1:
            {
                printf("Orc attacks!\n");
                int attackRoll = random_int(1,6)+monster.attack-player.attackResist+monster.attackBoost;
                if(attackRoll>0)
                {
                    printf("The orc did %d damage to you!\n",attackRoll);
                    player.health-=attackRoll;
                    nextAct = 0;
                    monster.attackBoost=0;
                }
                else
                {
                    printf("Orc missed!\n");
                }
                break;
            }
            case 2:
            {
                printf("Orc defends!\n");
                monster.attackResist = random_int(1,3);
                break;
            }
            case 3:
            {
                printf("The orc Roars at you! Its attack increased!\n");
                monster.attackBoost = random_int(1,3)+monster.level;
                nextAct = 1;
                break;
            }
            printf("\n");

        }
        //Monster Turn Ends
        player.ironSkinTurns -=1;
        if (player.ironSkinTurns == 0)
        {
            printf("Your iron skin wore off!\n\n");
            player.attackResist=player.baseAttackResist;
        }
        player.mana+=player.maxMana/10;
        if (player.mana>player.maxMana)
        {
            player.mana = player.maxMana;
        }
        if(player.health<1)
        {
            break;
            abort();
        }
    }
    return;
}

void FightShaman(Player& player, Room& room)
{
    Shaman monster;
    monster.maxMana-=monster.manaRemainder;
    int numInput = 0;
    monster.level = random_int(0,player.level);
    monster.maxHealth +=random_int(1,5)*(monster.level);
    monster.health = monster.maxHealth;
    monster.attack += monster.level;
    monster.maxMana += random_int(1,10)*monster.level;
    monster.mana = monster.maxMana;

    printf("\nYou encountered a level %d Shaman!\n",monster.level);

    //Player turn starts
    while(true)
    {
        do{
            printf("\nYou:                Shaman:\
                    \nHealth: %d/%d       Health %d/%d\
                    \nMana:   %d/%d       Mana:  %d/%d\n\
                    ",player.health,player.maxHealth,monster.health,monster.maxHealth,
                    player.mana,player.maxMana,monster.mana,monster.maxMana);
            printf("\n1: Attack\n2: Magic\n\n");
            numInput = request_int("Enter a number to proceed");
            
        } while(numInput != 1 && numInput != 2);
        switch (numInput)
        {
            case 1: 
            {
                int attackRoll = random_int(1,6) + player.attack-monster.attackResist;
                if(attackRoll>0)
                {
                    printf("You did %d damage to the shaman\n\n",attackRoll);
                    monster.health-=attackRoll;
                }
                else
                {
                    printf("You missed!\n");
                }
                break;
            }
            case 2: 
            {
                do{
                    printf("\n1: Heal: heal yourself for %d-%d hp at the cost of 10 mana\
                            \n2: Iron Skin: increases your damage resistance by %d-%d points for 3 rounds at the cost of 15 mana\
                            \n3: Fireball: deals %d-%d damage and ignores resistances at the cost of 30 mana \n\n",
                            5+player.healingPower,10+player.healingPower,
                            1+player.ironSkinPower,5+player.ironSkinPower,
                            10+player.fireballDamageBoost,20+player.fireballDamageBoost);
                    numInput = request_int("Enter a number to proceed");
                } while(numInput != 1 && numInput != 2 && numInput != 3);

                switch (numInput)
                {
                case 1: 
                {
                if(player.mana>=10)
                {
                    player.mana -= 10;
                    int healRoll = random_int(5, 10)+player.healingPower;
                    printf("You healed yourself for %d points!\n\n",healRoll);
                    player.health += healRoll;
                    if (player.health>player.maxHealth)
                    {
                        player.health=player.maxHealth;
                    }
                    player.mana-=player.maxMana/10;
                }
                else
                {
                    printf("Not enough mana!\n\n");
                }
                break;
                }
                case 2:
                {
                    if (player.mana >= 15)
                    {
                        player.mana -= 15;
                        int ironSkinRoll = random_int(1, 5)+player.ironSkinPower;
                        printf("Your Physical Resist rose by %d points!\n\n",ironSkinRoll);
                        player.attackResist = ironSkinRoll+player.baseAttackResist;
                        player.ironSkinTurns = 4;
                        player.mana-=player.maxMana/10;
                    }
                    else
                    {
                        printf("Not enough mana!\n\n");
                    }
                break;
                }
                case 3:
                {
                    if(player.mana>=30)
                    {
                        player.mana-=30;
                        player.mana-=player.maxMana/10;
                        int attackRoll = random_int(10,20)+player.fireballDamageBoost;
                        printf("You did %d damage to the shaman\n",attackRoll);
                        monster.health-=attackRoll;
                    }
                    else
                    {
                        printf("Not enough mana!\n");
                    }
                    break;
                }

                break;
                }
            }
        }
        //End Player Turn
        monster.ironSkinTurns -=1;
        if (monster.ironSkinTurns == 0)
        {
            printf("Shaman's iron skin wore off!\n\n");
            monster.attackResist=0;
        }
        if (monster.health<1)
        {
            room.monsterPile-=1;
            int XP = random_int(25,50)+(random_int(15,45)*monster.level);
            player.XP+=XP;
            printf("You defeated the shaman!\n");
            int gold = 0;
            for(int i=0; i<=monster.level;i++)
            {
                gold+=random_int(12,30);
            }
            player.goldCount+=gold;
            printf("You got %d Gold Pieces and %d XP\n",gold,XP);
            break;
        }
        //Monster Turn Start
        int MonsterAct = random_int(1,4);
        switch(MonsterAct)
        {
            case 1:
            {
                printf("Shaman attacks!\n");
                int attackRoll = random_int(1,3)+monster.attack-player.attackResist;
                if(attackRoll>0)
                {
                    printf("The shaman did %d damage to you!\n",attackRoll);
                    player.health-=attackRoll;
                    monster.mana+=5;
                }
                else
                {
                    printf("Shaman missed!\n");
                }
                break;
            }
            case 2:
            {
                if(monster.mana>=20)
                {
                    printf("Shaman casts fireball!\n");
                    int attackRoll = random_int(5,15)+3*monster.level-player.magicResist;
                    monster.mana-=25;
                    printf("You took %d points of damage!\n",attackRoll);
                    player.health-=attackRoll;
                }
                else
                {
                    printf("Shaman attacks!\n");
                int attackRoll = random_int(1,3)+monster.attack-player.attackResist;
                if(attackRoll>0)
                {
                    printf("The shaman did %d damage to you!\n",attackRoll);
                    player.health-=attackRoll;
                    monster.mana+=5;
                }
                else
                {
                    printf("Shaman missed!\n");
                }
                }
                break;
            }
            case 3:
            {
                if(monster.mana>=10)
                {
                    printf("Shaman casts heal!\n");
                    int healRoll = random_int(5,10)+3*monster.level;
                    monster.mana-=15;
                    printf("Shaman was healed for %d points\n",healRoll);
                    monster.health+=healRoll;
                    if (monster.health>monster.maxHealth)
                    {
                        monster.health=monster.maxHealth;
                    }
                }
                else
                {
                    printf("Shaman attacks!\n");
                    int attackRoll = random_int(1,3)+monster.attack-player.attackResist;
                    if(attackRoll>0)
                    {
                        printf("The shaman did %d damage to you!\n",attackRoll);
                        player.health-=attackRoll;
                        monster.mana+=5;
                    }
                    else
                    {
                        printf("Shaman missed!\n");
                    }
                }
                break;
            }
            case 4:
            {
                if(monster.mana>=15)
                {
                    printf("Shaman cast iron skin!\n");
                    monster.attackResist = random_int(1,5)+2*monster.level;
                    monster.ironSkinTurns = 3;
                }
                else
                {
                    printf("Shaman attacks!\n");
                    int attackRoll = random_int(1,3)+monster.attack-player.attackResist;
                    if(attackRoll>0)
                    {
                        printf("The shaman did %d damage to you!\n",attackRoll);
                        player.health-=attackRoll;
                        monster.mana+=5;
                    }
                    else
                    {
                        printf("Shaman missed!\n");
                    }
                }
                break;
            }
            printf("\n");

        }
        //Monster Turn Ends
        player.ironSkinTurns -=1;
        if (player.ironSkinTurns == 0)
        {
            printf("Your iron skin wore off!\n\n");
            player.attackResist=player.baseAttackResist;
        }
        player.mana+=5;
        if (player.mana>player.maxMana)
        {
            player.mana = player.maxMana;
        }
        monster.mana+=5;
        if (monster.mana>monster.maxMana)
        {
            monster.mana = monster.maxMana;
        }
        if(player.health<1)
        {
            break;
            abort();
        }
    }
    return;
}