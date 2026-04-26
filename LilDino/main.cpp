#include <iostream>
#include "Game.h"
using namespace std;

int main() {
    int sessionHighScore = 0; // 在 main 函式中保留歷史最高分
    bool playAgain = true;

    // 遊戲主迴圈：支援無限次重新遊玩
    while (playAgain) {
        // 每次遊玩都會建立一個全新的 Game 物件 (狀態重置)
        Game game(sessionHighScore);

        game.run(); // 執行該局遊戲

        // 遊戲結束後，從剛結束的物件中取出更新後的最高分
        sessionHighScore = game.getHighScore();

        // 詢問玩家是否要再玩一次
        playAgain = game.waitForReplay();
    }

    system("cls");
    cout << "Thanks for playing! See you next time." << endl;

    return 0;
}