long mono_address = 0;
using namespace std;std::string utf16le_to_utf8(const std::u16string &u16str) {
    if (u16str.empty()) {
        return std::string();
    }
    const char16_t *p = u16str.data();
    std::u16string::size_type len = u16str.length();
    if (p[0] == 0xFEFF) {
        p += 1;
        len -= 1;
    }
    std::string u8str;
    u8str.reserve(len * 3);
    char16_t u16char;
    for (std::u16string::size_type i = 0; i < len; ++i) {
        u16char = p[i];
        if (u16char < 0x0080) {
            u8str.push_back((char) (u16char & 0x00FF));
            continue;
        }
        if (u16char >= 0x0080 && u16char <= 0x07FF) {
            u8str.push_back((char) (((u16char >> 6) & 0x1F) | 0xC0));
            u8str.push_back((char) ((u16char & 0x3F) | 0x80));
            continue;
        }
        if (u16char >= 0xD800 && u16char <= 0xDBFF) {
            uint32_t highSur = u16char;
            uint32_t lowSur = p[++i];
            uint32_t codePoint = highSur - 0xD800;
            codePoint <<= 10;
            codePoint |= lowSur - 0xDC00;
            codePoint += 0x10000;
            u8str.push_back((char) ((codePoint >> 18) | 0xF0));
            u8str.push_back((char) (((codePoint >> 12) & 0x3F) | 0x80));
            u8str.push_back((char) (((codePoint >> 06) & 0x3F) | 0x80));
            u8str.push_back((char) ((codePoint & 0x3F) | 0x80));
            continue;
        }
        {
            u8str.push_back((char) (((u16char >> 12) & 0x0F) | 0xE0));
            u8str.push_back((char) (((u16char >> 6) & 0x3F) | 0x80));
            u8str.push_back((char) ((u16char & 0x3F) | 0x80));
            continue;
        }
    }
    return u8str;
}

#include <math.h>

#include "../ImGui/imgui.h"
#include "../ImGui/imgui_internal.h"


	
static Color FromHSB(float hue, float saturation, float brightness)
{
float h = hue == 1.0f ? 0 : hue * 6.0f;
float f = h - (int)h;
float p = brightness * (1.0f - saturation);
float q = brightness * (1.0f - saturation * f);
float t = brightness * (1.0f - (saturation * (1.0f - f)));
if (h < 1)
{
return Color(
(unsigned char)(brightness * 255),
(unsigned char)(t * 255),
(unsigned char)(p * 255)
);
}
else if (h < 2)
{
return Color(
(unsigned char)(q * 255),
(unsigned char)(brightness * 255),
(unsigned char)(p * 255)
);
}
else if (h < 3)
{
return Color(
(unsigned char)(p * 255),
(unsigned char)(brightness * 255),
(unsigned char)(t * 255)
);
}
else if (h < 4)
{
return Color(
(unsigned char)(p * 255),
(unsigned char)(q * 255),
(unsigned char)(brightness * 255)
);
}
else if (h < 5)
{
return Color(
(unsigned char)(t * 255),
(unsigned char)(p * 255),
(unsigned char)(brightness * 255)
);
}
else
{
return Color(
(unsigned char)(brightness * 255),
(unsigned char)(p * 255),
(unsigned char)(q * 255));
}




#pragma once

#define _USE_MATH_DEFINES
#include <math.h>


struct Vec3
{
    float x;
    float y;
    float z;

    Vec3();
    Vec3(float x, float y, float z);
    ~Vec3();


    /**
     * Constructors.
     */


    /**
     * Constants for common vectors.
     */
    static inline Vec3 zero();
    static inline Vec3 One();
    static inline Vec3 Right();
    static inline Vec3 Left();
    static inline Vec3 Up();
    static inline Vec3 Down();
    static inline Vec3 Forward();
    static inline Vec3 Backward();


    /**
     * Returns the angle between two vectors in radians.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A scalar value.
     */
    static inline float Angle(Vec3 a, Vec3 b);

    /**
     * Returns a vector with its magnitude clamped to maxLength.
     * @param vector: The target vector.
     * @param maxLength: The maximum length of the return vector.
     * @return: A new vector.
     */
    static inline Vec3 ClampMagnitude(Vec3 vector, float maxLength);

    /**
     * Returns the component of a in the direction of b (scalar projection).
     * @param a: The target vector.
     * @param b: The vector being compared against.
     * @return: A scalar value.
     */
    static inline float Component(Vec3 a, Vec3 b);

    /**
     * Returns the cross product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A new vector.
     */
    static inline Vec3 Cross(Vec3 lhs, Vec3 rhs);

    /**
     * Returns the distance between a and b.
     * @param a: The first point.
     * @param b: The second point.
     * @return: A scalar value.
     */
    static inline float Distance(Vec3 a, Vec3 b);

    static inline char ToChar(Vec3 a);

    /**
     * Returns the dot product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A scalar value.
     */
    static inline float Dot(Vec3 lhs, Vec3 rhs);

    /**
     * Converts a spherical representation of a vector into cartesian
     * coordinates.
     * This uses the ISO convention (radius r, inclination theta, azimuth phi).
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the xy plane from the x axis.
     * @param phi: The angle from the positive z axis to the vector.
     * @return: A new vector.
     */
    static inline Vec3 FromSpherical(float rad, float theta, float phi);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line. The vector is clamped to never go beyond the end points.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1].
     * @return: A new vector.
     */
    static inline Vec3 Lerp(Vec3 a, Vec3 b, float t);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1] (no actual bounds).
     * @return: A new vector.
     */
    static inline Vec3 LerpUnclamped(Vec3 a, Vec3 b, float t);

    /**
     * Returns the magnitude of a vector.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float Magnitude(Vec3 v);

    /**
     * Returns a vector made from the largest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vec3 Max(Vec3 a, Vec3 b);

    /**
     * Returns a vector made from the smallest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vec3 Min(Vec3 a, Vec3 b);

    /**
     * Returns a vector "maxDistanceDelta" units closer to the target. This
     * interpolation is in a straight line, and will not overshoot.
     * @param current: The current position.
     * @param target: The destination position.
     * @param maxDistanceDelta: The maximum distance to move.
     * @return: A new vector.
     */
    static inline Vec3 MoveTowards(Vec3 current, Vec3 target,
                                   float maxDistanceDelta);

    /**
     * Returns a new vector with magnitude of one.
     * @param v: The vector in question.
     * @return: A new vector.
     */
    static inline Vec3 Normalized(Vec3 v);

    /**
     * Returns an arbitrary vector orthogonal to the input.
     * This vector is not normalized.
     * @param v: The input vector.
     * @return: A new vector.
     */
    static inline Vec3 Orthogonal(Vec3 v);

    /**
     * Creates a new coordinate system out of the three vectors.
     * Normalizes "normal", normalizes "tangent" and makes it orthogonal to
     * "normal" and normalizes "binormal" and makes it orthogonal to both
     * "normal" and "tangent".
     * @param normal: A reference to the first axis vector.
     * @param tangent: A reference to the second axis vector.
     * @param binormal: A reference to the third axis vector.
     */
    static inline void OrthoNormalize(Vec3 &normal, Vec3 &tangent,
                                      Vec3 &binormal);

    /**
     * Returns the vector projection of a onto b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vec3 Project(Vec3 a, Vec3 b);

    /**
     * Returns a vector projected onto a plane orthogonal to "planeNormal".
     * This can be visualized as the shadow of the vector onto the plane, if
     * the light source were in the direction of the plane normal.
     * @param vector: The vector to project.
     * @param planeNormal: The normal of the plane onto which to project.
     * @param: A new vector.
     */
    static inline Vec3 ProjectOnPlane(Vec3 vector, Vec3 planeNormal);

    /**
     * Returns a vector reflected off the plane orthogonal to the normal.
     * The input vector is pointed inward, at the plane, and the return vector
     * is pointed outward from the plane, like a beam of light hitting and then
     * reflecting off a mirror.
     * @param vector: The vector traveling inward at the plane.
     * @param planeNormal: The normal of the plane off of which to reflect.
     * @return: A new vector pointing outward from the plane.
     */
    static inline Vec3 Reflect(Vec3 vector, Vec3 planeNormal);

    /**
     * Returns the vector rejection of a on b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vec3 Reject(Vec3 a, Vec3 b);

    /**
     * Rotates vector "current" towards vector "target" by "maxRadiansDelta".
     * This treats the vectors as directions and will linearly interpolate
     * between their magnitudes by "maxMagnitudeDelta". This function does not
     * overshoot. If a negative delta is supplied, it will rotate away from
     * "target" until it is pointing the opposite direction, but will not
     * overshoot that either.
     * @param current: The starting direction.
     * @param target: The destination direction.
     * @param maxRadiansDelta: The maximum number of radians to rotate.
     * @param maxMagnitudeDelta: The maximum delta for magnitude interpolation.
     * @return: A new vector.
     */
    static inline Vec3 RotateTowards(Vec3 current, Vec3 target,
                                     float maxRadiansDelta,
                                     float maxMagnitudeDelta);

    /**
     * Multiplies two vectors element-wise.
     * @param a: The lhs of the multiplication.
     * @param b: The rhs of the multiplication.
     * @return: A new vector.
     */
    static inline Vec3 Scale(Vec3 a, Vec3 b);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is clamped to 0 <= t <= 1.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vec3 Slerp(Vec3 a, Vec3 b, float t);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is unclamped.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vec3 SlerpUnclamped(Vec3 a, Vec3 b, float t);

    /**
     * Returns the squared magnitude of a vector.
     * This is useful when comparing relative lengths, where the exact length
     * is not important, and much time can be saved by not calculating the
     * square root.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float SqrMagnitude(Vec3 v);

    /**
     * Calculates the spherical coordinate space representation of a vector.
     * This uses the ISO convention (radius r, inclination theta, azimuth phi).
     * @param vector: The vector to convert.
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the xy plane from the x axis.
     * @param phi: The angle from the positive z axis to the vector.
     */
    static inline void ToSpherical(Vec3 vector, float &rad, float &theta,
                                   float &phi);


    /**
     * Operator overloading.
     */
    inline struct Vec3& operator+=(const float rhs);
    inline struct Vec3& operator-=(const float rhs);
    inline struct Vec3& operator*=(const float rhs);
    inline struct Vec3& operator/=(const float rhs);
    inline struct Vec3& operator+=(const Vec3 rhs);
    inline struct Vec3& operator-=(const Vec3 rhs);
};

inline Vec3 operator-(Vec3 rhs);
inline Vec3 operator+(Vec3 lhs, const float rhs);
inline Vec3 operator-(Vec3 lhs, const float rhs);
inline Vec3 operator*(Vec3 lhs, const float rhs);
inline Vec3 operator/(Vec3 lhs, const float rhs);
inline Vec3 operator+(const float lhs, Vec3 rhs);
inline Vec3 operator-(const float lhs, Vec3 rhs);
inline Vec3 operator*(const float lhs, Vec3 rhs);
inline Vec3 operator/(const float lhs, Vec3 rhs);
inline Vec3 operator+(Vec3 lhs, const Vec3 rhs);
inline Vec3 operator-(Vec3 lhs, const Vec3 rhs);
inline bool operator==(const Vec3 lhs, const Vec3 rhs);
inline bool operator!=(const Vec3 lhs, const Vec3 rhs);



/*******************************************************************************
 * Implementation
 */

Vec3::Vec3() {}
Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}
Vec3::~Vec3() {}


Vec3 Vec3::zero() { return Vec3(0, 0, 0); }
Vec3 Vec3::One() { return Vec3(1, 1, 1); }
Vec3 Vec3::Right() { return Vec3(1, 0, 0); }
Vec3 Vec3::Left() { return Vec3(-1, 0, 0); }
Vec3 Vec3::Up() { return Vec3(0, 1, 0); }
Vec3 Vec3::Down() { return Vec3(0, -1, 0); }
Vec3 Vec3::Forward() { return Vec3(0, 0, 1); }
Vec3 Vec3::Backward() { return Vec3(0, 0, -1); }


float Vec3::Angle(Vec3 a, Vec3 b)
{
    float v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

Vec3 Vec3::ClampMagnitude(Vec3 vector, float maxLength)
{
    float length = Magnitude(vector);
    if (length > maxLength)
        vector *= maxLength / length;
    return vector;
}

float Vec3::Component(Vec3 a, Vec3 b)
{
    return Dot(a, b) / Magnitude(b);
}

Vec3 Vec3::Cross(Vec3 lhs, Vec3 rhs)
{
    float x = lhs.y * rhs.z - lhs.z * rhs.y;
    float y = lhs.z * rhs.x - lhs.x * rhs.z;
    float z = lhs.x * rhs.y - lhs.y * rhs.x;
    return Vec3(x, y, z);
}

float Vec3::Distance(Vec3 a, Vec3 b)
{
    return Vec3::Magnitude(a - b);
}

float Vec3::Dot(Vec3 lhs, Vec3 rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vec3 Vec3::FromSpherical(float rad, float theta, float phi)
{
    Vec3 v;
    v.x = rad * sin(theta) * cos(phi);
    v.y = rad * sin(theta) * sin(phi);
    v.z = rad * cos(theta);
    return v;
}

Vec3 Vec3::Lerp(Vec3 a, Vec3 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

Vec3 Vec3::LerpUnclamped(Vec3 a, Vec3 b, float t)
{
    return (b - a) * t + a;
}

float Vec3::Magnitude(Vec3 v)
{
    return sqrt(SqrMagnitude(v));
}

Vec3 Vec3::Max(Vec3 a, Vec3 b)
{
    float x = a.x > b.x ? a.x : b.x;
    float y = a.y > b.y ? a.y : b.y;
    float z = a.z > b.z ? a.z : b.z;
    return Vec3(x, y, z);
}

Vec3 Vec3::Min(Vec3 a, Vec3 b)
{
    float x = a.x > b.x ? b.x : a.x;
    float y = a.y > b.y ? b.y : a.y;
    float z = a.z > b.z ? b.z : a.z;
    return Vec3(x, y, z);
}

Vec3 Vec3::MoveTowards(Vec3 current, Vec3 target,
                       float maxDistanceDelta)
{
    Vec3 d = target - current;
    float m = Magnitude(d);
    if (m < maxDistanceDelta || m == 0)
        return target;
    return current + (d * maxDistanceDelta / m);
}

Vec3 Vec3::Normalized(Vec3 v)
{
    float mag = Magnitude(v);
    if (mag == 0)
        return Vec3::zero();
    return v / mag;
}

Vec3 Vec3::Orthogonal(Vec3 v)
{
    return v.z < v.x ? Vec3(v.y, -v.x, 0) : Vec3(0, -v.z, v.y);
}

void Vec3::OrthoNormalize(Vec3 &normal, Vec3 &tangent,
                          Vec3 &binormal)
{
    normal = Normalized(normal);
    tangent = ProjectOnPlane(tangent, normal);
    tangent = Normalized(tangent);
    binormal = ProjectOnPlane(binormal, tangent);
    binormal = ProjectOnPlane(binormal, normal);
    binormal = Normalized(binormal);
}

Vec3 Vec3::Project(Vec3 a, Vec3 b)
{
    float m = Magnitude(b);
    return Dot(a, b) / (m * m) * b;
}

Vec3 Vec3::ProjectOnPlane(Vec3 vector, Vec3 planeNormal)
{
    return Reject(vector, planeNormal);
}

Vec3 Vec3::Reflect(Vec3 vector, Vec3 planeNormal)
{
    return vector - 2 * Project(vector, planeNormal);
}

Vec3 Vec3::Reject(Vec3 a, Vec3 b)
{
    return a - Project(a, b);
}

Vec3 Vec3::RotateTowards(Vec3 current, Vec3 target,
                         float maxRadiansDelta,
                         float maxMagnitudeDelta)
{
    float magCur = Magnitude(current);
    float magTar = Magnitude(target);
    float newMag = magCur + maxMagnitudeDelta *
                            ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));

    float totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0)
        return Normalized(target) * newMag;
    else if (totalAngle >= M_PI)
        return Normalized(-target) * newMag;

    Vec3 axis = Cross(current, target);
    float magAxis = Magnitude(axis);
    if (magAxis == 0)
        axis = Normalized(Cross(current, current + Vec3(3.95, 5.32, -4.24)));
    else
        axis /= magAxis;
    current = Normalized(current);
    Vec3 newVector = current * cos(maxRadiansDelta) +
                     Cross(axis, current) * sin(maxRadiansDelta);
    return newVector * newMag;
}

Vec3 Vec3::Scale(Vec3 a, Vec3 b)
{
    return Vec3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vec3 Vec3::Slerp(Vec3 a, Vec3 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

Vec3 Vec3::SlerpUnclamped(Vec3 a, Vec3 b, float t)
{
    float magA = Magnitude(a);
    float magB = Magnitude(b);
    a /= magA;
    b /= magB;
    float dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    float theta = acos(dot) * t;
    Vec3 relativeVec = Normalized(b - a * dot);
    Vec3 newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

float Vec3::SqrMagnitude(Vec3 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

void Vec3::ToSpherical(Vec3 vector, float &rad, float &theta,
                       float &phi)
{
    rad = Magnitude(vector);
    float v = vector.z / rad;
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    theta = acos(v);
    phi = atan2(vector.y, vector.x);
}


struct Vec3& Vec3::operator+=(const float rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
}

struct Vec3& Vec3::operator-=(const float rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
    return *this;
}

struct Vec3& Vec3::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

struct Vec3& Vec3::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

struct Vec3& Vec3::operator+=(const Vec3 rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

struct Vec3& Vec3::operator-=(const Vec3 rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}



Vec3 operator-(Vec3 rhs) { return rhs * -1; }
Vec3 operator+(Vec3 lhs, const float rhs) { return lhs += rhs; }
Vec3 operator-(Vec3 lhs, const float rhs) { return lhs -= rhs; }
Vec3 operator*(Vec3 lhs, const float rhs) { return lhs *= rhs; }
Vec3 operator/(Vec3 lhs, const float rhs) { return lhs /= rhs; }
Vec3 operator+(const float lhs, Vec3 rhs) { return rhs += lhs; }
Vec3 operator-(const float lhs, Vec3 rhs) { return rhs -= lhs; }
Vec3 operator*(const float lhs, Vec3 rhs) { return rhs *= lhs; }
Vec3 operator/(const float lhs, Vec3 rhs) { return rhs /= lhs; }
Vec3 operator+(Vec3 lhs, const Vec3 rhs) { return lhs += rhs; }
Vec3 operator-(Vec3 lhs, const Vec3 rhs) { return lhs -= rhs; }

bool operator==(const Vec3 lhs, const Vec3 rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const Vec3 lhs, const Vec3 rhs)
{
    return !(lhs == rhs);
}
#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>
struct Vector3
{
    union
    {
        struct
        {
            float x;
            float y;
            float z;



        };
        ///float data[3];
    };


    /**
     * Constructors.
     */
    inline Vector3();
    inline Vector3(float data[]);
    inline Vector3(float value);
    inline Vector3(float x, float y);
    inline Vector3(float x, float y, float z);

    /**
     * Constants for common vectors.
     */
    static inline Vector3 zero();
    static inline Vector3 One();
    static inline Vector3 Right();
    static inline Vector3 Left();
    static inline Vector3 Up();
    static inline Vector3 Down();
    static inline Vector3 Forward();
    static inline Vector3 Backward();


    /**
     * Returns the angle between two vectors in radians.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A scalar value.
     */
    static inline float Angle(Vector3 a, Vector3 b);

    /**
     * Returns a vector with its magnitude clamped to maxLength.
     * @param vector: The target vector.
     * @param maxLength: The maximum length of the return vector.
     * @return: A new vector.
     */
    static inline Vector3 ClampMagnitude(Vector3 vector, float maxLength);

    /**
     * Retorna o componente de a na direção de b (projeção escalar).
     * @param a: O vetor de destino.
     * @param b: O vetor que está sendo comparado.
     * @return: Um valor escalar.
     */
    static inline float Component(Vector3 a, Vector3 b);

    /**
     * Retorna o produto vetorial de dois vetores.
     * @param lhs: O lado esquerdo da multiplicação.
     * @param rhs: O lado direito da multiplicação.
     * @return: Um novo vetor.
     */
    static inline Vector3 Cross(Vector3 lhs, Vector3 rhs);

    /**
     * Returns the distance between a and b.
     * @param a: The first point.
     * @param b: The second point.
     * @return: A scalar value.
     */
    static inline float Distance(Vector3 a, Vector3 b);

    static inline char ToChar(Vector3 a);

    /**
     * Returns the dot product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A scalar value.
     */
    static inline float Dot(Vector3 lhs, Vector3 rhs);

    /**
     * Converte uma representação esférica de um vetor em cartesiano
     * coordenadas.
     * Isso usa a convenção ISO (raio r, inclinação theta, azimute phi).
     * @param rad: A magnitude do vetor.
     * @param theta: O ângulo no plano xy do eixo x.
     * @param phi: O ângulo do eixo z positivo para o vetor.
     * @return: Um novo vetor.
     */
    static inline Vector3 FromSpherical(float rad, float theta, float phi);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line. The vector is clamped to never go beyond the end points.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1].
     * @return: A new vector.
     */
    static inline Vector3 Lerp(Vector3 a, Vector3 b, float t);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1] (no actual bounds).
     * @return: A new vector.
     */
    static inline Vector3 LerpUnclamped(Vector3 a, Vector3 b, float t);

    /**
     * Returns the magnitude of a vector.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float Magnitude(Vector3 v);

    /**
     * Returns a vector made from the largest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector3 Max(Vector3 a, Vector3 b);

    /**
     * Returns a vector made from the smallest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector3 Min(Vector3 a, Vector3 b);

    /**
     * Returns a vector "maxDistanceDelta" units closer to the target. This
     * interpolation is in a straight line, and will not overshoot.
     * @param current: The current position.
     * @param target: The destination position.
     * @param maxDistanceDelta: The maximum distance to move.
     * @return: A new vector.
     */
    static inline Vector3 MoveTowards(Vector3 current, Vector3 target,
                                      float maxDistanceDelta);

    /**
     * Returns a new vector with magnitude of one.
     * @param v: The vector in question.
     * @return: A new vector.
     */
    static inline Vector3 Normalized(Vector3 v);

    /**
     * Returns an arbitrary vector orthogonal to the input.
     * This vector is not normalized.
     * @param v: The input vector.
     * @return: A new vector.
     */
    static inline Vector3 Orthogonal(Vector3 v);

    /**
     * Creates a new coordinate system out of the three vectors.
     * Normalizes "normal", normalizes "tangent" and makes it orthogonal to
     * "normal" and normalizes "binormal" and makes it orthogonal to both
     * "normal" and "tangent".
     * @param normal: A reference to the first axis vector.
     * @param tangent: A reference to the second axis vector.
     * @param binormal: A reference to the third axis vector.
     */
    static inline void OrthoNormalize(Vector3 &normal, Vector3 &tangent,
                                      Vector3 &binormal);

    /**
     * Returns the vector projection of a onto b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector3 Project(Vector3 a, Vector3 b);

    /**
     * Returns a vector projected onto a plane orthogonal to "planeNormal".
     * This can be visualized as the shadow of the vector onto the plane, if
     * the light source were in the direction of the plane normal.
     * @param vector: The vector to project.
     * @param planeNormal: The normal of the plane onto which to project.
     * @param: A new vector.
     */
    static inline Vector3 ProjectOnPlane(Vector3 vector, Vector3 planeNormal);

    /**
     * Returns a vector reflected off the plane orthogonal to the normal.
     * The input vector is pointed inward, at the plane, and the return vector
     * is pointed outward from the plane, like a beam of light hitting and then
     * reflecting off a mirror.
     * @param vector: The vector traveling inward at the plane.
     * @param planeNormal: The normal of the plane off of which to reflect.
     * @return: A new vector pointing outward from the plane.
     */
    static inline Vector3 Reflect(Vector3 vector, Vector3 planeNormal);

    /**
     * Returns the vector rejection of a on b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector3 Reject(Vector3 a, Vector3 b);

    /**
     * Rotates vector "current" towards vector "target" by "maxRadiansDelta".
     * This treats the vectors as directions and will linearly interpolate
     * between their magnitudes by "maxMagnitudeDelta". This function does not
     * overshoot. If a negative delta is supplied, it will rotate away from
     * "target" until it is pointing the opposite direction, but will not
     * overshoot that either.
     * @param current: The starting direction.
     * @param target: The destination direction.
     * @param maxRadiansDelta: The maximum number of radians to rotate.
     * @param maxMagnitudeDelta: The maximum delta for magnitude interpolation.
     * @return: A new vector.
     */
    static inline Vector3 RotateTowards(Vector3 current, Vector3 target,
                                        float maxRadiansDelta,
                                        float maxMagnitudeDelta);

    /**
     * Multiplies two vectors element-wise.
     * @param a: The lhs of the multiplication.
     * @param b: The rhs of the multiplication.
     * @return: A new vector.
     */
    static inline Vector3 Scale(Vector3 a, Vector3 b);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is clamped to 0 <= t <= 1.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector3 Slerp(Vector3 a, Vector3 b, float t);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is unclamped.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector3 SlerpUnclamped(Vector3 a, Vector3 b, float t);

    /**
     * Returns the squared magnitude of a vector.
     * This is useful when comparing relative lengths, where the exact length
     * is not important, and much time can be saved by not calculating the
     * square root.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float SqrMagnitude(Vector3 v);

    /**
     * Calculates the spherical coordinate space representation of a vector.
     * This uses the ISO convention (radius r, inclination theta, azimuth phi).
     * @param vector: The vector to convert.
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the xy plane from the x axis.
     * @param phi: The angle from the positive z axis to the vector.
     */
    static inline void ToSpherical(Vector3 vector, float &rad, float &theta,
                                   float &phi);


    /**
     * Operator overloading.
     */
    inline struct Vector3& operator+=(const float rhs);
    inline struct Vector3& operator-=(const float rhs);
    inline struct Vector3& operator*=(const float rhs);
    inline struct Vector3& operator/=(const float rhs);
    inline struct Vector3& operator+=(const Vector3 rhs);
    inline struct Vector3& operator-=(const Vector3 rhs);
};

inline Vector3 operator-(Vector3 rhs);
inline Vector3 operator+(Vector3 lhs, const float rhs);
inline Vector3 operator-(Vector3 lhs, const float rhs);
inline Vector3 operator*(Vector3 lhs, const float rhs);
inline Vector3 operator/(Vector3 lhs, const float rhs);
inline Vector3 operator+(const float lhs, Vector3 rhs);
inline Vector3 operator-(const float lhs, Vector3 rhs);
inline Vector3 operator*(const float lhs, Vector3 rhs);
inline Vector3 operator/(const float lhs, Vector3 rhs);
inline Vector3 operator+(Vector3 lhs, const Vector3 rhs);
inline Vector3 operator-(Vector3 lhs, const Vector3 rhs);
inline bool operator==(const Vector3 lhs, const Vector3 rhs);
inline bool operator!=(const Vector3 lhs, const Vector3 rhs);



/*******************************************************************************
 * Implementation
 */

Vector3::Vector3() : x(0), y(0), z(0) {}
Vector3::Vector3(float data[]) : x(data[0]), y(data[1]), z(data[2]) {}
Vector3::Vector3(float value) : x(value), y(value), z(value) {}
Vector3::Vector3(float x, float y) : x(x), y(y), z(0) {}
Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z) {}


Vector3 Vector3::zero() { return Vector3(0, 0, 0); }
Vector3 Vector3::One() { return Vector3(1, 1, 1); }
Vector3 Vector3::Right() { return Vector3(1, 0, 0); }
Vector3 Vector3::Left() { return Vector3(-1, 0, 0); }
Vector3 Vector3::Up() { return Vector3(0, 1, 0); }
Vector3 Vector3::Down() { return Vector3(0, -1, 0); }
Vector3 Vector3::Forward() { return Vector3(0, 0, 1); }
Vector3 Vector3::Backward() { return Vector3(0, 0, -1); }


float Vector3::Angle(Vector3 a, Vector3 b)
{
    float v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

Vector3 Vector3::ClampMagnitude(Vector3 vector, float maxLength)
{
    float length = Magnitude(vector);
    if (length > maxLength)
        vector *= maxLength / length;
    return vector;
}

float Vector3::Component(Vector3 a, Vector3 b)
{
    return Dot(a, b) / Magnitude(b);
}

Vector3 Vector3::Cross(Vector3 lhs, Vector3 rhs)
{
    float x = lhs.y * rhs.z - lhs.z * rhs.y;
    float y = lhs.z * rhs.x - lhs.x * rhs.z;
    float z = lhs.x * rhs.y - lhs.y * rhs.x;
    return Vector3(x, y, z);
}

float Vector3::Distance(Vector3 a, Vector3 b)
{
    return Vector3::Magnitude(a - b);
}

float Vector3::Dot(Vector3 lhs, Vector3 rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3 Vector3::FromSpherical(float rad, float theta, float phi)
{
    Vector3 v;
    v.x = rad * sin(theta) * cos(phi);
    v.y = rad * sin(theta) * sin(phi);
    v.z = rad * cos(theta);
    return v;
}

Vector3 Vector3::Lerp(Vector3 a, Vector3 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

Vector3 Vector3::LerpUnclamped(Vector3 a, Vector3 b, float t)
{
    return (b - a) * t + a;
}

float Vector3::Magnitude(Vector3 v)
{
    return sqrt(SqrMagnitude(v));
}

Vector3 Vector3::Max(Vector3 a, Vector3 b)
{
    float x = a.x > b.x ? a.x : b.x;
    float y = a.y > b.y ? a.y : b.y;
    float z = a.z > b.z ? a.z : b.z;
    return Vector3(x, y, z);
}

Vector3 Vector3::Min(Vector3 a, Vector3 b)
{
    float x = a.x > b.x ? b.x : a.x;
    float y = a.y > b.y ? b.y : a.y;
    float z = a.z > b.z ? b.z : a.z;
    return Vector3(x, y, z);
}

Vector3 Vector3::MoveTowards(Vector3 current, Vector3 target,
                             float maxDistanceDelta)
{
    Vector3 d = target - current;
    float m = Magnitude(d);
    if (m < maxDistanceDelta || m == 0)
        return target;
    return current + (d * maxDistanceDelta / m);
}

Vector3 Vector3::Normalized(Vector3 v)
{
    float mag = Magnitude(v);
    if (mag == 0)
        return Vector3::zero();
    return v / mag;
}

Vector3 Vector3::Orthogonal(Vector3 v)
{
    return v.z < v.x ? Vector3(v.y, -v.x, 0) : Vector3(0, -v.z, v.y);
}

void Vector3::OrthoNormalize(Vector3 &normal, Vector3 &tangent,
                             Vector3 &binormal)
{
    normal = Normalized(normal);
    tangent = ProjectOnPlane(tangent, normal);
    tangent = Normalized(tangent);
    binormal = ProjectOnPlane(binormal, tangent);
    binormal = ProjectOnPlane(binormal, normal);
    binormal = Normalized(binormal);
}

Vector3 Vector3::Project(Vector3 a, Vector3 b)
{
    float m = Magnitude(b);
    return Dot(a, b) / (m * m) * b;
}

Vector3 Vector3::ProjectOnPlane(Vector3 vector, Vector3 planeNormal)
{
    return Reject(vector, planeNormal);
}

Vector3 Vector3::Reflect(Vector3 vector, Vector3 planeNormal)
{
    return vector - 2 * Project(vector, planeNormal);
}

Vector3 Vector3::Reject(Vector3 a, Vector3 b)
{
    return a - Project(a, b);
}

Vector3 Vector3::RotateTowards(Vector3 current, Vector3 target,
                               float maxRadiansDelta,
                               float maxMagnitudeDelta)
{
    float magCur = Magnitude(current);
    float magTar = Magnitude(target);
    float newMag = magCur + maxMagnitudeDelta *
                            ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));

    float totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0)
        return Normalized(target) * newMag;
    else if (totalAngle >= M_PI)
        return Normalized(-target) * newMag;

    Vector3 axis = Cross(current, target);
    float magAxis = Magnitude(axis);
    if (magAxis == 0)
        axis = Normalized(Cross(current, current + Vector3(3.95, 5.32, -4.24)));
    else
        axis /= magAxis;
    current = Normalized(current);
    Vector3 newVector = current * cos(maxRadiansDelta) +
                        Cross(axis, current) * sin(maxRadiansDelta);
    return newVector * newMag;
}

Vector3 Vector3::Scale(Vector3 a, Vector3 b)
{
    return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3 Vector3::Slerp(Vector3 a, Vector3 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

Vector3 Vector3::SlerpUnclamped(Vector3 a, Vector3 b, float t)
{
    float magA = Magnitude(a);
    float magB = Magnitude(b);
    a /= magA;
    b /= magB;
    float dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    float theta = acos(dot) * t;
    Vector3 relativeVec = Normalized(b - a * dot);
    Vector3 newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

float Vector3::SqrMagnitude(Vector3 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

void Vector3::ToSpherical(Vector3 vector, float &rad, float &theta,
                          float &phi)
{
    rad = Magnitude(vector);
    float v = vector.z / rad;
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    theta = acos(v);
    phi = atan2(vector.y, vector.x);
}


struct Vector3& Vector3::operator+=(const float rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
}

struct Vector3& Vector3::operator-=(const float rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
    return *this;
}

struct Vector3& Vector3::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

struct Vector3& Vector3::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

struct Vector3& Vector3::operator+=(const Vector3 rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

struct Vector3& Vector3::operator-=(const Vector3 rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}



Vector3 operator-(Vector3 rhs) { return rhs * -1; }
Vector3 operator+(Vector3 lhs, const float rhs) { return lhs += rhs; }
Vector3 operator-(Vector3 lhs, const float rhs) { return lhs -= rhs; }
Vector3 operator*(Vector3 lhs, const float rhs) { return lhs *= rhs; }
Vector3 operator/(Vector3 lhs, const float rhs) { return lhs /= rhs; }
Vector3 operator+(const float lhs, Vector3 rhs) { return rhs += lhs; }
Vector3 operator-(const float lhs, Vector3 rhs) { return rhs -= lhs; }
Vector3 operator*(const float lhs, Vector3 rhs) { return rhs *= lhs; }
Vector3 operator/(const float lhs, Vector3 rhs) { return rhs /= lhs; }
Vector3 operator+(Vector3 lhs, const Vector3 rhs) { return lhs += rhs; }
Vector3 operator-(Vector3 lhs, const Vector3 rhs) { return lhs -= rhs; }

bool operator==(const Vector3 lhs, const Vector3 rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const Vector3 lhs, const Vector3 rhs)
{
    return !(lhs == rhs);
}

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>


#define SMALL_float 0.0000000001

#pragma once

using namespace std;

#define SMALL_FLOAT 0.0000000001

struct Quaternion
{
    union
    {
        struct
        {
            float x;
            float y;
            float z;
            float w;
        };
        float data[4];
    };


    /**
     * Constructors.
     */
    inline Quaternion();
    inline Quaternion(float data[]);
    inline Quaternion(Vector3 vector, float scalar);
    inline Quaternion(float x, float y, float z, float w);
    inline Quaternion(float Pitch, float Yaw, float Roll);


    /**
     * Constants for common quaternions.
     */
    static inline Quaternion Identity();

    /**
     * The following let you quickly get a direction vector from a quat.
     */
    static inline Vector3 Up(Quaternion q);
    static inline Vector3 Down(Quaternion q);
    static inline Vector3 Left(Quaternion q);
    static inline Vector3 Right(Quaternion q);
    static inline Vector3 Forward(Quaternion q);
    static inline Vector3 Back(Quaternion q);


    /**
     * Returns the angle between two quaternions.
     * The quaternions must be normalized.
     * @param a: The first quaternion.
     * @param b: The second quaternion.
     * @return: A scalar value.
     */
    static inline float Angle(Quaternion a, Quaternion b);

    /**
     * Returns the conjugate of a quaternion.
     * @param rotation: The quaternion in question.
     * @return: A new quaternion.
     */
    static inline Quaternion Conjugate(Quaternion rotation);

    /**
     * Returns the dot product of two quaternions.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A scalar value.
     */
    static inline float Dot(Quaternion lhs, Quaternion rhs);

    /**
     * Creates a new quaternion from the angle-axis representation of
     * a rotation.
     * @param angle: The rotation angle in radians.
     * @param axis: The vector about which the rotation occurs.
     * @return: A new quaternion.
     */
    static inline Quaternion FromAngleAxis(float angle, Vector3 axis);

    /**
     * Create a new quaternion from the euler angle representation of
     * a rotation. The z, x and y values represent rotations about those
     * axis in that respective order.
     * @param rotation: The x, y and z rotations.
     * @return: A new quaternion.
     */
    static inline Quaternion FromEuler(Vector3 rotation);

    /**
     * Create a new quaternion from the euler angle representation of
     * a rotation. The z, x and y values represent rotations about those
     * axis in that respective order.
     * @param x: The rotation about the x-axis in radians.
     * @param y: The rotation about the y-axis in radians.
     * @param z: The rotation about the z-axis in radians.
     * @return: A new quaternion.
     */
    static inline Quaternion FromEuler(float x, float y, float z);

    /**
     * Create a quaternion rotation which rotates "fromVector" to "toVector".
     * @param fromVector: The vector from which to start the rotation.
     * @param toVector: The vector at which to end the rotation.
     * @return: A new quaternion.
     */
    static inline Quaternion FromToRotation(Vector3 fromVector,
                                            Vector3 toVector);

    /**
     * Returns the inverse of a rotation.
     * @param rotation: The quaternion in question.
     * @return: A new quaternion.
     */
    static inline Quaternion Inverse(Quaternion rotation);

    /**
     * Interpolates between a and b by t, which is clamped to the range [0-1].
     * The result is normalized before being returned.
     * @param a: The starting rotation.
     * @param b: The ending rotation.
     * @return: A new quaternion.
     */
    static inline Quaternion Lerp(Quaternion a, Quaternion b, float t);

    /**
     * Interpolates between a and b by t. This normalizes the result when
     * complete.
     * @param a: The starting rotation.
     * @param b: The ending rotation.
     * @param t: The interpolation value.
     * @return: A new quaternion.
     */
    static inline Quaternion LerpUnclamped(Quaternion a, Quaternion b,
                                           float t);

    /**
     * Creates a rotation with the specified forward direction. This is the
     * same as calling LookRotation with (0, 1, 0) as the upwards vector.
     * The output is undefined for parallel vectors.
     * @param forward: The forward direction to look toward.
     * @return: A new quaternion.
     */
    static inline Quaternion LookRotation(Vector3 forward);

    /**
     * Creates a rotation with the specified forward and upwards directions.
     * The output is undefined for parallel vectors.
     * @param forward: The forward direction to look toward.
     * @param upwards: The direction to treat as up.
     * @return: A new quaternion.
     */
    static inline Quaternion LookRotation(Vector3 forward, Vector3 upwards);

    /**
     * Returns the norm of a quaternion.
     * @param rotation: The quaternion in question.
     * @return: A scalar value.
     */
    static inline float Norm(Quaternion rotation);

    /**
     * Returns a quaternion with identical rotation and a norm of one.
     * @param rotation: The quaternion in question.
     * @return: A new quaternion.
     */
    static inline Quaternion Normalized(Quaternion rotation);

    /**
     * Returns a new Quaternion created by rotating "from" towards "to" by
     * "maxRadiansDelta". This will not overshoot, and if a negative delta is
     * applied, it will rotate till completely opposite "to" and then stop.
     * @param from: The rotation at which to start.
     * @param to: The rotation at which to end.
     # @param maxRadiansDelta: The maximum number of radians to rotate.
     * @return: A new Quaternion.
     */
    static inline Quaternion RotateTowards(Quaternion from, Quaternion to,
                                           float maxRadiansDelta);

    /**
     * Returns a new quaternion interpolated between a and b, usinfg spherical
     * linear interpolation. The variable t is clamped to the range [0-1]. The
     * resulting quaternion will be normalized.
     * @param a: The starting rotation.
     * @param b: The ending rotation.
     * @param t: The interpolation value.
     * @return: A new quaternion.
     */
    static inline Quaternion Slerp(Quaternion a, Quaternion b, float t);

    /**
     * Returns a new quaternion interpolated between a and b, usinfg spherical
     * linear interpolation. The resulting quaternion will be normalized.
     * @param a: The starting rotation.
     * @param b: The ending rotation.
     * @param t: The interpolation value.
     * @return: A new quaternion.
     */
    static inline Quaternion SlerpUnclamped(Quaternion a, Quaternion b,
                                            float t);

    /**
     * Outputs the angle axis representation of the provided quaternion.
     * @param rotation: The input quaternion.
     * @param angle: The output angle.
     * @param axis: The output axis.
     */
    static inline void ToAngleAxis(Quaternion rotation, float &angle,
                                   Vector3 &axis);

    /**
     * Returns the Euler angle representation of a rotation. The resulting
     * vector contains the rotations about the z, x and y axis, in that order.
     * @param rotation: The quaternion to convert.
     * @return: A new vector.
     */
    static inline Vector3 ToEuler(Quaternion rotation);

    /**
     * Operator overloading.
     */
    inline struct Quaternion& operator+=(const float rhs);
    inline struct Quaternion& operator-=(const float rhs);
    inline struct Quaternion& operator*=(const float rhs);
    inline struct Quaternion& operator/=(const float rhs);
    inline struct Quaternion& operator+=(const Quaternion rhs);
    inline struct Quaternion& operator-=(const Quaternion rhs);
    inline struct Quaternion& operator*=(const Quaternion rhs);
};

inline Quaternion operator-(Quaternion rhs);
inline Quaternion operator+(Quaternion lhs, const float rhs);
inline Quaternion operator-(Quaternion lhs, const float rhs);
inline Quaternion operator*(Quaternion lhs, const float rhs);
inline Quaternion operator/(Quaternion lhs, const float rhs);
inline Quaternion operator+(const float lhs, Quaternion rhs);
inline Quaternion operator-(const float lhs, Quaternion rhs);
inline Quaternion operator*(const float lhs, Quaternion rhs);
inline Quaternion operator/(const float lhs, Quaternion rhs);
inline Quaternion operator+(Quaternion lhs, const Quaternion rhs);
inline Quaternion operator-(Quaternion lhs, const Quaternion rhs);
inline Quaternion operator*(Quaternion lhs, const Quaternion rhs);
inline Vector3 operator*(Quaternion lhs, const Vector3 rhs);
inline bool operator==(const Quaternion lhs, const Quaternion rhs);
inline bool operator!=(const Quaternion lhs, const Quaternion rhs);



/*******************************************************************************
 * Implementation
 */

Quaternion::Quaternion() : x(0), y(0), z(0), w(1) {}
Quaternion::Quaternion(float data[]) : x(data[0]), y(data[1]), z(data[2]),
                                       w(data[3]) {}
Quaternion::Quaternion(Vector3 vector, float scalar) : x(vector.x),
                                                       y(vector.y), z(vector.z), w(scalar) {}
Quaternion::Quaternion(float x, float y, float z, float w) : x(x), y(y),
                                                             z(z), w(w) {}
Quaternion::Quaternion(float Pitch, float Yaw, float Roll) {
    Quaternion tmp = Quaternion::FromEuler(Pitch, Yaw, Roll);
    x = tmp.x;
    y = tmp.y;
    z = tmp.z;
    w = tmp.w;
}



inline Vector3 Quaternion::Up(Quaternion q)
{
    return q * Vector3::Up();
}

inline Vector3 Quaternion::Down(Quaternion q)
{
    return q * Vector3::Down();
}

inline Vector3 Quaternion::Left(Quaternion q)
{
    return q * Vector3::Left();
}

inline Vector3 Quaternion::Right(Quaternion q)
{
    return q * Vector3::Right();
}

inline Vector3 Quaternion::Forward(Quaternion q)
{
    return q * Vector3::Forward();
}

inline Vector3 Quaternion::Back(Quaternion q)
{
    return q * Vector3::Backward();
}

float Quaternion::Angle(Quaternion a, Quaternion b)
{
    float dot = Dot(a, b);
    return acosf(fminf(fabs(dot), 1)) * 2;
}

Quaternion Quaternion::Conjugate(Quaternion rotation)
{
    return Quaternion(-rotation.x, -rotation.y, -rotation.z, rotation.w);
}

float Quaternion::Dot(Quaternion lhs, Quaternion rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
}

Quaternion Quaternion::FromAngleAxis(float angle, Vector3 axis)
{
    Quaternion q;
    float m = sqrt(axis.x * axis.x + axis.y * axis.y + axis.z * axis.z);
    float s = sinf(angle / 2) / m;
    q.x = axis.x * s;
    q.y = axis.y * s;
    q.z = axis.z * s;
    q.w = cosf(angle / 2);
    return q;
}

Quaternion Quaternion::FromEuler(Vector3 rotation)
{
    return FromEuler(rotation.x, rotation.y, rotation.z);
}

Quaternion Quaternion::FromEuler(float x, float y, float z)
{
    float cx = cosf(x * 0.5f);
    float cy = cosf(y * 0.5f);
    float cz = cosf(z * 0.5f);
    float sx = sinf(x * 0.5f);
    float sy = sinf(y * 0.5f);
    float sz = sinf(z * 0.5f);
    Quaternion q;
    q.x = cx * sy * sz + cy * cz * sx;
    q.y = cx * cz * sy - cy * sx * sz;
    q.z = cx * cy * sz - cz * sx * sy;
    q.w = sx * sy * sz + cx * cy * cz;
    return q;
}

Quaternion Quaternion::FromToRotation(Vector3 fromVector, Vector3 toVector)
{
    float dot = Vector3::Dot(fromVector, toVector);
    float k = sqrt(Vector3::SqrMagnitude(fromVector) *
                   Vector3::SqrMagnitude(toVector));
    if (fabs(dot / k + 1) < 0.00001)
    {
        Vector3 ortho = Vector3::Orthogonal(fromVector);
        return Quaternion(Vector3::Normalized(ortho), 0);
    }
    Vector3 cross = Vector3::Cross(fromVector, toVector);
    return Normalized(Quaternion(cross, dot + k));
}

Quaternion Quaternion::Inverse(Quaternion rotation)
{
    float n = Norm(rotation);
    return Conjugate(rotation) / (n * n);
}

Quaternion Quaternion::Lerp(Quaternion a, Quaternion b, float t)
{
    if (t < 0) return Normalized(a);
    else if (t > 1) return Normalized(b);
    return LerpUnclamped(a, b, t);
}

Quaternion Quaternion::LerpUnclamped(Quaternion a, Quaternion b, float t)
{
    Quaternion quaternion;
    if (Dot(a, b) >= 0)
        quaternion = a * (1 - t) + b * t;
    else
        quaternion = a * (1 - t) - b * t;
    return Normalized(quaternion);
}

Quaternion Quaternion::LookRotation(Vector3 forward)
{
    return LookRotation(forward, Vector3(0, 1, 0));
}

Quaternion Quaternion::LookRotation(Vector3 forward, Vector3 upwards)
{
    // Normalize inputs
    forward = Vector3::Normalized(forward);
    upwards = Vector3::Normalized(upwards);
    // Don't allow zero vectors
    if (Vector3::SqrMagnitude(forward) < SMALL_FLOAT || Vector3::SqrMagnitude(upwards) < SMALL_FLOAT)
        return Quaternion(0, 0, 0, 1);
    // Handle alignment with up direction
    if (1 - fabs(Vector3::Dot(forward, upwards)) < SMALL_FLOAT)
        return FromToRotation(Vector3::Forward(), forward);
    // Get orthogonal vectors
    Vector3 right = Vector3::Normalized(Vector3::Cross(upwards, forward));
    upwards = Vector3::Cross(forward, right);
    // Calculate rotation
    Quaternion quaternion;
    float radicand = right.x + upwards.y + forward.z;
    if (radicand > 0)
    {
        quaternion.w = sqrt(1.0f + radicand) * 0.5f;
        float recip = 1.0f / (4.0f * quaternion.w);
        quaternion.x = (upwards.z - forward.y) * recip;
        quaternion.y = (forward.x - right.z) * recip;
        quaternion.z = (right.y - upwards.x) * recip;
    }
    else if (right.x >= upwards.y && right.x >= forward.z)
    {
        quaternion.x = sqrt(1.0f + right.x - upwards.y - forward.z) * 0.5f;
        float recip = 1.0f / (4.0f * quaternion.x);
        quaternion.w = (upwards.z - forward.y) * recip;
        quaternion.z = (forward.x + right.z) * recip;
        quaternion.y = (right.y + upwards.x) * recip;
    }
    else if (upwards.y > forward.z)
    {
        quaternion.y = sqrt(1.0f - right.x + upwards.y - forward.z) * 0.5f;
        float recip = 1.0f / (4.0f * quaternion.y);
        quaternion.z = (upwards.z + forward.y) * recip;
        quaternion.w = (forward.x - right.z) * recip;
        quaternion.x = (right.y + upwards.x) * recip;
    }
    else
    {
        quaternion.z = sqrt(1.0f - right.x - upwards.y + forward.z) * 0.5f;
        float recip = 1.0f / (4.0f * quaternion.z);
        quaternion.y = (upwards.z + forward.y) * recip;
        quaternion.x = (forward.x + right.z) * recip;
        quaternion.w = (right.y - upwards.x) * recip;
    }
    return quaternion;
}

float Quaternion::Norm(Quaternion rotation)
{
    return sqrt(rotation.x * rotation.x +
                rotation.y * rotation.y +
                rotation.z * rotation.z +
                rotation.w * rotation.w);
}

Quaternion Quaternion::Normalized(Quaternion rotation)
{
    return rotation / Norm(rotation);
}

Quaternion Quaternion::RotateTowards(Quaternion from, Quaternion to,
                                     float maxRadiansDelta)
{
    float angle = Quaternion::Angle(from, to);
    if (angle == 0)
        return to;
    maxRadiansDelta = fmaxf(maxRadiansDelta, angle - (float)M_PI);
    float t = fminf(1, maxRadiansDelta / angle);
    return Quaternion::SlerpUnclamped(from, to, t);
}

Quaternion Quaternion::Slerp(Quaternion a, Quaternion b, float t)
{
    if (t < 0) return Normalized(a);
    else if (t > 1) return Normalized(b);
    return SlerpUnclamped(a, b, t);
}

Quaternion Quaternion::SlerpUnclamped(Quaternion a, Quaternion b, float t)
{
    float n1;
    float n2;
    float n3 = Dot(a, b);
    bool flag = false;
    if (n3 < 0)
    {
        flag = true;
        n3 = -n3;
    }
    if (n3 > 0.999999)
    {
        n2 = 1 - t;
        n1 = flag ? -t : t;
    }
    else
    {
        float n4 = acosf(n3);
        float n5 = 1 / sinf(n4);
        n2 = sinf((1 - t) * n4) * n5;
        n1 = flag ? -sinf(t * n4) * n5 : sinf(t * n4) * n5;
    }
    Quaternion quaternion;
    quaternion.x = (n2 * a.x) + (n1 * b.x);
    quaternion.y = (n2 * a.y) + (n1 * b.y);
    quaternion.z = (n2 * a.z) + (n1 * b.z);
    quaternion.w = (n2 * a.w) + (n1 * b.w);
    return Normalized(quaternion);
}

void Quaternion::ToAngleAxis(Quaternion rotation, float &angle, Vector3 &axis)
{
    if (rotation.w > 1)
        rotation = Normalized(rotation);
    angle = 2 * acosf(rotation.w);
    float s = sqrt(1 - rotation.w * rotation.w);
    if (s < 0.00001) {
        axis.x = 1;
        axis.y = 0;
        axis.z = 0;
    } else {
        axis.x = rotation.x / s;
        axis.y = rotation.y / s;
        axis.z = rotation.z / s;
    }
}

Vector3 Quaternion::ToEuler(Quaternion rotation)
{
    float sqw = rotation.w * rotation.w;
    float sqx = rotation.x * rotation.x;
    float sqy = rotation.y * rotation.y;
    float sqz = rotation.z * rotation.z;
    // If normalized is one, otherwise is correction factor
    float unit = sqx + sqy + sqz + sqw;
    float test = rotation.x * rotation.w - rotation.y * rotation.z;
    Vector3 v;
    // sinfgularity at north pole
    if (test > 0.4995f * unit)
    {
        v.y = 2 * atan2f(rotation.y, rotation.x);
        v.x = (float)M_PI_2;
        v.z = 0;
        return v;
    }
    // sinfgularity at south pole
    if (test < -0.4995f * unit)
    {
        v.y = -2 * atan2f(rotation.y, rotation.x);
        v.x = -(float)M_PI_2;
        v.z = 0;
        return v;
    }
    // yaw
    v.y = atan2f(2 * rotation.w * rotation.y + 2 * rotation.z * rotation.x,
                 1 - 2 * (rotation.x * rotation.x + rotation.y * rotation.y));
    // Pitch
    v.x = asinf(2 * (rotation.w * rotation.x - rotation.y * rotation.z));
    // Roll
    v.z = atan2f(2 * rotation.w * rotation.z + 2 * rotation.x * rotation.y,
                 1 - 2 * (rotation.z * rotation.z + rotation.x * rotation.x));
    return v;
}

struct Quaternion& Quaternion::operator+=(const float rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
    w += rhs;
    return *this;
}

struct Quaternion& Quaternion::operator-=(const float rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
    w -= rhs;
    return *this;
}

struct Quaternion& Quaternion::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

struct Quaternion& Quaternion::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

struct Quaternion& Quaternion::operator+=(const Quaternion rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

struct Quaternion& Quaternion::operator-=(const Quaternion rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

struct Quaternion& Quaternion::operator*=(const Quaternion rhs)
{
    Quaternion q;
    q.w = w * rhs.w - x * rhs.x - y * rhs.y - z * rhs.z;
    q.x = x * rhs.w + w * rhs.x + y * rhs.z - z * rhs.y;
    q.y = w * rhs.y - x * rhs.z + y * rhs.w + z * rhs.x;
    q.z = w * rhs.z + x * rhs.y - y * rhs.x + z * rhs.w;
    *this = q;
    return *this;
}

Quaternion operator-(Quaternion rhs) { return rhs * -1; }
Quaternion operator+(Quaternion lhs, const float rhs) { return lhs += rhs; }
Quaternion operator-(Quaternion lhs, const float rhs) { return lhs -= rhs; }
Quaternion operator*(Quaternion lhs, const float rhs) { return lhs *= rhs; }
Quaternion operator/(Quaternion lhs, const float rhs) { return lhs /= rhs; }
Quaternion operator+(const float lhs, Quaternion rhs) { return rhs += lhs; }
Quaternion operator-(const float lhs, Quaternion rhs) { return rhs -= lhs; }
Quaternion operator*(const float lhs, Quaternion rhs) { return rhs *= lhs; }
Quaternion operator/(const float lhs, Quaternion rhs) { return rhs /= lhs; }
Quaternion operator+(Quaternion lhs, const Quaternion rhs)
{
    return lhs += rhs;
}
Quaternion operator-(Quaternion lhs, const Quaternion rhs)
{
    return lhs -= rhs;
}
Quaternion operator*(Quaternion lhs, const Quaternion rhs)
{
    return lhs *= rhs;
}

Vector3 operator*(Quaternion lhs, const Vector3 rhs)
{
    Vector3 u = Vector3(lhs.x, lhs.y, lhs.z);
    float s = lhs.w;
    return u * (Vector3::Dot(u, rhs) * 2.0f)
           + rhs * (s * s - Vector3::Dot(u, u))
           + Vector3::Cross(u, rhs) * (2.0f * s);
}

bool operator==(const Quaternion lhs, const Quaternion rhs)
{
    return lhs.x == rhs.x &&
           lhs.y == rhs.y &&
           lhs.z == rhs.z &&
           lhs.w == rhs.w;
}

bool operator!=(const Quaternion lhs, const Quaternion rhs)
{
    return !(lhs == rhs);
}

std::string to_string(Quaternion a) {
    return to_string(a.x) + (", ") + to_string(a.y) + (", ") + to_string(a.z) + (", ") + to_string(a.w);
}
#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>

#define SMALL_float 0.0000000001

struct Vector3_2
{
    float x;
    float y;
    float z;

    Vector3_2();
    Vector3_2(float x, float y, float z);
    ~Vector3_2();


    /**
     * Constructors.
     */


    /**
     * Constants for common vectors.
     */
    static inline Vector3_2 zero();
    static inline Vector3_2 One();
    static inline Vector3_2 Right();
    static inline Vector3_2 Left();
    static inline Vector3_2 Up();
    static inline Vector3_2 Down();
    static inline Vector3_2 Forward();
    static inline Vector3_2 Backward();


    /**
     * Returns the angle between two vectors in radians.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A scalar value.
     */
    static inline float Angle(Vector3_2 a, Vector3_2 b);

    /**
     * Returns a vector with its magnitude clamped to maxLength.
     * @param vector: The target vector.
     * @param maxLength: The maximum length of the return vector.
     * @return: A new vector.
     */
    static inline Vector3_2 ClampMagnitude(Vector3_2 vector, float maxLength);

    /**
     * Returns the component of a in the direction of b (scalar projection).
     * @param a: The target vector.
     * @param b: The vector being compared against.
     * @return: A scalar value.
     */
    static inline float Component(Vector3_2 a, Vector3_2 b);

    /**
     * Returns the cross product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A new vector.
     */
    static inline Vector3_2 Cross(Vector3_2 lhs, Vector3_2 rhs);

    /**
     * Returns the distance between a and b.
     * @param a: The first point.
     * @param b: The second point.
     * @return: A scalar value.
     */
    static inline float Distance(Vector3_2 a, Vector3_2 b);

    static inline char ToChar(Vector3_2 a);

    /**
     * Returns the dot product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A scalar value.
     */
    static inline float Dot(Vector3_2 lhs, Vector3_2 rhs);

    /**
     * Converts a spherical representation of a vector into cartesian
     * coordinates.
     * This uses the ISO convention (radius r, inclination theta, azimuth phi).
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the xy plane from the x axis.
     * @param phi: The angle from the positive z axis to the vector.
     * @return: A new vector.
     */
    static inline Vector3_2 FromSpherical(float rad, float theta, float phi);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line. The vector is clamped to never go beyond the end points.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1].
     * @return: A new vector.
     */
    static inline Vector3_2 Lerp(Vector3_2 a, Vector3_2 b, float t);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1] (no actual bounds).
     * @return: A new vector.
     */
    static inline Vector3_2 LerpUnclamped(Vector3_2 a, Vector3_2 b, float t);

    /**
     * Returns the magnitude of a vector.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float Magnitude(Vector3_2 v);

    /**
     * Returns a vector made from the largest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector3_2 Max(Vector3_2 a, Vector3_2 b);

    /**
     * Returns a vector made from the smallest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector3_2 Min(Vector3_2 a, Vector3_2 b);

    /**
     * Returns a vector "maxDistanceDelta" units closer to the target. This
     * interpolation is in a straight line, and will not overshoot.
     * @param current: The current position.
     * @param target: The destination position.
     * @param maxDistanceDelta: The maximum distance to move.
     * @return: A new vector.
     */
    static inline Vector3_2 MoveTowards(Vector3_2 current, Vector3_2 target,
                                        float maxDistanceDelta);

    /**
     * Returns a new vector with magnitude of one.
     * @param v: The vector in question.
     * @return: A new vector.
     */
    static inline Vector3_2 Normalized(Vector3_2 v);

    /**
     * Returns an arbitrary vector orthogonal to the input.
     * This vector is not normalized.
     * @param v: The input vector.
     * @return: A new vector.
     */
    static inline Vector3_2 Orthogonal(Vector3_2 v);

    /**
     * Creates a new coordinate system out of the three vectors.
     * Normalizes "normal", normalizes "tangent" and makes it orthogonal to
     * "normal" and normalizes "binormal" and makes it orthogonal to both
     * "normal" and "tangent".
     * @param normal: A reference to the first axis vector.
     * @param tangent: A reference to the second axis vector.
     * @param binormal: A reference to the third axis vector.
     */
    static inline void OrthoNormalize(Vector3_2 &normal, Vector3_2 &tangent,
                                      Vector3_2 &binormal);

    /**
     * Returns the vector projection of a onto b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector3_2 Project(Vector3_2 a, Vector3_2 b);

    /**
     * Returns a vector projected onto a plane orthogonal to "planeNormal".
     * This can be visualized as the shadow of the vector onto the plane, if
     * the light source were in the direction of the plane normal.
     * @param vector: The vector to project.
     * @param planeNormal: The normal of the plane onto which to project.
     * @param: A new vector.
     */
    static inline Vector3_2 ProjectOnPlane(Vector3_2 vector, Vector3_2 planeNormal);

    /**
     * Returns a vector reflected off the plane orthogonal to the normal.
     * The input vector is pointed inward, at the plane, and the return vector
     * is pointed outward from the plane, like a beam of light hitting and then
     * reflecting off a mirror.
     * @param vector: The vector traveling inward at the plane.
     * @param planeNormal: The normal of the plane off of which to reflect.
     * @return: A new vector pointing outward from the plane.
     */
    static inline Vector3_2 Reflect(Vector3_2 vector, Vector3_2 planeNormal);

    /**
     * Returns the vector rejection of a on b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector3_2 Reject(Vector3_2 a, Vector3_2 b);

    /**
     * Rotates vector "current" towards vector "target" by "maxRadiansDelta".
     * This treats the vectors as directions and will linearly interpolate
     * between their magnitudes by "maxMagnitudeDelta". This function does not
     * overshoot. If a negative delta is supplied, it will rotate away from
     * "target" until it is pointing the opposite direction, but will not
     * overshoot that either.
     * @param current: The starting direction.
     * @param target: The destination direction.
     * @param maxRadiansDelta: The maximum number of radians to rotate.
     * @param maxMagnitudeDelta: The maximum delta for magnitude interpolation.
     * @return: A new vector.
     */
    static inline Vector3_2 RotateTowards(Vector3_2 current, Vector3_2 target,
                                          float maxRadiansDelta,
                                          float maxMagnitudeDelta);

    /**
     * Multiplies two vectors element-wise.
     * @param a: The lhs of the multiplication.
     * @param b: The rhs of the multiplication.
     * @return: A new vector.
     */
    static inline Vector3_2 Scale(Vector3_2 a, Vector3_2 b);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is clamped to 0 <= t <= 1.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector3_2 Slerp(Vector3_2 a, Vector3_2 b, float t);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is unclamped.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector3_2 SlerpUnclamped(Vector3_2 a, Vector3_2 b, float t);

    /**
     * Returns the squared magnitude of a vector.
     * This is useful when comparing relative lengths, where the exact length
     * is not important, and much time can be saved by not calculating the
     * square root.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float SqrMagnitude(Vector3_2 v);

    /**
     * Calculates the spherical coordinate space representation of a vector.
     * This uses the ISO convention (radius r, inclination theta, azimuth phi).
     * @param vector: The vector to convert.
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the xy plane from the x axis.
     * @param phi: The angle from the positive z axis to the vector.
     */
    static inline void ToSpherical(Vector3_2 vector, float &rad, float &theta,
                                   float &phi);


    /**
     * Operator overloading.
     */
    inline struct Vector3_2& operator+=(const float rhs);
    inline struct Vector3_2& operator-=(const float rhs);
    inline struct Vector3_2& operator*=(const float rhs);
    inline struct Vector3_2& operator/=(const float rhs);
    inline struct Vector3_2& operator+=(const Vector3_2 rhs);
    inline struct Vector3_2& operator-=(const Vector3_2 rhs);
};

inline Vector3_2 operator-(Vector3_2 rhs);
inline Vector3_2 operator+(Vector3_2 lhs, const float rhs);
inline Vector3_2 operator-(Vector3_2 lhs, const float rhs);
inline Vector3_2 operator*(Vector3_2 lhs, const float rhs);
inline Vector3_2 operator/(Vector3_2 lhs, const float rhs);
inline Vector3_2 operator+(const float lhs, Vector3_2 rhs);
inline Vector3_2 operator-(const float lhs, Vector3_2 rhs);
inline Vector3_2 operator*(const float lhs, Vector3_2 rhs);
inline Vector3_2 operator/(const float lhs, Vector3_2 rhs);
inline Vector3_2 operator+(Vector3_2 lhs, const Vector3_2 rhs);
inline Vector3_2 operator-(Vector3_2 lhs, const Vector3_2 rhs);
inline bool operator==(const Vector3_2 lhs, const Vector3_2 rhs);
inline bool operator!=(const Vector3_2 lhs, const Vector3_2 rhs);



/*******************************************************************************
 * Implementation
 */

Vector3_2::Vector3_2() {}
Vector3_2::Vector3_2(float x, float y, float z) : x(x), y(y), z(z) {}
Vector3_2::~Vector3_2() {}


Vector3_2 Vector3_2::zero() { return Vector3_2(0, 0, 0); }
Vector3_2 Vector3_2::One() { return Vector3_2(1, 1, 1); }
Vector3_2 Vector3_2::Right() { return Vector3_2(1, 0, 0); }
Vector3_2 Vector3_2::Left() { return Vector3_2(-1, 0, 0); }
Vector3_2 Vector3_2::Up() { return Vector3_2(0, 1, 0); }
Vector3_2 Vector3_2::Down() { return Vector3_2(0, -1, 0); }
Vector3_2 Vector3_2::Forward() { return Vector3_2(0, 0, 1); }
Vector3_2 Vector3_2::Backward() { return Vector3_2(0, 0, -1); }


float Vector3_2::Angle(Vector3_2 a, Vector3_2 b)
{
    float v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

Vector3_2 Vector3_2::ClampMagnitude(Vector3_2 vector, float maxLength)
{
    float length = Magnitude(vector);
    if (length > maxLength)
        vector *= maxLength / length;
    return vector;
}

float Vector3_2::Component(Vector3_2 a, Vector3_2 b)
{
    return Dot(a, b) / Magnitude(b);
}

Vector3_2 Vector3_2::Cross(Vector3_2 lhs, Vector3_2 rhs)
{
    float x = lhs.y * rhs.z - lhs.z * rhs.y;
    float y = lhs.z * rhs.x - lhs.x * rhs.z;
    float z = lhs.x * rhs.y - lhs.y * rhs.x;
    return Vector3_2(x, y, z);
}

float Vector3_2::Distance(Vector3_2 a, Vector3_2 b)
{
    return Vector3_2::Magnitude(a - b);
}

float Vector3_2::Dot(Vector3_2 lhs, Vector3_2 rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
}

Vector3_2 Vector3_2::FromSpherical(float rad, float theta, float phi)
{
    Vector3_2 v;
    v.x = rad * sin(theta) * cos(phi);
    v.y = rad * sin(theta) * sin(phi);
    v.z = rad * cos(theta);
    return v;
}

Vector3_2 Vector3_2::Lerp(Vector3_2 a, Vector3_2 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

Vector3_2 Vector3_2::LerpUnclamped(Vector3_2 a, Vector3_2 b, float t)
{
    return (b - a) * t + a;
}

float Vector3_2::Magnitude(Vector3_2 v)
{
    return sqrt(SqrMagnitude(v));
}

Vector3_2 Vector3_2::Max(Vector3_2 a, Vector3_2 b)
{
    float x = a.x > b.x ? a.x : b.x;
    float y = a.y > b.y ? a.y : b.y;
    float z = a.z > b.z ? a.z : b.z;
    return Vector3_2(x, y, z);
}

Vector3_2 Vector3_2::Min(Vector3_2 a, Vector3_2 b)
{
    float x = a.x > b.x ? b.x : a.x;
    float y = a.y > b.y ? b.y : a.y;
    float z = a.z > b.z ? b.z : a.z;
    return Vector3_2(x, y, z);
}

Vector3_2 Vector3_2::MoveTowards(Vector3_2 current, Vector3_2 target,
                                 float maxDistanceDelta)
{
    Vector3_2 d = target - current;
    float m = Magnitude(d);
    if (m < maxDistanceDelta || m == 0)
        return target;
    return current + (d * maxDistanceDelta / m);
}

Vector3_2 Vector3_2::Normalized(Vector3_2 v)
{
    float mag = Magnitude(v);
    if (mag == 0)
        return Vector3_2::zero();
    return v / mag;
}

Vector3_2 Vector3_2::Orthogonal(Vector3_2 v)
{
    return v.z < v.x ? Vector3_2(v.y, -v.x, 0) : Vector3_2(0, -v.z, v.y);
}

void Vector3_2::OrthoNormalize(Vector3_2 &normal, Vector3_2 &tangent,
                               Vector3_2 &binormal)
{
    normal = Normalized(normal);
    tangent = ProjectOnPlane(tangent, normal);
    tangent = Normalized(tangent);
    binormal = ProjectOnPlane(binormal, tangent);
    binormal = ProjectOnPlane(binormal, normal);
    binormal = Normalized(binormal);
}

Vector3_2 Vector3_2::Project(Vector3_2 a, Vector3_2 b)
{
    float m = Magnitude(b);
    return Dot(a, b) / (m * m) * b;
}

Vector3_2 Vector3_2::ProjectOnPlane(Vector3_2 vector, Vector3_2 planeNormal)
{
    return Reject(vector, planeNormal);
}

Vector3_2 Vector3_2::Reflect(Vector3_2 vector, Vector3_2 planeNormal)
{
    return vector - 2 * Project(vector, planeNormal);
}

Vector3_2 Vector3_2::Reject(Vector3_2 a, Vector3_2 b)
{
    return a - Project(a, b);
}

Vector3_2 Vector3_2::RotateTowards(Vector3_2 current, Vector3_2 target,
                                   float maxRadiansDelta,
                                   float maxMagnitudeDelta)
{
    float magCur = Magnitude(current);
    float magTar = Magnitude(target);
    float newMag = magCur + maxMagnitudeDelta *
                            ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));

    float totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0)
        return Normalized(target) * newMag;
    else if (totalAngle >= M_PI)
        return Normalized(-target) * newMag;

    Vector3_2 axis = Cross(current, target);
    float magAxis = Magnitude(axis);
    if (magAxis == 0)
        axis = Normalized(Cross(current, current + Vector3_2(3.95, 5.32, -4.24)));
    else
        axis /= magAxis;
    current = Normalized(current);
    Vector3_2 newVector = current * cos(maxRadiansDelta) +
                          Cross(axis, current) * sin(maxRadiansDelta);
    return newVector * newMag;
}

Vector3_2 Vector3_2::Scale(Vector3_2 a, Vector3_2 b)
{
    return Vector3_2(a.x * b.x, a.y * b.y, a.z * b.z);
}

Vector3_2 Vector3_2::Slerp(Vector3_2 a, Vector3_2 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

Vector3_2 Vector3_2::SlerpUnclamped(Vector3_2 a, Vector3_2 b, float t)
{
    float magA = Magnitude(a);
    float magB = Magnitude(b);
    a /= magA;
    b /= magB;
    float dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    float theta = acos(dot) * t;
    Vector3_2 relativeVec = Normalized(b - a * dot);
    Vector3_2 newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

float Vector3_2::SqrMagnitude(Vector3_2 v)
{
    return v.x * v.x + v.y * v.y + v.z * v.z;
}

void Vector3_2::ToSpherical(Vector3_2 vector, float &rad, float &theta,
                            float &phi)
{
    rad = Magnitude(vector);
    float v = vector.z / rad;
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    theta = acos(v);
    phi = atan2(vector.y, vector.x);
}


struct Vector3_2& Vector3_2::operator+=(const float rhs)
{
    x += rhs;
    y += rhs;
    z += rhs;
    return *this;
}

struct Vector3_2& Vector3_2::operator-=(const float rhs)
{
    x -= rhs;
    y -= rhs;
    z -= rhs;
    return *this;
}

struct Vector3_2& Vector3_2::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

struct Vector3_2& Vector3_2::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

struct Vector3_2& Vector3_2::operator+=(const Vector3_2 rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

struct Vector3_2& Vector3_2::operator-=(const Vector3_2 rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

char Vector3_2::ToChar(Vector3_2 a) {
    const char* x = (const char*)(int)a.x;
    const char* y = (const char*)(int)a.y;
    const char* z = (const char*)(int)a.z;
    char buffer[25];
    strncpy(buffer, x, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    strncpy(buffer, y, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    strncpy(buffer, z, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    return buffer[25];
}

Vector3_2 operator-(Vector3_2 rhs) { return rhs * -1; }
Vector3_2 operator+(Vector3_2 lhs, const float rhs) { return lhs += rhs; }
Vector3_2 operator-(Vector3_2 lhs, const float rhs) { return lhs -= rhs; }
Vector3_2 operator*(Vector3_2 lhs, const float rhs) { return lhs *= rhs; }
Vector3_2 operator/(Vector3_2 lhs, const float rhs) { return lhs /= rhs; }
Vector3_2 operator+(const float lhs, Vector3_2 rhs) { return rhs += lhs; }
Vector3_2 operator-(const float lhs, Vector3_2 rhs) { return rhs -= lhs; }
Vector3_2 operator*(const float lhs, Vector3_2 rhs) { return rhs *= lhs; }
Vector3_2 operator/(const float lhs, Vector3_2 rhs) { return rhs /= lhs; }
Vector3_2 operator+(Vector3_2 lhs, const Vector3_2 rhs) { return lhs += rhs; }
Vector3_2 operator-(Vector3_2 lhs, const Vector3_2 rhs) { return lhs -= rhs; }

bool operator==(const Vector3_2 lhs, const Vector3_2 rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
}

bool operator!=(const Vector3_2 lhs, const Vector3_2 rhs)
{
    return !(lhs == rhs);
}

struct IVector2;
struct Vector2
{
    union
    {
        struct
        {
            float x;
            float y;
        };
        float data[2];
    };


    /**
     * Constructors.
     */
    inline Vector2();
    inline Vector2(float data[]);
    inline Vector2(float value);
    inline Vector2(float x, float y);
    inline Vector2(IVector2 a);

    /**
     * Constants for common vectors.
     */
    static inline Vector2 Zero();
    static inline Vector2 One();
    static inline Vector2 Right();
    static inline Vector2 Left();
    static inline Vector2 Up();
    static inline Vector2 Down();


    /**
     * Returns the angle between two vectors in radians.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A scalar value.
     */
    static inline float Angle(Vector2 a, Vector2 b);

    /**
     * Returns a vector with its magnitude clamped to maxLength.
     * @param vector: The target vector.
     * @param maxLength: The maximum length of the return vector.
     * @return: A new vector.
     */
    static inline Vector2 ClampMagnitude(Vector2 vector, float maxLength);

    /**
     * Returns the component of a in the direction of b (scalar projection).
     * @param a: The target vector.
     * @param b: The vector being compared against.
     * @return: A scalar value.
     */
    static inline float Component(Vector2 a, Vector2 b);

    /**
     * Returns the distance between a and b.
     * @param a: The first point.
     * @param b: The second point.
     * @return: A scalar value.
     */
    static inline float Distance(Vector2 a, Vector2 b);

    /**
     * Returns the dot product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A scalar value.
     */
    static inline float Dot(Vector2 lhs, Vector2 rhs);

    /**
     * Converts a polar representation of a vector into cartesian
     * coordinates.
     * @param rad: The magnitude of the vector.
     * @param theta: The angle from the X axis.
     * @return: A new vector.
     */
    static inline Vector2 FromPolar(float rad, float theta);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line. The vector is clamped to never go beyond the end points.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1].
     * @return: A new vector.
     */
    static inline Vector2 Lerp(Vector2 a, Vector2 b, float t);

    /**
     * Returns a vector linearly interpolated between a and b, moving along
     * a straight line.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1] (no actual bounds).
     * @return: A new vector.
     */
    static inline Vector2 LerpUnclamped(Vector2 a, Vector2 b, float t);

    /**
     * Returns the magnitude of a vector.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float Magnitude(Vector2 v);

    /**
     * Returns a vector made from the largest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector2 Max(Vector2 a, Vector2 b);

    /**
     * Returns a vector made from the smallest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector2 Min(Vector2 a, Vector2 b);

    /**
     * Returns a vector "maxDistanceDelta" units closer to the target. This
     * interpolation is in a straight line, and will not overshoot.
     * @param current: The current position.
     * @param target: The destination position.
     * @param maxDistanceDelta: The maximum distance to move.
     * @return: A new vector.
     */
    static inline Vector2 MoveTowards(Vector2 current, Vector2 target,
                                      float maxDistanceDelta);

    /**
     * Returns a new vector with magnitude of one.
     * @param v: The vector in question.
     * @return: A new vector.
     */
    static inline Vector2 Normalized(Vector2 v);

    /**
     * Creates a new coordinate system out of the two vectors.
     * Normalizes "normal" and normalizes "tangent" and makes it orthogonal to
     * "normal"..
     * @param normal: A reference to the first axis vector.
     * @param tangent: A reference to the second axis vector.
     */
    static inline void OrthoNormalize(Vector2 &normal, Vector2 &tangent);

    /**
     * Returns the vector projection of a onto b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector2 Project(Vector2 a, Vector2 b);

    /**
     * Returns a vector reflected about the provided line.
     * This behaves as if there is a plane with the line as its normal, and the
     * vector comes in and bounces off this plane.
     * @param vector: The vector traveling inward at the imaginary plane.
     * @param line: The line about which to reflect.
     * @return: A new vector pointing outward from the imaginary plane.
     */
    static inline Vector2 Reflect(Vector2 vector, Vector2 line);

    /**
     * Returns the vector rejection of a on b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector2 Reject(Vector2 a, Vector2 b);

    /**
     * Rotates vector "current" towards vector "target" by "maxRadiansDelta".
     * This treats the vectors as directions and will linearly interpolate
     * between their magnitudes by "maxMagnitudeDelta". This function does not
     * overshoot. If a negative delta is supplied, it will rotate away from
     * "target" until it is pointing the opposite direction, but will not
     * overshoot that either.
     * @param current: The starting direction.
     * @param target: The destination direction.
     * @param maxRadiansDelta: The maximum number of radians to rotate.
     * @param maxMagnitudeDelta: The maximum delta for magnitude interpolation.
     * @return: A new vector.
     */
    static inline Vector2 RotateTowards(Vector2 current, Vector2 target,
                                        float maxRadiansDelta,
                                        float maxMagnitudeDelta);

    /**
     * Multiplies two vectors component-wise.
     * @param a: The lhs of the multiplication.
     * @param b: The rhs of the multiplication.
     * @return: A new vector.
     */
    static inline Vector2 Scale(Vector2 a, Vector2 b);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is clamped to 0 <= t <= 1.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector2 Slerp(Vector2 a, Vector2 b, float t);

    /**
     * Returns a vector rotated towards b from a by the percent t.
     * Since interpolation is done spherically, the vector moves at a constant
     * angular velocity. This rotation is unclamped.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector2 SlerpUnclamped(Vector2 a, Vector2 b, float t);

    /**
     * Returns the squared magnitude of a vector.
     * This is useful when comparing relative lengths, where the exact length
     * is not important, and much time can be saved by not calculating the
     * square root.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float SqrMagnitude(Vector2 v);

    /**
     * Calculates the polar coordinate space representation of a vector.
     * @param vector: The vector to convert.
     * @param rad: The magnitude of the vector.
     * @param theta: The angle from the X axis.
     */
    static inline void ToPolar(Vector2 vector, float &rad, float &theta);


    /**
     * Operator overloading.
     */
    inline struct Vector2& operator+=(const float rhs);
    inline struct Vector2& operator-=(const float rhs);
    inline struct Vector2& operator*=(const float rhs);
    inline struct Vector2& operator/=(const float rhs);
    inline struct Vector2& operator+=(const Vector2 rhs);
    inline struct Vector2& operator-=(const Vector2 rhs);
};

inline Vector2 operator-(Vector2 rhs);
inline Vector2 operator+(Vector2 lhs, const float rhs);
inline Vector2 operator-(Vector2 lhs, const float rhs);
inline Vector2 operator*(Vector2 lhs, const float rhs);
inline Vector2 operator/(Vector2 lhs, const float rhs);
inline Vector2 operator+(const float lhs, Vector2 rhs);
inline Vector2 operator-(const float lhs, Vector2 rhs);
inline Vector2 operator*(const float lhs, Vector2 rhs);
inline Vector2 operator*(Vector2 lhs, Vector2 rhs);
inline Vector2 operator/(const float lhs, Vector2 rhs);
inline Vector2 operator+(Vector2 lhs, const Vector2 rhs);
inline Vector2 operator-(Vector2 lhs, const Vector2 rhs);
inline bool operator==(const Vector2 lhs, const Vector2 rhs);
inline bool operator!=(const Vector2 lhs, const Vector2 rhs);



/*******************************************************************************
 * Implementation
 */

Vector2::Vector2() : x(0), y(0) {}
Vector2::Vector2(float data[]) : x(data[0]), y(data[1]) {}
Vector2::Vector2(float value) : x(value), y(value) {}
Vector2::Vector2(float x, float y) : x(x), y(y) {}


Vector2 Vector2::Zero() { return Vector2(0, 0); }
Vector2 Vector2::One() { return Vector2(1, 1); }
Vector2 Vector2::Right() { return Vector2(1, 0); }
Vector2 Vector2::Left() { return Vector2(-1, 0); }
Vector2 Vector2::Up() { return Vector2(0, 1); }
Vector2 Vector2::Down() { return Vector2(0, -1); }


float Vector2::Angle(Vector2 a, Vector2 b)
{
    float v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

Vector2 Vector2::ClampMagnitude(Vector2 vector, float maxLength)
{
    float length = Magnitude(vector);
    if (length > maxLength)
        vector *= maxLength / length;
    return vector;
}

float Vector2::Component(Vector2 a, Vector2 b)
{
    return Dot(a, b) / Magnitude(b);
}

float Vector2::Distance(Vector2 a, Vector2 b)
{
    return Vector2::Magnitude(a - b);
}

float Vector2::Dot(Vector2 lhs, Vector2 rhs)
{
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 Vector2::FromPolar(float rad, float theta)
{
    Vector2 v;
    v.x = rad * cos(theta);
    v.y = rad * sin(theta);
    return v;
}

Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

Vector2 Vector2::LerpUnclamped(Vector2 a, Vector2 b, float t)
{
    return (b - a) * t + a;
}

float Vector2::Magnitude(Vector2 v)
{
    return sqrt(SqrMagnitude(v));
}

Vector2 Vector2::Max(Vector2 a, Vector2 b)
{
    float x = a.x > b.x ? a.x : b.x;
    float y = a.y > b.y ? a.y : b.y;
    return Vector2(x, y);
}

Vector2 Vector2::Min(Vector2 a, Vector2 b)
{
    float x = a.x > b.x ? b.x : a.x;
    float y = a.y > b.y ? b.y : a.y;
    return Vector2(x, y);
}

Vector2 Vector2::MoveTowards(Vector2 current, Vector2 target,
                             float maxDistanceDelta)
{
    Vector2 d = target - current;
    float m = Magnitude(d);
    if (m < maxDistanceDelta || m == 0)
        return target;
    return current + (d * maxDistanceDelta / m);
}

Vector2 Vector2::Normalized(Vector2 v)
{
    float mag = Magnitude(v);
    if (mag == 0)
        return Vector2::Zero();
    return v / mag;
}

void Vector2::OrthoNormalize(Vector2 &normal, Vector2 &tangent)
{
    normal = Normalized(normal);
    tangent = Reject(tangent, normal);
    tangent = Normalized(tangent);
}

Vector2 Vector2::Project(Vector2 a, Vector2 b)
{
    float m = Magnitude(b);
    return Dot(a, b) / (m * m) * b;
}

Vector2 Vector2::Reflect(Vector2 vector, Vector2 planeNormal)
{
    return vector - 2 * Project(vector, planeNormal);
}

Vector2 Vector2::Reject(Vector2 a, Vector2 b)
{
    return a - Project(a, b);
}

Vector2 Vector2::RotateTowards(Vector2 current, Vector2 target,
                               float maxRadiansDelta,
                               float maxMagnitudeDelta)
{
    float magCur = Magnitude(current);
    float magTar = Magnitude(target);
    float newMag = magCur + maxMagnitudeDelta *
                            ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));

    float totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0)
        return Normalized(target) * newMag;
    else if (totalAngle >= M_PI)
        return Normalized(-target) * newMag;

    float axis = current.x * target.y - current.y * target.x;
    axis = axis / fabs(axis);
    if (!(1 - fabs(axis) < 0.00001))
        axis = 1;
    current = Normalized(current);
    Vector2 newVector = current * cos(maxRadiansDelta) +
                        Vector2(-current.y, current.x) * sin(maxRadiansDelta) * axis;
    return newVector * newMag;
}

Vector2 Vector2::Scale(Vector2 a, Vector2 b)
{
    return Vector2(a.x * b.x, a.y * b.y);
}

Vector2 Vector2::Slerp(Vector2 a, Vector2 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

Vector2 Vector2::SlerpUnclamped(Vector2 a, Vector2 b, float t)
{
    float magA = Magnitude(a);
    float magB = Magnitude(b);
    a /= magA;
    b /= magB;
    float dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    float theta = acos(dot) * t;
    Vector2 relativeVec = Normalized(b - a * dot);
    Vector2 newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

float Vector2::SqrMagnitude(Vector2 v)
{
    return v.x * v.x + v.y * v.y;
}

void Vector2::ToPolar(Vector2 vector, float &rad, float &theta)
{
    rad = Magnitude(vector);
    theta = atan2(vector.y, vector.x);
}


struct Vector2& Vector2::operator+=(const float rhs)
{
    x += rhs;
    y += rhs;
    return *this;
}

struct Vector2& Vector2::operator-=(const float rhs)
{
    x -= rhs;
    y -= rhs;
    return *this;
}

struct Vector2& Vector2::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
}

struct Vector2& Vector2::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    return *this;
}

struct Vector2& Vector2::operator+=(const Vector2 rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

struct Vector2& Vector2::operator-=(const Vector2 rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vector2 operator-(Vector2 rhs) { return rhs * -1; }
Vector2 operator+(Vector2 lhs, const float rhs) { return lhs += rhs; }
Vector2 operator-(Vector2 lhs, const float rhs) { return lhs -= rhs; }
Vector2 operator*(Vector2 lhs, const float rhs) { return lhs *= rhs; }
Vector2 operator/(Vector2 lhs, const float rhs) { return lhs /= rhs; }
Vector2 operator+(const float lhs, Vector2 rhs) { return rhs += lhs; }
Vector2 operator-(const float lhs, Vector2 rhs) { return rhs -= lhs; }
Vector2 operator*(const float lhs, Vector2 rhs) { return rhs *= lhs; }
Vector2 operator*(Vector2 lhs, Vector2 rhs) { return Vector2(lhs.x * rhs.x, lhs.y * rhs.y); }
Vector2 operator/(const float lhs, Vector2 rhs) { return rhs /= lhs; }
Vector2 operator+(Vector2 lhs, const Vector2 rhs) { return lhs += rhs; }
Vector2 operator-(Vector2 lhs, const Vector2 rhs) { return lhs -= rhs; }

bool operator==(const Vector2 lhs, const Vector2 rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}

bool operator!=(const Vector2 lhs, const Vector2 rhs)
{
    return !(lhs == rhs);
}


struct IVector2 {
    float x;
    float y;

    inline IVector2(float x, float y);
    inline IVector2(Vector2 a);
    inline IVector2();
};
IVector2::IVector2() {};
IVector2::IVector2(float x, float y) : x(x), y(y) {}
IVector2::IVector2(Vector2 a) : x(a.x), y(a.y) {}
Vector2::Vector2(IVector2 a) : x(a.x), y(a.y) {}
bool operator==(const IVector2 lhs, const Vector2 rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator==(const IVector2 lhs, const IVector2 rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y;
}
bool operator!=(const IVector2 lhs, const Vector2 rhs)
{
    return !(lhs == rhs);
}
bool operator!=(const IVector2 lhs, const IVector2 rhs)
{
    return !(lhs == rhs);
}
#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <string.h>

struct Vector4
{
    float X;
    float Y;
    float Z;

    Vector4();
    Vector4(float X, float Y, float Z);
    ~Vector4();


    /**
     * Constructors.
     */


    /**
     * Constants for common vectors.
     */
    static inline Vector4 Zero();
    static inline Vector4 One();
    static inline Vector4 Right();
    static inline Vector4 Left();
    static inline Vector4 Up();
    static inline Vector4 Down();
    static inline Vector4 Forward();
    static inline Vector4 Backward();


    /**
     * Returns the angle between two vectors in radians.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A scalar value.
     */
    static inline float Angle(Vector4 a, Vector4 b);

    /**
     * Returns a vector with its magnitude clamped to m.XLength.
     * @param vector: The target vector.
     * @param m.XLength: The m.Ximum length of the return vector.
     * @return: A new vector.
     */
    static inline Vector4 ClampMagnitude(Vector4 vector, float maXLength);

    /**
     * Returns the component of a in the direction of b (scalar projection).
     * @param a: The target vector.
     * @param b: The vector being compared against.
     * @return: A scalar value.
     */
    static inline float Component(Vector4 a, Vector4 b);

    /**
     * Returns the cross product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A new vector.
     */
    static inline Vector4 Cross(Vector4 lhs, Vector4 rhs);

    /**
     * Returns the distance between a and b.
     * @param a: The first point.
     * @param b: The second point.
     * @return: A scalar value.
     */
    static inline float Distance(Vector4 a, Vector4 b);

    static inline char ToChar(Vector4 a);

    /**
     * Returns the dot product of two vectors.
     * @param lhs: The left side of the multiplication.
     * @param rhs: The right side of the multiplication.
     * @return: A scalar value.
     */
    static inline float Dot(Vector4 lhs, Vector4 rhs);

    /**
     * Converts a spherical representation of a vector into cartesian
     * coordinates.
     * This uses the ISO convention (radius r, inclination theta, .Zimuth phi).
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the..Y plane from the.X .Xis.
     * @param phi: The angle from the positive.Z .Xis to the vector.
     * @return: A new vector.
     */
    static inline Vector4 FromSpherical(float rad, float theta, float phi);

    /**
     * Returns a vector linear.Y interpolated between a and b, moving along
     * a straight line. The vector is clamped to never go b.Yond the end points.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1].
     * @return: A new vector.
     */
    static inline Vector4 Lerp(Vector4 a, Vector4 b, float t);

    /**
     * Returns a vector linear.Y interpolated between a and b, moving along
     * a straight line.
     * @param a: The starting point.
     * @param b: The ending point.
     * @param t: The interpolation value [0-1] (no actual bounds).
     * @return: A new vector.
     */
    static inline Vector4 LerpUnclamped(Vector4 a, Vector4 b, float t);

    /**
     * Returns the magnitude of a vector.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float Magnitude(Vector4 v);

    /**
     * Returns a vector made from the largest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector4 max(Vector4 a, Vector4 b);

    /**
     * Returns a vector made from the smallest components of two other vectors.
     * @param a: The first vector.
     * @param b: The second vector.
     * @return: A new vector.
     */
    static inline Vector4 Min(Vector4 a, Vector4 b);

    /**
     * Returns a vector "m.XDistanceDelta" units closer to the target. This
     * interpolation is in a straight line, and will not overshoot.
     * @param current: The current position.
     * @param target: The destination position.
     * @param m.XDistanceDelta: The m.Ximum distance to move.
     * @return: A new vector.
     */
    static inline Vector4 MoveTowards(Vector4 current, Vector4 target,
                                      float maXDistanceDelta);

    /**
     * Returns a new vector with magnitude of one.
     * @param v: The vector in question.
     * @return: A new vector.
     */
    static inline Vector4 Normalized(Vector4 v);

    /**
     * Returns an arbitra.Y vector orthogonal to the input.
     * This vector is not normal.Zed.
     * @param v: The input vector.
     * @return: A new vector.
     */
    static inline Vector4 Orthogonal(Vector4 v);

    /**
     * Creates a new coordinate .Ystem out of the three vectors.
     * Normal.Zes "normal", normal.Zes "tangent" and makes it orthogonal to
     * "normal" and normal.Zes "binormal" and makes it orthogonal to both
     * "normal" and "tangent".
     * @param normal: A reference to the first .Xis vector.
     * @param tangent: A reference to the second .Xis vector.
     * @param binormal: A reference to the third .Xis vector.
     */
    static inline void OrthoNormalize(Vector4 &normal, Vector4 &tangent,
                                      Vector4 &binormal);

    /**
     * Returns the vector projection of a onto b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector4 Project(Vector4 a, Vector4 b);

    /**
     * Returns a vector projected onto a plane orthogonal to "planeNormal".
     * This can be visual.Zed as the shadow of the vector onto the plane, if
     * the light source were in the direction of the plane normal.
     * @param vector: The vector to project.
     * @param planeNormal: The normal of the plane onto which to project.
     * @param: A new vector.
     */
    static inline Vector4 ProjectOnPlane(Vector4 vector, Vector4 planeNormal);

    /**
     * Returns a vector reflected off the plane orthogonal to the normal.
     * The input vector is pointed inward, at the plane, and the return vector
     * is pointed outward from the plane, like a beam of light hitting and then
     * reflecting off a mirror.
     * @param vector: The vector traveling inward at the plane.
     * @param planeNormal: The normal of the plane off of which to reflect.
     * @return: A new vector pointing outward from the plane.
     */
    static inline Vector4 Reflect(Vector4 vector, Vector4 planeNormal);

    /**
     * Returns the vector rejection of a on b.
     * @param a: The target vector.
     * @param b: The vector being projected onto.
     * @return: A new vector.
     */
    static inline Vector4 Reject(Vector4 a, Vector4 b);

    /**
     * Rotates vector "current" towards vector "target" .Y "m.XRadiansDelta".
     * This treats the vectors as directions and will linear.Y interpolate
     * between their magnitudes .Y "m.XMagnitudeDelta". This function does not
     * overshoot. If a negative delta is supplied, it will rotate aw.Y from
     * "target" until it is pointing the opposite direction, but will not
     * overshoot that either.
     * @param current: The starting direction.
     * @param target: The destination direction.
     * @param m.XRadiansDelta: The m.Ximum number of radians to rotate.
     * @param m.XMagnitudeDelta: The m.Ximum delta for magnitude interpolation.
     * @return: A new vector.
     */
    static inline Vector4 RotateTowards(Vector4 current, Vector4 target,
                                        float maxRadiansDelta,
                                        float maxMagnitudeDelta);

    /**
     * Multiplies two vectors element-wise.
     * @param a: The lhs of the multiplication.
     * @param b: The rhs of the multiplication.
     * @return: A new vector.
     */
    static inline Vector4 Scale(Vector4 a, Vector4 b);

    /**
     * Returns a vector rotated towards b from a .Y the percent t.
     * Since interpolation is done spherical.Y, the vector moves at a constant
     * angular veloci.Y. This rotation is clamped to 0 <= t <= 1.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector4 Slerp(Vector4 a, Vector4 b, float t);

    /**
     * Returns a vector rotated towards b from a .Y the percent t.
     * Since interpolation is done spherical.Y, the vector moves at a constant
     * angular veloci.Y. This rotation is unclamped.
     * @param a: The starting direction.
     * @param b: The ending direction.
     * @param t: The interpolation value [0-1].
     */
    static inline Vector4 SlerpUnclamped(Vector4 a, Vector4 b, float t);

    /**
     * Returns the squared magnitude of a vector.
     * This is useful when comparing relative lengths, where the .Xact length
     * is not important, and much time can be saved .Y not calculating the
     * square root.
     * @param v: The vector in question.
     * @return: A scalar value.
     */
    static inline float SqrMagnitude(Vector4 v);

    /**
     * Calculates the spherical coordinate space representation of a vector.
     * This uses the ISO convention (radius r, inclination theta, .Zimuth phi).
     * @param vector: The vector to convert.
     * @param rad: The magnitude of the vector.
     * @param theta: The angle in the..Y plane from the.X .Xis.
     * @param phi: The angle from the positive.Z .Xis to the vector.
     */
    static inline void ToSpherical(Vector4 vector, float &rad, float &theta,
                                   float &phi);


    /**
     * Operator overloading.
     */
    inline struct Vector4& operator+=(const float rhs);
    inline struct Vector4& operator-=(const float rhs);
    inline struct Vector4& operator*=(const float rhs);
    inline struct Vector4& operator/=(const float rhs);
    inline struct Vector4& operator+=(const Vector4 rhs);
    inline struct Vector4& operator-=(const Vector4 rhs);
};

inline Vector4 operator-(Vector4 rhs);
inline Vector4 operator+(Vector4 lhs, const float rhs);
inline Vector4 operator-(Vector4 lhs, const float rhs);
inline Vector4 operator*(Vector4 lhs, const float rhs);
inline Vector4 operator/(Vector4 lhs, const float rhs);
inline Vector4 operator+(const float lhs, Vector4 rhs);
inline Vector4 operator-(const float lhs, Vector4 rhs);
inline Vector4 operator*(const float lhs, Vector4 rhs);
inline Vector4 operator/(const float lhs, Vector4 rhs);
inline Vector4 operator+(Vector4 lhs, const Vector4 rhs);
inline Vector4 operator-(Vector4 lhs, const Vector4 rhs);
inline bool operator==(const Vector4 lhs, const Vector4 rhs);
inline bool operator!=(const Vector4 lhs, const Vector4 rhs);



/*******************************************************************************
 * Implementation
 */

Vector4::Vector4() {}
Vector4::Vector4(float X, float Y, float Z) : X(X),Y(Y),Z(Z) {}
Vector4::~Vector4() {}


Vector4 Vector4::Zero() { return Vector4(0, 0, 0); }
Vector4 Vector4::One() { return Vector4(1, 1, 1); }
Vector4 Vector4::Right() { return Vector4(1, 0, 0); }
Vector4 Vector4::Left() { return Vector4(-1, 0, 0); }
Vector4 Vector4::Up() { return Vector4(0, 1, 0); }
Vector4 Vector4::Down() { return Vector4(0, -1, 0); }
Vector4 Vector4::Forward() { return Vector4(0, 0, 1); }
Vector4 Vector4::Backward() { return Vector4(0, 0, -1); }


float Vector4::Angle(Vector4 a, Vector4 b)
{
    float v = Dot(a, b) / (Magnitude(a) * Magnitude(b));
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    return acos(v);
}

Vector4 Vector4::ClampMagnitude(Vector4 vector, float maxLength)
{
    float length = Magnitude(vector);
    if (length > maxLength)
        vector *= maxLength / length;
    return vector;
}

float Vector4::Component(Vector4 a, Vector4 b)
{
    return Dot(a, b) / Magnitude(b);
}

Vector4 Vector4::Cross(Vector4 lhs, Vector4 rhs)
{
    float X = lhs.Y * rhs.Z - lhs.Z * rhs.Y;
    float Y = lhs.Z * rhs.X - lhs.X * rhs.Z;
    float Z = lhs.X * rhs.Y - lhs.Y * rhs.X;
    return Vector4(X,Y,Z);
}

float Vector4::Distance(Vector4 a, Vector4 b)
{
    return Vector4::Magnitude(a - b);
}

float Vector4::Dot(Vector4 lhs, Vector4 rhs)
{
    return lhs.X * rhs.X + lhs.Y * rhs.Y + lhs.Z * rhs.Z;
}

Vector4 Vector4::FromSpherical(float rad, float theta, float phi)
{
    Vector4 v;
    v.X = rad * sin(theta) * cos(phi);
    v.Y = rad * sin(theta) * sin(phi);
    v.Z = rad * cos(theta);
    return v;
}

Vector4 Vector4::Lerp(Vector4 a, Vector4 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return LerpUnclamped(a, b, t);
}

Vector4 Vector4::LerpUnclamped(Vector4 a, Vector4 b, float t)
{
    return (b - a) * t + a;
}

float Vector4::Magnitude(Vector4 v)
{
    return sqrt(SqrMagnitude(v));
}

Vector4 Vector4::max(Vector4 a, Vector4 b)
{
    float X = a.X > b.X ? a.X : b.X;
    float Y = a.Y > b.Y ? a.Y : b.Y;
    float Z = a.Z > b.Z ? a.Z : b.Z;
    return Vector4(X,Y,Z);
}

Vector4 Vector4::Min(Vector4 a, Vector4 b)
{
    float X = a.X > b.X ? b.X : a.X;
    float Y = a.Y > b.Y ? b.Y : a.Y;
    float Z = a.Z > b.Z ? b.Z : a.Z;
    return Vector4(X,Y,Z);
}

Vector4 Vector4::MoveTowards(Vector4 current, Vector4 target,
                             float maxDistanceDelta)
{
    Vector4 d = target - current;
    float m = Magnitude(d);
    if (m < maxDistanceDelta || m == 0)
        return target;
    return current + (d * maxDistanceDelta / m);
}

Vector4 Vector4::Normalized(Vector4 v)
{
    float mag = Magnitude(v);
    if (mag == 0)
        return Vector4::Zero();
    return v / mag;
}

Vector4 Vector4::Orthogonal(Vector4 v)
{
    return v.Z < v.X ? Vector4(v.Y, -v.X, 0) : Vector4(0, -v.Z, v.Y);
}

void Vector4::OrthoNormalize(Vector4 &normal, Vector4 &tangent,
                             Vector4 &binormal)
{
    normal = Normalized(normal);
    tangent = ProjectOnPlane(tangent, normal);
    tangent = Normalized(tangent);
    binormal = ProjectOnPlane(binormal, tangent);
    binormal = ProjectOnPlane(binormal, normal);
    binormal = Normalized(binormal);
}

Vector4 Vector4::Project(Vector4 a, Vector4 b)
{
    float m = Magnitude(b);
    return Dot(a, b) / (m * m) * b;
}

Vector4 Vector4::ProjectOnPlane(Vector4 vector, Vector4 planeNormal)
{
    return Reject(vector, planeNormal);
}

Vector4 Vector4::Reflect(Vector4 vector, Vector4 planeNormal)
{
    return vector - 2 * Project(vector, planeNormal);
}

Vector4 Vector4::Reject(Vector4 a, Vector4 b)
{
    return a - Project(a, b);
}

Vector4 Vector4::RotateTowards(Vector4 current, Vector4 target,
                               float maxRadiansDelta,
                               float maxMagnitudeDelta)
{
    float magCur = Magnitude(current);
    float magTar = Magnitude(target);
    float newMag = magCur + maxMagnitudeDelta *
                            ((magTar > magCur) - (magCur > magTar));
    newMag = fmin(newMag, fmax(magCur, magTar));
    newMag = fmax(newMag, fmin(magCur, magTar));

    float totalAngle = Angle(current, target) - maxRadiansDelta;
    if (totalAngle <= 0)
        return Normalized(target) * newMag;
    else if (totalAngle >= M_PI)
        return Normalized(-target) * newMag;

    Vector4 axis = Cross(current, target);
    float magaxis = Magnitude(axis);
    if (magaxis == 0)
        axis = Normalized(Cross(current, current + Vector4(3.95, 5.32, -4.24)));
    else
        axis /= magaxis;
    current = Normalized(current);
    Vector4 newVector = current * cos(maxRadiansDelta) +
                        Cross(axis, current) * sin(maxRadiansDelta);
    return newVector * newMag;
}

Vector4 Vector4::Scale(Vector4 a, Vector4 b)
{
    return Vector4(a.X * b.X, a.Y * b.Y, a.Z * b.Z);
}

Vector4 Vector4::Slerp(Vector4 a, Vector4 b, float t)
{
    if (t < 0) return a;
    else if (t > 1) return b;
    return SlerpUnclamped(a, b, t);
}

Vector4 Vector4::SlerpUnclamped(Vector4 a, Vector4 b, float t)
{
    float magA = Magnitude(a);
    float magB = Magnitude(b);
    a /= magA;
    b /= magB;
    float dot = Dot(a, b);
    dot = fmax(dot, -1.0);
    dot = fmin(dot, 1.0);
    float theta = acos(dot) * t;
    Vector4 relativeVec = Normalized(b - a * dot);
    Vector4 newVec = a * cos(theta) + relativeVec * sin(theta);
    return newVec * (magA + (magB - magA) * t);
}

float Vector4::SqrMagnitude(Vector4 v)
{
    return v.X * v.X + v.Y * v.Y + v.Z * v.Z;
}

void Vector4::ToSpherical(Vector4 vector, float &rad, float &theta,
                          float &phi)
{
    rad = Magnitude(vector);
    float v = vector.Z / rad;
    v = fmax(v, -1.0);
    v = fmin(v, 1.0);
    theta = acos(v);
    phi = atan2(vector.Y, vector.X);
}


struct Vector4& Vector4::operator+=(const float rhs)
{
    X += rhs;
    Y += rhs;
    Z += rhs;
    return *this;
}

struct Vector4& Vector4::operator-=(const float rhs)
{
    X -= rhs;
    Y -= rhs;
    Z -= rhs;
    return *this;
}

struct Vector4& Vector4::operator*=(const float rhs)
{
    X *= rhs;
    Y *= rhs;
    Z *= rhs;
    return *this;
}

struct Vector4& Vector4::operator/=(const float rhs)
{
    X /= rhs;
    Y /= rhs;
    Z /= rhs;
    return *this;
}

struct Vector4& Vector4::operator+=(const Vector4 rhs)
{
    X += rhs.X;
    Y += rhs.Y;
    Z += rhs.Z;
    return *this;
}

struct Vector4& Vector4::operator-=(const Vector4 rhs)
{
    X -= rhs.X;
    Y -= rhs.Y;
    Z -= rhs.Z;
    return *this;
}

char Vector4::ToChar(Vector4 a) {
    const char* X = (const char*)(int)a.X;
    const char* Y = (const char*)(int)a.Y;
    const char* Z = (const char*)(int)a.Z;
    char buffer[25];
    strncpy(buffer, X, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    strncpy(buffer, Y, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    strncpy(buffer, Z, sizeof(buffer));
    strncpy(buffer, ", ", sizeof(buffer));
    return buffer[25];
}

Vector4 operator-(Vector4 rhs) { return rhs * -1; }
Vector4 operator+(Vector4 lhs, const float rhs) { return lhs += rhs; }
Vector4 operator-(Vector4 lhs, const float rhs) { return lhs -= rhs; }
Vector4 operator*(Vector4 lhs, const float rhs) { return lhs *= rhs; }
Vector4 operator/(Vector4 lhs, const float rhs) { return lhs /= rhs; }
Vector4 operator+(const float lhs, Vector4 rhs) { return rhs += lhs; }
Vector4 operator-(const float lhs, Vector4 rhs) { return rhs -= lhs; }
Vector4 operator*(const float lhs, Vector4 rhs) { return rhs *= lhs; }
Vector4 operator/(const float lhs, Vector4 rhs) { return rhs /= lhs; }
Vector4 operator+(Vector4 lhs, const Vector4 rhs) { return lhs += rhs; }
Vector4 operator-(Vector4 lhs, const Vector4 rhs) { return lhs -= rhs; }

bool operator==(const Vector4 lhs, const Vector4 rhs)
{
    return lhs.X == rhs.X && lhs.Y == rhs.Y && lhs.Z == rhs.Z;
}

bool operator!=(const Vector4 lhs, const Vector4 rhs)
{
    return !(lhs == rhs);
}
