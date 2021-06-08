#include "Ground.h"

Ground::Ground()
{
	groundR.x = 0;
	groundR.y = 0;
}

Ground::~Ground()
{
}

int Ground::getX()
{
	return groundR.x;
}

int Ground::getY()
{
	return groundR.y;
}
