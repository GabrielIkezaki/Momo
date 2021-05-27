#pragma once
#include "Character.h"
class EnemyBullet :     //The class EnemyBullet inherits from the Class Character, which defines the HP, collision box, position, movement and sprite of a given character
    public Character
{
private:
    bool canDealDamage;

public:
    sf::Vector2f direction;     //Stores the direction (as a 2D Vector) in which the bullet will travel
    Character* player;

    EnemyBullet(sf::Vector2f position, Character* player) :        //The position of the enemybullet is passed as an argument to the Character constructor. The remaining args are predetermined
        Character(1, position, sf::Vector2f(250, 140.5f), "./Sprites/Projectiles/Daisy.png", sf::Vector2f(.6f, .6f), sf::Vector2f(20, 20), sf::Vector2f(-20, -20)) {
        //Character(health, position, sprite origin, sprite texture, sprite scale, collision box offset, collision box size, collision box offset)
        this->player = player;

    }

    void SetDirection(sf::Vector2f direction);      //This function determines the trajectory of the bullet object
    void CheckCollision();
    void Update();
    void ChangePosition(sf::Vector2f newPosition)override;
};

