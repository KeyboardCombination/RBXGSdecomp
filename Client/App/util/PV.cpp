#include "util/PV.h"

namespace RBX
{
	Velocity PV::velocityAtPoint(const G3D::Vector3& worldPos) const
	{
		Vector3 delta = worldPos - this->position.translation;
		Vector3 deltaCross = this->velocity.rotational.cross(delta);
		return Velocity(this->velocity.linear + deltaCross, this->velocity.rotational);
	}

	PV PV::pvAtLocalCoord(const G3D::CoordinateFrame& localCoord) const
	{
		CoordinateFrame worldPos = this->position * localCoord;
		Velocity worldVel = this->velocityAtPoint(worldPos.translation);
		return PV(worldPos, worldVel);
	}

	PV PV::pvAtLocalOffset(const G3D::Vector3& localOffset) const
	{
		CoordinateFrame cf(Matrix3::identity(), localOffset);
		return this->pvAtLocalCoord(cf);
	}
}