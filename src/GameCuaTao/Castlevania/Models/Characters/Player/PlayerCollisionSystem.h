#pragma once

#include "../../Systems/Collision/CollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// Check for collision with all objects in game
	class PlayerCollisionSystem : public CollisionSystem
	{
	public:
		PlayerCollisionSystem(GameObject &parent);

		IGameObject &GetParent() override;
		void Update(UpdateData &updateData) override;

	private:
		IGameObject &parent;
	};
}