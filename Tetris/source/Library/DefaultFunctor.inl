#include "DefaultFunctor.h"

namespace Library
{



	/*template <typename TKey>
	std::uint32_t DefaultFunctor<TKey>::operator()(const TKey& key) const
	{
		std::int32_t hash = 0;

		const char* data = reinterpret_cast<const char*>(&key);
		std::uint32_t size = sizeof(TKey);

		for (std::uint32_t i = 0; i < size; i++)
		{
			hash = hashPrime * hash + data[i];
		}

		return hash;
	}*/
#pragma region DefaultFunctor


	//Default bernstein hash
	template <typename TKey>
	std::uint32_t DefaultFunctor<TKey>::operator()(const TKey& key) const
	{
		std::uint32_t hash = 0;

		const char* data = reinterpret_cast<const char*>(&key);
		std::uint32_t size = sizeof(TKey);

		for (std::uint32_t i = 0; i < size; i++)
		{
			hash = hashPrime * hash + data[i];
		}

		return hash;
	}

	//Hash for pointers
	template <typename TKey>
	std::uint32_t DefaultFunctor<TKey*>::operator()(const TKey* key) const
	{
		std::uint32_t hash = 0;

		const char* data = reinterpret_cast<const char*>(key);
		std::uint32_t size = sizeof(TKey);

		for (std::uint32_t i = 0; i < size; i++)
		{
			hash = hashPrime * hash + data[i];
		}

		return hash;
	}
	
	//Hash for strings
	inline std::uint32_t DefaultFunctor<std::string>::operator()(const std::string& key) const
	{
		std::uint32_t hash = 0;

		for (std::uint32_t i = 0; i < key.size(); i++)
		{
			hash = hashPrime * hash + key[i];
		}

		return hash;
	}


	//Hash for foos
	inline std::uint32_t DefaultFunctor<Foo>::operator()(const Foo& key) const
	{
		std::uint32_t hash = 0;

		std::uint32_t fooData = key.mData;

		const char* data = reinterpret_cast<const char*>(&fooData);
		std::uint32_t size = sizeof(data);


		for (std::uint32_t i = 0; i < size; i++)
		{
			hash = hashPrime * hash + data[i];
		}

		return hash;
	}
#pragma endregion
	

}