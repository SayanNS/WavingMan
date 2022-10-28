//
// Created by sayan on 02.05.2022.
//

#ifndef CONNECTIVEGAMES_CONTAINER_H
#define CONNECTIVEGAMES_CONTAINER_H

#include "frame_struct.h"
#include "Matrix3x3.h"
#include <vector>


class Frame
{
public:
	virtual void onDraw(Matrix3x3 &model) = 0;

	Frame();
	Frame(struct frame_struct frame);

	void move(Vector2 translate);
	void scale(Vector2 scale);
	void rotate(float angle);

	bool isVisible() const;
	
protected:
	struct frame_struct frame;
	bool visible;
};

class FrameGroup : public Frame
{
public:
	FrameGroup();
	FrameGroup(struct frame_struct frame);

	void addChild(Drawable *child);
	void onDraw(Matrix3x3 &model) override;

private:
	std::vector<Frame *> children;
};


#endif //CONNECTIVEGAMES_FRAME_STRUCT_H
