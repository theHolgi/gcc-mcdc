#include "test.h"


int testfunc (int var_a, int var_b)
{
   int result_x;
   if (var_a && var_b)
   {
      result_x = 0;
   }
   else
   {
      result_x = 1;
   }
   return result_x;
}

int testfunc2 (int var_a, int var_b)
{
   int x;
   if (var_a || var_b)
   {
      x = 0;
   }
   else
   {
      x = 1;
   }
   return x;
}
