//----------------------------------------------------------------
//           PLIK NAG£ÓWKOWY WYKORZYSTYWANY W PROJEKCIE
//----------------------------------------------------------------
#include<fstream>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip>
#include<iostream>
#include<stdlib.h>
//----------------------------------------------------------------
using namespace std;
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
class book
{
	char bno[6];
	char bname[50];
	char aname[20];
  public:
	void create_book()
	{
         cout<<"\nDodaj nowa ksiazke...\n";
        cout<<"\nWpisz numer ksiazki";
        cin>>bno;
        cout<<"\n\nWpisz nazwe ksiazki";
        gets(bname);
        gets(bname);

        cout<<"\n\nWpisz imie autora ";
        gets(aname);
        cout<<"\n\n\nKsiazka zostala stworzona..";
    }

    void show_book()
    {
        cout<<"\nNumer ksiazki : "<<bno;
        cout<<"\nNazwa ksiazki : ";
        puts(bname);
        cout<<"Nazwa autora: ";
        puts(aname);
    }

    void modify_book()
    {
        cout<<"\nNumer ksiazki : "<<bno;
        gets(bno);
        cout<<"\nZmien nazwe ksiazki: ";
        gets(bname);
        cout<<"\nZmien autora ksiazki : ";
        gets(aname);
    }

    char* retbno()
    {
        return bno;
    }

    void report()
    {cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;}


};
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
class student
{
    char admno[6];
    char name[20];
    char stbno[6];
    int token;
public:
    void create_student()
    {
        system("cls");
         cout<<"\nNowy student...\n";
        cout<<"\nWpisz numer indeksu . ";
        cin>>admno;
        cout<<"\n\nWpisz imie ";
        gets(name);
        gets(name);
        token=0;
        stbno[0]='/0';
        cout<<"\n\nIndeks studenta stworzony ..";
    }

    void show_student()
    {
        cout<<"\nNumer indeksu. : "<<admno;
        cout<<"\nImie studenta: ";
        puts(name);
        cout<<"\nKsiazki nie wydano: "<<token;
        if(token==1)
            cout<<"\nNumer ksiazki "<<stbno;
    }

    void modify_student()
    {
        cout<<"\nNumer indeksu.: "<<admno;
        cout<<"\nZmien imie studenta : ";
        gets(name);

    }

    char* retadmno()
    {
        return admno;
    }

    char* retstbno()
    {
        return stbno;
    }

    int rettoken()
    {
        return token;
    }

    void addtoken()
    {token=1;}

    void resettoken()
    {token=0;}

    void getstbno(char t[])
    {
        strcpy(stbno,t);
    }

    void report()
    {cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

};
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
//        Deklaracje globalne
//----------------------------------------------------------------
fstream fp,fp1;
book bk;
student st;
//----------------------------------------------------------------
//----------------------------------------------------------------
//        Funkcja zapisujaca
//----------------------------------------------------------------
void write_book()
{
    char ch;
    fp.open("book.dat",ios::out|ios::app);
    do
    {
       system("cls");
        bk.create_book();
        fp.write((char*)&bk,sizeof(book));
        cout<<"\n\nCzy chcesz dodac wiecej indeksow..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}
//----------------------------------------------------------------
void write_student()
{
    char ch;
    fp.open("student.dat",ios::out|ios::app);
    do
    {
        st.create_student();
        fp.write((char*)&st,sizeof(student));
        cout<<"\n\nCzy chcesz dodac wiecej indeksow..(y/n?)";
        cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
//        Funkcje pozwalajace czytac z konkretnego indeksu
//----------------------------------------------------------------
//----------------------------------------------------------------
void display_spb(char n[])
{
    cout<<"\nSzczegoly ksiazki\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.show_book();
             flag=1;
        }
    }

    fp.close();
    if(flag==0)
        cout<<"\n\nKsiazka nie istnieje";
    getch();
}
//----------------------------------------------------------------
void display_sps(char n[])
{
    cout<<"\nSzczegoly studenta\n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
        if((strcmpi(st.retadmno(),n)==0))
        {
            st.show_student();
            flag=1;
        }
    }

    fp.close();
    if(flag==0)
            cout<<"\n\nStudenta nie odnaleziono ";
     getch();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
//        Funkcja zmieniajaca indeks
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
void modify_book()
{
    char n[6];
    int found=0;
    system("cls");
    cout<<"\n\n\tZmien numer indeksu ksiazki... ";
    cout<<"\n\n\tWpisz numer indeksu ksiazki";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
        if(strcmpi(bk.retbno(),n)==0)
        {
            bk.show_book();
            cout<<"\nWpisz nowy numer indeksu"<<endl;
            bk.modify_book();
            int pos=-1*sizeof(bk);
                fp.seekp(pos,ios::cur);
                fp.write((char*)&bk,sizeof(book));
                cout<<"\n\n\t Indeks zaktualizowany";
                found=1;
        }
    }

        fp.close();
        if(found==0)
            cout<<"\n\n Indeks nie znaleziony ";
        getch();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
void modify_student()
{
    char n[6];
    int found=0;
   system("cls");
    cout<<"\n\n\tZmiana indeksu studenta... ";
    cout<<"\n\n\tWpisz numer indeksu studenta";
    cin>>n;


    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
        if(strcmpi(st.retadmno(),n)==0)
        {
            st.show_student();
            cout<<"\nWpisz nowy numer indeksu studenta"<<endl;
                cin>>n;

            st.modify_student();
            int pos=-1*sizeof(st);
            fp.seekp(pos,ios::cur);
            fp.write((char*)&st,sizeof(student));
            cout<<"\n\n\t Indeks zmieniono;";
            found=1;
        }
    }

    fp.close();
    if(found==0)
        cout<<"\n\n Indeks nie odnaleziono  ";
    getch();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
//       Funkcja usuwajaca indeks
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
void delete_student()
{
    char n[6];
    int flag=0;
    system("cls");
        cout<<"\n\n\n\tUsun studenta...";
        cout<<"\n\nWpisz numer studenta ktorego chcesz usunac ";
        cin>>n;
        fp.open("student.dat",ios::in|ios::out);
        fstream fp2;
        fp2.open("Temp.dat",ios::out);
        fp.seekg(0,ios::beg);
        while(fp.read((char*)&st,sizeof(student)))
    {
        if(strcmpi(st.retadmno(),n)!=0)
                 fp2.write((char*)&st,sizeof(student));
        else
               flag=1;
    }

    fp2.close();
        fp.close();
        remove("student.dat");
        rename("Temp.dat","student.dat");
        if(flag==1)
             cout<<"\n\n\tStudent usuniety ..";
        else
             cout<<"\n\nStudent nie odnaleziony";
        getch();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
void delete_book()
{
    char n[6];
    system("cls");
    cout<<"\n\n\n\tUsun ksiazke ...";
    cout<<"\n\nWpisz numer ksiazki ktora chcesz usunac";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
        if(strcmpi(bk.retbno(),n)!=0)
        {
            fp2.write((char*)&bk,sizeof(book));
        }
    }

    fp2.close();
        fp.close();
        remove("book.dat");
        rename("Temp.dat","book.dat");
        cout<<"\n\n\tKsiazka usunieta ..";
        getch();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
//        Funkcja rozdzielajaca poszczegolnych studentow
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
void display_alls()
{
   system("cls");
         fp.open("student.dat",ios::in);
         if(!fp)
         {
               cout<<"Blad plik nie moze byc otwarty ";
               getch();
               return;
         }

    cout<<"\n\n\t\tLista studentow\n\n";
    cout<<"==================================================================\n";
    cout<<"\tNumer indeksu."<<setw(10)<<"  Imie "<<setw(20)<<"  Ksiazka wydana\n";
    cout<<"==================================================================\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
        st.report();
    }

    fp.close();
    getch();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
//        Funkcja dystrubuujaca ksiazki
//----------------------------------------------------------------
//----------------------------------------------------------------
void display_allb()
{
   system("cls");
    fp.open("book.dat",ios::in);
    if(!fp)
    {
        cout<<"Blad plik nie moze byc otwarty ";
               getch();
               return;
         }

    cout<<"\n\n\t\tLista ksiazek\n\n";
    cout<<"=========================================================================\n";
    cout<<"Numer ksiazki"<<setw(20)<<"Nazwa"<<setw(25)<<"Autor\n";
    cout<<"=========================================================================\n";

    while(fp.read((char*)&bk,sizeof(book)))
    {
        bk.report();
    }
         fp.close();
         getch();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
//        Funkcja sluzaca do wydawania ksiazek
//----------------------------------------------------------------
//----------------------------------------------------------------
void book_issue()
{
    char sn[6],bn[6];
    int found=0,flag=0;
   system("cls");
    cout<<"\n\nWydanie ksiazki ...";
    cout<<"\n\n\tWpisz numer studenta";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
        fp1.open("book.dat",ios::in|ios::out);
        while(fp.read((char*)&st,sizeof(student)) && found==0)
           {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==0)
            {
                      cout<<"\n\n\tWpisz numer ksiazki ";
                cin>>bn;
                while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
                {
                       if(strcmpi(bk.retbno(),bn)==0)
                    {
                        bk.show_book();
                        flag=1;
                        st.addtoken();
                        st.getstbno(bk.retbno());
                               int pos=-1*sizeof(st);
                        fp.seekp(pos,ios::cur);
                        fp.write((char*)&st,sizeof(student));
                        cout<<"\n\n\t Ksiazka zostala wydana. Pamietaj aby zwrocic ksiazke w okresie do 2 tygodni ";
                    }
                    }
                  if(flag==0)
                        cout<<"Ksizka nie istnije";
            }
                else
                  cout<<" Nie oddale ostatniej ksiazki";

        }
    }
          if(found==0)
        cout<<"Indeks studenta nie istnieje";
    getch();
      fp.close();
      fp1.close();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
//        Funkcja pozwalajaca zwrocic ksiazke
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
void book_deposit()
{
    char sn[6],bn[6];
    int found=0,flag=0,day,fine;
    system("cls");
    cout<<"\n\nZwrot ksiazki ...";
    cout<<"\n\n\tWpisz numer indeksu studenta";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
        if(strcmpi(st.retadmno(),sn)==0)
        {
            found=1;
            if(st.rettoken()==1)
            {
            while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
            {
               if(strcmpi(bk.retbno(),st.retstbno())==0)
            {
                bk.show_book();
                flag=1;
                cout<<"\n\nKsiazka zwrocona po liczbie dni wynaszacej : ";
                cin>>day;
                if(day>15)
                {
                   fine=(day-15)*1;
                   cout<<"\n\nKsiazke mozna zwrocic "<<fine;
                }
                    st.resettoken();
                    int pos=-1*sizeof(st);
                    fp.seekp(pos,ios::cur);
                    fp.write((char*)&st,sizeof(student));
                    cout<<"\n\n\t Ksiazka zwrocona ";
            }
            }
          if(flag==0)
            cout<<"Ksiazka nie istnieje";
              }
         else
            cout<<"Nie bylo wydanej ksiazki";
        }
       }
      if(found==0)
    cout<<"Indeks studenta nie istnieje...";
    getch();
  fp.close();
  fp1.close();
  }
//----------------------------------------------------------------
//----------------------------------------------------------------
//       Funkcja wprowadzajaca do menu
//----------------------------------------------------------------
//----------------------------------------------------------------
void intro()
{
    system("cls");

    cout<<"Biblioteka";

    cout<<"SYSTEM";
    cout<<"\n\. Wykonano przez : Angelika Suligowska, Pawel Marciniak ";
    cout<<"\n\. PUW Informatyka 2021 ";

    getch();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
//        Menu administratora
//----------------------------------------------------------------
//----------------------------------------------------------------
void admin_menu()
{
    system("cls");
    int ch2;
    cout<<"\n\n\n\tMenu Administratora";
    cout<<"\n\n\t1.Stworz indeks studenta";
    cout<<"\n\n\t2.Wszyscy studenci";
    cout<<"\n\n\t3.Sprawdz konkretnego studenta ";
    cout<<"\n\n\t4.Zmien indeks studenta";
    cout<<"\n\n\t5.Usun indeks studenta";
    cout<<"\n\n\t6.Stworz ksiazke ";
    cout<<"\n\n\t7.Sprawdz ksiazki ";
    cout<<"\n\n\t8.SPrawdz konkretna ksiazke ";
    cout<<"\n\n\t9.Zmien ksiazke";
    cout<<"\n\n\t10.Usun ksiazke ";
    cout<<"\n\n\t11.Powrot do menu";
    cout<<"\n\n\tProsze wprowadz liczbe odpowiadajaca numerowi w menu (1-11) ";
    cin>>ch2;
    switch(ch2)
    {
            case 1: system("cls");
                write_student();break;
            case 2: display_alls();break;
            case 3:
                   char num[6];
                   system("cls");
                   cout<<"\n\n\tWprowadz numer indeksu ";
                   cin>>num;
                   display_sps(num);
                   break;
              case 4: modify_student();break;
              case 5: delete_student();break;
        case 6: system("cls");
            write_book();break;
        case 7: display_allb();break;
        case 8: {
                   char num[6];
                   system("cls");
                   cout<<"\n\n\tWprowadz numer ksiazki ";
                   cin>>num;
                   display_spb(num);
                   break;
            }
              case 9: modify_book();break;
              case 10: delete_book();break;
             case 11: return;
              default:cout<<"\a";
       }
       admin_menu();
}
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
//        plik main programu
//----------------------------------------------------------------
//----------------------------------------------------------------
//----------------------------------------------------------------
int main()
{
    char ch;
    intro();
    do
    {
        system("cls");
        cout<<"\n\n\n\tMenu glowne";
        cout<<"\n\n\t01. Wydanie ksiazki";
        cout<<"\n\n\t02. Zwrot ksiazki";
          cout<<"\n\n\t03. Menu administartora";
          cout<<"\n\n\t04. Wyscie";
          cout<<"\n\n\tWybierz numer opcji odpowiadajacej  (1-4) ";
          ch=getche();
          switch(ch)
          {
            case '1':system("cls"); ;
                 book_issue();
                    break;
              case '2':book_deposit();
                     break;
              case '3':admin_menu();
                 break;
              case '4' :return(0);;
              default :cout<<"\a";
        }
        }while(ch!='4');
}



