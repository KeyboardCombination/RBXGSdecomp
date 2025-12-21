#include "util/Quaternion.h"

namespace RBX
{
	Quaternion::Quaternion(const G3D::Matrix3& rot)
	{
		// https://euclideanspace.com/maths/geometry/rotations/conversions/matrixToQuaternion/index.htm
		float trace = rot[0][0] + rot[1][1] + rot[2][2];
		if (trace > 0)
		{
			float S = sqrt(trace + 1);
			this->w = S * 0.5;
			float reciprocal = 0.5 / S;
			this->x = (rot[2][1] - rot[1][2]) * reciprocal;
			this->y = (rot[0][2] - rot[2][0]) * reciprocal;
			this->z = (rot[1][0] - rot[0][1]) * reciprocal;
		}
		else
		{
			if (rot[0][0] > rot[1][1] && rot[0][0] > rot[2][2])
			{
				float S = -sqrt(rot[0][0] + 1.0 - rot[1][1] - rot[2][2]);
				this->x = S * 0.5;
				float reciprocal = 0.5 / S;
				this->y = (rot[1][0] + rot[0][1]) * reciprocal;
				this->z = (rot[2][0] + rot[0][2]) * reciprocal;
				this->w = reciprocal * (rot[2][1] - rot[1][2]);
			}
			else
			{
				if (rot[1][1] > rot[2][2])
				{
					float S = -sqrt(rot[1][1] + 1.0 - rot[0][0] - rot[2][2]);
					this->y = S * 0.5;
					float reciprocal = 0.5 / S;
					this->x = (rot[1][0] + rot[0][1]) * reciprocal;
					this->z = (rot[2][1] + rot[1][2]) * reciprocal;
					float v9 = rot[0][2] - rot[2][0];
					this->w = reciprocal * v9;
				}
				else
				{
					float S = -sqrt(rot[2][2] + 1.0 - rot[0][0] - rot[1][1]);
					this->z = S * 0.5;
					float reciprocal = 0.5 / S;
					this->x = (rot[2][0] + rot[0][2]) * reciprocal;
					this->y = (rot[2][1] + rot[1][2]) * reciprocal;
					float v9 = rot[1][0] - rot[0][1];
					this->w = reciprocal * v9;
				}
			}
		}
	}

	Quaternion& Quaternion::operator=(const Quaternion& other)
	{
		this->w = other.w;
		this->x = other.x;
		this->y = other.y;
		this->z = other.z;
		return *this;
	}

	//needs to be moved to the header
	Quaternion Quaternion::operator*(const Quaternion& other) const
	{
		Vector3& thisConvert = *(G3D::Vector3*)this;
		Vector3& otherConvert = *(G3D::Vector3*)&other;
		float thisW = this->w;
		float otherW = other.w;

		return Quaternion(otherConvert * thisW + thisConvert * otherW + thisConvert.cross(otherConvert), thisW * otherW - thisConvert.dot(otherConvert));
	}

	float& Quaternion::operator[](int i) const
	{
		return ((float*)this)[i];
	}

	void Quaternion::normalize()
	{
		float sqY = square(this->y);
		float len = sqY + square(this->x) + square(this->z) + square(this->w);
		float invLen = rsq(len); // Is there evidence they used rsqrt?
		this->x *= invLen;
		this->y *= invLen;
		this->z *= invLen;
		this->w *= invLen;
	}

	void Quaternion::toRotationMatrix(G3D::Matrix3& rot) const
	{
		// https://euclideanspace.com/maths/geometry/rotations/conversions/quaternionToMatrix/index.htm
		Quaternion QuatMul = *this * 2.0f;

		float xx = x * QuatMul.x;
		float xy = x * QuatMul.y;
		float xz = x * QuatMul.z;

		float wx = w * QuatMul.x;
		float wy = w * QuatMul.y;
		float wz = w * QuatMul.z;

		float yy = y * QuatMul.y;
		float yz = y * QuatMul.z;
		float zz = z * QuatMul.z;

		rot[0][0] = 1.0 - (zz + yy);
		rot[0][1] = xy - wz;
		rot[0][2] = wy + xz;

		rot[1][0] = xy + wz;
		rot[1][1] = 1.0 - (zz + xx);
		rot[1][2] = yz - wx;

		rot[2][0] = xz - wy;
		rot[2][1] = wx + yz;
		rot[2][2] = 1.0 - (xx + yy);
	}

	//needs to be moved to the header
	float Quaternion::maxComponent() const
	{
		Quaternion qAbs = Quaternion(fabs(w), fabs(z), fabs(y), fabs(x));
		return std::max(std::max(qAbs.w, qAbs.z), std::max(qAbs.y, qAbs.x));
	}
}