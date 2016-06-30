#pragma once
#include <cstdint>
#include <string>
#include "Foo.h"


//Number used for hash functions
const std::uint32_t hashPrime = 65;

namespace Library
{
	/*template <typename TKey>
	class DefaultFunctor
	{
	public:
		std::int32_t operator()(const TKey& key) const;
	};*/

		/**
	This is the default functor class. It is used for the generic T data types of
	keys as well as a few specializations. Specifically, it supports pointers,
	strings, and Foo.
	*/
	template <typename TKey>
	class DefaultFunctor
	{
	public:
		std::uint32_t operator()(const TKey& key) const;
	};

	template <typename TKey>
	class DefaultFunctor <TKey*>
	{
	public:
		std::uint32_t operator()(const TKey* key) const;
	};

	template<>
	class DefaultFunctor <std::string>
	{
	public:
		std::uint32_t operator()(const std::string& key) const;
	};
	
	template<>
	class DefaultFunctor <Foo>
	{
	public:
		std::uint32_t operator()(const Foo& key) const;
	};
}

#include "DefaultFunctor.inl"
