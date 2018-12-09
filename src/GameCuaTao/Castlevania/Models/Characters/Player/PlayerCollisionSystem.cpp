#include "Direct2DGame/MathHelper.h"
#include "PlayerCollisionSystem.h"
#include "../../GameObject.h"
#include "../../../Models/Factories/ObjectCollection.h"

using namespace Castlevania;

PlayerCollisionSystem::PlayerCollisionSystem(GameObject &parent) : parent{ parent }
{
}

IGameObject &PlayerCollisionSystem::GetParent()
{
	return parent;
}

void PlayerCollisionSystem::Update(ObjectCollection &objectCollection)
{
	auto &body = parent.GetBody();
	body.ClearCollisionData();

	if (!body.Enabled())
		return;

	auto results = std::vector<CollisionResult>{};

	for (auto &boundary : objectCollection.boundaries)
	{
		CalculateCollision(*boundary, results);
	}

	for (auto &trigger : objectCollection.triggers)
	{
		CalculateCollision(*trigger, results);
	}

	for (auto &entity : objectCollection.entities)
	{
		CalculateCollision(*entity, results);
	}

	// TODO: do we need to sort?
	body.SetCollisionData(FilterCollision(results));
}
