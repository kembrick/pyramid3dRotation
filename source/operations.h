#ifndef PYRAMID3D_OPERATIONS_H
#define PYRAMID3D_OPERATIONS_H

#include <cmath>

struct matrix {
    double m[3][3];
    matrix& operator=(matrix A) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                m[i][j] = A.m[i][j];
            }
        }
        return *this;
    }
};

struct quaternion {
    double r, i, j, k;
};

struct vector {
    double x, y, z;
};

const matrix zero = {0, 0, 0, 0, 0, 0, 0, 0, 0};
matrix iInv = zero;

matrix matrix2Multi(matrix A, matrix B) {
    matrix mul{};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mul.m[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                mul.m[i][j] += A.m[i][k] * B.m[k][j];
            }
        }
    }
    return mul;
}

vector matrix2MultiVector(matrix A, vector v) {
    vector vec{};
    vec.x = A.m[0][0] * v.x + A.m[0][1] * v.y + A.m[0][2] * v.z;
    vec.y = A.m[1][0] * v.x + A.m[1][1] * v.y + A.m[1][2] * v.z;
    vec.z = A.m[2][0] * v.x + A.m[2][1] * v.y + A.m[2][2] * v.z;
    return vec;
}

matrix transpose(matrix A) {
    matrix transpose{};
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            transpose.m[i][j] = A.m[j][i];
        }
    }
    return transpose;
}

matrix quaternion2Matrix(const quaternion& q) {
    matrix m{};
    m.m[0][0] = 1 - 2 * q.j * q.j - 2 * q.k * q.k;
    m.m[0][1] = 2 * q.i * q.j - 2 * q.r * q.k;
    m.m[0][2] = 2 * q.i * q.k + 2 * q.r * q.j;
    m.m[1][0] = 2 * q.i * q.j + 2 * q.r * q.k;
    m.m[1][1] = 1 - 2 * q.i * q.i - 2 * q.k * q.k;
    m.m[1][2] = 2 * q.j * q.k - 2 * q.r * q.i;
    m.m[2][0] = 2 * q.i * q.k - 2 * q.r * q.j;
    m.m[2][1] = 2 * q.j * q.k + 2 * q.r * q.i;
    m.m[2][2] = 1 - 2 * q.i * q.i - 2 * q.j * q.j;
    return m;
}

quaternion quaternion2MultiQuaternion(const quaternion& q1, const quaternion& q2) {
    quaternion q{};
    q.r = q1.r * q2.r - q1.i * q2.i - q1.j * q2.j - q1.k * q2.k;
    q.i = q1.r * q2.i + q1.i * q2.r + q1.j * q2.k - q1.k * q2.j;
    q.j = q1.r * q2.j - q1.i * q2.k + q1.j * q2.r + q1.k * q2.i;
    q.k = q1.r * q2.k + q1.i * q2.j - q1.j * q2.i + q1.k * q2.r;
    return q;
}

quaternion normalize(const quaternion& q) {
    quaternion qn = q;
    double len = sqrt(q.r * q.r + q.i * q.i + q.j * q.j + q.k * q.k);
    if (len != 0) {
        qn.r = q.r / len;
        qn.i = q.i / len;
        qn.j = q.j / len;
        qn.k = q.k / len;
    }
    return qn;
}

double rad2Deg(double rad) {
    return rad * 180 / M_PI;
}


#endif //PYRAMID3D_OPERATIONS_H