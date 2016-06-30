namespace Library
{
//Pragma region for node class
#pragma region Node

	//Constructor
	template <typename T>
	SList<T>::Node::Node(const T& data, Node* next) :
		mData(data), mNext(next) 
	{
	}

	//Getter for the data
	template <typename T>
	T& SList<T>::Node::GetData()
	{
		return mData;
	}

	//Getter for the next pointer
	template <typename T>
	typename SList<T>::Node* SList<T>::Node::GetNext()
	{
		return mNext;
	}

	//Setter for the next pointr
	template <typename T>
	void SList<T>::Node::SetNext(Node* newNext)
	{
		mNext = newNext;
	}

#pragma endregion

//Pragma region for iterator class
#pragma region Iterator

	//Constructor
	template <typename T>
	SList<T>::Iterator::Iterator(Node* node, SList* owner) :
		mNode(node), mOwner(owner)
	{
	}

	//Copy constructor
	template <typename T>
	SList<T>::Iterator::Iterator(const typename SList<T>::Iterator& rhs) :
		mNode(nullptr), mOwner(nullptr)
	{
		operator=(rhs);
	}

	//Assignment operator
	template<typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator=(const typename SList<T>::Iterator& rhs)
	{
		mNode = rhs.mNode;
		mOwner = rhs.mOwner;
		return *this;
	}

	//Comparison operator
	template <typename T>
	bool SList<T>::Iterator::operator==(const Iterator& rhs) const
	{		

		return(mOwner == rhs.mOwner && mNode == rhs.mNode);

	}

	//Not-equal operator
	template <typename T>
	bool SList<T>::Iterator::operator!=(const Iterator& rhs) const
	{
		return !(*this == rhs);
	}

	//Prefix increment operator
	template <typename T>
	typename SList<T>::Iterator& SList<T>::Iterator::operator++()
	{
		if (mNode != nullptr)
		{
			mNode = mNode->GetNext();
		}
		return *this;
	}

	//Postfix increment operator
	template <typename T>
	typename SList<T>::Iterator SList<T>::Iterator::operator++(int)
	{
		Iterator temp = *this;
		operator++();
		return temp;
	}

	//Dereference operator
	template <typename T>
	T& SList<T>::Iterator::operator*() const
	{
		if (mNode == nullptr)
		{
			throw std::exception("Bad iterator. Cannot dereference nullptr");
		}

		return mNode->GetData();
	}
	

#pragma endregion

	//Default constructor
	template <typename T>
	SList<T>::SList() :
		mFront(nullptr), mBack(nullptr), mSize(0)
	{
	}

	//Destructor
	template <typename T>
	SList<T>::~SList()
	{
		Clear();
	}

	//Copy constructor
	template <typename T>
	SList<T>::SList(const SList& rhs) :
		mFront(nullptr), mBack(nullptr), mSize(0)
	{
		operator=(rhs);
	}

	//Assignment operator
	template <typename T>
	SList<T>& SList<T>::operator=(const SList& rhs)
	{
		Clear();
		
		SList<T>::Iterator listWalker = rhs.begin();

		for (; listWalker != rhs.end(); listWalker++)
		{
			PushBack(listWalker.mNode->GetData());
		}

		return *this;
	}
	
	//Returns the size of the list
	template <typename T>
	std::uint32_t SList<T>::Size() const
	{
		return mSize;
	}

	//Returns a reference to the data in the  front of the lsit
	template <typename T>
	T& SList<T>::Front() const
	{
		if (IsEmpty())
		{
			throw std::exception("Empty list");
		}

		return mFront->GetData();
	}

	//Returns a reference to the data in the back of the list
	template <typename T>
	T& SList<T>::Back() const
	{
		if (IsEmpty())
		{
			throw std::exception("Empty list");
		}

		return mBack->GetData();
	}

	//Creates a new node at the front of the list with the data given in the parameters
	template <typename T>
	void SList<T>::PushFront(const T& data)
	{
		Node* newNode = new Node(data, mFront);
		mFront = newNode;
		mSize++;
		if (mSize == 1)
		{
			mBack = newNode;
		}
	}

	//Deletes the node at the front of the list
	template <typename T>
	void SList<T>::PopFront()
	{
		if (mSize > 0)
		{
			Node* temporary = mFront;
			mFront = mFront->GetNext();

			delete temporary;
			temporary = nullptr;

			mSize--;

			if (mSize == 0)
			{
				mBack = mFront;
			}
		}
	}

	//Creates a new node at the back of the list with the data given in the parameters
	template <typename T>
	typename SList<T>::Iterator SList<T>::PushBack(T data)
	{
		Node* newNode = new Node(data, nullptr);
		
		if (mSize == 0)
		{
			mFront = newNode;
			mBack = newNode;
		}
		else
		{
			mBack->SetNext(newNode);
			mBack = newNode;
		}

		mSize++;

		return Iterator(newNode, this);

	}

	//Checks to see if the list is empty
	template <typename T>
	bool SList<T>::IsEmpty() const
	{
		return mSize == 0;
	}

	//Deletes all nodes in the list
	template <typename T>
	void SList<T>::Clear()
	{
		while (mSize > 0)
		{
			PopFront();
		}
	}

	//Get an iterator for the front of our list
	template <typename T>
	typename SList<T>::Iterator SList<T>::begin() const
	{
		return Iterator(mFront, const_cast<SList<T>*>(this));
	}

	//Get an iterator for the back of our list
	template <typename T>
	typename SList<T>::Iterator SList<T>::end() const
	{
		return Iterator(nullptr, const_cast<SList<T>*>(this));
	}
	
	//Append and item after a position given by an iterator
	template <typename T>
	void SList<T>::InsertAfter(const T& item, const Iterator& insertionIterator)
	{
		//Sanity check that the iterator is owned by this SList
		if (insertionIterator.mOwner != this)
		{
			throw std::exception("Iterator is not owned by correct SList");
		}

		//Check for the case where we want to insert the item at the end
		if (insertionIterator == end() || *insertionIterator == Back())
		{
			PushBack(item);
			return;
		}

		Node* newNode = new Node(item, insertionIterator.mNode->GetNext());
		insertionIterator.mNode->SetNext(newNode);
		mSize++;
	}

	//Get an iterator pointing to the given item
	template <typename T>
	typename SList<T>::Iterator SList<T>::Find(const T& value) const
	{
		SList<T>::Iterator listWalkIterator = begin();
		while (listWalkIterator != end())
		{
			if (listWalkIterator.mNode->GetData() == value)
			{
				break;
			}
			++listWalkIterator;
		}
		return listWalkIterator;
	}

	//Remove a given item
	template <typename T>
	void SList<T>::Remove(const T& value)
	{
		if (mSize == 0)
		{
			return;
		}

		//Check the head
		if (*begin() == value)
		{
			PopFront();
			return;
		}


		Iterator it = Find(value);

		//else search the list
		if (it == end())
		{
			return;
		}
		
		Iterator prev = begin();

		while (prev.mNode->GetNext() != it.mNode)
		{
			prev++;
		}
		//pointer fix

		prev.mNode->SetNext(it.mNode->GetNext());


		if (it.mNode == mBack)
		{
			mBack = prev.mNode;
		}

		//delete the node;
		delete it.mNode;

		mSize--;
	}

}