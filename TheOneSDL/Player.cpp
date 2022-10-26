#include "Player.h"
#include <cmath>

Player::Player(SDL_Texture* default_texture)
{
	playerR.h = 32;
	playerR.w = 32;
	tilemap_x = 1;
	tilemap_y = 16;
	playerR.x = tilemap_x*32;
	playerR.y = tilemap_y*32;
	textureWidth = 1920;
	textureHeight = 32;
	frameWidth = textureWidth / 60;
	frameHeight = textureHeight;
	frame_time = 0;
	editMS(2);
	setTexture(default_texture);
	std::cout << "Player Created!\n";

}

Player::~Player()
{
	std::cout << "Player Destroyed!\n";
}

const float Player::getSpeed()
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

int Player::getTexX()
{
	return textureR.x;
}

SDL_Texture* Player::getTexture()
{
	return player_texture;
}

void Player::updateTexture(Physics* phys_eng, Terrain* terrain_eng)
{
	//std::cout << "[Type,F,TEX_X,X,Y]" << texture_name << "," << frame_time << "," << getTexX()
	//	<< "," << getX() << "," << getY() << std::endl;

	xTexEdit(getTexX() + frameWidth);
	if (frame_time >= 59)
	{
		frame_time = 0;
		if (getTexX() >= textureWidth)
		{
			xTexEdit(0);
		}
	}
	else
	{
		handleMovement(phys_eng,terrain_eng, 1);
		frame_time++;
	}
}

int Player::getY()
{
	return playerR.y;
}

float Player::getMS()
{
	return movementModifier;
}

SDL_Rect* Player::getRect()
{
	return &playerR;
}

SDL_Rect* Player::getRectTex()
{
	return &textureR;
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

void Player::wEdit(int w)
{
	playerR.w = w;
}

void Player::hEdit(int h)
{
	playerR.h = h;
}

void Player::xTexEdit(int x)
{
	textureR.x = x;
}

void Player::yTexEdit(int y)
{
	textureR.y = y;
}

void Player::wTexEdit(int w)
{
	textureR.w = w;
}

void Player::hTexEdit(int h)
{
	textureR.h = h;
}

void Player::editMS(float speed)
{
	movementModifier = speed;
}

//Setting Textures to the passed in texture
void Player::setTexture(SDL_Texture* texture)
{
	player_texture = texture;
	SDL_QueryTexture(player_texture, NULL, NULL, &textureWidth, &textureHeight);
	frameWidth = textureWidth / 60;
	frameHeight = textureHeight;
	xTexEdit(0);
	yTexEdit(0);
	wTexEdit(frameWidth);
	hTexEdit(frameHeight);
}

void Player::handleMovement(Physics* phys_eng, Terrain* terrain_eng, bool animation)
{
	terrain_eng->background_tilemap[tilemap_y][tilemap_x] = '1';
	if (boundsCheck(getX(), getY()))
	{
		switch (xPath())
		{
		case Left:
		{
			xEdit(getX() - getSpeed());
			terrain_eng->background_tilemap[tilemap_y][tilemap_x] = '~';
			tilemap_x = round(getX()/32);
			tilemap_y = round(getY()/32);
			terrain_eng->background_tilemap[tilemap_y][tilemap_x] = '1';
			break;
		}
		case Right:
		{
			xEdit(getX() + getSpeed());
			terrain_eng->background_tilemap[tilemap_y][tilemap_x] = '~';
			tilemap_x = round(getX()/32);
			tilemap_y = round(getY()/32);
			terrain_eng->background_tilemap[tilemap_y][tilemap_x] = '1';
			break;
		}
		}
		switch (yPath())
		{
		case Up:
		{
			yEdit(getY() - getSpeed());
			terrain_eng->background_tilemap[tilemap_y][tilemap_x] = '~';
			tilemap_x = round(getX()/32);
			tilemap_y = round(getY()/32);
			terrain_eng->background_tilemap[tilemap_y][tilemap_x] = '1';
			break;
		}
		// Case Down will be needed in future not currently
		// If Case down is needed implement collision check
		// case Down:
		// {
		// 		yEdit(getY() + getSpeed());
		// 		terrain_eng->background_tilemap[tilemap_y][tilemap_x] = '~';
		// 		tilemap_x = round(getX()/32);
		// 		tilemap_y = round(getY()/32);
		// 		terrain_eng->background_tilemap[tilemap_y][tilemap_x] = '1';
		// 		break;
		// }
		}
	}
	// Gravity handle

	if(phys_eng->checkCollision(getX(),getY(),terrain_eng->obj_tilemap))
	{
		phys_eng->incTime(); // Increase time when away from ground
		yEdit(getY() + phys_eng->getGravity() * phys_eng->getTime());
		// std::cout << phys_eng->getGravity() * phys_eng->getTime() << std::endl;
	}
	else{
		// std::cout << getX() << "," << getY() << std::endl;
		phys_eng->resetTime(); // Reset time on ground
	}
	if (!boundsCheck(getX(), getY()))
	{
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

void Player::set_tilemap_pos(int x, int y)
{
	tilemap_x = x;
	tilemap_y = y;
}
