#pragma once
#include "Attributed.h"

namespace Library
{
	class AttributedFoo : public Attributed
	{
	public:
		AttributedFoo();
		~AttributedFoo();
		int testInt;
		int testIntArray[3];

		float testFloat;
		float testFloatArray[3];

		glm::vec4 testVec;
		glm::vec4 testVecArray[3];

		glm::mat4 testMat;
		glm::mat4 testMatArray[3];

		std::string testString;
		std::string testStringArray[3];

		RTTI* testPointer[1];
		Scope* testScope;
	};
}