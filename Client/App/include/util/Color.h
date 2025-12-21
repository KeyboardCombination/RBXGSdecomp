#pragma once
#include <g3d/color.h>

namespace RBX
{
	class Color 
	{
	public:
		// Guessed from https://alumni.media.mit.edu/~wad/color/numbers.html except lightGreen
		static const G3D::Color3 black()
		{
			return G3D::Color3::black();
		}

		static const G3D::Color3 darkGray()
		{
			return G3D::Color3(87/255, 87/255, 87/255);
		}

		static const G3D::Color3 red()
		{
			return G3D::Color3(173/255, 35/255, 35/255);
		}

		static const G3D::Color3 blue()
		{
			return G3D::Color3(42/255, 75/255, 215/255);
		}

		static const G3D::Color3 brown()
		{
			return G3D::Color3(129/255, 74/255, 192/255);
		}

		static const G3D::Color3 purple()
		{
			return G3D::Color3(129/255, 38/255, 192/255);
		}

		static const G3D::Color3 lightGray()
		{
			return G3D::Color3(160/255, 160/255, 160/255);
		}

		static const G3D::Color3 lightGreen()
		{
			return G3D::Color3(129/255, 197/255, 22/255);
		}

		static const G3D::Color3 lightBlue()
		{
			return G3D::Color3(157/255, 175/255, 255/255);
		}

		static const G3D::Color3 cyan()
		{
			return G3D::Color3(41/255, 208/255, 208/255);
		}

		static const G3D::Color3 orange()
		{
			return G3D::Color3(255/255, 146/255, 51/255);
		}

		static const G3D::Color3 yellow()
		{
			return G3D::Color3(255/255, 238/255, 51/255);
		}

		static const G3D::Color3 tan()
		{
			return G3D::Color3(233/255, 222/255, 187/255);
		}

		static const G3D::Color3 pink()
		{
			return G3D::Color3(255/255, 205/255, 243/255);
		}

		static const G3D::Color3 white()
		{
			return G3D::Color3::white();
		}
	};
}