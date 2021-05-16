#pragma once
#include "Character.h"
class EnemyBullet :
    public Character
{

public:
    sf::Vector2f direction;

    EnemyBullet(sf::Vector2f position) :
        Character(1, position, sf::Vector2f(250, 140.5f), "./Sprites/Projectiles/Daisy.png", sf::Vector2f(.6f, .6f), sf::Vector2f(70, 70), sf::Vector2f(0, 0)) {
        this->direction = direction;
    }

    void SetDirection(sf::Vector2f direction);
};

