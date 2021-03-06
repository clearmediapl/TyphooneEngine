

#pragma once 

class CTimeCounter 
{ 
   
   public : 
   protected : 
      LARGE_INTEGER      liFreq; 
      LARGE_INTEGER      liCStart, liCEnd; 
      unsigned __int64   iCStart, iCEnd, iCFreq; 
      double            dFreq, dDiff; 
      bool            cancount; 
      bool            counted; 
      double            cval; 

   private : 

   // metody : 
   public : 
      // konstruktor 
      CTimeCounter (); 

      // destruktor 
      ~CTimeCounter (); 

      /** METODY UŻYTKOWE **/ 
      // rozpoczęcie pomiaru 
      void   StartCount ( void ); 
      // zakończenie pomiaru 
      void   StopCount ( void ); 
      // pobranie wyników pomiaru [s] 
      double   GetTime ( void ); 

   protected : 
   private : 

}; 
