#pragma once

#include "Direct2DGame/Content/ContentManager.h"
#include "Direct2DGame/Utilities/Stopwatch.h"
#include "Cutscene.h"

namespace Castlevania
{
	class NextMapCutscene : public Cutscene
	{
	public:
		NextMapCutscene(Stage &stage, ContentManager &content);

		void Update(UpdateData &updateData) override;
		void Draw(SpriteExtensions &spriteBatch) override;

	private:
		std::unique_ptr<Sprite> cutsceneBackground;
		Stopwatch transitionTimer;
	};
}