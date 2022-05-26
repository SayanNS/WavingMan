//
// Created by sayan on 25.04.2022.
//

#ifndef CONNECTIVEGAMES_HUMAN_H
#define CONNECTIVEGAMES_HUMAN_H

#include "Frame.h"
#include "Sprite.h"
#include "Animation.h"

namespace human {

class Human;

enum class State
{
	NOT_MOVING,
	WAVING_HAND,
	STOPPING_HAND,
	SWITCHING_HAND
};

class HandAnimation : public Animation
{
public:
	HandAnimation(Human *human, float duration, FrameGroup *left_arm, FrameGroup *left_forearm, FrameGroup *left_hand,
			FrameGroup *right_arm, FrameGroup *right_forearm, FrameGroup *right_hand);

	void start(bool left);
	void revert(bool left);

protected:
	Human *human;

	FrameGroup *left_arm, *left_forearm, *left_hand;
	FrameGroup *right_arm, *right_forearm, *right_hand;

	bool left;
};

class HandWaveAnimation : public HandAnimation
{
public:
	HandWaveAnimation(Human *human, float duration, FrameGroup *left_arm, FrameGroup *left_forearm,
			FrameGroup *left_hand, FrameGroup *right_arm, FrameGroup *right_forearm, FrameGroup *right_hand);

	void onUpdate(float value) override;
	void onCompleted() override;
};

class HandRaiseAnimation : public HandAnimation
{
public:
	HandRaiseAnimation(Human *human, float duration, FrameGroup *left_arm, FrameGroup *left_forearm,
			FrameGroup *left_hand, FrameGroup *right_arm, FrameGroup *right_forearm, FrameGroup *right_hand);

	void onUpdate(float value) override;
	void onCompleted() override;
	void onReverted() override;
};

class Human : public FrameGroup
{
public:
	Human();

	void draw();
	void waveLeftHand();
	void waveRightHand();
	void takeStick();
	void update(unsigned int deltaTime);

	void onHandRaiseAnimationCompleted(bool left);
	void onHandWaveAnimationCompleted(bool left);
	void onHandRaiseAnimationReverted(bool left);
	void onWindowSizeChanged(unsigned int width, unsigned int height);


private:
	Matrix3x3 projection;

	Ellipse head_sprite;
	FrameGroup chest_frame;
	Trapezium chest_sprite;
	FrameGroup hig_frame;
	Trapezium hig_sprite;
	FrameGroup left_arm;
	Trapezium left_arm_sprite;
	FrameGroup right_arm;
	Trapezium right_arm_sprite;
	FrameGroup left_forearm;
	Trapezium left_forearm_sprite;
	FrameGroup right_forearm;
	Trapezium right_forearm_sprite;
	FrameGroup left_hand;
	Trapezium left_hand_sprite;
	FrameGroup right_hand;
	Trapezium right_hand_sprite;
	FrameGroup left_thigh;
	Trapezium left_thigh_sprite;
	FrameGroup right_thigh;
	Trapezium right_thigh_sprite;
	FrameGroup left_wrist;
	Trapezium left_wrist_sprite;
	FrameGroup right_wrist;
	Trapezium right_wrist_sprite;
	FrameGroup left_foot;
	Trapezium left_foot_sprite;
	FrameGroup right_foot;
	Trapezium right_foot_sprite;
	Trapezium right_hand_stick;
	Trapezium left_hand_stick;

	HandRaiseAnimation handRaiseAnimation;
	HandWaveAnimation handWaveAnimation;

	bool left;
	State state;
};


}

#endif //CONNECTIVEGAMES_HUMAN_H
