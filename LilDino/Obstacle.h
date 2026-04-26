#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <iostream>
#include "GameObject.h"
#include "Dinosaur.h"
using namespace std;

// 障礙物基礎類別 (抽象類別，仙人掌與鳥都繼承它)
class Obstacle : public GameObject {
public:
    // 純虛擬函式：每個障礙物自己決定怎麼跟恐龍碰撞 (例如寬仙人掌要檢查三個點)
    virtual bool checkCollision(const Dinosaur* dino) = 0;

    // 判斷是否已經移出畫面 (用於加分與觸發下一個障礙物生成)
    virtual bool isOffScreen() const = 0;
};

#endif