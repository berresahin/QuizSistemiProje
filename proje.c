#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ktphn.h"

void sonuclariDosyayaYaz(struct kullanici kisi, int toplampuan) {
    FILE *dosya = fopen("C:\\Users\\CASPER\\Desktop\\algoritma\\sonuclar.txt", "a");

    if (dosya == NULL) {
        printf("Sonuclar dosyasi acilamadi!\n");
        return;
    }

    fprintf(dosya, "\nAdi: %s %s \nNo: %lld \nSube: %hd  \nPuan: %d ", kisi.ad,kisi.soyad,kisi.no,kisi.sube, toplampuan);
    fprintf(dosya, "\n*******************************************************************");

    fclose(dosya);
}

void sonuclariGoruntule() {
    FILE *dosya = fopen("C:\\Users\\CASPER\\Desktop\\algoritma\\sonuclar.txt", "r");

    if (dosya == NULL) {
        printf("Sonuclar dosyasi acilamadi!\n");
        return;
    }

    char karakter;
    while ((karakter = fgetc(dosya)) != EOF) {
        printf(" %c", karakter);
    }

    fclose(dosya);
}

void quiziBaslat() {
    FILE *dosya = fopen("C:\\Users\\CASPER\\Desktop\\algoritma\\sorular.txt", "r");

    if (dosya == NULL) {
        printf("Dosya acilamadi!\n");
        return;
    }

    struct quizeal sorular[MAX_SORU_SAYISI];
    char satir[MAX_SORU_UZUNLUK];

    int index = 0;
    while (fgets(satir, sizeof(satir), dosya) && index < MAX_SORU_SAYISI) {
        char *token = strtok(satir, ";");

        if (token != NULL) {
            strcpy(sorular[index].metin, token);
        }

        for (int i = 0; i < 4; ++i) {
            token = strtok(NULL, ";");
            if (token != NULL) {
                strcpy(sorular[index].secenekler[i], token);
            }
        }

        token = strtok(NULL, ";");
        if (token != NULL) {
            sorular[index].dogruolan = atoi(token);
        }

        index++;
    }

    fclose(dosya);

    struct kullanici kisi;

    printf("Adinizi ve soyadinizi giriniz: ");
    scanf("%s" "%s",&kisi.ad,&kisi.soyad);
    printf("Numaranizi giriniz: ");
    scanf("%lld",&kisi.no);
    printf("Subenizi giriniz: ");
    scanf("%hd",&kisi.sube);

    int toplampuan = 0;

    for (int i = 0; i < MAX_SORU_SAYISI; ++i) {
        printf("\nSoru %d: %s\n", i + 1, sorular[i].metin);

        for (int j = 0; j < 4; ++j) {
            printf("%s\n", sorular[i].secenekler[j]);
        }

        int cevap;
        printf("Cevabinizi giriniz (1-4): ");
        if (scanf("%d", &cevap) != 1 || cevap < 1 || cevap > 4) {
            printf("Gecersiz cevap! Lutfen 1 ile 4 arasinda bir sayi girin.\n");
            while (getchar() != '\n'); // Geçersiz girişi temizle
            i--; // Aynı soruyu tekrar sor
            continue;
        }

        if (cevap == sorular[i].dogruolan) {
            printf("Dogru!\n");
            toplampuan = toplampuan + 5;
        } else {
            printf("Yanlis!\n");
        }
    }

    printf("\n\nQuizi tamamladiniz. Toplam puaniniz: %d\n",toplampuan);
    sonuclariDosyayaYaz(kisi, toplampuan);
}

int main() {
    int secim;

    do {
        printf("\nLutfen bir secenek seciniz:\n");
        printf("1. Quizi baslat\n");
        printf("2. Sonuclari goruntule\n");
        printf("3. Programdan cik\n");
        scanf("%d", &secim);

        switch (secim) {
            case 1: {
                quiziBaslat();
                break;
            }
            case 2: {
                sonuclariGoruntule();
                break;
            }
            case 3: {
                printf("Programdan cikiliyor...\n");
                return 0;
            }
            default: {
                printf("Gecersiz secim! Lutfen tekrar secim yapin.\n");
                break;
            }
        }

    } while (secim != 3);

    return 0;
}