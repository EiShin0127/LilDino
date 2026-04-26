#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <iostream>
using namespace std;

// 遊戲畫面常數定義 
const int GAME_WIDTH = 50;
const int GAME_HEIGHT = 10;

// 遊戲物件的基礎類別 
class GameObject {
public:
    // 確保衍生類別被正確釋放 
    virtual ~GameObject() {}

    // 強迫所有子類別都必須實作自己的更新邏輯
    virtual void update() = 0;

    // 將物件畫在暫存的 2D 陣列畫布上，避免畫面閃爍
    virtual void draw(char buffer[GAME_HEIGHT][GAME_WIDTH]) = 0;
};

#endif