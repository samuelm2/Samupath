#pragma once
#include "glm/glm.hpp"
#define Point3D glm::dvec3
#define Point2D glm::dvec2
#define Direction glm::dvec3
#define RGBColor glm::vec3

const float MAX_FLOAT = 1.0e+10;

const RGBColor zero = RGBColor(0., 0., 0.);
const RGBColor one = RGBColor(1., 1., 1.);

const double MAX_DOUBLE = 1.0e+100;
const double TINY_DOUBLE = 0.001;
const int MAX_DEPTH = 5;