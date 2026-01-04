#pragma once
#include "Entity.h"

class Bullet : public Entity {
public:
    bool isEnemyBullet;
    BulletType type;
    float timer = 0.f;
    float baseAngle = 0.f;

    Bullet(sf::Texture& tex, sf::Vector2f pos, sf::Vector2f vel, bool enemy, BulletType t = BulletType::Normal);
    void update(float dt);
};