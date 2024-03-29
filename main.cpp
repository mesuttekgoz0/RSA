#include <iostream>
#include <locale.h>
#include <cmath>
#include <string.h>
#include <fstream>
#include <utility> 
using namespace std;

int MODULER_TERS(int a, int m); //uzatılmış öklid algoritmasını kullanarak açık anahtardan gizli anahtarı bulmak içinb kullanacağız.
int asal_kontrol(int a); //seçilen sayıların asal olup olmadığının kontrolü için
int USTELMOD(int a, int b, int c); //a^b(mod(c)) 
int OBEB(int x,int y); // Bunu phi sayısı ile aralarında asal olan sayıları bulmak için kullanacağız.
pair<int, pair<int, int> > oklid_algoritmasi(int a, int b); // uzatılmış öklid algoritması.








int asal_kontrol(int a){ 

  for (int i = 2; i < a; i++)
  {
    if (a % i == 0){
      cout << "asal olmayan sayı girdiniz. "<<endl;
      return false;
    }
  }
 


  return true;
}
int OBEB(int x,int y)// 
{ 
  int min= fmin(x,y);
  int obeb=1;
  for(int i=2;i<=min;i++){
    if (x%i==0&&y%i==0)
    obeb=i;

  }
  return obeb;
}
int USTELMOD(int a, int b, int c)
{
  int _a=a%c;
  int _b=b;

  if (b==0)
  {
    return 1;
  }
  while (_b>1)
  {
    _a*=a;
    _a%=c;
    _b--;
  }
return _a; 
}
pair<int, pair<int, int> > oklid_algoritmasi(int a, int b)
{
    int x = 1, y = 0;
    int xLast = 0, yLast = 1;
    int q, r, m, n;
    while (a != 0) 
    {
        q = b / a;
        r = b % a;
        m = xLast - q * x;
        n = yLast - q * y;
        xLast = x; 
        yLast = y;
        x = m; 
        y = n;
        b = a; 
        a = r;
    }
    return make_pair(b, make_pair(xLast, yLast));
}
int MODULER_TERS(int a, int m) 
{
    return (oklid_algoritmasi(a, m).second.first + m) % m;
}

int main ()
{
setlocale(LC_ALL, "Turkish");
int n,e,p,q,phi;
float d;
ifstream oku_dosya;
ofstream dosya_yaz;
string metin;

 char a;
 cout<<"şifreleme için e deşifreleme için d giriniz:"; cin>>a;
switch (a)
{
  case 'e':
     
     bas:
     cout<<"1. asal sayiyi giriniz:"; cin>>p;
     cout<<"2. asal sayiyi giriniz:"; cin>>q;
     if (asal_kontrol(p)==false||asal_kontrol(q)==false){
       cout<<"Lütfen asal sayi olmasina dikkat ediniz. "<<endl;
       goto bas;
     }
     n=p*q;
     phi=(p-1)*(q-1);
     cout<<"Lütfen açik anahtariniz için aşagidaki sayilardan birini seçin."<<endl;
     for (int j=2;j<phi;j++){
     if (OBEB(phi,j)==1)
     cout<<j<<" ";
     
     }
     cout<<endl; cin>>e;
     
     d=MODULER_TERS(e,phi);
     cout<<"d:"<<d<<endl;
      
     
      oku_dosya.open("dosya1.txt");
      while (getline(oku_dosya,metin)){
     
      
      dosya_yaz.open("sifreli.txt");
      int index =0;
      while (index <metin.length()){
       int chptext=0;
       char chars = metin[index];
       chptext=USTELMOD((int)chars,e,n);
      
       dosya_yaz<<chptext<<" ";
       
       index++;
       }
       dosya_yaz.close();
       }
      
       oku_dosya.close();
       cout<<"desifre için anahtariniz. n:"<<n<<" d:"<<d;
       break;
    case 'd':
     cout<<"lütfen size verilen anahtari giriniz"<<endl;
     cout<<"n:"<<endl;cin>>n;
     cout<<"d:"<<endl;cin>>d;
     oku_dosya.open("sifreli.txt");
     dosya_yaz.open("desifre.txt");
     int kelime,dechp;
      while (oku_dosya>>kelime){
       
      dechp=USTELMOD(kelime,d,n);
      dosya_yaz<<(char)dechp;
     
      
      
       }
       oku_dosya.close();
       dosya_yaz.close();

     break;
     default : cout<<"yanliş giriş yaptiniz.";
     break;
   

 }





return 0;
}
