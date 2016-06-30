#include "pch.h"
#include "Foo.h"
namespace Library
{
	RTTI_DEFINITIONS(Foo);

	Foo::Foo() :
		mData(0), mPointer(nullptr)
	{
		mPointer = new int(1);
	}

	Foo::~Foo()
	{
		delete mPointer;
		mPointer = nullptr;
	}

	Foo::Foo(const Foo& rhs) :
		mData(0), mPointer(nullptr)
	{
		operator=(rhs);
	}

	Foo& Foo::operator=(const Foo& other)
	{
		mData = other.mData;
		mPointer = new int(*(other.mPointer));
		return *this;
	}

	Foo::Foo(int data) :
		mData(0), mPointer(nullptr)
	{
		mData = data;
		mPointer = new int(1);
	}

	bool Foo::operator==(Foo other)
	{
		return ( (mData == other.mData) && (*mPointer == *(other.mPointer)) );
	}

	bool Foo::operator==(const Foo other) const
	{
		return ((mData == other.mData) && (*mPointer == *(other.mPointer)));
	}

	bool Foo::operator!=(Foo other)
	{
		return !(operator==(other));
	}
}