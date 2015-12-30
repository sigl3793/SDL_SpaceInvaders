#pragma once

class Utility
{
	// In the utility class i will put misc functions that may be useful several places in the program, all the
	// functions in this class will be public static so that they will belong to the class and not to an object
	// of that class.
public:
	static float RandomFloat(float p_fMin, float p_fMax); // Returns a random value between p_fMin and p_fMax
};
