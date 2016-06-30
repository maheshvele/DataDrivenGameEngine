#pragma once
#include "RTTI.H"

namespace Library
{
	class Foo : public RTTI
	{

	RTTI_DECLARATIONS(Foo, RTTI);

	public:
		Foo();
		~Foo();
		Foo(const Foo& rhs);
		Foo(int data);
		bool operator== (Foo other);
		bool operator== (const Foo other) const;
		bool operator!= (Foo other);
		Foo& operator= (const Foo& other);

		int mData;
		int* mPointer;
	};
}