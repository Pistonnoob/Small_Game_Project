#ifndef PLAYER_H
#define PLAYER_H

#include "Actor.h"

class Player : public Actor {

private:

public:
	Player();
	~Player();
	virtual void moveRight();
	virtual void moveLeft();
	virtual void moveUp();
	virtual void moveDown();
	virtual void move(DirectX::XMFLOAT3 moveVec);
};

#endif