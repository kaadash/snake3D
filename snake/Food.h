#pragma once
#include "GameObject.h"
class Food : public GameObject
{
public:
	Food() : GameObject() {}
	void respawnInNewPlace(int maxRandomNumber);
	~Food();
};

