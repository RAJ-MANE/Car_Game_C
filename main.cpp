#include <graphics.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>

using namespace std;

const int roadWidth = 300;
const int laneWidth = 100;
const int screenWidth = 500;
const int screenHeight = 600;

int carX = screenWidth / 2 - laneWidth / 2;
int carY = screenHeight - 100;
int obstacleX, obstacleY;
int score = 0;

void drawRoad() {
    setcolor(WHITE);
    line(screenWidth / 2 - roadWidth / 2, 0, screenWidth / 2 - roadWidth / 2, screenHeight);
    line(screenWidth / 2 + roadWidth / 2, 0, screenWidth / 2 + roadWidth / 2, screenHeight);

    for (int i = 0; i < screenHeight; i += 40) {
        line(screenWidth / 2 - 2, i, screenWidth / 2 + 2, i + 20);
    }
}

void drawCar(int x, int y) {
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    rectangle(x, y, x + 40, y + 60);
    floodfill(x + 20, y + 30, RED);
}

void drawObstacle(int x, int y) {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    rectangle(x, y, x + 40, y + 60);
    floodfill(x + 20, y + 30, BLUE);
}

bool checkCollision() {
    return (carX < obstacleX + 40 && carX + 40 > obstacleX && carY < obstacleY + 60 && carY + 60 > obstacleY);
}

void updateGame() {
    obstacleY += 10;

    if (obstacleY > screenHeight) {
        obstacleY = -60;
        obstacleX = screenWidth / 2 - roadWidth / 2 + (rand() % 3) * laneWidth;
        score++;
    }

    if (checkCollision()) {
        setcolor(RED);
        settextstyle(3, 0, 4);
        outtextxy(screenWidth / 4, screenHeight / 2, "Game Over!");

        while (!kbhit()) {
            delay(100);
        }
        getch();
        exit(0);
    }
}

int main() {
    initwindow(screenWidth, screenHeight);
    srand(time(0));

    obstacleX = screenWidth / 2 - roadWidth / 2 + (rand() % 3) * laneWidth;
    obstacleY = -60;

    while (true) {
        cleardevice();
        drawRoad();
        drawCar(carX, carY);
        drawObstacle(obstacleX, obstacleY);

        updateGame();

        if (GetAsyncKeyState(VK_LEFT) && carX > screenWidth / 2 - roadWidth / 2) {
            carX -= laneWidth;
        }
        if (GetAsyncKeyState(VK_RIGHT) && carX < screenWidth / 2 + roadWidth / 2 - 40) {
            carX += laneWidth;
        }

        setcolor(WHITE);
        settextstyle(3, 0, 2);
        char scoreText[10];
        sprintf(scoreText, "Score: %d", score);
        outtextxy(10, 10, scoreText);

        delay(50);
    }

    closegraph();
    return 0;
}
