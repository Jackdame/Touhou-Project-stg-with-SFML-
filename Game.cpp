#include "Game.h"
#include <iostream>

Game::Game() : window(sf::VideoMode(800, 780), "Do you want power?") {
    tP.loadFromFile("player.png");
    tE.loadFromFile("enemy.png");
    tBP.loadFromFile("bullet_player.png");
    tBE.loadFromFile("bullet_enemy.png");
    tBg.loadFromFile("background.png");
    bgm.openFromFile("bgm.mp3");
    shootBuffer.loadFromFile("graze.wav");
    shootSound.setBuffer(shootBuffer);
    shootSound.setVolume(30);
    explosionBuffer.loadFromFile("damage00.wav");
    explosionSound.setBuffer(explosionBuffer);
    timeoutbuffer.loadFromFile("timeout.wav");
    timeout.setBuffer(timeoutbuffer);
    mBg.loadFromFile("crino.png");
    sBg.setTexture(mBg);
    gBg.setTexture(tBg);
    font.loadFromFile("AdobeArabic-Bold.otf");
    sBg.setPosition(0.f, 300.f);
    for (int i = 0; i < 2; i++) {
        mText[i].setFont(font);
        mText[i].setString(i == 0 ? "START" : "QUIT");
        mText[i].setPosition(380, 300 + i * 60);
    }
    cText.setFont(font); cText.setString("Sure? (Enter/Esc)"); cText.setPosition(270, 300);
    lText.setFont(font); lText.setString("You lose.Please enter then back in menu."); lText.setPosition(200, 300);
    overlay.setSize({ 1000,780 }); overlay.setFillColor({ 0,0,0,180 });
    player.init(tP);
    sidebarBg.setSize(sf::Vector2f(200.f, 780.f)); 
    sidebarBg.setPosition(600.f, 0.f);            
    sidebarBg.setFillColor(sf::Color(30, 30, 30)); 

    // Score
    scoreText.setFont(font);
    scoreText.setCharacterSize(36);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(600.f, 100.f);

    // HP 
    hpText.setFont(font);
    hpText.setCharacterSize(36);
    hpText.setFillColor(sf::Color::Red);
    hpText.setPosition(600.f, 200.f);
    bgm.setLoop(true);  
    bgm.setVolume(50);  
    bgm.play();         
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        process();
        update(clock.restart().asSeconds());
        render();
    }
}

void Game::process() {
    sf::Event e;
    while (window.pollEvent(e)) {
        if (e.type == sf::Event::Closed) window.close();

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorldPos = window.mapPixelToCoords(mousePos);

        if (state == State::Menu) {

            for (int i = 0; i < 2; i++) {
                if (mText[i].getGlobalBounds().contains(mouseWorldPos)) {
                    mIdx = i; 
                }
            }
            if (e.type == sf::Event::MouseButtonPressed && e.mouseButton.button == sf::Mouse::Left) {
                if (mText[0].getGlobalBounds().contains(mouseWorldPos)) {
                    state = State::Playing;
                    enemies.clear();
                    bullets.clear();
                    player.hp = 10;
                }
                else if (mText[1].getGlobalBounds().contains(mouseWorldPos)) {
                    window.close();
                }
            }
        }
        else if (state == State::Playing) {
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape) state = State::ConfirmExit;
        }
        else if (state == State::ConfirmExit) {
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Enter) { state = State::Menu; enemies.clear(); bullets.clear(); player.hp = 10; }
                if (e.key.code == sf::Keyboard::Escape) state = State::Playing;
            }
        }
        else if (state == State::Lose) {
            if (e.type == sf::Event::KeyPressed) {
                if (e.key.code == sf::Keyboard::Enter) { state = State::Menu; enemies.clear(); bullets.clear(); player.hp = 10; }
            }
        }
    }
}

void Game::update(float dt) {
    if (state != State::Playing) return;
    player.update(dt);
    player.shoot(bullets, tBP);
    spawnT += dt;
    if (spawnT > 2.0f) { enemies.emplace_back(tE, sf::Vector2f(rand() % 500 + 50, -50)); spawnT = 0; }
    for (auto& en : enemies) {
        en.update(dt, bullets, tBE, player.sprite.getPosition()); 
    }
    for (auto& b : bullets) b.update(dt);
    checkCollisions();
    enemies.erase(std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& en) {return !en.active; }), enemies.end());
    bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {return !b.active; }), bullets.end());
    
}

void Game::checkCollisions() {
    for (auto& b : bullets) {
        if (!b.active) continue;
        if (!b.isEnemyBullet) { 
            for (auto& en : enemies) {
                if (en.active && b.getHitbox().intersects(en.getHitbox())) {
                    b.active = false;
                    shootSound.play();
                    en.hp--;
                    score += 10; 
                    if (en.hp <= 0) {
                        en.active = false;
                        explosionSound.play();
                        score += 500; 
                    }
                }
            }
        }
        else {
            if (b.getHitbox().intersects(player.getHitbox())) {
                b.active = false; player.hp--;
                timeout.play();
            }
        }
    }
    scoreText.setString("Score:" + std::to_string(score));
    hpText.setString("HP:" + std::to_string(player.hp));
}

void Game::render() {
    window.clear();
    if (state == State::Menu) {
        window.draw(sBg);
        for (int i = 0; i < 2; i++) { 
            mText[i].setFillColor(mIdx == i ? sf::Color::Red : sf::Color::White); window.draw(mText[i]); 
        }
    }
    else {
        window.draw(gBg);
        window.draw(sidebarBg);
        window.draw(scoreText);
        window.draw(hpText);
        for (auto& b : bullets) window.draw(b.sprite);
        for (auto& en : enemies) window.draw(en.sprite);
        if (player.hp > 0) window.draw(player.sprite);
        else {
            window.draw(overlay);
            window.draw(lText);
            state = State::Lose;
        }
        if (state == State::ConfirmExit) { window.draw(overlay); window.draw(cText); }
    }
    window.display();
}