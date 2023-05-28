/*
 * pointer2.c
	kullanıcıdan birçok username bilgisini alıp bu kullanıcı adlarını
	users adlı bir dizide sakla
	programı kontrol eden bir menü sistemimiz olacak
	menü yapısı:
	1- kullanıcı ekle
	2- kullanıcı listele
	3- kullanıcı sil
	4- kullanıcı düzenle
	-------------------
	0 - Çıkış
	
	Data validasyonları:
	 7 < username < 90
	 0 < length_users_array < 10⁵ 
	 
	 1) do-while dongusunu 0'a basınca program sonlanacak
	 2) menuGoster gibi bir fonk. olusturulacak
	 3) Kullanıcının neyi sectiği alınacak
	    -getSelection fonk. olsun örn secenek sunacak (0-1-2-3-4)
	    -ve bu fonk. dogru sayı girilene kadar dönecek 0 ve 4 dahil.
	    -menuGoster'i bu fonksiyon kullanmalı.
	    -getSelection fonk. dogru veriyi return edecek,
	     dogru veri girildiğinde sonlanacak.
	    -seçenek adında değişkenin olsun,
	    getSelection  değişkenin içerinini dolduracak.switch-case ile
	    -her bir case bir fonk. cağırıyor olacak.
	 4)switch-case yapısı için fonksiyonlar oluşturacagız
		-1 icin >> addUser -> kullanıcıdan getName ile username(max.89)alınacak
		-username alındıktan sonra validasyonları kontrol edilmeli(getName içinde)
		* 
		-kullanıcı kac karakter girdiyse o kadar yer ayıracak
		-dogru veri alınana kadar geri bildirim yapılmalı
		*users adında global dizi tanımlanacak
		-Alınan veriyi main içerisinde kurulan users adlı değişkene eklemeliyiz
		// 
	    -2 icin >> listUsers fonk. -> users içerisindeki bilgileri alacağız
		- users içerisinde veri olup olmadıgının da kontrolu yapılmalı(null)
	    -3 için >> delUser fonk. -> kullanıcıdan silinecek username iste
	    -usernamein listede olup olmadıgını kontrol et
	    -eger listede silmek istenilen kullanıcı adı yoksa mesaj verilmeli
	    - ve devam etmek istiyor musunuz diye sorulmalı
	    - kullanıcı devam etmek istemiyorsa üst menüye dön
	    - eger silinmek istenen username dogru ise işlemini
	      evet/hayır secenekleri ile onaylatmalıyız
	    -isim listede yoksa uyarı ver, tekrar isim al
	    -silme işlemine evet denirse silme işlemi yapılıp basarılı mesajı verilmeli
	    -cevap hayır ise silme işlemi gercekleştirilemedi mesajı verilmeli.
		-4 icin >> editUser fonk ->  kullanıcıdan username alınacak
		-username ın olup olmadıgını kontrol edecegiz
		 yoksa uyarı mesajı/varsa değiştirme işlemi
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MIN_NAME 4
#define MAX_NAME 89
#define MAX_USERS 100000

char **users = NULL;  
int len_user = 0;


void showMenu(void);
int getSelection(void);
char *getName(char *promt);
void addUser(void);
void listUsers(void);
void delUser(void);
void editUser(void);

int main(int argc, char **argv)
{

	int flag = 1, selection;
	
	while(flag == 1)
	{
		selection = getSelection();
		switch(selection)
		{
			case 0:
				flag = 0;
				break;
			case 1: 
				addUser();
				break;
			case 2:
				listUsers();
				break;
			case 3:
				delUser();	
				break;
			case 4:
				editUser();
				break;
		}
	}
	
	return 0;
}
void clearInputBuffer(void)
{
	char c;
	while((c = getchar()) != '\n' && c != EOF);
}
void showMenu(void)
{
	puts("\n1-Kullanici Ekle");
	puts("2-Kullanici Listele");
	puts("3-Kullanici Sil");
	puts("4-Kullanici Duzenle");
	puts("-------------------");
	puts("0-CIKIS\n");
	
}
int getSelection(void)
{	 
	 int select, flag = 1;
	 
	do
	{
		showMenu();
		printf("\nistediginiz secenegi giriniz: ");
		scanf("%d", &select);
		printf("\n");
		if(select < 0 || select > 4)
		{
			puts("\n HATA!Gecerli bir deger giriniz.");
		}
		else
		{
			flag = 0;
		}	
	}while (flag);
	
return select;
}

char *getName(char *promt)
{
	char buff[MAX_NAME + 1];   //buff geçici bellek olarak kullanmak amaclı olusturuluyor
	char *name;
	int len, flag = 1;
	
	do{
		printf("%s >>",promt);
		//scanf("%s",&buff);
		
		
		//clearInputBuffer();
		fflush(stdin);
		gets(buff);
		len = strlen(buff);
		if(len <= MAX_NAME && len >= MIN_NAME)
		{
			name = (char*)malloc(sizeof(char)* (len+1));
			strcpy(name,buff);
			flag =0;
		}
		else
			puts("HATA! please try again...");
	}while(flag);
	
	return name;
}

void addUser(void)
{
	char *uname = getName("Kullanici adini giriniz:");
	if(users == NULL)
	{
		users = (char**)malloc(sizeof(char*) * (len_user + 1));
	}
	else
	{
		users = (char**)realloc(users,sizeof(char*) * (len_user + 1));
	}
		
	users[len_user] = uname;
	len_user++;
	puts("kullanici basari ile eklendi");
}

void listUsers(void)
{
	if(len_user > 0)
	{
		for(int i = 0; i < len_user ; i++)	
			if(users[i] != NULL)
				printf("%s \n",users[i]);
		
	}
	else
		printf("Kullanici Bulunamadi!");
	
}
void delUser(void)
{
	char *uname = getName("Kullanici adini giriniz:");
	int ret;
	char ans;
	
	for(int i = 0; i < len_user ; i++)
	{
		ret = strcmp(uname, users[i]);
		
		if(ret == 0)
		{		
			puts("Kullanici bulundu");
			printf("Silme islemini onayliyor musunuz(y/n):");
			fflush(stdin);
			scanf("%c",&ans);	
			ans = toupper(ans);
			if(ans == 'Y')
			{
				free(users[i]);
				users[i] = NULL;		
				printf("Silme isleminiz gerceklestirildi.\n");
			}
			else if(ans == 'N')
				printf("Silme islemi iptal.");
			
			else
				printf("gecersiz secenek.");	
		}
		else
			puts("Boyle bir kullanici bulunmamaktir.");	
	}
	free(uname);
}
void editUser(void)
{
	char *uname = getName("Duzenlemek istediginiz kullanici adini giriniz:");
	int ret;
	char ans,input;
	
	 for(int i = 0; i < len_user ; i++)
	 {
		ret = strcmp(uname, users[i]);
		
		if(ret == 0)
		{		
			puts("Kullanici bulundu");
			printf("Duzenleme islemini onayliyor musunuz(y/n):");
			
			scanf("%c",&ans);	
			ans = toupper(ans);
			if(ans == 'Y')
			{
				free(users[i]);	
				printf("yeni ismi giriniz.\n");
				fflush(stdin);
				scanf("%s",&input);
				users[i] = input;	
				printf("Duzenleme islemi basarili");
			}
			else if(ans == 'N')
				printf("Duzenleme islemi iptal.");
			
			else
				printf("gecersiz secenek.");	
		}
		else
			puts("Boyle bir kullanici bulunmamaktir.");	
	 }
	free(uname);
}
//EDİT KISMI RUNTİME ERROR VERİYOR

