#include "Player.hpp"
#include "fogpi/fogpi.hpp"
#include "Dice.hpp"
#include "Fight.hpp"

#include "Room.hpp"


void Player::Start()
{
    m_character = 'P';
}

void Player::Update()
{
    if (XP>=XPThreshold)
    {
        printf("You have reached level %d\n",level+1);
        printf("Choose your specialization upgrade!\
            \n\n1: Warrior: upgrades your attack, hp, and physical attack resist\
              \n2: Mage: upgrades spell power and mana\n\n");
        int upgradeChoice;
        XPTotal+=XP;
        XP-=XPThreshold;
        level++;
        do{
        upgradeChoice = request_int("Press 1 or 2 and press Enter");
        } while(upgradeChoice != 1 and upgradeChoice != 2);
        if (upgradeChoice == 1)
        {
            maxHealth +=5;
            attack += 1;
            baseAttackResist += 1;
        }
        if (upgradeChoice == 2)
        {
            maxMana = 30+10*level;
            healingPower+=2;
            fireballDamageBoost+=3;
            ironSkinPower+=2;
        }
        health = maxHealth;
        mana = maxMana;
        XPThreshold += 20*level+(level^2)/3;
        room->Draw();
    }
    
    printf("XP:%d/%d          Level %d\
          \nHealth: %d/%d     Mana: %d/%d\
          \nGold: %d          keys: %d\n",XP,XPThreshold,level,health,maxHealth,mana,maxMana,goldCount,m_keyCount);

    char directionInput;

    do {
        directionInput = request_char("wasd and Enter to move");
    }while (
        directionInput != 'w'
        && directionInput != 'a'
        && directionInput != 's'
        && directionInput != 'd');
        
    Vector2D direction(0.0f);

    switch (directionInput)
    {
    case 'w':
        direction = {0.0f, -1.0f};
        break;
    case 'a':
        direction = {-1.0f, 0.0f};
        break;
    case 's':
        direction = {0.0f, 1.0f};
        break;
    case 'd':
        direction = {1.0f, 0.0f};
        break;
    }

    Vector2D TryPos = m_position + direction;
    //check for a key
    if (room->GetLocation(TryPos) == 'K')
    {
        m_keyCount ++;
        room->ClearLocation(TryPos);
    }

    //check for door
    if (room->GetLocation(TryPos) == 'D')
    {
        if(room->monsterPile<=0)
        {
            room->OpenDoor(TryPos);
        }
        else
        {
            printf("Cannot Leave until all monsters are defeated!\n");
        }
    }
    
    //check for locked door
    if (room->GetLocation(TryPos) == 'L')
    {
        if (m_keyCount <= 0)
        {
            printf("no key\n");
            return;
        }
        else
        {
            m_keyCount--;
            room->SetLocation(TryPos, 'D');
            return;
        }
    }

    if (room->GetLocation(TryPos) == 'C')
    {
        if(m_keyCount>0)
        {
            m_keyCount-=1;
            int number = random_int(1,100);
            if (number >= 99)
                {
                    printf("Jackpot! Found 100 gold pieces!\n");
                    goldCount+=100;
                }
            if (number >=90 && number <99)
                {
                    printf("Found 80 gold pieces!\n");
                    goldCount+=80;
                }
            if (number >=80 && number <90)
                {
                    printf("Found 60 gold pieces!\n");
                    goldCount+=60;
                }
            if (number >=50 && number <80)
                {
                    printf("Found 35 gold pieces!\n");
                    goldCount+=35;
                }
            if (number >=20 && number <50)
                {
                    printf("Found 15 gold pieces!\n");
                    goldCount+=15;
                }
            if (number >=0 && number <20)
                {
                    printf("Found 10 gold pieces!\n");
                    goldCount+=10;
                }
            room->ClearLocation(TryPos);
        }
        else
        {
            printf("Need a key to open!\n");
        }
    }

    if (room->GetLocation(TryPos) == 'H')
    {
        health += 10;
        if(health>maxHealth)
            health = maxHealth;
        room->ClearLocation(TryPos);
    }

    if (room->GetLocation(TryPos) == 'M')
    {
        //Fight
        room->ClearLocation(TryPos);
        FightOrc(*this,*room);
        
    }
    if (room->GetLocation(TryPos) == 'm')
    {
        //Fight
        room->ClearLocation(TryPos);
        FightShaman(*this,*room);
        
    }
    if (room->GetLocation(TryPos)=='s')
    {
        //Shop Open
        
        int shopChoice;
        while(true){
            do
            {
                printf("\nGold:%d\nWelcome to the shop! Please make a selection!\
                    \n\n1: Armor Upgrade 100g: Increases physical resist by 1\
                    \n2: Mana Upgrade 110g: Increases mana by 10\
                    \n3: Health Upgrade 120g: Increases health by 5\
                    \n4: Magic Protection 150g: Reduces magical damage taken by 3\
                    \n5: Leave\n\n",goldCount);
                shopChoice = request_int("Enter a number and press enter");
            }while(shopChoice!=1 &&
                shopChoice!=2 &&
                shopChoice!=3 &&
                shopChoice!=4 &&
                shopChoice!=5);
            switch(shopChoice)
            {
                case 1:
                {
                    if(goldCount>100)
                    {
                        printf("Thank you for your purchase!\n");
                        goldCount-=100;
                        baseAttackResist+=1;
                        printf("Your physical attack resistance increased!\n");
                    }
                    else
                    {
                        printf("Sorry, not enough gold!\n");
                    }
                    break;
                }
                case 2:
                {
                    if(goldCount>110)
                    {
                        printf("Thank you for your purchase!\n");
                        goldCount-=110;
                        maxMana+=10;
                        printf("Your max mana has increased!\n");
                    }
                    else
                    {
                        printf("Sorry, not enough gold!\n");
                    }
                    break;
                }
                case 3:
                {
                    if(goldCount>120)
                    {
                        printf("Thank you for your purchase!\n");
                        goldCount-=120;
                        maxHealth+=5;
                        printf("Your max health has increased!\n");
                    }
                    else
                    {
                        printf("Sorry, not enough gold!\n");
                    }
                    break;
                }
                case 4:
                {
                    if(goldCount>150)
                    {
                        printf("Thank you for your purchase!\n");
                        goldCount-=150;
                        magicResist+=3;
                        printf("Your magic resistance increased!\n");
                    }
                    else
                    {
                        printf("Sorry, not enough gold!\n");
                    }
                    break;
                }
                case 5:
                {
                    printf("Thank you for shopping!\n");
                    break;
                }
                break;
            }
            break;
        }

    }

    if (room->GetLocation(TryPos) == ' ')
        m_position = TryPos;
    
    if (mana<maxMana)
        mana+=maxMana/10;
    if (mana>maxMana)
        mana = maxMana;

}