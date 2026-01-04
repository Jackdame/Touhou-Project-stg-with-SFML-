#include "Enemy.h"

Enemy::Enemy(sf::Texture& tex, sf::Vector2f pos) {
    sprite.setTexture(tex);
    sprite.scale(0.8f, 0.8f);
    sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);
    sprite.setPosition(pos);
    int poa = rand() % 2;
    if (poa == 0) {
        velocity = sf::Vector2f(-10, 60);
    }
    else {
        velocity = sf::Vector2f(10, 60);
    }
}

void Enemy::update(float dt, std::vector<Bullet>& bullets, sf::Texture& bTex, sf::Vector2f playerPos) {
    sprite.move(velocity * dt);
    shootTimer -= dt;

    if (shootTimer <= 0) {
        int pattern = rand() % 3;
        if (pattern == 0) {//ÂÝÐý
            for (int i = 0; i < 12; i++) {
                float a = (i * 30.f + angleOffset) * 3.14159f / 180.f;

                float bulletSpeed = 150.f;
                sf::Vector2f vel(std::cos(a) * bulletSpeed, std::sin(a) * bulletSpeed);
                bullets.emplace_back(bTex, sprite.getPosition(), vel, true, BulletType::Normal);
            }
            angleOffset += 30.f;
            shootTimer = 1.2f;
        }
        else if (pattern == 1) {
            //Ö±Éä
            sf::Vector2f dir = playerPos - sprite.getPosition();
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len != 0) {
                sf::Vector2f unitDir = dir / len;
                for (int i = -1; i <= 1; i++) {
                    float spread = i * 0.25f; 
                    sf::Vector2f finalVel(
                        (unitDir.x * cos(spread) - unitDir.y * sin(spread)) * 350.f,
                        (unitDir.x * sin(spread) + unitDir.y * cos(spread)) * 350.f
                    );
                    bullets.emplace_back(bTex, sprite.getPosition(), finalVel, true, BulletType::Normal);
                }
            }
            shootTimer = 1.0f;
        }
        else {
            //À©É¢
            for (int i = 0; i < 10; i++) {
                float a = (i * 36.f) * 3.14159f / 180.f;
                sf::Vector2f vel(std::cos(a) * 200.f, std::sin(a) * 200.f);
                bullets.emplace_back(bTex, sprite.getPosition(), vel, true, BulletType::Normal);
            }
            shootTimer = 1.2f;
        }
    }

    if (sprite.getPosition().y > 850) active = false;
    if (sprite.getPosition().x > 600) active = false;
}