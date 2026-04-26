#ifndef GAME_H
#define GAME_H

#include <iostream>
#include "Dinosaur.h"
#include "Obstacle.h"
using namespace std;

// 遊戲管理類別 (封裝所有遊戲流程)
class Game {
private:
    bool gameOver;           // 遊戲結束標記
    int score;               // 該局遊戲分數
    int highScore;           // 歷史最高分數紀錄
    char buffer[GAME_HEIGHT][GAME_WIDTH]; // 2D 畫面暫存區 (Double Buffering 概念)

    Dinosaur* dino;          // 恐龍物件指標
    Obstacle* currentObstacle; // 當前畫面上的唯一障礙物 (利用多型儲存仙人掌或鳥)

    void setCursorPosition(int x, int y); // 游標控制
    void hideCursor();                    // 隱藏游標
    void spawnObstacle();                 // 隨機生成新的障礙物

    // 遊戲迴圈的三大核心步驟
    void draw();
    void input();
    void logic();

public:
    // 建構子現在需要接收「最高分數」以便在畫面中顯示與更新
    Game(int currentHighScore);
    ~Game();

    void run(); // 執行單局遊戲

    int getHighScore() const;  // 取得更新後的最高分
    bool waitForReplay();      // 遊戲結束時詢問是否重新遊玩
};

#endif