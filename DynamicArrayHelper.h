//File: DynamicArrayHelper.h //Created by: S. Schutten, schutten@hotmail.com
 #ifndef DynamicArrayHelper_h
 #define DynamicArrayHelper_h
 #include <wiring.h>

class DynamicArrayHelper {
 public:
 // Enlarge the array to be able to hold the specified number of elements
 static bool SetArrayLength(void *& array, byte newelements , byte & elements , byte elementsize);

// Store an element in the array
 static bool SetElementInArray(void *& array, void * element, byte elementindex , byte & elements , byte elementsize);

// Add an element to the array
 static bool AddToArray(void *& array, void * element, byte & elements , byte elementsize);

// Remove an element from the array
 static bool RemoveFromArray(void *& array, int elementindex, byte & elements , byte elementsize);
 };
 #endif
