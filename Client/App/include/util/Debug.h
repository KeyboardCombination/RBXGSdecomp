#pragma once

namespace RBX {
	class Debugable {
		public:
			virtual void PlaceHolder();
			static void doCrash();
			enum AssertAction
			{
			  CrashOnAssert = 0x0,
			  IgnoreAssert = 0x1,
			};
			static AssertAction assertAction;
	};
}

#define RBXAssert(expr) if ( RBX::Debugable::assertAction == Debugable::CrashOnAssert && !(expr)) RBX::Debugable::doCrash()