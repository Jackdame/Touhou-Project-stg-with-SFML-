#include "Bullet.h"

Bullet::Bullet(sf::Texture& tex, sf::Vector2f pos, sf::Vector2f vel, bool enemy, BulletType t) {
    sprite.scale(0.6f, 0.6f);
    sprite.setTexture(tex);
    sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);
    sprite.setPosition(pos);
    velocity = vel;
    isEnemyBullet = enemy;
    type = t;
}

void Bullet::update(float dt) {
    timer += dt;
    if (type == BulletType::Normal) {
        sprite.move(velocity * dt);
    }
    else if (type == BulletType::Spiral) {
        float speed = 150.f;
        float angle = baseAngle + timer * 2.0f;
        sprite.move(std::cos(angle) * speed * dt, std::sin(angle) * speed * dt);
    }

    float rot = std::atan2(velocity.y, velocity.x) * 180.f / 3.14159f;
    sprite.setRotation(rot + 90.f);

    if (sprite.getPosition().y < -50 || sprite.getPosition().y > 850 ||
        sprite.getPosition().x < -50 || sprite.getPosition().x > 600) active = false;
}