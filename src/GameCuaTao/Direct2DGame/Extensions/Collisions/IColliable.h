#pragma once

#include "../RectF.h"
#include "../../Base/Vector2.h"

class IColliable
{
public:
	// Identify object type to handle collision response accordingly
	virtual int GetType() = 0;
	virtual Vector2 GetDistance() = 0;
	virtual RectF GetBoundingBox() = 0;
	virtual ~IColliable() {}
};
