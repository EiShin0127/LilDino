#ifndef BIRD_H
#define BIRD_H

#include <iostream>
#include "Obstacle.h"
using namespace std;

// 鳥群類別，負責處理空中的障礙物
class Bird : public Obstacle {
private:
    int x, y;

public:
    Bird(int startX, int startY);
    void update() override; // 鳥的移動邏輯 (速度較快)
    void draw(char buffer[GAME_HEIGHT][GAME_WIDTH]) override;
    bool checkCollision(const Dinosaur* dino) override;
    bool isOffScreen() const override;
};

#endif