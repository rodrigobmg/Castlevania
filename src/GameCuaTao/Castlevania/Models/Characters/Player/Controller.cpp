#include "Controller.h"
#include "../../../Settings/Button.h"

using namespace Castlevania;

Controller::Controller(Player &player, ObjectFactory &objectFactory) :
	player{ player },
	keyboardState{ nullptr },
	objectFactory{ objectFactory }
{
}

void Controller::OnKeyStateChanged(KeyboardState &keyboardState)
{
	this->keyboardState = keyboardState;
}

void Controller::OnKeyDown(int keyCode)
{
	if (!enabled)
		return;

	if (player.IsAttacking())
		return;

	switch (player.GetMoveState())
	{
		case MoveState::IDLE:
			if (keyCode == Button::Jump)
				player.Jump();
			else if (keyCode == Button::Attack)
				player.Attack();
			else if (keyCode == Button::Throw)
				Throw();
			break;

		case MoveState::WALKING:
			if (IsHoldingLeftAndRight())
				player.Idle();
			else if (keyCode == Button::Jump)
				player.Jump();
			else if (keyCode == Button::Duck)
				player.Duck();
			else if (keyCode == Button::Attack)
				player.Attack();
			else if (keyCode == Button::Throw)
				Throw();
			break;

		case MoveState::IDLE_UPSTAIRS:
		case MoveState::IDLE_DOWNSTAIRS:
			if (keyCode == Button::Attack)
				player.Attack();
			else if (keyCode == Button::Throw)
				Throw();
			break;

		case MoveState::JUMPING:
		case MoveState::HOVERING:
		case MoveState::FALLING:
		case MoveState::LANDING:
		case MoveState::DUCKING:
			if (keyCode == Button::Attack)
				player.Attack();
			else if (keyCode == Button::Throw)
				Throw();
			break;
	}
}

void Controller::OnKeyUp(int keyCode)
{
	if (!enabled)
		return;

	if (player.IsAttacking())
		return;
}

void Controller::Update(UpdateData &updateData)
{
	if (!enabled)
		return;

	if (player.IsAttacking())
		return;

	switch (player.GetMoveState())
	{
		case MoveState::IDLE:
			if (IsHoldingLeftAndRight() || IsHoldingUpAndDown())
				break;
			else if (keyboardState.IsKeyDown(Button::WalkLeft))
				player.WalkLeft();
			else if (keyboardState.IsKeyDown(Button::WalkRight))
				player.WalkRight();
			else if (keyboardState.IsKeyDown(Button::GoUpstair) && player.CanGoUpstairs())
				player.WalkToStairs();
			else if (keyboardState.IsKeyDown(Button::GoDownstair) && player.CanGoDownstairs())
				player.WalkToStairs();
			else if (keyboardState.IsKeyDown(Button::Duck))
				player.Duck();
			break;

		case MoveState::IDLE_UPSTAIRS:
		case MoveState::IDLE_DOWNSTAIRS:
			if (IsHoldingUpAndDown())
				break;
			else if (keyboardState.IsKeyDown(Button::GoUpstair))
				player.GoUpstairs();
			else if (keyboardState.IsKeyDown(Button::GoDownstair))
				player.GoDownstairs();
			break;

		case MoveState::WALKING:
			if (keyboardState.IsKeyUp(Button::WalkLeft) && player.GetFacing() == Facing::Left)
				player.Idle();
			if (keyboardState.IsKeyUp(Button::WalkRight) && player.GetFacing() == Facing::Right)
				player.Idle();
			break;

		case MoveState::DUCKING:
			if (keyboardState.IsKeyUp(Button::Duck))
				player.Idle();
			if (IsHoldingUpAndDown())
				player.Idle();
			break;
	}
}

bool Controller::IsHoldingLeftAndRight()
{
	return keyboardState.IsKeyDown(Button::WalkLeft) && keyboardState.IsKeyDown(Button::WalkRight);
}

bool Controller::IsHoldingUpAndDown()
{
	return keyboardState.IsKeyDown(Button::Duck) && keyboardState.IsKeyDown(Button::GoUpstair);
}

void Controller::Throw()
{
	auto weaponItem = player.GetSubWeapon();

	switch (weaponItem)
	{
		case EntityType::DaggerItem:
		{
			auto weapon = objectFactory.CreateDagger();
			
			player.Throw(std::move(weapon));
			break;
		}
	}
}
