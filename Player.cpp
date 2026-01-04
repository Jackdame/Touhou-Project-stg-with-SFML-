#include "Player.h"

void Player::init(sf::Texture& tex) {
    sprite.setTexture(tex);
    sprite.scale(0.6f, 0.6f);
    sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);
    sprite.setPosition(300, 700);
}

void Player::update(float dt) {
    float curSpeed = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? speed * 0.4f : speed;
    sf::Vector2f move(0, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) move.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) move.x += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) move.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) move.y += 1;

    if (move.x != 0 || move.y != 0) {
        float len = std::sqrt(move.x * move.x + move.y * move.y);
        sprite.move((move / len) * curSpeed * dt);
    }
    sf::Vector2f pos = sprite.getPosition();
    if (pos.x < 20) sprite.setPosition(20, pos.y);
    if (pos.x > 580) sprite.setPosition(580, pos.y);
    if (pos.y < 20) sprite.setPosition(pos.x, 20);
    if (pos.y > 780) sprite.setPosition(pos.x, 780);
    if (shootTimer > 0) shootTimer -= dt;
}

void Player::shoot(std::vector<Bullet>& bullets, sf::Texture& bulletTex) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z) && shootTimer <= 0) {

        bool isFocus = sf::Keyboard::isKeyPressed(sf::Keyboard::LShift);

        if (isFocus) {
            //רעģʽ
            bullets.emplace_back(bulletTex, sf::Vector2f(sprite.getPosition().x - 15, sprite.getPosition().y), sf::Vector2f(0, -700), false);
            bullets.emplace_back(bulletTex, sf::Vector2f(sprite.getPosition().x + 15, sprite.getPosition().y), sf::Vector2f(0, -700), false);
            bullets.emplace_back(bulletTex, sf::Vector2f(sprite.getPosition().x - 15, sprite.getPosition().y), sf::Vector2f(0, -700), false);
            bullets.emplace_back(bulletTex, sf::Vector2f(sprite.getPosition().x + 15, sprite.getPosition().y), sf::Vector2f(0, -700), false);
            shootTimer = 0.1f;
        }
        else {
            bullets.emplace_back(bulletTex, sf::Vector2f(sprite.getPosition().x - 15, sprite.getPosition().y), sf::Vector2f(-20, -700), false);
            bullets.emplace_back(bulletTex, sf::Vector2f(sprite.getPosition().x + 15, sprite.getPosition().y), sf::Vector2f(20, -700), false);
            bullets.emplace_back(bulletTex, sf::Vector2f(sprite.getPosition().x - 45, sprite.getPosition().y), sf::Vector2f(-10, -700), false);
            bullets.emplace_back(bulletTex, sf::Vector2f(sprite.getPosition().x + 45, sprite.getPosition().y), sf::Vector2f(10, -700), false);
            shootTimer = 0.05f;
        }
    }
}