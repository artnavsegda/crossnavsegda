#include <stdio.h> 
#include <search.h>
int compare(int *x, int *y)
{
   return (*x - *y);
}
void main ()
{
   int array[5] = {44, 69, 3, 17, 23};
   size_t elems = 5;
   int key = 69;
   int *result;
   result = (int *)lfind (&key, &array, &elems, sizeof (int), (int(*) (const void *, const void *)) compare);
   if (result)
      printf ("Key %d found in linear search\n", key);
   else
      printf ("Key %d not found in linear search\n", key);
}
