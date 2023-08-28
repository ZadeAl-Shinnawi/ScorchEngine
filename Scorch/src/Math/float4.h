#pragma once

namespace Scorch
{

// Basic RGBA float quadruplet.
struct Float4
{
	float red;
	float green;
	float blue;
	float alpha;

	Float4(float red, float green, float blue, float alpha)
		: red(red), green(green), blue(blue), alpha(alpha)
	{}
};

} // namespace Scorch