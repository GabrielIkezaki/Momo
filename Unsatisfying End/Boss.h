#pragma once
#include "Character.h"
#include "Animation.h"
#include "GameScene.h"

#include <cmath>
class Bloom :
    public Character
{

    
    class DaisyBullet :
        public Character {

    public:

        sf::Vector2f direction;

        
        DaisyBullet(sf::Vector2f position, sf::Vector2f direction) :
            Character(1, position, "./Sprites/Projectiles/Daisy.png", sf::Vector2f(.7f, .7f), sf::Vector2f(70, 70), sf::Vector2f(170, 130)) {
            this->direction = direction;
        }
    };
    

private:
    bool isEntering;
    Character* boss;

    sf::Vector2f offset;

    void GenerateCircumference();

public:

    sf::Clock clock; 
    sf::Time timeBetweenCircumference;

    GameScene* scene;

    std::vector<DaisyBullet*> daisyBullets;

    Bloom(Character* boss, GameScene* scene, sf::Vector2f offset);

    Animation bloomEntry = Animation(&characterSprite.objectTexture, sf::Vector2u(3, 2), 0.2f, false);
    void Update();

};


class Boss :
    public Character
{

private:
    sf::Clock clock, blinkClock, patternClock;
    sf::Time timer, blinkTimer, patternCooldown;
    sf::Color blinkColor = sf::Color(255,0,0,230);
    GameScene* scene; 

    std::vector<Bloom> bloomObjects;

    enum class Pattern
    {
        BLOOM
    };

    Pattern currentPattern;

    bool canAttack = true;
    float xVelocity;
public:

    Boss(GameScene* window);
    void Update();
    void ArcMovement();

    void TakeDamage(int tempDamage)override;

    sf::Vector2f velocity;

    float ArcYVelocity();
    float ArcXVelocity();

    void BloomPattern();

};

