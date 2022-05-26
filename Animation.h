//
// Created by sayan on 25.05.2022.
//

#ifndef CONNECTIVEGAMES_ANIMATION_H
#define CONNECTIVEGAMES_ANIMATION_H


enum class State
{
	PLAYING,
	REVERTING,
	COMPLETED,
	REVERTED
};

class Animation
{
public:
	Animation(float duration);

	void start();
	void revert();

	void update(float deltaTime);

	virtual void onUpdate(float value) = 0;
	virtual void onCompleted();
	virtual void onReverted();

private:
	State state;

	float current_time;
	float duration;
};


#endif //CONNECTIVEGAMES_ANIMATION_H
