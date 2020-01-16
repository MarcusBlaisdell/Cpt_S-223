	//copy constructor
	//MA #1 TODO: Implement!
	LinkedList(const LinkedList<T> &other)
	{

		if (this->_front != nullptr)
		{
			for (int i = 0; i < this->_size; i++)
			{
				removeElementAt(i);
			} // end 
		} // end if list is not empty

			// use for loop to iterate through LinkedList index and copy each node
			// use size_of other LinkedList for index
		for (int i = 0; i < other.getSize(); i++)
		{
			this->addElementAt(other.getElementAt(i), i);
		} // end for loop to copy all elements of linked list
		
	} // end LinkedList copy constructor

	//move constructor
	//MA #1 TODO: Implement!
	LinkedList(LinkedList<T> &&other)
	{
		if (this == other)
		{
			cout << "Not allowed" << endl;
		} // end if this == other

		//get other's meta data
		this->_last_accessed_index = other._last_accessed_index;
		this->_size = other._size;

		//then steal its pointers
		this->_front = other._front;
		this->_end = other._end;
		this->_last_accessed_node = other._last_accessed_node;

		//and give them nullptr instead
		other._front = nullptr;
		other._end = nullptr;
		other._last_accessed_node = nullptr;
		other._last_accessed_index = 0;
		other._size = 0;
	} // end move constructor

	//initializer list constructor
	//MA #1 TODO: Implement!
	LinkedList(initializer_list<T> values)
	{
		for (auto item : values)
		{
			addElement(item);
		} // the "cool" way to iterate
	}

	//Always remeber to clean up pointers in destructor!
	//MA #1 TODO: Implement!
	virtual ~LinkedList()
	{
		if (_front != nullptr)
		{
			for (int i = 0; i < this->_size; i++)
			{
				removeElementAt(i);
			} // end for loop to remove each element
		} // end if _front is not null
	} // end LinkedList destructor

	//copy operator
	//MA #1 TODO: Implement!
	virtual LinkedList<T> &operator=(const LinkedList<T> &other)
	{
		//copy other's meta data
		this->_last_accessed_index = other._last_accessed_index;
		this->_size = other._size;
		
		//copy other's items
		for (int i = 0; i < other.getSize(); i++)
		{
			this->setElementAt(other.getElementAt(i), i );
		} // end for loop to copy all items

		return *this;
	}

	//move operator
	//MA #1 TODO: Implement!
	virtual LinkedList<T> &operator=(LinkedList<T> &&other)
	{
		//get other's meta data
		this->_last_accessed_index = other._last_accessed_index;
		this->_size = other._size;

		//then steal its pointers
		this->_front = other._front;
		this->_end = other._end;
		this->_last_accessed_node = other._last_accessed_node;

		//and give them nullptr instead
		other._front = nullptr;
		other._end = nullptr;
		other._last_accessed_node = nullptr;
		other._last_accessed_index = 0;
		other._size = 0;

		return *this;
	}