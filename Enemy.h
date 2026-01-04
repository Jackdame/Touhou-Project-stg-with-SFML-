#pragma once
#include "Bullet.h"

class Enemy : public Entity {
public:
    float shootTimer = 0.f;
    int hp = 10;
    float angleOffset = 0.f;

    Enemy(sf::Texture& tex, sf::Vector2f pos);
    void update(float dt, std::vector<Bullet>& bullets, sf::Texture& bTex, sf::Vector2f playerPos);
};

