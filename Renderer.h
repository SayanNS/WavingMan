//
// Created by sayan on 05.05.2022.
//

#ifndef CONNECTIVEGAMES_RENDERER_H
#define CONNECTIVEGAMES_RENDERER_H

#include "Matrix3x3.h"

bool init_shaders_and_vertexes();

void draw_ellipse(Matrix3x3 &model, Matrix3x3 &projection);

void draw_trapezium(Matrix3x3 &model, Matrix3x3 &projection, float a, float b);


#endif //CONNECTIVEGAMES_RENDERER_H
