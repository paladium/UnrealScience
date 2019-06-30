#include "Animation.h"

bool pred(Key *a, Key *b)
{
	return a->startOrder < b->startOrder;
}

Animation::Animation()
{
	currKey = 0;

	isOBO = true;
}

void Animation::Initialize(Mesh3D &_m)
{
	InitialTransformation.Position = _m.Position;
	InitialTransformation.Rotation = _m.Rotation;
	InitialTransformation.Scale = _m.Scale;

	m = &_m;

	SetKeys();
}

void Animation::SetKeys()
{

	std::sort(AnimationKeys.begin(), AnimationKeys.end(), pred);

	for (int i = 0; i < AnimationKeys.size(); i++)
	{
		if (i > 0)
		{
			AnimationKeys[i]->Start = AnimationKeys[i - 1]->Destination;

			//AnimationKeys[i]->Start.Position = m->Position;
			

			//find nearest interpolation point [position]
			if (!AnimationKeys[i - 1]->setPosition)
			{

				AnimationKeys[i]->Start.Position = m->Position;

				int k = i - 1;

				while (true)
				{
					if (AnimationKeys[k]->setPosition)
					{
						AnimationKeys[i]->Start.Position = AnimationKeys[k]->Destination.Position;
						
						break;
					}

					if (k > 0)
					{
						k--;
					}
					else break;
				}
			}

			//find nearest interpolation point [rotation]
			if (!AnimationKeys[i - 1]->setRotation)
			{

				AnimationKeys[i]->Start.Rotation = m->Rotation;

				int k = i - 1;

				while (true)
				{
					if (AnimationKeys[k]->setRotation)
					{
						AnimationKeys[i]->Start.Rotation = AnimationKeys[k]->Destination.Rotation;

						break;
					}

					if (k > 0)
					{
						k--;
					}
					else break;
				}
			}


			//find nearest interpolation point [scale]
			if (!AnimationKeys[i - 1]->setScale)
			{

				AnimationKeys[i]->Start.Scale = m->Scale;

				int k = i - 1;

				while (true)
				{
					if (AnimationKeys[k]->setScale)
					{
						AnimationKeys[i]->Start.Scale = AnimationKeys[k]->Destination.Scale;

						break;
					}

					if (k > 0)
					{
						k--;
					}
					else break;
				}
			}
		}
		else
		{
			AnimationKeys[i]->Start.Position = m->Position;
			AnimationKeys[i]->Start.Rotation = m->Rotation;
			AnimationKeys[i]->Start.Scale = m->Scale;
		}
	}

	std::vector<Key*> temp;

	for (int i = 0; i < AnimationKeys.size(); i++)
	{
		AnimationKeys[i]->Initialize(*m);
	}

	/*for (int i = 0; i < AnimationKeys.size(); i++)
	{
		if (i + 1 < AnimationKeys.size() - 1)
		{
			if (AnimationKeys[i]->startOrder == AnimationKeys[i + 1]->startOrder)
			{
				Key *k = AnimationKeys[i];

				Key *k2 = AnimationKeys[i + 1];

				if (!k->setPosition && k2->setPosition)
				{
					k->Destination.Position = k2->Destination.Position;

					k->setPosition = true;
				}

				if (!k->setRotation && k2->setRotation)
				{
					k->Destination.Rotation = k2->Destination.Rotation;

					k->setRotation = true;
				}

				if (!k->setScale && k2->setScale)
				{
					k->Destination.Scale = k2->Destination.Scale;

					k->setScale = true;
				}

				temp.push_back(k);

				i++;
			}
			else
			{
				temp.push_back(AnimationKeys[i]);
			}
		}
		
	}*/

	/*AnimationKeys.clear();

	AnimationKeys = temp;*/
	
}

void Animation::Update(float dt)
{

	if (isRunning)
	{
		time += dt;


		if (!isOBO)
		{
			for (int i = 0; i < AnimationKeys.size(); i++)
			{
				AnimationKeys[i]->RunAnimation(dt);
			}
		}
		else
		{
			if (currKey > 0)
			{
				AnimationKeys[currKey - 1]->RunAnimation(dt);

				if (AnimationKeys[currKey - 1]->isPlayed)
				{
					StopAnimation();
				}
			}
			
		}

		

		if (isEndless)
		{
			if (AnimationKeys[AnimationKeys.size() - 1]->isPlayed == true)
			{
				for (int i = 0; i < AnimationKeys.size(); i++)
				{
					AnimationKeys[i]->Reset();
				}

				time = 0;
			}
		}
	}

	

	
}

void Animation::Reset()
{
	StopAnimation();

	for (int i = 0; i < AnimationKeys.size(); i++)
	{
		AnimationKeys[i]->Reset();
	}

	if (m != nullptr)
	{
		m->Position = InitialTransformation.Position;
		m->Rotation = InitialTransformation.Rotation;
		m->Scale = InitialTransformation.Scale;
	}

	currKey = 0;

	AnimationKeys.clear();
}

void Animation::NextKey()
{
	StopAnimation();

	if (currKey < AnimationKeys.size())
	{
		currKey++;
	}
	/*else
	{
		if (isEndless)
		{

			for (int i = 0; i < AnimationKeys.size(); i++)
			{
				AnimationKeys[i]->Reset();
			}

			currKey = 0;
			time = 0;
		}
	}*/
	

	StartAnimation();
}

void Animation::PrevKey()
{
	StopAnimation();

	if (currKey > 1)
	{
		currKey--;
	}

	StartAnimation();
}