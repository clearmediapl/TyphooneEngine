

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

      /** METODY U�YTKOWE **/ 
      // rozpocz�cie pomiaru 
      void   StartCount ( void ); 
      // zako�czenie pomiaru 
      void   StopCount ( void ); 
      // pobranie wynik�w pomiaru [s] 
      double   GetTime ( void ); 

   protected : 
   private : 

}; 
