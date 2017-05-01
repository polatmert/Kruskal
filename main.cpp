


///kisa yol agacinin cizilebilmesi icin  allegro kutuphanesinin ekli olmasi gerekmektedir
///grafik ekranin calismasi icin  'arkaplan.bmp'  ve 'beyazarkaplan.bmp' dosyalarinn  proje klasorunda olması gerekmektedir






#include <iostream>
#include <iomanip>      // std::setw
#include <stdlib.h>
#include <stdio.h>
#include <allegro.h>


using namespace std;

class C_dugum{
    public:
        int satir;
        int sutun;

        void koordinat_ayarla(int sat,int sut){
            this->satir=sat;
            this->sutun=sut;
        };

};
struct kenar {
    int d1;//birinci dugum
    int d2;//ikinci dugum
    int uzaklik;//dugumler arasi uzaklik

};

int main()
{
    int dugum_matrisi[20][20]={};
    int dugum_adet=0;
    C_dugum dugum[400];
    int temp_satir=-1;
    int temp_sutun=-1;
    int sayac1=0;

    char temp_char[10];

    cout<<"kac tane dugum girelecek = ";
    while(!(cin>>dugum_adet))
          {
            cout<<"Hatali giris !!";
            cin.clear();
            cin.ignore(500, '\n');
          }


    cout<<endl;

    for(sayac1=0; sayac1< dugum_adet; sayac1++)
    {
        temp_satir=-999;
        temp_sutun=-999;
    cout<<sayac1<<".dugum satiri giriniz : ";

    while (!(cin >> temp_satir) || temp_satir<0 || temp_satir>19)
	{
		cout << "Hatali giris tekrar satir giriniz " ;
		cin.clear();
		cin.ignore(500, '\n');
	}


    cout<<sayac1<<".dugum sutun giriniz  : ";
    while (!(cin >> temp_sutun) || temp_sutun<0 || temp_sutun>19)
	{
		cout << "Hatali giris tekrar sutun giriniz " ;
		cin.clear();
		cin.ignore(500, '\n');
	}



          if((dugum_matrisi[temp_satir][temp_sutun])==1)
          {
              cout<<"!!!  bu dugum daha once girilmis !!!"<<endl;
              sayac1--;

              continue;
          }
        ///alinan satir,sutun degerlerini  dugumler dizisinde sakliyor
        dugum[sayac1].koordinat_ayarla(temp_satir,temp_sutun);
        ///alinan dugumlerin koordinatlarini kullanarak matris ustunde isaratleme yapiyor
        /// "1"e esit olmasi orda bir dugum oldugunu gosteriyor
        dugum_matrisi[temp_satir][temp_sutun]=1;
        cout<<endl;


    }//for sonu




//MATRISIN EKRANA YAZILMASI
int ii=0,jj=0;
for(ii=0;ii<20;ii++)
    {
        for(jj=0;jj<20;jj++){
            cout<<dugum_matrisi[ii][jj]<<" ";
        }
        cout<<endl;
    }


///KOMSULUK MATRISI  olusturuluyor

    int komsuluk_matrisi[400][400]={};
    int kom_sat=0,kom_sut=0;

    for(kom_sat=0;kom_sat<dugum_adet;kom_sat++)
        {
        for(kom_sut=0;kom_sut<dugum_adet;kom_sut++)
            {
               ///dugumlar arasi uzaklik hesaplama
                if(kom_sut==kom_sat)
                    {
                    ///dugumun kendine olan uzakligi sonsuzlugu temsili olarak 99999 olarak kayit edilmistir
                    komsuluk_matrisi[kom_sat][kom_sut]=99999;
                    }else
                        {
                        ///her dugumun digerine olan uzakligi hesaplanarak komsuluk matrisi olusturuluyor
                        komsuluk_matrisi[kom_sat][kom_sut]=abs(dugum[kom_sat].satir-dugum[kom_sut].satir)+abs(dugum[kom_sat].sutun-dugum[kom_sut].sutun);
                        }
            }

        }///matris okuma ve komsuluk matrisi olusturma dongusu sonu



cout<<endl<<"**************************************************************"<<endl<<endl;
///komsuluk matrisinin ekrana yazdirilmasi
cout<<"Komsuluk matrisi"<<endl;
int jjj=0,iii=0;
for(jjj=0;jjj<dugum_adet;jjj++){
    for(iii=0;iii<dugum_adet;iii++)
        {
            cout<<setw(5)<<komsuluk_matrisi[jjj][iii]<<"   ";
        }
    cout<<endl;
}
cout<<endl<<"**************************************************************"<<endl<<endl;

int sirala_sat=0;
int sirala_sut=0;
int enk_kenar=999;
int enk_x=0,enk_y=0;
int kenar_adet=(((dugum_adet-1)*(dugum_adet))/2);

struct kenar * sirali_kenarlar;
sirali_kenarlar = (struct kenar*)malloc(kenar_adet* sizeof(struct kenar));


////////////////////
int whi_sayac=0;
while(whi_sayac<kenar_adet)
{
 enk_kenar=999;
      for(sirala_sat=0;sirala_sat<dugum_adet;sirala_sat++)
        {
            for(sirala_sut=sirala_sat+1;sirala_sut<dugum_adet;sirala_sut++)
            {
                if(komsuluk_matrisi[sirala_sat][sirala_sut]<enk_kenar)
                {
                    enk_kenar=komsuluk_matrisi[sirala_sat][sirala_sut];
                    enk_x=sirala_sat;
                    enk_y=sirala_sut;
                }
            }
        }


   ///ulunan en kucuk kenari listedeki ilk bosluga ekler
   ///komsuluk matirsindeki degerin yerine buyuk bir deger yazar
    ///bu sayede dongu tekrar donerken en kisa kenari tekrar bulmaz
    	//sirali_kenarlar = (struct kenar*)realloc(sirali_kenarlar, whi_sayac * sizeof(struct kenar));
    sirali_kenarlar[whi_sayac].d1=enk_x;
    sirali_kenarlar[whi_sayac].d2=enk_y;
    sirali_kenarlar[whi_sayac].uzaklik=enk_kenar;
   // cout<<" enkisalar"<<enk_x<<" "<<enk_y;
    komsuluk_matrisi[enk_x][enk_y]=99;
    whi_sayac++;

}//while sonu

//cout<<"**************************************************************"<<endl;

///siralanmis kenarlari harfharf ekrana yazdirir
whi_sayac=0;
while(whi_sayac<kenar_adet)
{
printf("%c___",sirali_kenarlar[whi_sayac].d1+'A');
printf("%c  arasi uzaklik:",sirali_kenarlar[whi_sayac].d2+'A');
printf("%d\n",sirali_kenarlar[whi_sayac].uzaklik);

    whi_sayac++;
}

cout<<endl<<"______________________________________________________________"<<endl<<endl;

///renkler dizisinin birinci indeksinde 1 .kisa kenar icin
    ///ikinci indekste ikinci icin renk sayisi tutulacak

///en kisa kenar alinacak kenarin uclarinda sayilarin, renk dizisindeki renkleri kontrol edilecek
 ///e?er renkler farkli ise o kenar kisa yol agacina adindaki dinamik listeye ekelenecek
 ///bu iki dugum renkleri birbirine esit olacak ssekilde islem yapilacak bu duguma bagli diger dugumlerde bulunarak onlarda renklendirecek
     ///eger renkler ayni ise cevrim oldugu icin dugum enkysa yol agacyna eklenmeyecek gecilecek


struct kenar * kisayol;
kisayol = (struct kenar*)malloc(kenar_adet* sizeof(struct kenar));

int maliyet=0;

int *renkler = (int*)malloc(kenar_adet * sizeof(int));
int enk_sayac=0;///en kisa yol agacindaki yollari sayar

if(dugum_adet==2)
{
   kisayol[0].d1=sirali_kenarlar[0].d1;
   kisayol[0].d2=sirali_kenarlar[0].d2;
   kisayol[0].uzaklik=sirali_kenarlar[0].uzaklik;
   enk_sayac++;
   maliyet=kisayol[0].uzaklik;
}else{

cout<<"CEVRIM VE KENARLARIN EKLENMESI"<<endl<<endl;


for (int i = 0 ; i < kenar_adet ; i++)
    {
     renkler[i] = i;
	}

    for (int i = 0 ; i < kenar_adet ; i++)
      {

		int cevrim_varmi = 0;

		int d1 = sirali_kenarlar[i].d1;
		int d2 = sirali_kenarlar[i].d2;

		if (renkler[d1] == renkler[d2]) {
			/// iki dugum ayni renkteyse cevrim olmustur
			cevrim_varmi = 1;
			printf("eklenmedi cevrim var: %c - %c\n", 'A'+d1, 'A'+d2);
		}

        if (cevrim_varmi==0) {
			// su anda incelenen (i. indexteki) kenari ekle
			kisayol[enk_sayac] = sirali_kenarlar[i];////////////////////////&&&&&&&&&&&&&&&&&&&&&&&&&&
			enk_sayac++;
			maliyet=maliyet+sirali_kenarlar[i].uzaklik;
			printf("kenar eklendi: (%c - %c)\n",'A'+d1, 'A'+d2);
			// d2 dugumuyle ayni renkte olan tum dugumlere d1'in rengini ata
			int d1_renk = renkler[d1];
			int d2_renk = renkler[d2];
			for (int j = 0 ; j < dugum_adet ; j++) {
				if (renkler[j] == d2_renk) {
					renkler[j] = d1_renk;
				}
			}
		}
    }


    }///*da*s0d*asd*as9*0as9f0*as9f09as*0f9as*0f9as





cout<<"______________________________"<<endl<<endl<<endl;
cout<<endl<<"        MALIYET= "<<maliyet<<endl<<endl<<endl;
cout<<"______________________________"<<endl;

 allegro_init();///allegroyu projeye dahil eder
    set_window_title("_EN KISA YOL ALGORITMASI CIZIMI_");
    set_color_depth(32);///ekranin renk derinligini belir
    set_gfx_mode(GFX_AUTODETECT_WINDOWED, 500,500,0,0);///allegro ekraninin windowed yapar.belirli cozunurluk ayarlar
    BITMAP *buffer=NULL;
    BITMAP *arkaplan=NULL;
    BITMAP *arkaplan_beyaz=NULL;

    buffer=create_bitmap(500,500);///buffer icin yer ayriliyor

    arkaplan=load_bitmap("beyazarkaplan.bmp",NULL);
    draw_sprite(buffer,arkaplan,0,0);

    arkaplan=load_bitmap("arkaplan.bmp",NULL);///arkaplan degiskenine kareli ızgara desenini atar

    int dsat1=0,dsut1=0,dsat2=0,dsut2=0;
    draw_sprite(buffer,arkaplan,10,10);///arka plan resmini buffer ustune yazar

for(ii=0;ii<enk_sayac;ii++)
{

    dsat1=dugum[kisayol[ii].d1].satir;
    dsut1=dugum[kisayol[ii].d1].sutun;

    dsat2=dugum[kisayol[ii].d2].satir;
    dsut2=dugum[kisayol[ii].d2].sutun;


 //textout_ex(buffer, font,'A', dsut1*20, dsat1*20, makecol(0, 0, 255), -1);
//void textprintf_ex(BITMAP *bmp, const FONT *f, int x, int y, int color, int bg, const char *fmt, ...);

///dugumlerin oldugu yerlere dugumlerin adini yaziyor
textprintf_ex(buffer, font,dsut1*20+10, dsat1*20+10, makecol(255, 0, 0),-1, "%c", kisayol[ii].d1+'A');
textprintf_ex(buffer, font,dsut2*20+10, dsat2*20+10, makecol(255, 0, 0),-1, "%c", kisayol[ii].d2+'A');


         line(buffer,  dsut1*20+10,  dsat1*20+10, dsut1*20+10, dsat2*20 +10 ,  0x5a0543);//dikey
    if(dsat1-dsat2<0)//2.asagi ise
         line(buffer,  dsut1*20+10,  dsat2*20+10,  dsut2*20+10,  dsat2*20+10,  0x5a0543);//dikey
    else
        line(buffer,  dsut1*20+10,  dsat2*20+10,  dsut2*20+10,  dsat2*20+10,  0x5a0543);//dikey
    //line(BITMAP *bmp, int x1, int y1, int x2, int y2, int color);
    //line(buffer,  50,  50,  100,  100,  0xff);//dikey
    draw_sprite(screen,buffer,0,0);//buffery ekrana yazdiriyor

}
int sayi;
cin>>sayi;
    return 0;
}
END_OF_MAIN()

