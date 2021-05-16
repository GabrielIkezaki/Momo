#pragma once
#include "Character.h"
#include "Animation.h"
#include "GameScene.h"
#include "EnemyBullet.h"
#include <cmath>
class Bloom :
    public Character
{
private:

    bool isEntering;
    std::vector<EnemyBullet*>* bossBullets;
    sf::Vector2f offset;

    Character* boss;

public:
    bool wakeUp = false;

    Bloom(Character* boss, sf::Vector2f offset);

    Animation bloomEntry = Animation(&characterSprite.objectTexture, sf::Vector2u(3, 2), 0.2f, false);
    void Update();
    void DrawDaisy();


};


class Boss :
    public Character
{

private:
    sf::Clock clock, blinkClock, patternClock, bulletClock;
    sf::Time timer, blinkTimer, patternCooldown, timeBetweenBullets;
    sf::Color blinkColor = sf::Color(255,0,0,230);
    GameScene* scene; 

    int totalCircumferences = 4;
    int currentCircumference = 0;
    int numberOfBullets = 12;

    enum class Pattern
    {
        NONE,
        BLOOM
    };

    Pattern currentPattern;

    bool canAttack = true;
    float xVelocity;

    void Start();
public:

    std::vector<Bloom> bloomObjects;
    std::vector<EnemyBullet*> bossBullets;
    int totalBullets = 60;

    Boss(GameScene* window);
    void Update();
    void ArcMovement();

    void TakeDamage(int tempDamage)override;

    sf::Vector2f velocity;

    float ArcYVelocity();
    float ArcXVelocity();


    void DrawBullets();
    void BloomPattern();

};

