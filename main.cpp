#include <fstream>
#include <iostream>
#include <locale.h>
#include <string>
#include <utility>
using namespace std;

long long MODULER_TERS(
    long long a,
    long long m); // uzatilmis oklid algoritmasini kullanarak acik
                  // anahtardan gizli anahtari bulmak icin kullanacagiz.
int asal_kontrol(long long a); // secilen sayilarin asal olup olmadiginin
                               // kontrolu icin
long long USTELMOD(long long a, long long b, long long c); // a^b(mod(c))
long long OBEB(long long x,
               long long y); // Bunu phi sayisi ile aralarinda asal olan
                             // sayilari bulmak icin kullanacagiz.
pair<long long, pair<long long, long long>>
oklid_algoritmasi(long long a, long long b); // uzatilmis oklid algoritmasi.

int asal_kontrol(long long a) {

  for (long long i = 2; i < a; i++) {
    if (a % i == 0) {
      cout << "asal olmayan sayi girdiniz. " << endl;
      return false;
    }
  }

  return true;
}
long long OBEB(long long x, long long y) //
{
  long long min = (x < y ? x : y);
  long long obeb = 1;
  for (long long i = 2; i <= min; i++) {
    if (x % i == 0 && y % i == 0)
      obeb = i;
  }
  return obeb;
}
long long USTELMOD(long long a, long long b, long long c) {
  long long res = 1;
  a = a % c;
  while (b > 0) {
    if (b % 2 == 1)
      res = (res * a) % c;
    a = (a * a) % c;
    b /= 2;
  }
  return res;
}
pair<long long, pair<long long, long long>> oklid_algoritmasi(long long a,
                                                              long long b) {
  long long x = 1, y = 0;
  long long xLast = 0, yLast = 1;
  long long q, r, m, n;
  while (a != 0) {
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
long long MODULER_TERS(long long a, long long m) {
  return (oklid_algoritmasi(a, m).second.first + m) % m;
}

int main() {
  setlocale(LC_ALL, "Turkish");
  long long n, e, p, q, phi;
  long long d;
  ifstream oku_dosya;
  ofstream dosya_yaz;
  string metin;

  char a;
  cout << "sifreleme icin e desifreleme icin d giriniz:";
  cin >> a;
  switch (a) {
  case 'e':

  bas:
    cout << "1. asal sayiyi giriniz:";
    cin >> p;
    cout << "2. asal sayiyi giriniz:";
    cin >> q;
    if (asal_kontrol(p) == false || asal_kontrol(q) == false) {
      cout << "Lutfen asal sayi olmasina dikkat ediniz. " << endl;
      goto bas;
    }
    if (p * q <= 255) {
      cout << "n = p*q degeri 255'ten buyuk olmalidir. (ornegin 17 ve 19 "
              "girin). Lutfen daha buyuk asal sayilar secin."
           << endl;
      goto bas;
    }
    n = p * q;
    phi = (p - 1) * (q - 1);
    cout << "Lutfen acik anahtariniz icin asagidaki sayilardan birini secin."
         << endl;
    for (long long j = 2; j < phi; j++) {
      if (OBEB(phi, j) == 1)
        cout << j << " ";
    }
    cout << endl;
    cin >> e;

    d = MODULER_TERS(e, phi);
    cout << "d:" << d << endl;

    oku_dosya.open("dosya1.txt");
    dosya_yaz.open("sifreli.txt");
    char c_in;
    // Read char by char to preserve spaces and newlines
    while (oku_dosya.get(c_in)) {
      // Cast to unsigned char to prevent negative values for extended ASCII
      unsigned char uc_in = (unsigned char)c_in;
      long long chptext = USTELMOD((long long)uc_in, e, n);
      dosya_yaz << chptext << " ";
    }
    dosya_yaz.close();
    oku_dosya.close();

    cout << "desifre icin anahtariniz. n:" << n << " d:" << d;
    break;
  case 'd':
    cout << "lutfen size verilen anahtari giriniz" << endl;
    cout << "n:" << endl;
    cin >> n;
    cout << "d:" << endl;
    cin >> d;
    oku_dosya.open("sifreli.txt");
    dosya_yaz.open("desifre.txt");
    long long kelime, dechp;
    while (oku_dosya >> kelime) {
      dechp = USTELMOD(kelime, d, n);
      // Cast the result back to unsigned char first, then to char
      unsigned char uc_out = (unsigned char)(dechp % 256);
      dosya_yaz << (char)uc_out;
    }
    oku_dosya.close();
    dosya_yaz.close();
    cout << "desifre edildi.";

    break;
  default:
    cout << "yanlis giris yaptiniz.";
    break;
  }

  return 0;
}
