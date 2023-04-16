#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>
#include "Entity.h"
#include <vector>
#include <ctime>

using namespace std;

class Engine {
public:
    vector <Projectile> projectiles;
    vector <Entity> entities;
    vector <vector <char>> Map;
    string map;
    int MaxX = 0, MaxY = 0;

    void OpenMap() {
        string qwe123;
        cout << "Выберите карту(1-2): "; cin >> qwe123;
        system("cls");
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(0), (short)(20) });
        ifstream txt(qwe123 + ".txt");
        map = ""; MaxX = 0; MaxY = 1;
        char qwe124 = txt.get();

        while (qwe124 != '\n' && !txt.eof()) {
            map += qwe124;
            MaxX += 1;
            qwe124 = txt.get();
        }

        while (!txt.eof()) {
            if (qwe124 == '\n') MaxY += 1;
            else map += qwe124;
            qwe124 = txt.get();
        }

        Map.resize(MaxY, vector<char>(MaxX));

        for (int y = 0, i = 0; y < MaxY; y++) {
            for (int x = 0; x < MaxX; x++) {
                Map[y][x] = map[i++];
                if (Map[y][x] != ' ' && Map[y][x] != '\n') {
                    entities.push_back(Entity());
                    entities[entities.size() - 1].y = y;
                    entities[entities.size() - 1].x = x;
                    entities[entities.size() - 1].ebalo = Map[y][x];
                    /* cout << endl << "x: " << entities[entities.size() - 1].x;
                     cout << " y: " << entities[entities.size() - 1].y;
                     cout << " ebalo: " << entities[entities.size() - 1].ebalo;
                     cout << " i: " << i;*/
                }
            }
        }

        SpawnEntity(Actor(MaxX, MaxY));
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
            { (short)(0), (short)(25) });
        cout << entities[0].dmg;
        txt.close();
        
    }

    void SpawnEntity(Entity entity) {
        entities.insert(entities.begin(), entity);
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
            { (short)(entity.x + 1), (short)(entity.y) });
        cout << ("\b" + string(1, entity.ebalo));
        Map[entity.y][entity.x] = entity.ebalo;

    }

    void DeleteEntity(int q) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
            { (short)(entities[q].x + 1), (short)(entities[q].y) });
        cout << ("\b ");
        Map[entities[q].y][entities[q].x] = ' ';
        entities.erase(entities.begin() + q);
    }

    void DeleteProjectile(int q) {
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
            { (short)(projectiles[q].x + 1), (short)(projectiles[q].y) });
        cout << ("\b ");
        Map[projectiles[q].y][projectiles[q].x] = ' ';
        projectiles.erase(projectiles.begin() + q);
    }

    int GetEntityId(int x, int y) {
        for (int i = 0; i < entities.size(); i++) {
            if (entities[i].x == x && entities[i].y == y) {
                return i;
            }
        }
        return -1;
    }

    int GetProjectileId(int x, int y) {
        for (int i = 0; i < projectiles.size(); i++) {
            if (projectiles[i].x == x && projectiles[i].y == y) {
                return i;
            }
        }
        return -1;
    }

    void MoveObject(Entity& entity, int vectX, int vectY) {
        if (Map[entity.y + vectY][entity.x + vectX] == ' ') {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), 
                { (short)(entity.x + 1), (short)(entity.y) });
            cout << "\b ";
            Map[entity.y][entity.x] = ' ';
            entity.x += vectX; entity.y += vectY;
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), 
                { (short)(entity.x + 1), (short)(entity.y) });;
            cout << ("\b" + string(1, entity.ebalo));
            Map[entity.y][entity.x] = entity.ebalo;
        }
    }
    
    void Shoot(Entity& entity) {
        projectiles.push_back(Projectile(entity));
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(0), (short)(35) });
        cout << projectiles.back().dmg;
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),
            { (short)(entity.x + projectiles.back()._vectX + 1), (short)(entity.y + projectiles.back()._vectY)});
        cout << ("\b" + string(1, projectiles.back().ebalo));
        Map[entity.y + projectiles.back()._vectY][entity.x + projectiles.back()._vectX] = projectiles.back().ebalo;
    }

   /*Entity& GetEntity(int x, int y) {
        for (int i = 0; i < entities.size(); i++) {
            if (entities[i].x == x && entities[i].y == y) {
                return entities[i];
            }
        }
    }*/

    void Process() {
        for (int i = 0; i < projectiles.size(); i++) {
            if (Map[projectiles[i].y + projectiles[i]._vectY][projectiles[i].x + projectiles[i]._vectX] != ' ') {
                if (GetEntityId(projectiles[i].x + projectiles[i]._vectX, projectiles[i].y + projectiles[i]._vectY) == -1) {
                    int projId = GetProjectileId(projectiles[i].x + projectiles[i]._vectX, projectiles[i].y + projectiles[i]._vectY);
                    projectiles[projId].hp -= projectiles[i].dmg;
                    projectiles[i].hp -= projectiles[projId].dmg;

                    if (projectiles[i].hp <= 0) {
                        DeleteProjectile(i);
                    }

                    if (projectiles[projId].hp <= 0) {
                        DeleteProjectile(projId);
                    }
                }
                else {
                    int entId = GetEntityId(projectiles[i].x + projectiles[i]._vectX, projectiles[i].y + projectiles[i]._vectY);
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(0), (short)(20) });
                    cout << entities[entId].hp << "   " << projectiles[i].dmg;
                    entities[entId].hp -= projectiles[i].dmg;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(0), (short)(21) });
                    cout << entities[entId].hp << "   " << projectiles[i].dmg;
                    projectiles[i].hp -= entities[entId].dmg;
                    
                    if (projectiles[i].hp <= 0) {
                        DeleteProjectile(i);
                    }

                    if (entities[entId].hp <= 0) {
                        DeleteEntity(entId);
                    }
                }
            }
            else  {
                MoveObject(projectiles[i], projectiles[i]._vectX, projectiles[i]._vectY);
            }
        }
    }
};