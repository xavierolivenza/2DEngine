#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#include "p2Point.h"
#include <vector>
#include "j1Timer.h"

struct Frame
{
	SDL_Rect rect = { 0,0,0,0 };
	iPoint pivot = { 0,0 };
};

class Animation
{
public:
	bool loop = false;
	iPoint pivot = { 0,0 };
	std::vector<Frame> frames;
	uint frameMiliseconds = 0;
	
private:
	int current_frame = 0;
	int loops = 0;
	j1Timer AnimationTimer;
	bool FirstLoop = true;

public:
	Animation()
	{}

	Animation(const Animation& anim) : loop(anim.loop), frameMiliseconds(anim.frameMiliseconds), pivot(anim.pivot), frames(anim.frames)
	{
		
	}

	void PushBack(SDL_Rect* rect, iPoint* pivot)
	{
		Frame newframe;
		newframe.rect = *rect;
		newframe.pivot = *pivot;
		frames.push_back(newframe);
	}

	void ChangeSpeed(uint newframeMiliseconds)
	{
		frameMiliseconds = newframeMiliseconds;
	}

	void IncreseSpeedBy(uint IncreseframeMiliseconds)
	{
		frameMiliseconds += IncreseframeMiliseconds;
	}

	void DecreseSpeedBy(uint DecreseframeMiliseconds)
	{
		frameMiliseconds -= DecreseframeMiliseconds;
	}

	Frame& GetCurrentFrame()
	{
		if (FirstLoop)
		{
			AnimationTimer.Start();
			FirstLoop = false;
		}

		//if there's in fact an animation, calculate and return the current frame
		if (frames.size() > 1)
		{
			if (AnimationTimer.Read() >= (frameMiliseconds * (current_frame + 1)))
				current_frame += 1;
			if (current_frame > (frames.size() - 1))
			{
				if (loop)
				{
					current_frame = 0;
					AnimationTimer.Start();
				}
				loops++;
			}
			return frames.at(current_frame);
		}
		//If not, only one frame, it's an static image, just return the same image forever
		return frames.front();
	}

	bool Finished() const
	{
		return loops > 0;
	}

	void Reset()
	{
		current_frame = 0;
		loops = 0;
	}
};

#endif