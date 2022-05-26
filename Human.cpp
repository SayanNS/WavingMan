//
// Created by sayan on 25.04.2022.
//

#include "Human.h"


#define PI 3.1416

#define WIDTH 800
#define HEIGHT 600

#define HEAD_POSITION_SPRITE_X 0.f
#define HEAD_POSITION_SPRITE_Y 130.f
#define HEAD_SPRITE_RADIUS 	70.f

#define CHEST_POSITION_X 	0.f
#define CHEST_POSITION_Y 	40.f
#define CHEST_TOP_WIDTH 	80.f
#define CHEST_BOTTOM_WIDTH 	58.f
#define CHEST_HEIGHT		90.f

#define HIG_POSITION_X 0.f
#define HIG_POSITION_Y -40.f
#define HIG_TOP_WIDTH 54.f
#define HIG_BOTTOM_WIDTH 80.f
#define HIG_HEIGHT 55.f

#define ARM_WIDTH 60.f
#define ARM_HEIGHT 18.f
#define ARM_POSITION_X (ARM_WIDTH / 2 + 3)
#define ARM_POSITION_Y 0
#define ARM_FRAME_POSITION_X (CHEST_POSITION_X + CHEST_TOP_WIDTH / 2 + 3)
#define ARM_FRAME_POSITION_Y (CHEST_POSITION_Y + CHEST_HEIGHT / 2 - 3)

#define FOREARM_WIDTH 		65.f
#define FOREARM_HEIGHT		ARM_HEIGHT
#define FOREARM_POSITION_X 	(FOREARM_WIDTH / 2 + FOREARM_HEIGHT / 4)
#define FOREARM_POSITION_Y 	0
#define FOREARM_FRAME_POSITION_X (ARM_POSITION_X + ARM_WIDTH / 2 + FOREARM_HEIGHT / 4)
#define FOREARM_FRAME_POSITION_Y 0

#define HAND_WIDTH 23.f
#define HAND_HEIGHT FOREARM_HEIGHT
#define HAND_POSITION_X (HAND_WIDTH / 2 + 2)
#define HAND_POSITION_Y 0
#define HAND_FRAME_POSITION_X (FOREARM_POSITION_X + FOREARM_WIDTH / 2 + 2)
#define HAND_FRAME_POSITION_Y 0

#define THIGH_WIDTH 18.f
#define THIGH_HEIGHT 70.f
#define THIGH_POSITION_X 0
#define THIGH_POSITION_Y (-THIGH_HEIGHT / 2)
#define THIGH_FRAME_POSITION_X (HIG_POSITION_X + HIG_BOTTOM_WIDTH / 2 - THIGH_WIDTH / 2 + 2)
#define THIGH_FRAME_POSITION_Y (HIG_POSITION_Y - HIG_HEIGHT / 2 - 7)

#define WRIST_WIDTH 18.f
#define WRIST_HEIGHT 70.f
#define WRIST_POSITION_X 0
#define WRIST_POSITION_Y (-WRIST_HEIGHT / 2)
#define WRIST_FRAME_POSITION_X 0
#define WRIST_FRAME_POSITION_Y (-THIGH_HEIGHT - 3)

#define FOOT_WIDTH 50.f
#define FOOT_HEIGHT 18.f
#define FOOT_POSITION_X (FOOT_WIDTH / 2 - FOOT_HEIGHT / 2)
#define FOOT_POSITION_Y 0
#define FOOT_FRAME_POSITION_X 0
#define FOOT_FRAME_POSITION_Y (-WRIST_HEIGHT - FOOT_HEIGHT / 2 - 2)

#define FIRST_STAGE_ANIMATION_DURATION 0.7
#define HAND_WAVE_ANIMATION_DURATION 1.0

#define STICK_WIDTH 18.f
#define STICK_HEIGHT 60.f
#define STICK_POSITION_X -35
#define STICK_POSITION_Y (STICK_HEIGHT / 2 - STICK_WIDTH / 2 - 5)

const float array_projection[3][3] = {
		{2.f / WIDTH, 0.f, 0.f},
		{0.f, 2.f / HEIGHT, 0.f},
		{0.f, 0.f, 0.f}
};

const float array_identity[3][3] = {
		{1, 0, 0},
		{0, 1, 0},
		{0, 0, 1}
};

namespace human {


Human::Human()
	: projection(reinterpret_cast<const float *>(array_projection))
	, head_sprite(projection, HEAD_POSITION_SPRITE_X, HEAD_POSITION_SPRITE_Y, HEAD_SPRITE_RADIUS, HEAD_SPRITE_RADIUS)
	, chest_sprite(projection, CHEST_POSITION_X, CHEST_POSITION_Y, CHEST_TOP_WIDTH, CHEST_BOTTOM_WIDTH, CHEST_HEIGHT)
	, hig_sprite(projection, HIG_POSITION_X, HIG_POSITION_Y, HIG_TOP_WIDTH, HIG_BOTTOM_WIDTH, HIG_HEIGHT)
	, right_arm_sprite(projection, ARM_POSITION_X, ARM_POSITION_Y, ARM_WIDTH, ARM_WIDTH, ARM_HEIGHT)
	, left_arm_sprite(projection, -ARM_POSITION_X, ARM_POSITION_Y, ARM_WIDTH, ARM_WIDTH, ARM_HEIGHT)
	, right_forearm_sprite(projection, FOREARM_POSITION_X, FOREARM_POSITION_Y, FOREARM_WIDTH, FOREARM_WIDTH, FOREARM_HEIGHT)
	, left_forearm_sprite(projection, -FOREARM_POSITION_X, FOREARM_POSITION_Y, FOREARM_WIDTH, FOREARM_WIDTH, FOREARM_HEIGHT)
	, right_hand_sprite(projection, HAND_POSITION_X, HAND_POSITION_Y, HAND_WIDTH, HAND_WIDTH, HAND_HEIGHT)
	, left_hand_sprite(projection, -HAND_POSITION_X, HAND_POSITION_Y, HAND_WIDTH, HAND_WIDTH, HAND_HEIGHT)
	, right_thigh_sprite(projection, THIGH_POSITION_X, THIGH_POSITION_Y, THIGH_WIDTH, THIGH_WIDTH, THIGH_HEIGHT)
	, left_thigh_sprite(projection, THIGH_POSITION_X, THIGH_POSITION_Y, THIGH_WIDTH, THIGH_WIDTH, THIGH_HEIGHT)
	, right_wrist_sprite(projection, WRIST_POSITION_X, WRIST_POSITION_Y, WRIST_WIDTH, WRIST_WIDTH, WRIST_HEIGHT)
	, left_wrist_sprite(projection, WRIST_POSITION_X, WRIST_POSITION_Y, WRIST_WIDTH, WRIST_WIDTH, WRIST_HEIGHT)
	, right_foot_sprite(projection, FOOT_POSITION_X, FOOT_POSITION_Y, FOOT_WIDTH, FOOT_WIDTH, FOOT_HEIGHT)
	, left_foot_sprite(projection, -FOOT_POSITION_X, FOOT_POSITION_Y, FOOT_WIDTH, FOOT_WIDTH, FOOT_HEIGHT)
	, handRaiseAnimation(this, FIRST_STAGE_ANIMATION_DURATION, &left_arm, &left_forearm, &left_hand, &right_arm,
			&right_forearm, &right_hand)
	, handWaveAnimation(this, HAND_WAVE_ANIMATION_DURATION, &left_arm, &left_forearm, &left_hand, &right_arm,
			&right_forearm, &right_hand)
	, left_hand_stick(projection, STICK_POSITION_X, STICK_POSITION_Y, STICK_WIDTH, STICK_WIDTH, STICK_HEIGHT)
	, right_hand_stick(projection, -STICK_POSITION_X, STICK_POSITION_Y, STICK_WIDTH, STICK_WIDTH, STICK_HEIGHT)
{
	this->addChild(&chest_frame);
	chest_frame.addChild(&head_sprite);
	chest_frame.addChild(&chest_sprite);
	chest_frame.addChild(&hig_frame);
	chest_frame.addChild(&right_arm);
	chest_frame.addChild(&left_arm);
	hig_frame.addChild(&hig_sprite);
	right_arm.addChild(&right_arm_sprite);
	left_arm.addChild(&left_arm_sprite);
	right_arm.addChild(&right_forearm);
	right_forearm.addChild(&right_forearm_sprite);
	left_arm.addChild(&left_forearm);
	left_forearm.addChild(&left_forearm_sprite);
	right_forearm.addChild(&right_hand);
	right_hand.addChild(&right_hand_sprite);
	left_forearm.addChild(&left_hand);
	left_hand.addChild(&left_hand_sprite);
	hig_frame.addChild(&right_thigh);
	right_thigh.addChild(&right_thigh_sprite);
	hig_frame.addChild(&left_thigh);
	left_thigh.addChild(&left_thigh_sprite);
	right_thigh.addChild(&right_wrist);
	right_wrist.addChild(&right_wrist_sprite);
	left_thigh.addChild(&left_wrist);
	left_wrist.addChild(&left_wrist_sprite);
	right_wrist.addChild(&right_foot);
	right_foot.addChild(&right_foot_sprite);
	left_wrist.addChild(&left_foot);
	left_foot.addChild(&left_foot_sprite);
	left_hand.addChild(&left_hand_stick);
	right_hand.addChild(&right_hand_stick);

	right_arm.move({ARM_FRAME_POSITION_X, ARM_FRAME_POSITION_Y});
	left_arm.move({-ARM_FRAME_POSITION_X, ARM_FRAME_POSITION_Y});
	right_forearm.move({FOREARM_FRAME_POSITION_X, FOREARM_FRAME_POSITION_Y});
	left_forearm.move({-FOREARM_FRAME_POSITION_X, FOREARM_FRAME_POSITION_Y});
	right_hand.move({HAND_FRAME_POSITION_X, HAND_FRAME_POSITION_Y});
	left_hand.move({-HAND_FRAME_POSITION_X, HAND_FRAME_POSITION_Y});
	right_thigh.move({THIGH_FRAME_POSITION_X, THIGH_FRAME_POSITION_Y});
	left_thigh.move({-THIGH_FRAME_POSITION_X, THIGH_FRAME_POSITION_Y});
	right_wrist.move({WRIST_FRAME_POSITION_X, WRIST_FRAME_POSITION_Y});
	left_wrist.move({WRIST_FRAME_POSITION_X, WRIST_FRAME_POSITION_Y});
	right_foot.move({FOOT_FRAME_POSITION_X, FOOT_FRAME_POSITION_Y});
	left_foot.move({FOOT_FRAME_POSITION_X, FOOT_FRAME_POSITION_Y});

	right_arm.rotate(-45.f / 180 * PI);
	left_arm.rotate(45.f / 180 * PI);
	right_forearm.rotate(-45.f /180 * PI);
	left_forearm.rotate(45.f / 180 * PI);
	right_hand.rotate(-25.f / 180 * PI);
	left_hand.rotate(25.f / 180 * PI);

	left_thigh.rotate(-5.f / 180 * PI);
	left_wrist.rotate(5.f / 180 * PI);
	left_foot.rotate(5.F / 180 * PI);
	right_thigh.rotate(15.f / 180 * PI);
	right_wrist.rotate(-15.f / 180 * PI);
	right_foot.rotate(5.f / 180 * PI);

	left = false;
	state = State::WAVING_HAND;
	handWaveAnimation.start(left);

	left_hand_stick.setVisibility(false);
	right_hand_stick.setVisibility(false);
}

void Human::waveLeftHand()
{
	switch (state) {
	case State::NOT_MOVING:
		left = true;
		state = State::WAVING_HAND;
		handRaiseAnimation.start(left);
		break;
	case State::WAVING_HAND:
		if (left) {
			state = State::STOPPING_HAND;
		} else {
			state = State::SWITCHING_HAND;
		}
		break;
	default:
		break;
	}
}

void Human::waveRightHand()
{
	switch (state) {
	case State::NOT_MOVING:
		left = false;
		state = State::WAVING_HAND;
		handRaiseAnimation.start(left);
		break;
	case State::WAVING_HAND:
		if (!left) {
			state = State::STOPPING_HAND;
		} else {
			state = State::SWITCHING_HAND;
		}
		break;
	default:
		break;
	}
}

void Human::update(unsigned int deltaTime)
{
	handRaiseAnimation.update((float)deltaTime / 1000);
	handWaveAnimation.update((float)deltaTime / 1000);
}

void Human::draw()
{
	Matrix3x3 &identity = (Matrix3x3 &)array_identity;
	this->onDraw(identity);
}

void Human::onHandRaiseAnimationCompleted(bool left)
{
	if (state == State::WAVING_HAND) {
		handWaveAnimation.start(left);
	} else {
		handRaiseAnimation.revert(left);
	}
}

void Human::onHandRaiseAnimationReverted(bool left)
{
	if (state == State::STOPPING_HAND) {
		state = State::NOT_MOVING;
	} else if (state == State::SWITCHING_HAND) {
		this->left = !left;
		state = State::WAVING_HAND;
		handRaiseAnimation.start(this->left);
	}
}

void Human::onHandWaveAnimationCompleted(bool left)
{
	if (state == State::WAVING_HAND) {
		handWaveAnimation.start(left);
	} else {
		handRaiseAnimation.revert(left);
	}
}

void Human::onWindowSizeChanged(unsigned int width, unsigned int height)
{

}

void Human::takeStick()
{
	if (left) {
		left_hand_stick.setVisibility(true);
	} else {
		right_hand_stick.setVisibility(true);
	}
}

HandAnimation::HandAnimation(Human *human, float duration, FrameGroup *left_arm, FrameGroup *left_forearm,
		FrameGroup *left_hand, FrameGroup *right_arm, FrameGroup *right_forearm, FrameGroup *right_hand)
	: Animation(duration), human(human), left_arm(left_arm), left_forearm(left_forearm), left_hand(left_hand)
	, right_arm(right_arm), right_forearm(right_forearm), right_hand(right_hand)
{
}

void HandAnimation::start(bool left)
{
	this->left = left;
	Animation::start();
}

void HandAnimation::revert(bool left)
{
	this->left = left;
	Animation::revert();
}

HandRaiseAnimation::HandRaiseAnimation(Human *human, float duration, FrameGroup *left_arm, FrameGroup *left_forearm,
		FrameGroup *left_hand, FrameGroup *right_arm, FrameGroup *right_forearm, FrameGroup *right_hand)
		: HandAnimation(human, duration, left_arm, left_forearm, left_hand, right_arm, right_forearm, right_hand)
{
}

void HandRaiseAnimation::onUpdate(float value)
{
	if (left) {
		left_arm->rotate(45.f / 180 * PI * (1 - 1.5 * value));
		left_forearm->rotate(45.f / 180 * PI * (1 - 1.5 * value));
		left_hand->rotate(25.f / 180 * PI * (1 - 1.5 * value));
	} else {
		right_arm->rotate(-45.f / 180 * PI * (1 - 1.5 * value));
		right_forearm->rotate(-45.f / 180 * PI * (1 - 1.5 * value));
		right_hand->rotate(-25.f / 180 * PI * (1 - 1.5 * value));
	}
}

void HandRaiseAnimation::onCompleted()
{
	Animation::onCompleted();
	human->onHandRaiseAnimationCompleted(left);
}

void HandRaiseAnimation::onReverted()
{
	Animation::onReverted();
	human->onHandRaiseAnimationReverted(left);
}

HandWaveAnimation::HandWaveAnimation(Human *human, float duration, FrameGroup *left_arm, FrameGroup *left_forearm,
		FrameGroup *left_hand, FrameGroup *right_arm, FrameGroup *right_forearm, FrameGroup *right_hand)
		: HandAnimation(human, duration, left_arm, left_forearm, left_hand, right_arm, right_forearm, right_hand)
{
}

void HandWaveAnimation::onUpdate(float value)
{
	if (left) {
		left_arm->rotate(45.f / 180 * PI * (cos(2 * PI * value) - 3) / 4);
		left_forearm->rotate(45.f / 180 * PI * (cos(2 * PI * value) - 3) / 4);
		left_hand->rotate(25.f / 180 * PI * (cos(2 * PI * value) - 3) / 4);
	} else {
		right_arm->rotate(-45.f / 180 * PI * (cos(2 * PI * value) - 3) / 4);
		right_forearm->rotate(-45.f / 180 * PI * (cos(2 * PI * value) - 3) / 4);
		right_hand->rotate(-25.f / 180 * PI * (cos(2 * PI * value) - 3) / 4);
	}
}

void HandWaveAnimation::onCompleted()
{
	Animation::onCompleted();
	human->onHandWaveAnimationCompleted(left);
}

}
