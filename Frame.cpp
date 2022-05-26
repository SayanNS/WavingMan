//
// Created by sayan on 02.05.2022.
//

#include "Frame.h"


Frame::Frame() : frame({1, 1, 0, 0, 0})
{
}

Frame::Frame(struct frame_struct frame) : frame(frame)
{
}

FrameGroup::FrameGroup() : Frame()
{
}

FrameGroup::FrameGroup(struct frame_struct frame) : Frame(frame)
{
}

void Frame::move(Vector2 position)
{
	this->frame.translation = position;
}

void Frame::scale(Vector2 scale)
{
	this->frame.scale = scale;
}

void Frame::rotate(float angle)
{
	this->frame.angle = angle;
}

void FrameGroup::addChild(Drawable *child)
{
	children.push_back(child);
}

void FrameGroup::onDraw(Matrix3x3 &parentModel)
{
	Matrix3x3 model = parentModel * Matrix3x3(frame);

	for (Drawable *child : children) {
		child->onDraw(model);
	}
}
