#pragma once
#include "Bullet.h"
#include <vector>

class Player : public Entity {
public:
    float speed = 400.f;
    float shootTimer = 0.f;
    int hp = 10;

    void init(sf::Texture& tex);
    void update(float dt);
    void shoot(std::vector<Bullet>& bullets, sf::Texture& tex);
};