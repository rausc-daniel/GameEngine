#include "Matrix.h"

Matrix::Matrix() {
    *this = Matrix(
            1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    );
}

Matrix::Matrix(float v00, float v01, float v02, float v03, float v10, float v11, float v12, float v13, float v20,
               float v21, float v22, float v23, float v30, float v31, float v32, float v33) {
    m[0] = v00;
    m[4] = v01;
    m[8] = v02;
    m[12] = v03;
    m[1] = v10;
    m[5] = v11;
    m[9] = v12;
    m[13] = v13;
    m[2] = v20;
    m[6] = v21;
    m[10] = v22;
    m[14] = v23;
    m[3] = v30;
    m[7] = v31;
    m[11] = v32;
    m[15] = v33;
}

Matrix Matrix::operator*(const Matrix &mat) const {
    return {
            m[0] * mat.m[0] + m[4] * mat.m[1] + m[8] * mat.m[2] + m[12] * mat.m[3],
            m[0] * mat.m[4] + m[4] * mat.m[5] + m[8] * mat.m[6] + m[12] * mat.m[7],
            m[0] * mat.m[8] + m[4] * mat.m[9] + m[8] * mat.m[10] + m[12] * mat.m[11],
            m[0] * mat.m[12] + m[4] * mat.m[13] + m[8] * mat.m[14] + m[12] * mat.m[15],
            m[1] * mat.m[0] + m[5] * mat.m[1] + m[9] * mat.m[2] + m[13] * mat.m[3],
            m[1] * mat.m[4] + m[5] * mat.m[5] + m[9] * mat.m[6] + m[13] * mat.m[7],
            m[1] * mat.m[8] + m[5] * mat.m[9] + m[9] * mat.m[10] + m[13] * mat.m[11],
            m[1] * mat.m[12] + m[5] * mat.m[13] + m[9] * mat.m[14] + m[13] * mat.m[15],
            m[2] * mat.m[0] + m[6] * mat.m[1] + m[10] * mat.m[2] + m[14] * mat.m[3],
            m[2] * mat.m[4] + m[6] * mat.m[5] + m[10] * mat.m[6] + m[14] * mat.m[7],
            m[2] * mat.m[8] + m[6] * mat.m[9] + m[10] * mat.m[10] + m[14] * mat.m[11],
            m[2] * mat.m[12] + m[6] * mat.m[13] + m[10] * mat.m[14] + m[14] * mat.m[15],
            m[3] * mat.m[0] + m[7] * mat.m[1] + m[11] * mat.m[2] + m[15] * mat.m[3],
            m[3] * mat.m[4] + m[7] * mat.m[5] + m[11] * mat.m[6] + m[15] * mat.m[7],
            m[3] * mat.m[8] + m[7] * mat.m[9] + m[11] * mat.m[10] + m[15] * mat.m[11],
            m[3] * mat.m[12] + m[7] * mat.m[13] + m[11] * mat.m[14] + m[15] * mat.m[15]
    };
}

Vector3 Matrix::operator*(const Vector3 &v) const {
    return {
            m[0] * v.x + m[4] * v.y + m[8] * v.z + m[12],
            m[1] * v.x + m[5] * v.y + m[9] * v.z + m[13],
            m[2] * v.x + m[6] * v.y + m[10] * v.z + m[14]
    };
}

Matrix &Matrix::Translate(const Vector3 &v) {
    return *this = *this * Matrix(
            1, 0, 0, v.x,
            0, 1, 0, v.y,
            0, 0, 1, v.z,
            0, 0, 0, 1
    );
}

Matrix &Matrix::Scale(const Vector3 &v) {
    return *this = *this * Matrix(
            v.x, 0, 0, 0,
            0, v.y, 0, 0,
            0, 0, v.z, 0,
            0, 0, 0, 1
    );
}

Matrix &Matrix::RotateX(float ang) {
    return *this = *this * Matrix(
            1, 0, 0, 0,
            0, std::cos(ang), -std::sin(ang), 0,
            0, std::sin(ang), std::cos(ang), 0,
            0, 0, 0, 1
    );
}

Matrix &Matrix::RotateY(float ang) {
    return *this = *this * Matrix(
            std::cos(ang), 0, std::sin(ang), 0,
            0, 1, 0, 0,
            -std::sin(ang), 0, std::cos(ang), 0,
            0, 0, 0, 1
    );
}

Matrix &Matrix::RotateZ(float ang) {
    return *this = *this * Matrix(
            std::cos(ang), -std::sin(ang), 0, 0,
            std::sin(ang), std::cos(ang), 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1
    );
}

Matrix &Matrix::Rotate(const Vector3 &axis, float ang) {
    float s = std::sin(ang);
    float c = std::cos(ang);
    float t = 1 - c;
    Vector3 a = axis.Normal();

    return *this = *this * Matrix(
            a.x * a.x * t + c, a.x * a.y * t - a.z * s, a.x * a.z * t + a.y * s, 0,
            a.y * a.x * t + a.z * s, a.y * a.y * t + c, a.y * a.z * t - a.x * s, 0,
            a.z * a.x * t - a.y * s, a.z * a.y * t + a.x * s, a.z * a.z * t + c, 0,
            0, 0, 0, 1
    );
}

Matrix Matrix::Transpose() const {
    Matrix res;

    res.m[0] = m[0];
    res.m[1] = m[4];
    res.m[2] = m[8];
    res.m[3] = m[12];

    res.m[4] = m[1];
    res.m[5] = m[5];
    res.m[6] = m[9];
    res.m[7] = m[13];

    res.m[8] = m[2];
    res.m[9] = m[6];
    res.m[10] = m[10];
    res.m[11] = m[14];

    res.m[12] = m[3];
    res.m[13] = m[7];
    res.m[14] = m[11];
    res.m[15] = m[15];

    return res;
}

float Matrix::Determinant() const {
    return m[12] * m[9] * m[6] * m[3] - m[8] * m[13] * m[6] * m[3] - m[12] * m[5] * m[10] * m[3] +
           m[4] * m[13] * m[10] * m[3] +
           m[8] * m[5] * m[14] * m[3] - m[4] * m[9] * m[14] * m[3] - m[12] * m[9] * m[2] * m[7] +
           m[8] * m[13] * m[2] * m[7] +
           m[12] * m[1] * m[10] * m[7] - m[0] * m[13] * m[10] * m[7] - m[8] * m[1] * m[14] * m[7] +
           m[0] * m[9] * m[14] * m[7] +
           m[12] * m[5] * m[2] * m[11] - m[4] * m[13] * m[2] * m[11] - m[12] * m[1] * m[6] * m[11] +
           m[0] * m[13] * m[6] * m[11] +
           m[4] * m[1] * m[14] * m[11] - m[0] * m[5] * m[14] * m[11] - m[8] * m[5] * m[2] * m[15] +
           m[4] * m[9] * m[2] * m[15] +
           m[8] * m[1] * m[6] * m[15] - m[0] * m[9] * m[6] * m[15] - m[4] * m[1] * m[10] * m[15] +
           m[0] * m[5] * m[10] * m[15];
}

Matrix Matrix::Inverse() const {
    float det = Determinant();

    Matrix res;

    float t0 = m[0] * m[5] - m[1] * m[4];
    float t1 = m[0] * m[6] - m[2] * m[4];
    float t2 = m[0] * m[7] - m[3] * m[4];
    float t3 = m[1] * m[6] - m[2] * m[5];
    float t4 = m[1] * m[7] - m[3] * m[5];
    float t5 = m[2] * m[7] - m[3] * m[6];
    float t6 = m[8] * m[13] - m[9] * m[12];
    float t7 = m[8] * m[14] - m[10] * m[12];
    float t8 = m[8] * m[15] - m[11] * m[12];
    float t9 = m[9] * m[14] - m[10] * m[13];
    float t10 = m[9] * m[15] - m[11] * m[13];
    float t11 = m[10] * m[15] - m[11] * m[14];

    res.m[0] = (m[5] * t11 - m[6] * t10 + m[7] * t9) / det;
    res.m[1] = (-m[1] * t11 + m[2] * t10 - m[3] * t9) / det;
    res.m[2] = (m[13] * t5 - m[14] * t4 + m[15] * t3) / det;
    res.m[3] = (-m[9] * t5 + m[10] * t4 - m[11] * t3) / det;
    res.m[4] = (-m[4] * t11 + m[6] * t8 - m[7] * t7) / det;
    res.m[5] = (m[0] * t11 - m[2] * t8 + m[3] * t7) / det;
    res.m[6] = (-m[12] * t5 + m[14] * t2 - m[15] * t1) / det;
    res.m[7] = (m[8] * t5 - m[10] * t2 + m[11] * t1) / det;
    res.m[8] = (m[4] * t10 - m[5] * t8 + m[7] * t6) / det;
    res.m[9] = (-m[0] * t10 + m[1] * t8 - m[3] * t6) / det;
    res.m[10] = (m[12] * t4 - m[13] * t2 + m[15] * t0) / det;
    res.m[11] = (-m[8] * t4 + m[9] * t2 - m[11] * t0) / det;
    res.m[12] = (-m[4] * t9 + m[5] * t7 - m[6] * t6) / det;
    res.m[13] = (m[0] * t9 - m[1] * t7 + m[2] * t6) / det;
    res.m[14] = (-m[12] * t3 + m[13] * t1 - m[14] * t0) / det;
    res.m[15] = (m[8] * t3 - m[9] * t1 + m[10] * t0) / det;

    return res;
}

Matrix Matrix::Frustum(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    Matrix res;

    res.m[0] = nearPlane * 2.0f / (right - left);
    res.m[5] = nearPlane * 2.0f / (top - bottom);
    res.m[8] = (right + left) / (right - left);
    res.m[9] = (top + bottom) / (top - bottom);
    res.m[10] = (-farPlane - nearPlane) / (farPlane - nearPlane);
    res.m[11] = -1;
    res.m[14] = -2.0f * farPlane * nearPlane / (farPlane - nearPlane);
    res.m[15] = 0;

    return res;
}

Matrix Matrix::Perspective(float fovy, float aspect, float nearPlane, float farPlane) {
    float top = nearPlane * std::tan(fovy / 2.0f);
    float right = top * aspect;
    return Frustum(-right, right, -top, top, nearPlane, farPlane);
}

Matrix Matrix::Ortho(float left, float right, float bottom, float top, float nearPlane, float farPlane) {
    Matrix res;

    res.m[0] = 2 / (right - left);
    res.m[5] = 2 / (top - bottom);
    res.m[10] = -2 / (farPlane - nearPlane);
    res.m[12] = -(left + right) / (right - left);
    res.m[13] = -(top + bottom) / (top - bottom);
    res.m[14] = -(farPlane + nearPlane) / (farPlane - nearPlane);

    return res;
}

Matrix Matrix::LookAt(const Vector3 &eye, const Vector3 &center, const Vector3 &up) {
    Matrix res;

    Vector3 Z = (eye - center).Normal();

    Vector3 X = Vector3(
            up.y * Z.z - up.z * Z.y,
            up.z * Z.x - up.x * Z.z,
            up.x * Z.y - up.y * Z.x
    ).Normal();

    Vector3 Y = Vector3(
            Z.y * X.z - Z.z * X.y,
            Z.z * X.x - Z.x * X.z,
            Z.x * X.y - Z.y * X.x
    ).Normal();

    res.m[0] = X.x;
    res.m[1] = Y.x;
    res.m[2] = Z.x;
    res.m[4] = X.y;
    res.m[5] = Y.y;
    res.m[6] = Z.y;
    res.m[8] = X.z;
    res.m[9] = Y.z;
    res.m[10] = Z.z;
    res.m[12] = -X.DotProduct(eye);
    res.m[13] = -Y.DotProduct(eye);
    res.m[14] = -Z.DotProduct(eye);

    return res;
}

Vector3 Matrix::UnProject(const Vector3 &vec, const Matrix &view, const Matrix &proj, const float viewport[]) {
    Matrix inv = (proj * view).Inverse();
    Vector3 v(
            (vec.x - viewport[0]) * 2.0f / viewport[2] - 1.0f,
            (vec.y - viewport[1]) * 2.0f / viewport[3] - 1.0f,
            2.0f * vec.z - 1.0f
    );

    Vector3 res = inv * v;
    float w = inv.m[3] * v.x + inv.m[7] * v.y + inv.m[11] * v.z + inv.m[15];

    return res / w;
}

Vector3 Matrix::Project(const Vector3 &vec, const Matrix &view, const Matrix &proj, const float viewport[]) {
    Matrix trans = proj * view;
    Vector3 v = trans * vec;

    float w = trans.m[3] * vec.x + trans.m[7] * vec.y + trans.m[11] * vec.z + trans.m[15];
    v = v / w;

    return {
            viewport[0] + viewport[2] * (v.x + 1.0f) / 2.0f,
            viewport[1] + viewport[3] * (v.y + 1.0f) / 2.0f,
            (v.z + 1.0f) / 2.0f
    };
}

std::string Matrix::ToString() const {
    std::ostringstream result;
    result << std::endl << "(" <<
           m[0] << ", " << m[1] << ", " << m[2] << ", " << m[3] << "," << std::endl <<
           m[4] << ", " << m[5] << ", " << m[6] << ", " << m[7] << "," << std::endl <<
           m[8] << ", " << m[9] << ", " << m[10] << ", " << m[11] << "," << std::endl <<
           m[12] << ", " << m[13] << ", " << m[14] << ", " << m[15] << "," << ")";
    return result.str();
}
