#include "WaterEffect.h"
#include "../Models/Settings.h"

using namespace Castlevania;

constexpr auto WATER_EFFECT_LIFESPAN = 2000;

WaterEffect::WaterEffect(std::shared_ptr<Texture> waterTexture)
{
	water = std::make_unique<Sprite>(waterTexture);

	waterLeftVelocity = Vector2{ -50, -200 };
	waterTopVelocity = Vector2{ 25, -400 };
	waterRightVelocity = Vector2{ 50, -200 };

	isFinished = true;
}

void WaterEffect::Show(Vector2 position)
{
	auto waterRect = water->GetTextureRegion().GetFrameRectangle();
	auto waterPosition = Vector2{
		position.x - waterRect.Width() / 2,
		position.y - waterRect.Height() / 2 };

	waterLeftPosition = waterPosition;
	waterTopPosition = waterPosition;
	waterRightPosition = waterPosition;

	isFinished = false;
	lifespanTimer.Start();
}

bool WaterEffect::IsFinished()
{
	return isFinished;
}

void WaterEffect::Update(GameTime gameTime)
{
	if (isFinished)
		return;

	auto deltaTime = (float)gameTime.ElapsedGameTime.Seconds();

	waterLeftVelocity.y += GRAVITY;
	waterTopVelocity.y += GRAVITY;
	waterRightVelocity.y += GRAVITY;

	waterLeftPosition += waterLeftVelocity * deltaTime;
	waterTopPosition += waterTopVelocity * deltaTime;
	waterRightPosition += waterRightVelocity * deltaTime;

	if (lifespanTimer.ElapsedMilliseconds() >= WATER_EFFECT_LIFESPAN)
		isFinished = true;
}

void WaterEffect::Draw(SpriteExtensions &spriteBatch)
{
	spriteBatch.Draw(*water, waterLeftPosition);
	spriteBatch.Draw(*water, waterTopPosition);
	spriteBatch.Draw(*water, waterRightPosition);
}