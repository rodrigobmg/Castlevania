#pragma once

#include "MovementSystem.h"

namespace Castlevania
{
	class GameObject;

	// Basic movement system: distance = velocity * deltaTime
	class SimpleMovementSystem : public MovementSystem
	{
	public:
		SimpleMovementSystem(GameObject &parent);
		void Update(GameTime gameTime) override;

	private:
		GameObject &parent;
	};
}