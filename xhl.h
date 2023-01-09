#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <vector>
#include <map>

using namespace std;
using namespace glm;

#define print(x) cout << x << endl
#define len(x) sizeof(x)/sizeof(x[0])
#define type(x) typeid(x).name()
//#define printV3(x) cout<<"("<<x[0]<<","<<x[1]<<","<<x[2]<<")"
//#define printV2(x) cout<<"("<<x[0]<<","<<x[1]<<")"
#define printV3(x) cout<<x[0]<<","<<x[1]<<","<<x[2]
#define printV2(x) cout<<x[0]<<","<<x[1]
#define printCol3(x) cout<<"("<<x.r<<","<<x.g<<","<<x.b<<")"
#define aiVec3(x) vec3(x[0],x[1],x[2])
#define aiVec2(x) vec2(x[0],x[1])

#define print4x4(x) cout<<"("<<node->mTransformation.a1 << "," << node->mTransformation.a2 << "," << node->mTransformation.a3 << "," << node->mTransformation.a4<<")\n"<<"("<<node->mTransformation.b1 << "," << node->mTransformation.b2 << "," << node->mTransformation.b3 << "," << node->mTransformation.b4<<")\n"<<"("<<node->mTransformation.c1 << "," << node->mTransformation.c2 << "," << node->mTransformation.c3 << "," << node->mTransformation.c4<<")\n"<<"("<<node->mTransformation.d1 << "," << node->mTransformation.d2 << "," << node->mTransformation.d3 << "," << node->mTransformation.d4<<")\n"