#pragma once
#include <SFML/Graphics.hpp>
#include <cmath>

enum class BulletType { Normal, Sine, Spiral };

struct Entity {
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool active = true;

    sf::FloatRect getHitbox() const {
        sf::FloatRect bounds = sprite.getGlobalBounds();
        //×Ô»úÅÐ¶¨·¶Î§
        return sf::FloatRect(bounds.left + bounds.width * 0.3f, bounds.top + bounds.height * 0.3f, bounds.width * 0.4f, bounds.height * 0.4f);
    }
};