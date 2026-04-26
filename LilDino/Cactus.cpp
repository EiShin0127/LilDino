#include <iostream>
#include "Cactus.h"
using namespace std;

Cactus::Cactus(int startX, int startY, int cactusType) : x(startX), y(startY), type(cactusType) {}

void Cactus::update() {
    x--; // 仙人掌每回合固定向左移動 1 單位
}

void Cactus::draw(char buffer[GAME_HEIGHT][GAME_WIDTH]) {
    // 確保只繪製在畫面範圍內的點，避免陣列越界導致程式崩潰
    if (x >= 0 && x < GAME_WIDTH) {
        buffer[y][x] = 'X'; // 繪製基礎底部

        // 根據類型延伸繪製其他部分
        if (type == 1) { // 寬型 (向右延伸 2 單位)
            if (x + 1 < GAME_WIDTH) buffer[y][x + 1] = 'X';
            if (x + 2 < GAME_WIDTH) buffer[y][x + 2] = 'X';
        }
        else if (type == 2) { // 高型 (向上延伸 1 單位)
            buffer[y - 1][x] = 'X';
        }
    }
}

// 根據不同的仙人掌形狀，向恐龍發送多個碰撞檢測請求
bool Cactus::checkCollision(const Dinosaur* dino) {
    // 檢查基準點是否碰撞
    if (dino->collidesWith(x, y)) return true;

    // 檢查延伸的部分是否碰撞
    if (type == 1) {
        // 寬型需要檢查後方兩格
        if (dino->collidesWith(x + 1, y) || dino->collidesWith(x + 2, y)) return true;
    }
    else if (type == 2) {
        // 高型需要檢查上方一格
        if (dino->collidesWith(x, y - 1)) return true;
    }
    return false; // 都沒撞到則回傳安全
}

bool Cactus::isOffScreen() const {
    if (type == 1) return (x + 2 < 0); // 寬型必須等最右邊那一格也離開畫面才算數
    return (x < 0); // 一般與高型只要基準點離開即可
}