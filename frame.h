//
// Created by sayan on 28.04.2022.
//

#ifndef CONNECTIVEGAMES_FRAME_H
#define CONNECTIVEGAMES_FRAME_H


struct Vector2
{
	float x;
	float y;
};

struct frame
{
	Vector2 scale;
	float angle;
	Vector2 translation;
};


#endif //CONNECTIVEGAMES_FRAME_H
