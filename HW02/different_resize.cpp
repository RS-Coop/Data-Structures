void resize(wordItem **arrayPtr, int *capacity, int *doubles)
{
	int newCapacity = *capacity*2;
	wordItem *newArray = new wordItem [newCapacity];

	for(int i=0; i<*capacity; i++)
	{
		newArray[i] = *arrayPtr[i];
	}
	delete [] *arrayPtr;

  *arrayPtr = newArray;

  delete [] newArray;

	*capacity = newCapacity;
  (*doubles)++;
}

void resize(wordItem **arrayPtr, int *capacity, int *doubles)
{
	int newCapacity = *capacity*2;
	wordItem *newArray = new wordItem [newCapacity];

	for(int i=0; i<*capacity; i++)
	{
		*(newArray+i) = *(*arrayPtr+i);
	}
	delete [] *arrayPtr;

	*arrayPtr = newArray;
	*capacity = newCapacity;
  (*doubles)++;
}
