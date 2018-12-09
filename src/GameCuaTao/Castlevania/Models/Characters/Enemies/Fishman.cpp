#include "Fishman.h"
#include "../../UpdateData.h"
#include "../../Settings.h"

using namespace Castlevania;

constexpr auto SHOOTING_TIME = 600;
constexpr auto RELEASE_FIREBALL_TIME = SHOOTING_TIME / 2;
constexpr auto FIREBALL_SPEED = 300.0f;

Fishman::Fishman() : Enemy{ EntityType::Fishman }
{
}

void Fishman::SetLaunchSpeed(float speed)
{
	launchSpeed = speed;
}

FishmanState Fishman::GetFishmanState()
{
	return fishmanState;
}

void Fishman::Update(GameTime gameTime, UpdateData &updateData)
{
	Enemy::Update(gameTime, updateData);

	switch (fishmanState)
	{
		case FishmanState::SHOOTING:
			if (shootingTimer.ElapsedMilliseconds() > SHOOTING_TIME)
			{
				if (facing == Facing::Left)
					WalkRight();
				else // facing == Facing::Right
					WalkLeft();

				shootingTimer.Reset();
			}
			else if (shootingTimer.ElapsedMilliseconds() > RELEASE_FIREBALL_TIME)
			{
				if (fireball != nullptr)
					ReleaseFireball(*updateData.objectCollection);
			}
			break;
	}
}

void Fishman::Launch()
{
	velocity.y = -launchSpeed;
	SetFishmanState(FishmanState::LAUNCHING);
}

void Fishman::WalkRight()
{
	SetFacing(Facing::Right);
	velocity.x = speed;
	SetFishmanState(FishmanState::WALKING);
}

void Fishman::WalkLeft()
{
	SetFacing(Facing::Left);
	velocity.x = -speed;
	SetFishmanState(FishmanState::WALKING);
}

void Fishman::Shoot(std::unique_ptr<GameObject> fireball)
{
	this->fireball = std::move(fireball);
	velocity.x = 0.0f;
	SetFishmanState(FishmanState::SHOOTING);
	shootingTimer.Start();
}

void Fishman::Freeze()
{
	velocity = Vector2::Zero();
	SetDistance(Vector2::Zero());
	SetFishmanState(FishmanState::FALLING);
}

void Fishman::Land()
{
	if (facing == Facing::Left)
		WalkLeft();
	else
		WalkRight();
}

void Fishman::SetFishmanState(FishmanState state)
{
	fishmanState = state;
	SendMessageToSystems(MOVE_STATE_CHANGED);
}

void Fishman::ReleaseFireball(ObjectCollection &objectCollection)
{
	fireball->SetFacing(facing);

	auto fishmanRect = GetFrameRect();
	auto position = Vector2{
		fishmanRect.left + 20,
		fishmanRect.top + 6
	};
	fireball->SetPosition(position);

	if (facing == Facing::Right)
		fireball->SetVelocity_X(FIREBALL_SPEED);
	else
		fireball->SetVelocity_X(-FIREBALL_SPEED);

	objectCollection.entities.push_back(std::move(fireball));
}