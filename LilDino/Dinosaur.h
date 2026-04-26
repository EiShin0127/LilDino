#ifndef DINOSAUR_H
#define DINOSAUR_H

#include <iostream>
#include "GameObject.h"
using namespace std;

// 恐龍類別，繼承自 GameObject
class Dinosaur : public GameObject {
private:
    int x;          // 恐龍的 X 
    int baseY;      // 記錄地面的 Y 座標基準
    int jumpHeight; // 目前跳躍高度
    bool isJumping; // 是否正在往上跳
    bool isFalling; // 是否正在往下掉
    bool isCrouching;// 是否正在蹲下

public:
    // 初始化恐龍的座標與所有物理狀態
    Dinosaur(int startX, int startY);

    void jump();                // 觸發跳躍動作
    void crouch(bool state);    // 設定蹲下狀態

    void update() override;     // 處理跳躍與掉落的物理邏輯
    void draw(char buffer[GAME_HEIGHT][GAME_WIDTH]) override; // 將恐龍繪製到畫布上

    // 給障礙物檢查是否撞到恐龍的特定座標
    bool collidesWith(int checkX, int checkY) const;
};

#endif