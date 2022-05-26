//
// Created by sayan on 13.05.2022.
//

#include "Matrix3x3.h"

//#define first scale_matrix
//#define second rotate_matrix
//#define third translate_matrix

//Matrix3x3::Matrix3x3()
//{
//	for (int i = 0; i < 3; i++) {
//		for (int j = 0; j < 3; j++) {
//			this->array[i][j] = 0;
//		}
//	}
//}

Matrix3x3 Matrix3x3::operator*(Matrix3x3 multiplier) const
{
	Matrix3x3 model;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			model.array[i][j] = 0;
			for (int k = 0; k < 3; k++) {
				model.array[i][j] += this->array[i][k] * multiplier.array[k][j];
			}
		}
	}

	return model;
}

Matrix3x3::Matrix3x3(frame frame)
{
	array[0][0] = frame.scale.x * cos(frame.angle);
	array[0][1] = -(frame.scale.x * sin(frame.angle));
	array[0][2] = frame.translation.x;
	array[1][0] = frame.scale.y * sin(frame.angle);
	array[1][1] = frame.scale.y * cos(frame.angle);
	array[1][2] = frame.translation.y;
	array[2][0] = 0;
	array[2][1] = 0;
	array[2][2] = 1;
}

Matrix3x3::Matrix3x3()
{
}

Matrix3x3::Matrix3x3(const float *array)
{
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			this->array[i][j] = array[i * 3 + j];
		}
	}
}

const float *Matrix3x3::getArray() const
{
	return &this->array[0][0];
}
