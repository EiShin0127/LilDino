#include <iostream>
#include "Dinosaur.h"
using namespace std;

// 建構子：初始化跳躍與蹲下狀態，並設定初始座標
Dinosaur::Dinosaur(int startX, int startY)
    : x(startX), baseY(startY), jumpHeight(0), isJumping(false), isFalling(false), isCrouching(false) {
}

void Dinosaur::jump() {
    // 只有在地面上且沒有蹲下時才能跳躍
    if (jumpHeight == 0 && !isFalling && !isCrouching) {
        isJumping = true;
    }
}

void Dinosaur::crouch(bool state) {
    // 只有在地面上時才能改變蹲下狀態 (防止空中蹲下產生不合理的物理現象)
    if (jumpHeight == 0) {
        isCrouching = state;
    }
    else {
        isCrouching = false; // 在空中強制解除蹲下
    }
}

// 實作恐龍專屬的物理邏輯 (跳躍軌跡計算)
void Dinosaur::update() {
    if (isJumping) {
        jumpHeight++;
        if (jumpHeight >= 4) { // 達到最高點，開始掉落
            isJumping = false;
            isFalling = true;
        }
    }
    else if (isFalling) {
        jumpHeight--;
        if (jumpHeight <= 0) { // 回到地面
            jumpHeight = 0;
            isFalling = false;
        }
    }
}

void Dinosaur::draw(char buffer[GAME_HEIGHT][GAME_WIDTH]) {
    int currentY = baseY - jumpHeight; // 計算當前實際的 Y 座標

    // 畫出下半身 (不管站著還是蹲著都會有這部分)
    buffer[currentY][x] = 'T';

    // 如果沒有蹲下，就額外畫出上半身 (構成身高 2 單位的恐龍)
    if (!isCrouching) {
        buffer[currentY - 1][x] = 'T';
    }
}

// 檢查指定的座標 (checkX, checkY) 是否與恐龍的身體重疊
bool Dinosaur::collidesWith(int checkX, int checkY) const {
    int currentY = baseY - jumpHeight;

    // 檢查下半身是否發生碰撞
    if (checkX == x && checkY == currentY) return true;

    // 如果沒蹲下，也要檢查上半身是否發生碰撞 (用來被飛鳥撞擊)
    if (!isCrouching && checkX == x && checkY == currentY - 1) return true;

    return false;
}