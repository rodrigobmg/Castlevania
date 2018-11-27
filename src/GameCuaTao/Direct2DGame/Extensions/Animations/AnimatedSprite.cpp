#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory) :
	Sprite{ animationFactory->Create().GetCurrentFrame().GetTextureRegion() }
{
	this->animationFactory = animationFactory;
	this->animations = this->animationFactory->GetAnimations();
	this->currentAnimation = &animations.begin()->second;
}

AnimatedSprite::AnimatedSprite(std::shared_ptr<AnimationFactory> animationFactory, std::vector<std::string> animations) :
	Sprite{ animationFactory->Create().GetCurrentFrame().GetTextureRegion() }
{
	this->animationFactory = animationFactory->Clone(animations);
	this->animations = this->animationFactory->GetAnimations();
	this->currentAnimation = &this->animations.begin()->second;
}

Animation &AnimatedSprite::GetCurrentAnimation()
{
	return *currentAnimation;
}

bool AnimatedSprite::AnimateComplete()
{
	return currentAnimation->IsComplete();
}

void AnimatedSprite::Play(std::string name)
{
	if (currentAnimation->GetName() != name || currentAnimation->IsComplete())
	{
		currentAnimation->Stop();
		animations.at(name) = animationFactory->Create(name);
		currentAnimation = &animations.at(name);
	}
}

void AnimatedSprite::PlayCached(std::string name)
{
	if (currentAnimation->GetName() != name || currentAnimation->IsComplete())
	{
		currentAnimation->Stop();
		currentAnimation = &animations.at(name);
		currentAnimation->Continue();
	}
}

void AnimatedSprite::Update()
{
	if (currentAnimation->IsPlaying())
	{
		currentAnimation->Update();
		SetTextureRegion(currentAnimation->GetCurrentFrame().GetTextureRegion());
	}
}