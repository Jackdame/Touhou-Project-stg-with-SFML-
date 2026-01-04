#pragma once
#include "Player.h"
#include "Enemy.h"
#include <SFML/Audio.hpp>

enum class State { Menu, Playing, ConfirmExit, Lose };

class Game {
    long long score = 0;
    long long highScore = 0;
    sf::Text scoreText;
    sf::Text hpText;
    sf::RectangleShape sidebarBg; 
    sf::RenderWindow window;
    sf::Texture tP, tE, tBP, tBE, tBg, mBg;
    sf::Sprite sBg,gBg;
    sf::Font font;
    sf::Text mText[2], cText, lText;
    sf::RectangleShape overlay;
    sf::Music bgm;
    sf::SoundBuffer shootBuffer;
    sf::Sound shootSound;
    sf::SoundBuffer explosionBuffer;
    sf::Sound explosionSound;
    sf::SoundBuffer timeoutbuffer;
    sf::Sound timeout;
    State state = State::Menu;
    int mIdx = 0;
    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    float spawnT = 0;

public:
    Game();
    void run();
private:
    void process();
    void update(float dt);
    void render();
    void checkCollisions();
};