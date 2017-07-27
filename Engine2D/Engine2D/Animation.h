#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include "SDL/include/SDL_rect.h"
#include "p2Point.h"
#include <vector>

struct Frame
{
	SDL_Rect rect = { 0,0,0,0 };
	iPoint pivot = { 0,0 };
};

class Animation
{
public:
	bool loop = true;
	float speed = 1.0f;
	iPoint pivot = { 0,0 };
	std::vector<Frame> frames;
	int last_frame = 0;

private:
	float current_frame = 0.0f;
	int loops = 0;

public:
	Animation()
	{}

	Animation(const Animation& anim) : loop(anim.loop), speed(anim.speed), last_frame(anim.last_frame), pivot(anim.pivot), frames(anim.frames)
	{
		
	}

	void PushBack(SDL_Rect* rect, iPoint* pivot)
	{
		Frame newframe;
		newframe.rect = *rect;
		newframe.pivot = *pivot;
		frames.push_back(newframe);
	}

	Frame& GetCurrentFrame()
	{
		//if there's in fact an animation, calculate and return the current frame
		if (frames.size() > 1)
		{
			current_frame += speed;
			if (current_frame >= last_frame)
			{
				current_frame = (loop) ? 0.0f : last_frame - 1;
				loops++;
			}
			return frames.at((int)current_frame);
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
		current_frame = 0.0f;
		loops = 0;
	}
};

#endif