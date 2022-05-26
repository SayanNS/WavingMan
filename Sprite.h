//
// Created by sayan on 24.05.2022.
//

#ifndef CONNECTIVEGAMES_SPRITE_H
#define CONNECTIVEGAMES_SPRITE_H

#include "Frame.h"


class Sprite : public Frame
{
public:
	explicit Sprite(Matrix3x3 &projection);

	void setVisibility(bool visible);

protected:
	bool visible;
	Matrix3x3 &projection;
};

class Ellipse : public Sprite
{
public:
	Ellipse(Matrix3x3 &projection, float x, float y, float x_radius, float y_radius);

	void onDraw(Matrix3x3 &model) override;
};

class Trapezium : public Sprite
{
public:
	Trapezium(Matrix3x3 &projection, float x, float y, float top_width, float bottom_width, float height);

	void onDraw(Matrix3x3 &model) override;

private:
	float a, b;
};


#endif //CONNECTIVEGAMES_SPRITE_H
