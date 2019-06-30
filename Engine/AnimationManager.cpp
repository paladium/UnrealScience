#include "AnimationManager.h"

void AnimationManager::GetKeysFromAnimation(Animation* anim)
{
	for (int i = 0; i < anim->AnimationKeys.size(); i++)
	{
		Key *k = anim->AnimationKeys[i];

		Keys.push_back(std::make_pair(k->startOrder, k));

		maxOrder = max(maxOrder, k->startOrder);
	}
}

void AnimationManager::Initialize()
{
	std::sort(Keys.begin(), Keys.end());
}

void AnimationManager::NextOrder()
{
	if (currOrder < maxOrder)
	{
		currOrder++;

		currentlyRunning.clear();

		for (int i = 0; i < Keys.size(); i++)
		{
			if (Keys[i].first == currOrder)
			{
				currentlyRunning.push_back(i);
			}
		}
	}


}

void AnimationManager::Update(float dt)
{
	for (int i = 0; i < currentlyRunning.size(); i++)
	{
		Keys[currentlyRunning[i]].second->RunAnimation(dt);
	}
}