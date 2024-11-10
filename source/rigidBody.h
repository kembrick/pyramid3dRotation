#ifndef PYRAMID3D_SHAPE_H
#define PYRAMID3D_SHAPE_H

#include <cmath>
#include "operations.h"

const float a = 20, // side
            h = 30, // height
            deltaTime = 0.001; // rotation frequency

typedef struct RigidBody {
    matrix R;
    vector r, l, L;
    quaternion q;
} RigidBody;

RigidBody rb;

RigidBody f() {
    RigidBody result;
    result.r.x = rb.l.x;
    result.r.y = rb.l.y;
    result.r.z = rb.l.z;
    rb.R = quaternion2Matrix(rb.q);
    vector omega = matrix2MultiVector(matrix2Multi(matrix2Multi(rb.R, iInv), transpose(rb.R)), rb.L);
    result.q = quaternion2MultiQuaternion({0, omega.x, omega.y, omega.z}, rb.q);
    result.q.r *= 0.5, result.q.i *= 0.5, result.q.j *= 0.5, result.q.k *= 0.5;
    result.l = vector{0, 0, 0};
    result.L = vector{0, 0, 0};
    return result;
}

RigidBody add(RigidBody r1, RigidBody r2) {
    RigidBody result;
    result.r.x = r1.r.x + r2.r.x;
    result.r.y = r1.r.y + r2.r.y;
    result.r.z = r1.r.z + r2.r.z;
    result.q.r = r1.q.r + r2.q.r;
    result.q.i = r1.q.i + r2.q.i;
    result.q.j = r1.q.j + r2.q.j;
    result.q.k = r1.q.k + r2.q.k;
    result.l.x = r1.l.x + r2.l.x;
    result.l.y = r1.l.y + r2.l.y;
    result.l.z = r1.l.z + r2.l.z;
    result.L.x = r1.L.x + r2.L.x;
    result.L.y = r1.L.y + r2.L.y;
    result.L.z = r1.L.z + r2.L.z;
    return result;
}

RigidBody multiply(RigidBody r, double num) {
    RigidBody result = r;
    result.r.x *= num;
    result.r.y *= num;
    result.r.z *= num;
    result.q.r *= num;
    result.q.i *= num;
    result.q.j *= num;
    result.q.k *= num;
    result.l.x *= num;
    result.l.y *= num;
    result.l.z *= num;
    result.L.x *= num;
    result.L.y *= num;
    result.L.z *= num;
    return result;
}

RigidBody calculateRotation() {
    RigidBody k, k3 = f();
    rb = add(rb, add(multiply(k, deltaTime), add(multiply(k, deltaTime), add(multiply(k3, deltaTime), multiply(k, deltaTime)))));
    rb.q = normalize(rb.q);
    rb.R = quaternion2Matrix(rb.q);
    return rb;
}

void init() {
    iInv.m[0][0] = 1 / ((a * a / 40 +  h * h * 3 / 80));
    iInv.m[1][1] = 1 / ((a * a / 40 +  h * h * 3 / 80));
    iInv.m[2][2] = 20 / (a * a);
    rb.q = {cos(45), 0.0, 0.75, 0};
    rb.R = quaternion2Matrix(rb.q);
    rb.L = vector{100, 25, 100};
}

#endif //PYRAMID3D_SHAPE_H