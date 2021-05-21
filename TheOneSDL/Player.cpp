#include "Player.h"
#include "Application.h"
#include <iostream>

Player::Player()
{
	playerR.h = 32;
	playerR.w = 32;
	playerR.x = 100;
	playerR.y = 100;
	editMS(5);
	std::cout << "Player Created!\n";
}

Player::~Player()
{
	std::cout << "Player Destroyed!\n";
}

const int Player::getSpeed()
{
	return movementModifier;
}

MovementDirection Player::xPath()
{
	return currentDirectionX;
}

MovementDirection Player::yPath()
{
	return currentDirectionY;
}

int Player::getX()
{
	return playerR.x;
}

int Player::getY()
{
	return playerR.y;
}

int Player::getMS()
{
	return movementModifier;
}

SDL_Rect* Player::getRect()
{
	return &playerR;
}

void Player::xPathEdit(MovementDirection path)
{
	currentDirectionX = path;
}

void Player::yPathEdit(MovementDirection path)
{
	currentDirectionY = path;
}

void Player::xEdit(int x)
{
	playerR.x = x;
}

void Player::yEdit(int y)
{
	playerR.y = y;
}

void Player::editMS(int speed)
{
	movementModifier = speed;
}

void Player::handleMovement()
{
	if (boundsCheck(getX(), getY()))
	{
		switch (xPath())
		{
		case Left:
		{
			xEdit(getX() - getSpeed());
			break;
		}
		case Right:
		{
			xEdit(getX() + getSpeed());
			break;
		}
		}
		switch (yPath())
		{
		case Up:
		{
			yEdit(getY() - getSpeed());
			break;
		}
		case Down:
		{
			yEdit(getY() + getSpeed());
			break;
		}
		}
	}
	else if (!boundsCheck(getX(), getY()))
	{
		//std::cout << getX() << "," << getY() << std::endl;
		switch (xPath())
		{
		case Right:
		{
			xEdit(getX() + getSpeed());
			break;
		}
		case Left:
		{
			xEdit(getX() - getSpeed());
			break;
		}
		}
		switch (yPath())
		{
		case Down:
		{
			yEdit(getY() + getSpeed());
			break;
		}
		case Up:
		{
			yEdit(getY() - getSpeed());
			break;
		}
		}
		if (getX() >= SCREEN_WIDTH)
		{
			xEdit(getX() - getSpeed());
		}
		if (getY() >= SCREEN_HEIGHT)
		{
			yEdit(getY() - getSpeed());
		}
		if (getX() <= 0)
		{
			xEdit(getX() + getSpeed());
		}
		if (getY() <= 0)
		{
			yEdit(getY() + getSpeed());
		}
	}
}

bool Player::boundsCheck(int x, int y)
{
	if (x > 0 && y > 0)
	{
		if ((x < SCREEN_WIDTH) && (y < SCREEN_HEIGHT))
		{
			return true;
		}
	}
	return false;
}
