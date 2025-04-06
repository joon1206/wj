#pragma once

typedef struct { float x, y, z; } Vec3;

Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_norm(Vec3 v);
float vec3_dot(Vec3 a, Vec3 b);
