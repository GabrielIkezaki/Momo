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
            Character(1, position, sf::Vector2f(250, 140.5f), "./Sprites/Projectiles/Daisy.png", sf::Vector2f(.6f, .6f), sf::Vector2f(70, 70), sf::Vector2f(0, 0)) {
            this->direction = direction;
        }
    };
    

private:


    int totalCircumferences = 4;
    int currentCircumference;
    int numberOfBullets = 12;

    bool isEntering;
    Character* boss;

    sf::Vector2f offset;

    void GenerateCircumference();

public:

    sf::Clock clock; 
    sf::Time timeBetweenCircumference;
    float circumferenceCooldown = 4;
    GameScene* scene;

    std::vector<DaisyBullet*> daisyBullets;

    bool wakeUp = false;

    Bloom(Character* boss, GameScene* scene, sf::Vector2f offset);

    Animation bloomEntry = Animation(&characterSprite.objectTexture, sf::Vector2u(3, 2), 0.2f, false);
    void Update();
    void DrawDaisy();

};


class Boss :
    public Character
{

private:
    sf::Clock clock, blinkClock, patternClock;
    sf::Time timer, blinkTimer, patternCooldown;
    sf::Color blinkColor = sf::Color(255,0,0,230);
    GameScene* scene; 


    enum class Pattern
    {
        BLOOM
    };

    Pattern currentPattern;

    bool canAttack = true;
    float xVelocity;

    void Start();
public:

    std::vector<Bloom> bloomObjects;


    Boss(GameScene* window);
    void Update();
    void ArcMovement();

    void TakeDamage(int tempDamage)override;

    sf::Vector2f velocity;

    float ArcYVelocity();
    float ArcXVelocity();

    void BloomPattern();

};

