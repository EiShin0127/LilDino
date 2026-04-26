#ifndef CACTUS_H
#define CACTUS_H

#include <iostream>
#include "Obstacle.h"
using namespace std;

// 仙人掌類別，負責處理三種不同形狀的地面障礙物
class Cactus : public Obstacle {
private:
    int x, y; // 仙人掌的基準點座標 (左下角)
    int type; // 仙人掌類型 (0: 正常 1x1, 1: 寬型 3x1, 2: 高型 1x2)

public:
    // 建構子：傳入初始座標與指定的仙人掌類型
    Cactus(int startX, int startY, int cactusType);

    void update() override; // 處理向左移動
    void draw(char buffer[GAME_HEIGHT][GAME_WIDTH]) override; // 將對應形狀畫入畫布
    bool checkCollision(const Dinosaur* dino) override; // 針對不同形狀進行碰撞檢測
    bool isOffScreen() const override; // 判斷整株仙人掌是否完全離開畫面
};

#endif