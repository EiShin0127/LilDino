#include <iostream>
#include "Bird.h"
using namespace std;

// 建構子：鳥群固定飛在 y-1 的高度 (即比地面高 1 單位，恐龍必須蹲下才能躲避)
Bird::Bird(int startX, int groundY) : x(startX), y(groundY - 1) {}

void Bird::update() {
    x -= 2; // 鳥飛得比仙人掌快，每回合向左移動 2 單位，增加難度！
}

void Bird::draw(char buffer[GAME_HEIGHT][GAME_WIDTH]) {
    if (x >= 0 && x < GAME_WIDTH) {
        buffer[y][x] = 'V'; // 用字元 'V' 來代表展開翅膀的鳥
    }
}

bool Bird::checkCollision(const Dinosaur* dino) {
    // 鳥只有一格大小，直接檢測即可
    return dino->collidesWith(x, y);
}

bool Bird::isOffScreen() const {
    return (x < 0); // 飛出左側畫面即視為閃避成功
}