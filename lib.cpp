/****************************** Директивы препроцессора ******************************/
#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
using namespace std;


/********************************* Прототипы функций *********************************/
void processing(int NOW, int MAX);
string * load_base(string FILE_NAME);
int make_base(string INPUT_FILE);
bool check_repeat(string * ARRAY, string WORD, int POSITION);


/******************************** Объявление структур ********************************/
//struct _finddata_t findData;
struct slip
{
      string word;
      int syllables;
      char part_of_speech;
};


/************************************ Точка входа ************************************/
int main()
{
      SetConsoleCP(1251);
      SetConsoleOutputCP(1251);
      setlocale(LC_CTYPE, "Russian");
      cout << "<=LIBRARY=>\n\n";

      int lim;
      string inp, dat;
      
      //intptr_t hFile;
      //FILE *pFile;
      // ifstream fin;

      // проверить есть ли .dat файлы в папке
      // если нет, то:
      //if( (hFile = _findfirst("*.dat",  &findData )) == -1L)
      {
            // cout("Fail to find data file!\nTrying to load input base...\n");
            // проверить есть ли .inp файлы
            // да:
            //if( (hFile = _findfirst("*.inp",  &findData )) == -1L)
            {
                  // cout("Succesfull!");
                  inp = "base.inp";
                  lim = make_base(inp);
                  dat = "vocabulary.dat";
            }
            // нет:
                  // cerr("Fail to find input fail!");
      }
      // если да, то:
      {
            // получить его имя
            // dat = "name.dat";
            // fin.open(dat.c_str(), ios_base::open);
            // прочитать количество
      }
      
      string * Arr = new string [lim];
      Arr = load_base(dat);           

      
/**************************** Это все короче разминка была ***************************/

      string sub_str;

      while (sub_str != "quit")
      {
cout << "\nВведите последовательность символов: ";
            cin >> sub_str;

            int ssz = sub_str.size(), vsz;
            for (int i = 0; i < 40000; i++)
            {
                  vsz = Arr[i].size();
                  if (ssz >= vsz)
                        continue;
                  if (Arr[i].find(sub_str, vsz-ssz) != string::npos )
                        cout << Arr[i] << endl;
                  //processing(i, num);
            }
      }            

      getch();
      return 0;
}


bool check_repeat(string * ARRAY, string WORD, int POSITION)
{
      for (int i = POSITION; i >= 0; i--)
      {
            if (ARRAY[i] == WORD)
                  return true;
      }
      return false;
}


string * load_base(string FILE_NAME)
{
      string fn = FILE_NAME;
      ifstream f_in(fn.c_str(), ios_base::in);
      while (!f_in)
      {
            cerr << "Fail to open file \"" << fn << "\"!";

            cout << "Enter the filename of base: ";
            cin >> fn;
      
            f_in.open(fn.c_str(), ios_base::in);
      }
      int ln = 0;
      f_in >> ln;
      string * arr = new string [ln];
      for (int i = 0; i < ln && !EOF; i++)
      {
            getline(f_in, arr[i]);
      }

      return arr;
}

int make_base(string INPUT_FILE)
{  
      string in_name = INPUT_FILE;
cout << "Loading base: " << in_name << "...\n";

      char ch; int num = 0; bool flag = false;
      string input;
      ifstream fin(in_name.c_str(), ios_base::in);

      while (!fin)
      {
            cerr << "Fail to open file \"" << in_name << "\"!";
            cout << "Enter the filename of base: ";
            cin >> in_name;                                         
            fin.open(in_name.c_str(), ios_base::in);
      }      
      fin.unsetf(ios::skipws);
      while (fin >> ch)
      {
            if (ch=='\n' || ch=='\t' || ch=='\r' || ch==' ') 
            {
                  if (!flag)
                  {
                        input += " ";
                        num++;
                        flag = true;
                  }
            }
            else if (ch!='.' && ch!=',' && ch!='!' && ch!='\?' && ch!='(' && ch!=')' && ch!='+' &&
                     ch!='/' && ch!='\\' && ch!='\'' && ch!='\"' && ch!='-' && ch!='%' && ch!='=' &&
                     ch!='#' && ch!='№' && ch!='@' && ch!='$' && ch!=':' && ch!=';' && ch!='_' &&
                     ch!='1' && ch!='2' && ch!='3' && ch!='4' && ch!='5' && 
                     ch!='6' && ch!='7' && ch!='8' && ch!='9' && ch!='0')
            {     
                  if ( ((ch >= -64) && (ch <= -33)) || ch == -55 || ch == -88)
                        input += tolower(ch);
                  else
                        input += ch;
                  flag = false;
            }
      }
      input += " ";
      fin.close();
cout << "Successful!\n";

cout << "\nForming array... ";
      string * voc = new string [num+1];
      int pos = 0;
      for (int i = 0; i < num+1 && input.find(" ", pos) != string::npos; i++)
      {
            if (pos > 2)
                  voc[i] = input.substr(0, input.find(" ", pos));
            else {
                  i--;
                  num--;}
            input = input.substr(input.find(" ", pos) + 1);
            pos = input.find(" ");
            processing(i, num);
      }
cout << "\nSuccessful!\n";

      string d_name = "vocabulary.dat";
cout << "\nForming .dat file: " << d_name << "...    ";
      ofstream fout(d_name.c_str());
      fout << num+1 << endl;
      for (int i = 0; i < num+1; i++) 
      {
            if (!check_repeat(voc, voc[i], i-1))
                  fout << voc[i] << "\n";
            processing(i, num); 
      }
      fout.close();
cout << "\nSuccessful!\n";

      return num;
} 


void processing(int NOW, int MAX)
{
      if (NOW < 0)
            cout << "00%";

      int proc = 0;
      proc = 100 * NOW / MAX;

      cout << "\b\b\b";
      if (proc < 10)
            cout << "0" << proc << "%";
      else
            cout << proc << "%";
}