#pragma once
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;


class Entity {
public:
	int x, y;
	int dmg;
	int direction = 1;
	char ebalo;
	int hp;
	int rateOfFire = 50;
	Entity() {
		ebalo = '@';
		x = 0; y = 0, hp = 5; dmg = hp;
	}
};

class Actor : public Entity {
public:
	Actor(int mx, int my) {
		dmg = 1;
		direction = 1;
		x = mx / 2;
		y = my / 2;
		ebalo = '$';
		hp = 5;
	}
};

class Foe : public Entity {
public:
	Foe(int mx, int my) {
		x = rand() % mx;
		y = rand() % my;
		ebalo = "12345"[rand() % 5];
		hp = "12345"[rand() % 5];
	}
};

class Projectile : public Entity {
public:
	int _vectX = 0, _vectY = 0;
	Projectile(Entity& entity) {
		ebalo = '+';
		if (entity.direction == 1)      { y = entity.y; x = entity.x + 1;_vectX = 1; _vectY = 0;}
		else if (entity.direction == 2) { y = entity.y + 1; x = entity.x; _vectX = 0; _vectY = 1; }
		else if (entity.direction == 3) { y = entity.y; x = entity.x - 1; _vectX = -1; _vectY = 0; }
		else if (entity.direction == 4) { y = entity.y - 1; x = entity.x; _vectX = 0; _vectY = -1; }
		hp = entity.dmg;
		dmg = entity.dmg;
	}
};