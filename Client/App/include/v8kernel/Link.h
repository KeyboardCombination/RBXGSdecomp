#pragma once
#include <G3DAll.h>
//#include "v8kernel/Body.h"

namespace RBX
{
	class Body;
	class Link
	{
		protected:
			RBX::Body *body;
			G3D::CoordinateFrame parentCoord;
			G3D::CoordinateFrame childCoord;
			G3D::CoordinateFrame childCoordInverse;
			G3D::CoordinateFrame childInParent;
			int stateIndex;
			virtual void computeChildInParent(const G3D::CoordinateFrame&) const;
			void dirty();
			void setBody(RBX::Body*);
		public:
			Link();
			~Link();
			const G3D::CoordinateFrame& getChildInParent();
			Body* getBody() const;
			void reset(const G3D::CoordinateFrame&, const G3D::CoordinateFrame&);
	};
}