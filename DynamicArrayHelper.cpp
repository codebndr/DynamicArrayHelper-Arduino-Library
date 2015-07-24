//File: DynamicArrayHelper.cpp
//Created by: S. Schutten, schutten@hotmail.com
 #include <stdlib.h>
 #include <wiring.h>
 #include "DynamicArrayHelper.h"

 bool DynamicArrayHelper::SetArrayLength(void *& array, byte newelements , byte & elements , byte elementsize)
{
	// calculate the size of the buffer to be able to store the number of elements
	int newbuffersize = newelements  * elementsize;
	// calculate the size of the current buffer
	int currentbuffersize = elements * elementsize;
	// allocate enough memory for "newelements" number of elements
	void * newarray = malloc ( newbuffersize );
	// did memory allocation fail?
	if (newarray==0) 
	{ // yes, failed
		return false;
	}
	// copy the data from the old array, to the new array
	for (int idx=0;idx < currentbuffersize ;idx++)
	{
		((byte*)newarray)[idx] = ((byte *)array)[idx];
	}
	// free the original array
	if (array!=0)
	{
		free(array);
	}
	// clear the newly allocated memory space
	for (int idx= currentbuffersize;idx < newbuffersize;idx++)
	{
		((byte *)newarray)[idx] = 0;
	}
	// Store the number of elements the memory is allocated for
	elements = newelements;
	// set the array to the newly created array
	array = newarray;
	// success
	return true;
}
bool DynamicArrayHelper::SetElementInArray(void *& array, void * element, byte elementindex , byte & elements , byte elementsize) {
	// is the elementindex outside the range of the current array length?
	if (elementindex >= elements)
	{ // Yes
		// Can the array length be changed?
		if (!SetArrayLength( array , elementindex + 1 , elements , elementsize))
		{ // no, probably out-of-memory or memory corruption
			return false;
		}
	}
	// Is there enough memory allocated for another element?
	if ( elements > elementindex )
	{ // Yes
		int elementstartpos = (elementindex * elementsize);
		// Copy-in the element data into the array
		for (int idx=0;idx<elementsize;idx++)
		{
			((byte *)array)[elementstartpos + idx] = ((byte*)element)[idx];
		}
	} else 
	{
		return false;
	}
	return true;
}
bool DynamicArrayHelper::AddToArray(void *& array, void * element, byte & elements , byte elementsize) {
	byte elementindex = elements;
	return SetElementInArray( array , element , elementindex , elements , elementsize);
}
bool DynamicArrayHelper::RemoveFromArray(void *& array, int elementindex, byte & elements , byte elementsize) {
	// calculate the size of the buffer without 1 element
	int newbuffersize = (elements-1) * elementsize;
	int currentbuffersize = (elements * elementsize);
	// allocate memory for the new array
	void * newarray = malloc ( newbuffersize );
	// did the memory allocation fail?
	if (newarray==0)
	{ // Yes, failed
		return false;
	}
	// copy the elements in the array before the element-to-be-removed
	for (int idx=0;idx<(elementindex*elementsize);idx++)
	{
		((byte*)newarray)[idx] = ((byte*)array)[idx];
	}
	// copy the elements in the array after the element-to-be-removed
	for (int idx=((elementindex+1)*elementsize);idx < currentbuffersize;idx++)
	{
		((byte*)newarray)[idx-elementsize] = ((byte*)array)[idx];
	}
	if (array!=0)
	{
		free(array);
	}
	elements--;
	array = newarray;
	return true;
}
