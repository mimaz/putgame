/*
 * Mieszko Mazurek <mimaz@gmx.com> 
 * 2018
 */

#include <algorithm>
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <typeindex>
#include <memory>
#include <limits>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>

#include <cassert>
#include <cstdlib>
#include <cmath>

#define GLFW_INCLUDE_ES2
#include <GLFW/glfw3.h>

constexpr auto PI = static_cast<float>(M_PI);
