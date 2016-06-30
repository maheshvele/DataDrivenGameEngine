#pragma once
#include <cstdint>
#include <string>
#include "Vector.h"
#include "SList.h"
#include "Foo.h"
#include "DefaultFunctor.h"

namespace Library
{


	/**
	This class is an implementation of a hash map. It takes templated arguments for a type of key,
	a type of data, and a functor that is used as the hash function. The underlying data structure is
	a vector of SLists. The SLists are used for chaining, the way which this hash map deals with collisions.
	*/
	template <typename TKey, typename TData, template <class> class HashFunctor = DefaultFunctor>
	class Hashmap
	{

	public:
		typedef std::pair<TKey, TData> PairType;
		typedef SList<PairType> ChainType;
		typedef Vector<ChainType> BucketType;

		class Iterator
		{
			friend class Hashmap;
		public:
			/**
			Constructors
			*/
			Iterator(std::uint32_t startIndex, const Hashmap* owner);

			Iterator(std::uint32_t startIndex, const Hashmap* owner, typename SList<PairType>::Iterator iterator);

			/**
			Destructor
			*/
			~Iterator();

			/**
			Copy constructor
			*/
			Iterator(const Iterator& rhs);

			/**
			Assignment operator =
			*/
			Iterator& operator=(const Iterator& rhs);

			/**
			Increment operator ++(prefix)
			*/
			Iterator& operator++();

			/**
			Increment operator (postfix)++
			*/
			Iterator operator++(int);

			/**
			Dereference operator *
			*/
			PairType& operator*();

			/**
			Dereference operator ->
			*/
			PairType* operator->();

			/**
			Comparison operator ==
			*/
			bool operator==(const Iterator& rhs) const;

			/**
			Comparison operator !=
			*/
			bool operator!=(const Iterator& rhs) const;

			

		private:
			/**
			Index of our bucket
			*/
			std::uint32_t mIndex;

			/**
			Pointer to the hashmap that owns us
			*/
			const Hashmap* mOwner;

			/**
			Iterator for our current location in the chain
			*/
			typename SList<PairType>::Iterator mListIterator;
		};

		/**
		Default constructor
		*/
		Hashmap();

		/**
		Constructor
		*/
		Hashmap(std::uint32_t size);

		/**
		Copy constructor
		*/
		Hashmap(Hashmap& rhs);

		/**
		Destructor
		*/
		~Hashmap();

		/**
		Insert an entry into the list
		
		@param entry the item to be inserted into the list
		@return an iterator pointing at the new insertion
		*/
		Iterator Insert(const PairType& entry);

		/**
		Get the current size

		@return a std::uint32_t indicating the number of items in the map
		*/
		std::uint32_t Size() const;

		/**
		Find wether or not the given key exists in the hash map

		@param key the key to hash for the serach
		@return true if the key is in the map. False otherwise
		*/
		bool ContainsKey(const TKey& key) const;

		/**
		Remove a component at a given key

		@param key the key of the item to be removed
		*/
		void Remove(const TKey& key);

		/**
		Get a reference to data that matches a given key

		Find's a value with a given reference. If the value isn't in the list, a default value is added to the list in its place and returned

		@param key the key of the item to get a reference to
		@return a reference to the data at the location of key
		*/
		TData& operator[](const TKey& key);

		/**
		Delete all elements in the hash map
		*/
		void Clear();

		/**
		Get an iterator reference to the beginning of the contents

		@return an iterator to the first item in the list
		*/
		Iterator begin() const;

		/**
		Get an iterator reference to outside the list

		@return an iterator indicating being outside the list (but still owned by this hashmap)
		*/
		Iterator end() const;

		/**
		Get an iterator to a given key

		@param key the key of the item to search for
		@return an iterator to the item that was found. If the item isn't in the list, returns end()
		*/
		Iterator Find(const TKey& key) const;
		
		/**
		Assignment operator
		*/
		Hashmap& operator=(Hashmap& rhs);

	private:
		/**
		Potentially user defined hash function
		*/
		HashFunctor<TKey> mFunctor;

		/**
		Vector used to store the data
		*/
		BucketType mBuckets;

		/**
		Number of buckets
		*/
		//std::uint32_t mNumBuckets;

		/**
		Number of elements
		*/
		std::uint32_t mSize;
	};
}

#include "Hashmap.inl"