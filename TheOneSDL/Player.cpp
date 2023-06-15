#include "Player.h"
#include <cmath>

Player::Player(SDL_Renderer* renderer)
{
	// Rectangles
	playerR.h = 32;
	playerR.w = 32;
	tilemap_x = 1;
	tilemap_y = 16;
	playerR.x = tilemap_x*32;
	playerR.y = tilemap_y*32;

	// Hitbox
	hitboxOn = false;
	playerHitboxR.h = 20;
	playerHitboxR.w = 12;
	playerHitboxR.x = playerR.x+10;
	playerHitboxR.y = playerR.y+10;
	// Set Player defaults
	playerSpeed = 4;
	playerFalling = false;
	// Defaults zero no texture loaded yet
	textureWidth = 0;
	textureHeight = 0;
	frameWidth = textureWidth / 60;
	frameHeight = textureHeight;
	frame_time = 0;

	// Check default file existance and load default texture
	std::string idle_file = "textures/VGB/idle/vgb_idle-Sheet.png";
	const char* filename = idle_file.c_str();
	SDL_Texture* default_texture = IMG_LoadTexture(renderer, filename);
	SDL_QueryTexture(default_texture, NULL, NULL, &textureWidth, &textureHeight);
	std::cout << "File is " << filename << std::endl;
	std::cout << "Error Player.cpp: Texture loaded " << filename << "with dims " <<
	textureWidth << " and " << textureHeight << std::endl;
	// Load check
	if ( textureWidth == 0 || textureHeight == 0)
	{
		std::cout << "Error Player.cpp: Texture not loaded " << filename << "with dims " <<
		textureWidth << " and " << textureHeight << std::endl;
		exit(-1);
	}

	// Load Textures
	// Load filenames

	std::list<std::string> tex_files = {idle, run_left, run_right};
	std::list<std::string> tex_names = {"idle", "run_left","run_right"};
	
	while (tex_files.size() > 0) {
		std::string new_file = tex_files.front().c_str();		// Reference from front
		filename = new_file.c_str();
		std::string name = tex_names.front();
		tex_names.pop_front();						// pop
		tex_files.pop_front(); 						
		textures[name] = IMG_LoadTexture(renderer,filename);
		std::cout << filename << std::endl;
		if (textures[name] == 0){
			std::cout << name << "failed to load from path " << filename << std::endl;
		}
	}
	
	editMS(3); // push default speed
	setTexture(textures["idle"]);
	std::cout << "Player Created!\n";

}

Player::~Player()
{
	std::cout << "Player Destroyed!\n";
}

// Getters
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

bool Player::hitboxCheck()
{
	// Update position
	playerHitboxR.x = playerR.x+10;
	playerHitboxR.y = playerR.y+10;
	return hitboxOn;
}


SDL_Rect* Player::getHitboxRect()
{
	return &playerHitboxR;
}


// Setters

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

void Player::set_tilemap_pos(int x, int y)
{
	tilemap_x = x;
	tilemap_y = y;
}
// Methods

// Updating Texture per frame time
void Player::updateTexture(Physics* phys_eng, Terrain* terrain_eng)
{
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
		handleMovement(phys_eng,terrain_eng);
		frame_time++;
		
	}

	
}

void Player::checkCollision(int i, Physics* phys_eng)
{
	switch(i)
	{	
		case 0:	// Falling
			phys_eng->incTime(); // Increase time when away from ground
			yEdit(getY() + phys_eng->getGravity() * phys_eng->getTime());
			break;
		case 1: // On Ground
			playerFalling = false;
			phys_eng->resetTime(); // Reset time on ground
			break;
		case 2: // No edits
			break;
		
	}
	// Gravity-Collide handle If the player is not colliding with another object/tile

	// Old Player Collision check
	// if(phys_eng->checkCollision(getX(),getY(),terrain_eng->obj_tilemap))
	// {
	// 	phys_eng->incTime(); // Increase time when away from ground
	// 	yEdit(getY() + phys_eng->getGravity() * phys_eng->getTime());
	// }
	// else{
	// 	playerFalling = false;
	// 	phys_eng->resetTime(); // Reset time on ground
	// }
}

void Player::handleMovement(Physics* phys_eng, Terrain* terrain_eng)
{
	if (boundsCheck(getX(), getY()))
	{
		switch (xPath())
		{
		case Left:
		{
			if (!inAnimation)
			{
				setTexture(textures["run_left"]);
				inAnimation = true;
			}
			xEdit(getX() - getSpeed());
			tilemap_x = round(getX()/32);
			tilemap_y = round(getY()/32);
			break;
		}
		case Right:
		{
			if (!inAnimation)
			{
				setTexture(textures["run_right"]);
				inAnimation = true;
			}
			xEdit(getX() + getSpeed());
			tilemap_x = round(getX()/32);
			tilemap_y = round(getY()/32);
			break;
		}
		default:
		{
			setTexture(textures["idle"]);
			inAnimation = false;
		}
		}
		switch (yPath())
		{
		case Up:
		{
			if (!playerFalling)
			{
				yEdit(getY() - getSpeed());
				tilemap_x = round(getX()/32);
				tilemap_y = round(getY()/32);
			}
			break;
		}
		case None: // No input
		{
			playerFalling = true;
		}
		}
	}


	// If the Player is not outside of bounds
	if (!boundsCheck(getX(), getY()))
	{
		// Movement
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
		// Reset if out of bounds
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


