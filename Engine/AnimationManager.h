#pragma once

#include "Animation.h"

class AnimationManager
{
public:

	void NextOrder();

	void GetKeysFromAnimation(Animation* anim);

	void Initialize();

	std::vector<int> currentlyRunning;

	void Update(float dt);

private:

	int currOrder = 0;

	int maxOrder = 0;

	std::vector<std::pair<int, Key*>> Keys;
};