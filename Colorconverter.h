#pragma once

#include <iostream>
#include <glm/glm.hpp>          
#include <sstream>
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp>    
#include "stbi.h"

class colorconverter {
public:

	/*Converting hexadecimal numbers to RGB by shifting the numbers to the right for each color to remove the other colors and reach the desired color.
	 In C++, performing a bitwise AND (&) function acts like a stencil or a cookie cutter. 
	 It wipes out everything to the left and keeps only the lowest 8 bits (one single byte).*/

	static glm::vec3 HEX(unsigned int HEXvalue) {
		float r = ((HEXvalue >> 16) & 0xFF) / 255.0f;
		float g = ((HEXvalue >> 8) & 0xFF) / 255.0f;
		float b = (HEXvalue & 0xFF) / 255.0f;
		return glm::vec3(r, g, b);
	} 
	//handles the hashtag symbol in hexadecimal numbers 
	static glm::vec3 HEX(std::string hash) {
		if (!hash.empty() && hash[0] == '#') {
			hash = hash.substr(1);
		}

		//using string stream class to convert letters in hexadecimal systems into a number.
		unsigned int HEXValue = 0;
		std::stringstream ss;
		ss << std::hex << hash;
		ss >> HEXValue;
		return HEX(HEXValue);

	}

	//converting from standard RGB to Alpha Channel (A) RGBA 
	static glm::vec3 STD(float x, float y, float z)
	{
		return glm::vec3(x / 255.0f, y / 255.0f, z / 255.0f);
	};

};
