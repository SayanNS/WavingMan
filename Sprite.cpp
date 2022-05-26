//
// Created by sayan on 24.05.2022.
//

#include "Sprite.h"
#include "Renderer.h"


Sprite::Sprite(Matrix3x3 &projection) : projection(projection), visible(true)
{
}

void Sprite::setVisibility(bool visible)
{
	this->visible = visible;
}

Ellipse::Ellipse(Matrix3x3 &projection, float x, float y, float x_radius, float y_radius)
	: Sprite(projection)
{
	this->frame = {x_radius, y_radius, 0, x, y};
}

void Ellipse::onDraw(Matrix3x3 &parentModel)
{
	if (visible) {
		Matrix3x3 model = parentModel * Matrix3x3(frame);

		draw_ellipse(model, projection);
	}
}

Trapezium::Trapezium(Matrix3x3 &projection, float x, float y, float top_width, float bottom_width, float height)
	: Sprite(projection)
{
	if (top_width == bottom_width) {
		this->frame = {top_width, height, 0, x, y};
		a = 0;
		b = -1;
	} else if (top_width > bottom_width) {
		this->frame = {top_width, height, 0, x, y};
		float ratio = bottom_width / top_width;
		a = 2 / (ratio - 1);
		b = 1 + a;
	} else {
		this->frame = {bottom_width, height, 3.1416, x, y};
		float ratio = top_width / bottom_width;
		a = 2 / (ratio - 1);
		b = 1 + a;
	}
}

void Trapezium::onDraw(Matrix3x3 &parentModel)
{
	if (visible) {
		Matrix3x3 model = parentModel * Matrix3x3(frame);

		draw_trapezium(model, projection, a, b);
	}
}
