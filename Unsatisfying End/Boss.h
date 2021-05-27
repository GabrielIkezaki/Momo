#pragma once
#include "Character.h"
#include "Animation.h"
#include "GameScene.h"
#include "EnemyBullet.h"
#include <cmath>
class Bloom :
    public Character
{

protected:
    Character* boss;
    sf::Vector2f offset;

private:

    bool isEntering;
    std::vector<EnemyBullet*>* bossBullets;

public:
    bool wakeUp = false;

    Bloom(std::string textureAddress, Character* boss, sf::Vector2f scale, sf::Vector2f offset, sf::Vector2f origin);

    Animation bloomEntry = Animation(&characterSprite.objectTexture, sf::Vector2u(3, 2), 0.2f, false);
    virtual void Update();

};

class SpiralWindow :
    public Bloom {
public:
    SpiralWindow(std::string textureAddress, Character* boss, sf::Vector2f scale, sf::Vector2f offset) :Bloom( textureAddress, boss, scale, offset, sf::Vector2f(351,434)) {
        bloomEntry = Animation(&characterSprite.objectTexture, sf::Vector2u(2, 2), 0.2f, false);
    }
};

class Boss :
    public Character
{

private:
    sf::Clock clock, blinkClock, patternClock, bulletClock;
    sf::Time timer, blinkTimer, patternCooldown, timeBetweenBullets;
    sf::Color blinkColor = sf::Color(255,0,0,230);
    GameScene* scene; 

    Character* player;


    int totalCircumferences = 4;
    int currentCircumference = 0;
    int numberOfBullets = 20;
    float minTimeBetweenBullets = 0.8f;

    int spiralIndex = 0;

    void RedefineBullets(int numberOfBullets, sf::Vector2f scale);
    void UpdateBloomPattern();
    void UpdateSpiralPattern();


    enum class Pattern
    {
        NONE,
        BLOOM,
        SPIRAL
    };

    Pattern currentPattern;

    bool canAttack = true;
    float xVelocity;

public:

    std::vector<Bloom> bloomObjects;
    std::vector<EnemyBullet*> bossBullets;
    int totalBullets = 90;


    Boss(GameScene* window, Character* player);
    void Start();
    void Update();


    void ArcMovement();

    void TakeDamage(int tempDamage)override;

    sf::Vector2f velocity;

    float ArcYVelocity();
    float ArcXVelocity();

    void BlinkOnHit();

    void BeginPattern(sf::Vector2i indexRange);

    void DrawBullets();
    void GenerateCircumference();




};

