
#ifndef KUTUPHANE_KTPHN_H
#define KUTUPHANE_KTPHN_H

#define MAX_SORU_UZUNLUK 256
#define MAX_SECENEK_UZUNLUK 100
#define MAX_SORU_SAYISI 20

struct kullanici {
    char ad[20];
    char soyad[20];
    long long int no;
    short sube;
   
};

struct quizeal {
    char metin[MAX_SORU_UZUNLUK];
    char secenekler[4][MAX_SECENEK_UZUNLUK];
    int dogruolan;
};
#endif //KUTUPHANE_KTPHN_H

