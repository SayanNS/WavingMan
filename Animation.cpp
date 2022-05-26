//
// Created by sayan on 25.05.2022.
//

#include "Animation.h"

void Animation::onCompleted()
{
	state = State::COMPLETED;
}

void Animation::onReverted()
{
	state = State::REVERTED;
}

Animation::Animation(float duration) : duration(duration), state(State::COMPLETED)
{
}

void Animation::update(float deltaTime)
{
	if (state == State::PLAYING) {
		current_time += deltaTime;

		if (current_time >= duration) {
			onUpdate(1.0);
			onCompleted();
		} else {
			onUpdate(current_time / duration);
		}
	} else if (state == State::REVERTING) {
		current_time -= deltaTime;

		if (current_time <= 0) {
			onUpdate(0.0);
			onReverted();
		} else {
			onUpdate(current_time / duration);
		}
	}
}

void Animation::start()
{
	if (state == State::COMPLETED || state == State::REVERTED) {
		current_time = 0;
		state = State::PLAYING;
	}
}

void Animation::revert()
{
	if (state == State::PLAYING) {
		state = State::REVERTING;
	} else if (state == State::COMPLETED) {
		current_time = duration;
		state = State::REVERTING;
	}
}
