

#include "bibloteki.h"
#include "CTimer.h" 

////////////////////////////////////////////////////// 
//            STANDARDOWY STUFF 
////////////////////////////////////////////////////// 


CTimeCounter :: CTimeCounter () 
{ 
   cancount = false; 
   QueryPerformanceFrequency( &liFreq ); 
   iCFreq = (signed __int64)liFreq.QuadPart; 
   dFreq = (signed __int64)iCFreq; 
   if ( dFreq > 100 ) 
      cancount = true; 
   counted = false; 
   cval = 0.0; 
} 


CTimeCounter :: ~CTimeCounter () 
{ 
} 



////////////////////////////////////////////////////// 
//               METODY 
////////////////////////////////////////////////////// 

void CTimeCounter :: StartCount ( void ) 
{ 
   counted = false; 
   cval = 0.0; 
   QueryPerformanceCounter ( &liCStart ); 
} 



void CTimeCounter :: StopCount ( void ) 
{ 
   QueryPerformanceCounter ( &liCEnd ); 
   iCStart = (signed __int64)liCStart.QuadPart; 
   iCEnd = (signed __int64)liCEnd.QuadPart; 

   signed __int64 iCDiff = iCEnd - iCStart; 
   dDiff = (double)iCDiff; 
} 



double CTimeCounter :: GetTime ( void ) 
{ 
   if ( cancount ) 
   { 
      if ( !counted ) 
      { 
         cval = (dDiff*10000/dFreq); 
         counted = true; 
      } 
      return cval; 
   } 
   return 0; 
}