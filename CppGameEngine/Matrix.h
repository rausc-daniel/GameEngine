#pragma once

#include "Vector3.h"

struct Matrix {
    float m[16];

    Matrix();

    Matrix(float v00, float v01, float v02, float v03,
           float v10, float v11, float v12, float v13,
           float v20, float v21, float v22, float v23,
           float v30, float v31, float v32, float v33);

    Matrix operator*(const Matrix &mat) const;

    Vector3 operator*(const Vector3 &v) const;

    Matrix &Translate(const Vector3 &v);

    Matrix &Scale(const Vector3 &v);

    Matrix &RotateX(float ang);

    Matrix &RotateY(float ang);

    Matrix &RotateZ(float ang);

    Matrix &Rotate(const Vector3 &axis, float ang);

    Matrix Transpose() const;

    float Determinant() const;

    Matrix Inverse() const;

    static Matrix Frustum(float left, float right, float bottom, float top, float near, float far);

    static Matrix Perspective(float fovy, float aspect, float near, float far);

    static Matrix Ortho(float left, float right, float bottom, float top, float near, float far);

    static Matrix LookAt(const Vector3 &eye, const Vector3 &center, const Vector3 &up);

    static Vector3 UnProject(const Vector3 &vec, const Matrix &view, const Matrix &proj, const float viewport[]);

    static Vector3 Project(const Vector3 &vec, const Matrix &view, const Matrix &proj, const float viewport[]);

    std::string ToString() const;
};
