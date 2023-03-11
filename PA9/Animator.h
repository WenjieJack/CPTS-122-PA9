#pragma once

#include <vector>

#include "pa9.h"
#include "Animation.h"

class Animator {
private:
	bool mIsLooping = false;

	int mTypeAnim = UNKNOWN_ANIM;

	std::vector<Animation> allAnimations;
	// current playing animation
	Animation curAnimation;

public:
	bool isFlipped = false;

	Animator();

	// add animation
	void add(int typeAnim, Animation anim);

	void play(int typeAnim, bool isLooping = false);

	void update();
};