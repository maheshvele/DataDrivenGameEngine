namespace Library
{
	//Constructor
	template <typename T>
	Stack<T>::Stack() :
		mSize(0), mSList()
	{
	}

	//Destructor
	template <typename T>
	Stack<T>::~Stack()
	{
		Clear();
	}
	
	//Copy constructor
	template <typename T>
	Stack<T>::Stack(const Stack& rhs) :
		mSize(0), mSList()
	{
		operator=(rhs);
	}

	//Assignment operator
	template <typename T>
	typename Stack<T>& Stack<T>::operator=(const Stack& rhs)
	{
		mSList = rhs.mSList;
		mSize = rhs.mSize;

		return *this;
	}

	//Place the given item on top of the stack
	template <typename T>
	void Stack<T>::Push(const T& item)
	{
		mSList.PushFront(item);
		mSize++;
	}

	//Get top item
	template <typename T>
	T& Stack<T>::Top()
	{
		return mSList.Front();
	}


	//Get the top element
	template <typename T>
	const T& Stack<T>::Top() const
	{
		return mSList.Front();
	}

	//Remove top item
	template <typename T>
	void Stack<T>::Pop()
	{
		mSList.PopFront();
		mSize--;
	}

	//Clear the stack
	template <typename T>
	void Stack<T>::Clear()
	{
		mSList.Clear();
		mSize = 0;
	}
	
	//Get the size
	template <typename T>
	unsigned int Stack<T>::Size() const
	{
		return mSize;
	}

	//Check if we're empty
	template <typename T>
	bool Stack<T>::IsEmpty() const
	{
		return mSize == 0;
	}


}