#include <iostream>
#include <fstream>
#include <Windows.h>
#include <conio.h>
#include <ctime>
#include "Engine.h"
#include "Entity.h"
#include <sysinfoapi.h>

using namespace std;

int main()
{
    CONSOLE_CURSOR_INFO test;
    test.bVisible = false;
    test.dwSize = 10;
    int zxc = 0, asd = 0;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &test);
    system("chcp 1251");
    srand(time(NULL));
    bool gameOver = 0;
    Engine qwe;
    qwe.OpenMap();
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(0), (short)(0) });
    for (int y = 0; y < qwe.Map.size(); y++) {
        for (int x = 0; x < qwe.Map[0].size(); x++)
            cout << qwe.Map[y][x];
        cout << endl;
    }
    /*SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(0), (short)(25) });
    cout << qwe.entities.size();*/
    while (!gameOver) {
        SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &test);
        if (GetAsyncKeyState(0x57)) {
            qwe.MoveObject(qwe.entities[0], 0, -1);
            qwe.entities[0].direction = 4;
        }
        else if (GetAsyncKeyState(0x41)) {
            qwe.MoveObject(qwe.entities[0], -1, 0);
            qwe.entities[0].direction = 3;
        }
        else if (GetAsyncKeyState(0x53)) {
            qwe.MoveObject(qwe.entities[0], 0, 1);
            qwe.entities[0].direction = 2;
        }
        else if (GetAsyncKeyState(0x44)) {
            qwe.MoveObject(qwe.entities[0], 1, 0);
            qwe.entities[0].direction = 1;
        }
        else if (GetAsyncKeyState(VK_ESCAPE)) {
            gameOver = 1;
        }
        else if (GetAsyncKeyState(VK_SPACE)) {
            qwe.Shoot(qwe.entities[0]);
        }
       /* SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(0), (short)(20) });
        for (int y = 0; y < qwe.Map.size(); y++) {
            for (int x = 0; x < qwe.Map[0].size(); x++)
                cout << qwe.Map[y][x];
            cout << endl;
        }*/
        //cout << endl << qwe.entities[].direction;
        //cout << endl << qwe.entities[0].y;
        //cout << endl << qwe.entities[0].x;
        //cout << endl << qwe.GetX();
        //cout << endl << qwe.GetY();
        //cout << endl << qwe.entities[0].direction;
        //cout << endl << qwe.projectiles[0].x;
        //cout << endl << qwe.projectiles[0].y;
        //cout << GetSystemTime;
        //cout << endl << zxc++;

        qwe.Process();
        Sleep(45);
    }
    return 0;
}