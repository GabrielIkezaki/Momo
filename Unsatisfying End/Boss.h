#pragma once
#include "Character.h"

class Boss :
    public Character
{

private:
    sf::Clock clock, blinkClock;
    sf::Time timer, blinkTimer;
    sf::Color blinkColor = sf::Color(255,0,0,230);
    float xVelocity;
public:
    Boss();
    void Update();
    void ArcMovement();

    void TakeDamage(int tempDamage)override;

    float ArcYVelocity();
    float ArcXVelocity();
};

