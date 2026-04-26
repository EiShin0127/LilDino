#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include "Game.h"
#include "Cactus.h"
#include "Bird.h"
using namespace std;

// 初始化遊戲狀態，載入傳入的最高分數
Game::Game(int currentHighScore) : score(0), highScore(currentHighScore), gameOver(false) {
    srand((unsigned)time(0)); // 設定亂數種子以保證每次遊玩的障礙物順序不同

    dino = new Dinosaur(5, GAME_HEIGHT - 1);
    currentObstacle = nullptr;
    spawnObstacle(); // 遊戲一開始先隨機生成一個障礙物

    hideCursor();
    system("cls"); // 清空控制台準備渲染
}

Game::~Game() {
    // 釋放記憶體，避免重新遊玩時導致記憶體被塞爆
    delete dino;
    if (currentObstacle) delete currentObstacle;
}

void Game::spawnObstacle() {
    // 如果原本有障礙物，先將其銷毀
    if (currentObstacle) delete currentObstacle;

    // 隨機決定要出什麼障礙物 (0:正常仙人掌, 1:寬仙人掌, 2:高仙人掌, 3:飛鳥)
    int type = rand() % 4;

    // 透過多型機制，將不同的子類別實體指派給父類別指標
    if (type == 3) {
        currentObstacle = new Bird(GAME_WIDTH - 1, GAME_HEIGHT - 1);
    }
    else {
        currentObstacle = new Cactus(GAME_WIDTH - 1, GAME_HEIGHT - 1, type);
    }
}

void Game::setCursorPosition(int x, int y) {
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}

void Game::hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

void Game::draw() {
    setCursorPosition(0, 0); // 每次繪製都從終端機左上角開始覆蓋

    // 1. 初始化空畫布 (將天空填滿空白，將底部鋪滿地板 '_')
    for (int i = 0; i < GAME_HEIGHT; i++) {
        for (int j = 0; j < GAME_WIDTH; j++) {
            if (i == GAME_HEIGHT - 1) buffer[i][j] = '_';
            else buffer[i][j] = ' ';
        }
    }

    // 2. 讓畫面上的所有物件把自己畫到暫存區上
    dino->draw(buffer);
    if (currentObstacle) currentObstacle->draw(buffer);

    // 3. 一次性印出整個陣列 (這大幅減少了畫面更新時的閃爍感)
    for (int i = 0; i < GAME_HEIGHT; i++) {
        for (int j = 0; j < GAME_WIDTH; j++) {
            cout << buffer[i][j];
        }
        cout << endl;
    }

    // 顯示最高分紀錄與當前分數
    cout << "High Score: " << highScore << "  |  Score: " << score << endl;
    cout << "Press [SPACE] to jump, [SHIFT] to crouch, [Q] to quit." << endl;
}

void Game::input() {
    // 偵測 Shift 鍵 (運用 Windows API 直接抓取非 ASCII 按鍵狀態)
    // 0x8000 代表按鍵目前被按下的位元旗標
    if (GetAsyncKeyState(VK_SHIFT) & 0x8000) {
        dino->crouch(true);
    }
    else {
        dino->crouch(false);
    }

    // 處理標準鍵盤輸入 (跳躍與退出)
    if (_kbhit()) {
        char currentKey = _getch();
        if (currentKey == ' ') {
            dino->jump();
        }
        if (currentKey == 'q' || currentKey == 'Q') {
            gameOver = true;
        }
    }
}

void Game::logic() {
    dino->update();

    if (currentObstacle) {
        currentObstacle->update();

        // 碰撞偵測：將恐龍物件傳給障礙物，交由障礙物內部判斷形狀是否交疊
        if (currentObstacle->checkCollision(dino)) {
            gameOver = true;
        }

        // 成功閃避判定：障礙物離開畫面
        if (currentObstacle->isOffScreen()) {
            score++;
            // 即時更新最高分
            if (score > highScore) {
                highScore = score;
            }
            spawnObstacle(); // 重新生成新障礙物
        }
    }
}

void Game::run() {
    while (!gameOver) {
        draw();
        input();
        logic();
        Sleep(40); // 調整遊戲循環速率
    }
}

int Game::getHighScore() const {
    return highScore;
}

// 處理遊戲結束畫面，等待玩家選擇重玩或退出
bool Game::waitForReplay() {
    setCursorPosition(0, GAME_HEIGHT + 3);
    cout << "===========================================" << endl;
    cout << "  Game Over! Score: " << score << " | High Score: " << highScore << endl;
    cout << "  Press [R] to Replay or [Q] to Quit...    " << endl;
    cout << "===========================================" << endl;

    // 清除可能殘留的按鍵緩衝區
    while (_kbhit()) _getch();

    while (true) {
        if (_kbhit()) {
            char key = _getch();
            if (key == 'r' || key == 'R') return true;  // 回傳 true 進行重玩
            if (key == 'q' || key == 'Q') return false; // 回傳 false 結束程式
        }
        Sleep(50);
    }
}