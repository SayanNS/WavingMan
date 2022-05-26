//
// Created by sayan on 13.05.2022.
//

#ifndef CONNECTIVEGAMES_MATRIX3X3_H
#define CONNECTIVEGAMES_MATRIX3X3_H

#include "frame_struct.h"
#include <cmath>

class Matrix3x3
{
public:
	explicit Matrix3x3(const float array[9]);
	explicit Matrix3x3(frame_struct frame);

	Matrix3x3 operator*(Matrix3x3 model) const;
	const float *getArray() const;
//	void operator*=(Matrix3x3 model);
private:
	Matrix3x3();
	float array[3][3];
};


#endif //CONNECTIVEGAMES_MATRIX3X3_H
