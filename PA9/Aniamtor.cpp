#include "Animator.h"

Animator::Animator() {}

void Animator::add(int typeAnim, Animation anim) {
	allAnimations.push_back(anim);
}

void Animator::play(int typeAnim, bool isLooping) {
	mIsLooping = isLooping;
	if (mTypeAnim!= typeAnim || curAnimation.isDone()) {
		mTypeAnim = typeAnim;
		curAnimation = allAnimations[typeAnim];
		curAnimation.setFlip(isFlipped);
		curAnimation.play();
	}
}

void Animator::update() {
	if (!curAnimation.isDone())
		curAnimation.update();
	else {
		if (mIsLooping)
			curAnimation.update();
		else
			play(IDLE_ANIM, true);
	}
}