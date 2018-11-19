#pragma once

#include <map>
#include "../AnimatedObject.h"

namespace Castlevania
{
	class Whip : public AnimatedObject
	{
	public:
		Whip(GameObject &owner);

		void SetFacing(Facing facing);
		RectF GetBoundingBox() override;

		void LoadContent(ContentManager &content) override;
		void Update(float deltaTime, ObjectCollection *objectCollection) override;
		void Draw(SpriteExtensions &spriteBatch) override;

		void Unleash();
		void Withdraw();

	private:
		Vector2 GetPositionRelativeToPlayer(GameObject &player);
		GameObject &owner;
		int level; // 1, 2, 3
		int hitPoint;
	};
}