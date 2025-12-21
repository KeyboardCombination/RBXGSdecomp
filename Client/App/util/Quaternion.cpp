#include "util/Quaternion.h"

namespace RBX
{
	Quaternion::Quaternion(const G3D::Matrix3& rot)
	{
		float v2 = rot[0][0] + rot[1][1] + rot[2][2];
		if (v2 > 0)
		{
			float v3 = sqrt(v2 + 1);
			this->w = v3 * 0.5;
			float v4 = 0.5 / v3;
			this->x = (rot[2][1] - rot[1][2]) * v4;
			this->y = (rot[0][2] - rot[2][0]) * v4;
			this->z = (rot[1][0] - rot[0][1]) * v4;
		}
		else
		{
			if (rot[0][0] > rot[1][1] && rot[0][0] > rot[2][2])
			{
				float v5 = -sqrt(rot[0][0] + 1.0 - rot[1][1] - rot[2][2]);
				this->x = v5 * 0.5;
				float v6 = 0.5 / v5;
				this->y = (rot[1][0] + rot[0][1]) * v6;
				this->z = (rot[2][0] + rot[0][2]) * v6;
				this->w = v6 * (rot[2][1] - rot[1][2]);
			}
			else
			{
				if (rot[1][1] > rot[2][2])
				{
					float v7 = -sqrt(rot[1][1] + 1.0 - rot[0][0] - rot[2][2]);
					this->y = v7 * 0.5;
					float v8 = 0.5 / v7;
					this->x = (rot[1][0] + rot[0][1]) * v8;
					this->z = (rot[2][1] + rot[1][2]) * v8;
					float v9 = rot[0][2] - rot[2][0];
					this->w = v8 * v9;
				}
				else
				{
					float v10 = -sqrt(rot[2][2] + 1.0 - rot[0][0] - rot[1][1]);
					this->z = v10 * 0.5;
					float v8 = 0.5 / v10;
					this->x = (rot[2][0] + rot[0][2]) * v8;
					this->y = (rot[2][1] + rot[1][2]) * v8;
					float v9 = rot[1][0] - rot[0][1];
					this->w = v8 * v9;
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