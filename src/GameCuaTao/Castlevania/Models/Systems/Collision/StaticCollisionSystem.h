#pragma once

#include "CollisionSystem.h"

namespace Castlevania
{
	class GameObject;

	// Only check for collision with static object (wall, floor, platform)
	class StaticCollisionSystem : public CollisionSystem
	{
	public:
		StaticCollisionSystem(GameObject &parent);

		IGameObject &GetParent() override;
		void Update(ObjectCollection &objectCollection) override;

	private:
		IGameObject &parent;
	};
}