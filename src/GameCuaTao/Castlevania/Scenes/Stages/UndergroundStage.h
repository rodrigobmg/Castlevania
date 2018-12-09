#pragma once

#include "Stage.h"

namespace Castlevania
{
	class UndergroundStage : public Stage
	{
	public:
		UndergroundStage(GameplayScene &gameplayScene);

		void OnNotify(Subject &subject, int event) override;
		void Update(GameTime gameTime) override;
	};
}