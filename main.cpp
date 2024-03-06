#include <iostream>
#include <locale.h>
#include <math.h>
#include <string.h>
#include <ctime>

using namespace std;
int asal_kontrol(int a){
  int durum = 1;


  for (int i = 2; i < a; i++){

    if (a % i == 0){
      cout << "asal olmayan sayı girdiniz. "<<endl;
      durum = 0;
      return false;
    }

  }


  return true;
}
int OBEB(int x,int y){
  int min= fmin(x,y);
  int obeb=1;
  for(int i=2;i<=min;i++){
    if (x%i==0&&y%i==0)
    obeb=i;

  }
  return obeb;
}

int main (){
setlocale(LC_ALL, "Turkish");
int n,e,p,q,phi;
float d;
string metin;
int chptext;
bas:
cout<<"1. asal sayiyi giriniz:"; cin>>p;
cout<<"2. asal sayiyi giriniz:"; cin>>q;
if (asal_kontrol(p)==false||asal_kontrol(q)==false){
  cout<<"lütfen asal sayı olmasına dikkat ediniz. "<<endl;
  goto bas;
}
n=p*q;
phi=(p-1)*(q-1);
cout<<"Lütfen açık anahtarınız için aşağıdaki sayılardan birini seçin."<<endl;
for (int j=2;j<phi;j++){
if (OBEB(phi,j)==1)
cout<<j<<" ";
}
cout<<endl;
cin>>e;
for (int i=0;i<phi;i++){
 d=(1+i*phi)/e;
 if (d-(int)d==0){
  break;
 }
 
 
 }
 cout<<"d:"<<d;
 cout<<"şifrelenecek metni giriniz:";
 getline(cin, metin);
 int index=0,a;
 while (index<metin.length()){
  char chars = metin[index];
  int ascii = chars;
  index++;
  a=pow(ascii,e);
  chptext=a%n;

  cout<<chptext<<" ";
 }















 return 0;
}