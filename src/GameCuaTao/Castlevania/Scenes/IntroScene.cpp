#include "IntroScene.h"
#include "SceneManager.h"

using namespace Castlevania;

IntroScene::IntroScene(SceneManager &sceneManager) : AbstractScene(sceneManager)
{
}

void IntroScene::LoadContent()
{
}

void IntroScene::Update(float deltaTime)
{
}

void IntroScene::Draw(GameTime gameTime)
{
	auto spriteBatch = sceneManager.GetSpriteBatch();

	spriteBatch.GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);

	// Draw stuff

	spriteBatch.GetSpriteHandler()->End();
}