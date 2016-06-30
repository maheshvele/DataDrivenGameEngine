#include "Hashmap.h"

namespace Library
{

#pragma region Iterator
	//constructor defaults you to the first chain if no iterator is supplied
	template <typename TKey, typename TData, template <class> class HashFunctor>
	Hashmap<TKey, TData, HashFunctor>::Iterator::Iterator(std::uint32_t startIndex, const Hashmap* owner) :
		mIndex(startIndex), mOwner(owner), mListIterator()
	{
		if (mOwner != nullptr && startIndex < mOwner->mBuckets.Size())
		{
			mListIterator = mOwner->mBuckets[startIndex].begin();			
		}
	}

	//constructor for when all members are supplied
	template <typename TKey, typename TData, template <class> class HashFunctor>
	Hashmap<TKey, TData, HashFunctor>::Iterator::Iterator(std::uint32_t startIndex, const Hashmap* owner, typename SList<PairType>::Iterator iterator) :
		mIndex(startIndex), mOwner(owner), mListIterator(iterator)
	{
	}

	//destructor
	template <typename TKey, typename TData, template <class> class HashFunctor>
	Hashmap<TKey, TData, HashFunctor>::Iterator::~Iterator()
	{
	}

	//copy constructor
	template <typename TKey, typename TData, template <class> class HashFunctor>
	Hashmap<TKey, TData, HashFunctor>::Iterator::Iterator(const Iterator& rhs) :
		mIndex(rhs.mIndex), mOwner(rhs.mOwner), mListIterator(rhs.mListIterator)
	{
	}

	//assignment operator
	template <typename TKey, typename TData, template <class> class HashFunctor>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator& Hashmap<TKey, TData, HashFunctor>::Iterator::operator=(const Iterator& rhs)
	{
		if (this != &rhs)
		{
			mIndex = rhs.mIndex;
			mOwner = rhs.mOwner;
			mListIterator = rhs.mListIterator;
		}
		return *this;
	}

	//Dereference operator *
	template <typename TKey, typename TData, template <class> class HashFunctor>
	std::pair<TKey, TData>& Hashmap<TKey, TData, HashFunctor>::Iterator::operator*()
	{
		if (mListIterator == nullptr || mIndex >= mOwner->mBuckets.Size())
		{
			throw std::exception("List iterator uninitialzied or out of bounds");
		}

		return *mListIterator;
	}


	//Dereference operator ->
	template <typename TKey, typename TData, template <class> class HashFunctor>
	std::pair<TKey, TData>* Hashmap<TKey, TData, HashFunctor>::Iterator::operator->()
	{
		if (mListIterator == nullptr)
		{
			throw std::exception("List iterator uninitialzied");
		}

		return &(*mListIterator);
	}

	//Increment operator ++(prefix)
	template <typename TKey, typename TData, template <class> class HashFunctor>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator& Hashmap<TKey, TData, HashFunctor>::Iterator::operator++()
	{
		if (mOwner == nullptr)
		{
			return *this;
		}

		if (mOwner->mSize > 0)
		{
			++mListIterator;
			while(mListIterator == mOwner->mBuckets[mIndex].end())
			{
				++mIndex;
				mIndex %= mOwner->mBuckets.mCapacity;
				if (mIndex == 0)
				{
					*this = mOwner->end();
					return *this;
				}
				mListIterator = mOwner->mBuckets[mIndex].begin();
			}
		}

		return *this;
	}

	//Increment operator (postfix)++
	template <typename TKey, typename TData, template <class> class HashFunctor>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Iterator::operator++(int)
	{
		if (mOwner == nullptr)
		{
			return *this;
		}

		Iterator temp = *this;
		operator++();
		return temp;
	}

	//Comparison operator ==
	template <typename TKey, typename TData, template <class> class HashFunctor>
	bool Hashmap<TKey, TData, HashFunctor>::Iterator::operator==(const Iterator& rhs) const
	{
		return ((mIndex == rhs.mIndex) && (mOwner == rhs.mOwner) && (mListIterator == rhs.mListIterator));
	}

	//Comparison operator !=
	template <typename TKey, typename TData, template <class> class HashFunctor>
	bool Hashmap<TKey, TData, HashFunctor>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !operator==(rhs);
	}

	//Begin iterator
	template <typename TKey, typename TData, template <class> class HashFunctor>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::begin() const
	{
		for (std::uint32_t i = 0; i < mBuckets.mCapacity; i++)
		{
			if (!mBuckets[i].IsEmpty())
			{
				return Iterator(i, this);
			}
		}
		//For the case of an empty list
		return end();
	}

	//End iterator
	template <typename TKey, typename TData, template <class> class HashFunctor>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::end() const
	{
		return Iterator(mBuckets.mCapacity, this);
	}

#pragma endregion
	
	
	//Copy constructor
	template <typename TKey, typename TData, template <class> class HashFunctor>
	Hashmap<TKey, TData, HashFunctor>::Hashmap(Hashmap<TKey, TData, HashFunctor>& rhs)
	{
		operator=(rhs);
	}

	//Default constructor with a default size of 10
	template <typename TKey, typename TData, template <class> class HashFunctor>
	Hashmap<TKey, TData, HashFunctor>::Hashmap() :
		mSize(10)
	{
		mBuckets.Reserve(mSize);
	}

	//Constructor with a size
	template <typename TKey, typename TData, template <class> class HashFunctor>
	Hashmap<TKey, TData, HashFunctor>::Hashmap(std::uint32_t size) :
		mSize(0)
	{
		mBuckets.Reserve(size);
	}
	
	//Default destructor
	template <typename TKey, typename TData, template <class> class HashFunctor>
	Hashmap<TKey, TData, HashFunctor>::~Hashmap()
	{
		mBuckets.Clear();
	}

	//Insert
	template <typename TKey, typename TData, template <class> class HashFunctor>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Insert(const PairType& entry)
	{
		std::uint32_t hash = mFunctor(entry.first) % mBuckets.mCapacity;

		SList<PairType>::Iterator it = mBuckets[hash].begin();

		while (it != mBuckets[hash].end())
		{
			if ((*it).first == entry.first)
			{
				return Iterator(hash, this, it);
			}
			++it;
		}

		//Return an iterator pointing at the new item
		mSize++;
		return Iterator(hash, this, mBuckets[hash].PushBack(entry));

	}

	//Get the size
	template <typename TKey, typename TData, template <class> class HashFunctor>
	std::uint32_t Hashmap<TKey, TData, HashFunctor>::Size() const
	{	
		return mSize;
	}

	//Check for key
	template <typename TKey, typename TData, template <class> class HashFunctor>
	bool Hashmap<TKey, TData, HashFunctor>::ContainsKey(const TKey& key) const
	{
		//Iterate through the list at the hash value of key
		std::uint32_t hash = mFunctor(key) % mBuckets.mCapacity;

		for (auto &item : mBuckets[hash])
		{
			if (item.first == key)
			{
				return true;
			}
		}

		return false;
		
	}

	//Remove items
	template <typename TKey, typename TData, template <class> class HashFunctor>
	void Hashmap<TKey, TData, HashFunctor>::Remove(const TKey& key)
	{
		std::uint32_t hash = mFunctor(key) % mBuckets.mCapacity;

		for (auto &item : mBuckets[hash])
		{
			if (item.first == key)
			{
				mBuckets[hash].Remove(item);
				mSize--;
				return;
			}
		}

	}

	//Access items
	template <typename TKey, typename TData, template <class> class HashFunctor>
	TData& Hashmap<TKey, TData, HashFunctor>::operator[](const TKey& key)
	{
		std::uint32_t hash = mFunctor(key) % mBuckets.mCapacity;

		for (auto &item : mBuckets[hash])
		{
			if (item.first == key)
			{
				return item.second;
			}
		}

		//Otherwise, add a default value
		PairType defaultReturn;
		defaultReturn.first = key;
		
		//We don't actually need to call insert here, since we've already calculated the hash value
		mBuckets[hash].PushBack(defaultReturn);
		mSize++;

		return defaultReturn.second;
	}

	//Remove all items
	template <typename TKey, typename TData, template <class> class HashFunctor>
	void Hashmap<TKey, TData, HashFunctor>::Clear()
	{
		for (auto &list : mBuckets)
		{
			list.Clear();
		}
		mSize = 0;
	}

	//Find a data with a given key
	template <typename TKey, typename TData, template <class> class HashFunctor>
	typename Hashmap<TKey, TData, HashFunctor>::Iterator Hashmap<TKey, TData, HashFunctor>::Find(const TKey& key) const
	{
		std::uint32_t hash = mFunctor(key) % mBuckets.mCapacity;

		SList<PairType>::Iterator it = mBuckets[hash].begin();

		while (it != mBuckets[hash].end())
		{
			if ((*it).first == key)
			{
				break;
			}
			++it;
		}

		if (it != mBuckets[hash].end())
		{
			return Iterator(hash, this, it);
		}
		else
		{
			return end();
		}

	}

	//Assignemtn operator
	template <typename TKey, typename TData, template <class> class HashFunctor>
	typename Hashmap<TKey, TData, HashFunctor>& Hashmap<TKey, TData, HashFunctor>::operator=(Hashmap& rhs)
	{
		if (this != &rhs)
		{
			mBuckets.Clear();
			mBuckets = rhs.mBuckets;
			mBuckets.mCapacity = rhs.mBuckets.mCapacity;
			mSize = rhs.mSize;
		}

		return *this;

	}


}