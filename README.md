# RSA File Encryption & Decryption (C++)

Bu proje, standart **RSA Algoritması** kullanılarak metin dosyalarını şifrelemek ve deşifrelemek (çözmek) için geliştirilmiş bir C++ konsol uygulamasıdır. Açık anahtarlı şifreleme (Public-Key Cryptography) mantığını aslına uygun bir matematikle konsol üzerinden test etmenizi sağlar.

## 🚀 Özellikler
- **Gerçek RSA Matematiği:** Asal sayı tespiti, Genişletilmiş Öklid Algoritması ve Hızlı Üs Alma (Fast Modular Exponentiation) içerir.
- **Dosya Tabanlı Çalışma:** `dosya1.txt` içerisindeki metinleri okuyarak şifreler (`sifreli.txt`'ye yazar) ve sonrasında gizli anahtar ile orijinal haline çevirir (`desifre.txt`'ye yazar).
- **Taşma Koruması:** `long long` ve `unsigned char` kullanılarak 64-bit hassasiyetinde veri kaybı yaşanmadan işlem yapılır.
- **ASCII & Türkçe Karakter Desteği:** Dosyalardaki boşlukları, satır atlamaları ve genişletilmiş karakterleri eksiksiz okur/yazar.

---

## 🛠️ Kurulum ve Kullanım

### Gereksinimler
Kodu derlemek için **MinGW (g++)** veya herhangi bir modern C++ derleyicisine ihtiyacınız vardır.

### Derleme
Terminal veya CMD ekranında proje dizinine girerek şu komutu çalıştırın:
```bash
g++ main.cpp -o rsa_app.exe
```

### Çalıştırma
Programı çalıştırın:
```bash
./rsa_app.exe
```

Ekranda sizden şifreleme (**e**) veya deşifreleme (**d**) işlemi seçmeniz istenecektir.

#### 1. Şifreleme (e)
* Programa **e** girin.
* İki adet **asal sayı (p ve q)** girin.
> **⚠️ Önemli Kural:** Kendi metin dosyalarınızdaki bütün harflerin (ASCII) eksiksiz şifrelenebilmesi için seçeceğiniz iki asal sayının çarpımı 255'ten büyük olmalıdır! *(Örn: p=17, q=19 veya daha büyük).*
* Program size hesapladığı açık anahtar (e) ihtimallerini sunacaktır. Gördüğünüz sayılardan herhangi birini (genelde küçük bir sayı) seçin.
* Program `dosya1.txt` içindeki verileri okuyup şifreleyecek, oluşturduğu **n** ve **d** (gizli anahtar) değerlerini size verecek ve şifreli metni `sifreli.txt`'ye kaydedecektir.

#### 2. Deşifreleme (d)
* Programa **d** girin.
* Şifreleme adımında size verilen **n** ve **d** gizli anahtarlarını sırayla girin.
* `sifreli.txt` dosyasındaki karmaşık sayılar okunacak ve orijinal metin oluşturularak `desifre.txt` dosyasına kaydedilecektir.

---

## 🧠 Algoritmanın Çalışma Mantığı (Arka Plan)

Uygulama, RSA algoritmasının standart 3 adımını eksiksiz uygular:

### 1. Anahtar Oluşturma
1. İki asal sayı seçilir (**P** ve **Q**).
2. Modül olan **n** değeri hesaplanır: $n = p \times q$
3. Euler Totient (Phi) fonksiyonu hesaplanır: $\phi(n) = (p-1) \times (q-1)$
4. $\phi(n)$ ile aralarında asal olan bir **e** (açık üs) seçilir ($1 < e < \phi(n)$).
5. Genişletilmiş Öklid Algoritması ile **d** (gizli üs) hesaplanır. Denklik: $d \times e \equiv 1 \pmod{\phi(n)}$
   > *Genel anahtar: (n, e) | Özel anahtar: (n, d)*

### 2. Şifreleme
Açık anahtar *(e,n)* kullanılarak `dosya1.txt` içerisindeki her bir karakter ($m$) şifrelenir ($c$) ve `sifreli.txt`'ye sayılar halinde yazılır:
> $c = m^e \pmod n$

### 3. Şifre Çözme
Gizli anahtar *(d,n)* kullanılarak `sifreli.txt` içerisindeki şifreli değerler ($c$) alınıp asıl harflere ($m$) dönüştürülerek `desifre.txt`'ye yazılır:
> $m = c^d \pmod n$
