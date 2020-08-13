#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <cstringt.h>
#include <stdlib.h>
#include <ctype.h>
#include <locale.h>
#include <windows.h>
#include <winbase.h>
#include <afxdao.h>
using namespace std;

int nnmain()
{
      int iAttributes = faArchive | faAnyFile; 
      char* aPath = "C:/*.txt"; 
      TSearchRec SearchRec; 

      clrscr();// גלוסעמ Memo1->Clear(); 

      if (FindFirst(aPath, iAttributes, SearchRec) == 0) 
      { 
            do 
                  printf("%s", SearchRec.Name); // גלוסעמ Memo1->Lines->Add(SearchRec.Name); 
            while (FindNext(SearchRec) == 0); 
            FindClose(SearchRec); 
      }

      getch();
      return 0;
}