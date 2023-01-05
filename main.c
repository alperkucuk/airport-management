#include <stdio.h>
#include <stdlib.h>
int counter3=0,w,e,holder=0 ,holder2=0,holder_index, counter=0;
int disembarks_priority[24];
int disembarks_id[24];
int disembarks_demanding_time[24];
int disembarks_landing_time[24];
int disembarks_delay[24];
int takeoff_delay_counter[24];

int takeoff_runway_acceptence_priority[24];
int takeoff_runway_acceptance_id[24];
int takeoff_runway_acceptance_demanding_time[24];
int takeoff_runway_acceptance_landing_time[24];
int takeoff_runway_acceptance_takeoff_time[24];
int takeoff_runway_acceptance_delay[24];
int demand_time,departure_time,delay ;
int dizi[24] ;
void takeoffUpdate()
{
	int i ;
	for(i=0;i<24;i++)
	{
		takeoff_runway_acceptence_priority[i]=disembarks_priority[i];
		takeoff_runway_acceptance_id[i]=disembarks_id[i];
		takeoff_runway_acceptance_demanding_time[i]=disembarks_demanding_time[i];
		takeoff_runway_acceptance_landing_time[i]=disembarks_landing_time[i];
		if(disembarks_id[i]!=0){
			takeoff_runway_acceptance_takeoff_time[i]=disembarks_landing_time[i]+1;
		}
		
		takeoff_runway_acceptance_delay[i]=disembarks_delay[i];
		
		if(takeoff_runway_acceptance_landing_time[i]>=25){
			takeoff_runway_acceptance_landing_time[i]=takeoff_runway_acceptance_landing_time[i]%24;
		}
		if(disembarks_id[i]!=0){
			if(takeoff_runway_acceptance_takeoff_time[i]>=25)
			{
				takeoff_runway_acceptance_takeoff_time[i]=takeoff_runway_acceptance_takeoff_time[i]%24;
			}
			
		}
		
		
		
		
		
	}
	printf("Oncelik   id   talep    inis   kalkis  delay \t \t SAAT\n");
	for (i=0;i<24;i++)
	{
		printf("  %d \t  %d \t %d \t  %d \t  %d \t %d \t\t%d\n",takeoff_runway_acceptence_priority[i],takeoff_runway_acceptance_id[i],takeoff_runway_acceptance_demanding_time[i],takeoff_runway_acceptance_landing_time[i],takeoff_runway_acceptance_takeoff_time[i],takeoff_runway_acceptance_delay[i],i+1);
	}
	
}
void printDisembarksList()
{
	int i ;
	printf("\n");
	printf("\n");
	for(i=0;i<24;i++)
	{
		printf("%d ",disembarks_id[i]);
		if(i==8){
			printf(" ");
		}
		if(i>=9){
			printf(" ");
		}
	}
	
	printf("\n");
	
	printf("saat\n");
	printf("1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24");
	printf("\n");
	printf("\n");
	printf("\n");
}
void printTakeoff()
{
	int a ;
	FILE *file ;
	file=fopen("output.txt","w");
	for (a=0;a<24;a++){
		fprintf(file,"%d %d %d %d %d %d\n",takeoff_runway_acceptence_priority[a],takeoff_runway_acceptance_id[a],takeoff_runway_acceptance_demanding_time[a],takeoff_runway_acceptance_landing_time[a],takeoff_runway_acceptance_takeoff_time[a],takeoff_runway_acceptance_delay[a]);
	}
	fclose(file);
}
void insertByPriority(int w,int priority,int plane_id,int landing_time)
{
	int i=0,holder=0,holder2=0 ;
	
	for(i=w;i<24;i++)
	{
		if(disembarks_priority[i]>priority)
		{
			holder=i ;
			printf("Tutac : %d\n",holder);
			break;
		}
		else if (disembarks_priority[i]==0)
		{
			holder2=i ;
			break ;	
		}
		if(i==23)
		{
			i=0;
		}
	}
	if(holder2!=0)
	{
		
		printf("Siradaki ucaklarin onceligi sizden yuksek veya esit oldugundan dolayi bir sonraki bos saatte inebilirsiniz.\n");
		printf("%d id'li ucagin inis saati %d olarak izin verilmistir. Iyi yolculuklar dileriz.\n",plane_id,holder2+1);
			
		disembarks_id[holder2]=plane_id;
		disembarks_priority[holder2]=priority;
		disembarks_demanding_time[holder2]=landing_time;
		disembarks_landing_time[holder2]=holder2+1;
		if(disembarks_landing_time[holder2]>=25)
		{
			disembarks_landing_time[holder2]=disembarks_landing_time[holder2]%24 ;
		}
		disembarks_delay[holder2]=holder2-landing_time+1 ;
	}
	else
	{
		int holder0=50 ;
		for(i=holder;i<24;i++)
		{
			if(disembarks_id[i]==0)
			{
				holder0=i ;
				break ;
			}
		}
	/*	if(holder0==50)
		{
			
		}*/
		for(i=holder0;i>holder;i--)
		{
			disembarks_id[i]=disembarks_id[i-1];
			disembarks_priority[i]=disembarks_priority[i-1];
			disembarks_demanding_time[i]=disembarks_demanding_time[i-1];
			
			if(disembarks_id[i-1]!=0)
			{
				disembarks_landing_time[i]=disembarks_landing_time[i-1]+1;
				if(disembarks_landing_time[i]>=25)
				{
					disembarks_landing_time[i]=disembarks_landing_time[i]%24;
				}
				disembarks_delay[i]=disembarks_delay[i-1]+1 ;
			}
			
		}
		disembarks_id[holder]=plane_id;
		disembarks_priority[holder]=priority;
		disembarks_demanding_time[holder]=landing_time;
		disembarks_landing_time[holder]=holder+1; 
		if(disembarks_landing_time[holder]>=25)
		{
			disembarks_landing_time[holder]=disembarks_landing_time[holder]%24;
		}
		disembarks_delay[holder]=holder-landing_time+1 ;
		printf("%d id'li ucagin inis saati %d 'dir\n",disembarks_id[holder],disembarks_landing_time[holder]);
	}
}
void insert(int w,int priority,int plane_id,int landing_time)
{
	int dizi[24],i,j=0,holder=50;
	int dizi2[24],dizi3[24];
	for(i=w;i<24;i++)
	{
		if(disembarks_id[i]==0)
		{
			holder=i ;
			
			break ;
		}
		if(i==23 && holder==50)
		{
			i=0;
		}
	}
	if(w<holder)
	{
		for (i=holder;i>w;i--)
		{
			disembarks_id[i]=disembarks_id[i-1];
			disembarks_priority[i]=disembarks_priority[i-1];
			disembarks_demanding_time[i]=disembarks_demanding_time[i-1];
			disembarks_landing_time[i]=disembarks_landing_time[i-1]+1;
			if(disembarks_landing_time[i]>=25)
			{
				disembarks_landing_time[i]=disembarks_landing_time[i]%24;
			}
			disembarks_delay[i]=disembarks_delay[i-1]+1 ;
		}
	}
	else
	{
		int tutamac ;
		for(i=0;i<24;i++)
		{
			if(disembarks_id[i]==0)
			{
				tutamac=i ;
				break ;
			}
		}
		for(i=tutamac;i>0;i--)
		{
			disembarks_id[i]=disembarks_id[i-1];
			disembarks_priority[i]=disembarks_priority[i-1];
			disembarks_demanding_time[i]=disembarks_demanding_time[i-1];
			disembarks_landing_time[i]=disembarks_landing_time[i-1]+1;
			if(disembarks_landing_time[i]>=25)
			{
				disembarks_landing_time[i]=disembarks_landing_time[i]%24;
			}
			disembarks_delay[i]=disembarks_delay[i-1]+1 ;
		}
		disembarks_id[0]=disembarks_id[23];
		disembarks_priority[0]=disembarks_priority[23];
		disembarks_demanding_time[0]=disembarks_demanding_time[23];
		disembarks_landing_time[0]=disembarks_landing_time[23]+1;
		if(disembarks_landing_time[0]>=25){
			disembarks_landing_time[0]=disembarks_landing_time[0]%24;
		}
		disembarks_delay[0]=disembarks_delay[23]+1 ;
		for (i=23;i>w;i--)
		{
			disembarks_id[i]=disembarks_id[i-1];
			disembarks_priority[i]=disembarks_priority[i-1];
			disembarks_demanding_time[i]=disembarks_demanding_time[i-1];
			disembarks_landing_time[i]=disembarks_landing_time[i-1]+1;
			if(disembarks_landing_time[i]>=25)
			{
				disembarks_landing_time[i]=disembarks_landing_time[i]%24;
			}
			disembarks_delay[i]=disembarks_delay[i-1]+1 ;
		}
		
	}
	
	disembarks_id[w]=plane_id;
	disembarks_priority[w]=priority;
	disembarks_demanding_time[w]=landing_time;
	disembarks_landing_time[w]=landing_time;
	if(disembarks_landing_time[w]>=25)
	{
		disembarks_landing_time[w]=disembarks_landing_time[w]%24;
	}
	disembarks_delay[w]=0 ;
	
	/*
	for (i=w;i<24;i++)
	{
		dizi[i]=0 ;
		dizi2[i]=0 ;
		dizi3[i]=0 ;
	}
	for (i=w;i<24;i++)
	{
		if(inecek_olanlar_id[i]!=0 && inecek_olanlar_oncelik[i]!=0 &&inecek_olanlar_saat[i]!=0){
		
		dizi[i]=inecek_olanlar_id[i]+1;
		dizi2[i]=inecek_olanlar_oncelik[i]+1;
		dizi3[i]=inecek_olanlar_saat[i]+1 ;
		}
	}
	memmove(dizi+1,dizi,sizeof(dizi)-sizeof(*dizi));
	memmove(dizi2+1,dizi2,sizeof(dizi2)-sizeof(*dizi2));
	memmove(dizi3+1,dizi3,sizeof(dizi3)-sizeof(*dizi3));
	dizi[w]=plane_id;
	dizi2[w]=priority;
	dizi3[w]=landing_time;
	holder=0;
	for(i=0;i<24;i++)
	{
		if(i+1==w)
		{
			holder=1;	
		}
		else if(holder==1)
		{
			inecek_olanlar_id[i]=dizi[i];
			inecek_olanlar_oncelik[i]=dizi2[i];
			inecek_olanlar_saat[i]=dizi3[i];
		}
	}*/
}
void add(int priority,int plane_id,int landing_time){
	int a,b,c ;
	if(counter<=23)
	{
		for(w=0;w<24;w++)
		{
			if(disembarks_landing_time[w]==landing_time)
			{
				holder=1 ;
				holder_index=w ;
				break ;
			}
		}
		if(holder==1)
		{
			printf("Inis saatiniz icin farkli bir ucak izin almistir. Lutfen bekleyin, oncelik durumunuz kontrol ediliyor\n");
			if(disembarks_priority[holder_index]>priority)
			{
				printf("%d id'li ucagin oncelik sirasi dusuk oldugu icin inis saati erteleniyor.\n",disembarks_id[holder_index]);
				printf("%d id'li ucak %d saatine izin almistir.\n",plane_id,landing_time);
				insert(holder_index,priority,plane_id,landing_time);
			}
			else
			{
				printf("Istediginiz inis saatinde oncelik siralamasi sizden yuksek bir ucak bulunmaktadir. Onceliginize gore inis saatiniz hesaplaniyor.\n");
				insertByPriority(holder_index+1,priority,plane_id,landing_time);
			}
			
			
		}
		else
		{
			printf("%d id'li ucak %d saatine inis icin izin almistir.\n",plane_id,landing_time);
			disembarks_id[landing_time-1]=plane_id ;
			disembarks_priority[landing_time-1]=priority ;
			disembarks_landing_time[landing_time-1]=landing_time;
			if(disembarks_landing_time[landing_time-1]>=25)
			{
				disembarks_landing_time[landing_time-1]=disembarks_landing_time[landing_time-1]%24;
			}
			disembarks_demanding_time[landing_time-1]=landing_time;
			disembarks_delay[landing_time-1]=0 ;
			
		}
		holder=0;	
	}
	else
	{
		int tutamac2=0,holder_index;
		for(w=0;w<24;w++)
		{
			if(disembarks_landing_time[w]==landing_time)
			{
				tutamac2=1 ;
				holder_index=w ;
				break ;
			}
		}
		printf("Inis saatiniz icin farkli bir ucak izin almistir. Lutfen bekleyin, oncelik durumunuz kontrol ediliyor\n");
		if(disembarks_priority[holder_index]>priority)
		{
			printf("%d id'li ucagin oncelik sirasi dusuk sabiha gokcen hava alanina yonlendiriliyor.\n",disembarks_id[holder_index]);
			printf("%d id'li ucak %d saatine izin almistir.\n",plane_id,landing_time);
			
			disembarks_id[holder_index]=plane_id ;
			disembarks_priority[holder_index]=priority ;
			disembarks_landing_time[holder_index]=landing_time;
			if(disembarks_landing_time[holder_index]>=25)
			{
				disembarks_landing_time[holder_index]=disembarks_landing_time[holder_index]%24;
			}
			disembarks_demanding_time[holder_index]=landing_time;
			disembarks_delay[holder_index]=0 ;
			
		}
		else
		{
			printf("Istediginiz inis saatinde onceligi sizden yuksek bir ucak bulunmaktadir.\n");
			printf("Inis pistinde yer olmadigi ve inmek istediginiz saatte daha yuksek oncelikli bir ucak oldugundan izniniz reddedildi.\n");
		}
	}
	counter++;
}

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char *argv[]) {
	FILE *dosya ;
	dosya=fopen("input.txt","r");
	/*for (i=0;i<count;i++){
	fscanf(dosya,"%d %d %d\n",&a,&b,&c);
	indexfile[i].ogrno=a;
	indexfile[i].derskodu=b ;
	indexfile[i].puan=c ;
	}*/
	for (counter3=0;counter3<24;counter3++)
	{
	disembarks_id[counter3]=0;
	disembarks_priority[counter3]=0;
	disembarks_demanding_time[counter3]=0;
	disembarks_landing_time[counter3]=0;
	disembarks_delay[counter3]=0;
	takeoff_delay_counter[counter3]=0;
	
	}
	char deneme1[100];
	char deneme2[100];
	char deneme3[100];
	int i=0 ;
	while (!feof(dosya)) 
	{
		if(i!=0)
		{
			fscanf(dosya,"%s %s %s\n",&deneme1,&deneme2,&deneme3);
    		if (ferror(dosya)) 
			{
         	printf("Kaynak dosyadan okuma hatasi!\n");
         	break ;
     		}
  		}
		  i++ ;	
	}
  fclose (dosya);
  int linesayisi=i-2 ;
  FILE *dosya2 ;
  dosya2=fopen("input.txt","r");
  int oncelik_sirasi[i-2] ;
  int ucak_id[i-2] ;
  int inis_saati[i-2];
  int j=0;
  char a[3],b[3],c[3] ;
  while (!feof(dosya2)) 
	{
		
		if(j!=0)
		{
			fscanf(dosya2,"%s %s %s \n",&a,&b,&c);
			int a1,b1,c1 ;
			a1=atoi(a);
			b1=atoi(b);
			c1=atoi(c);	
			inis_saati[j-1]=c1;
			ucak_id[j-1]=b1;
			oncelik_sirasi[j-1]=a1;
    		if (ferror(dosya2)) 
			{
         	printf("Kaynak dosyadan okuma hatasi!\n");
         	break ;
     		}
  		}
		  j++ ;	
	}
  fclose(dosya2);
  int oncelik_sirasi_final[linesayisi];
  int ucak_id_final[linesayisi];
  int inis_saati_final[linesayisi];
  for(i=0;i<28;i++)
  {
	oncelik_sirasi_final[i]=oncelik_sirasi[i+1];
	ucak_id_final[i]=ucak_id[i+1];
	inis_saati_final[i]=inis_saati[i+1];
  }
  
  char aaa ;
  for(i=0;i<24;i++){
  	takeoff_runway_acceptence_priority[i]=0;
	takeoff_runway_acceptance_id[i]=0;
	takeoff_runway_acceptance_demanding_time[i]=0;
	takeoff_runway_acceptance_landing_time[i]=0;
	takeoff_runway_acceptance_takeoff_time[i]=0;
	takeoff_runway_acceptance_delay[i]=0;
  }
  for(i=0;i<linesayisi;i++)
  {
  	printf("%d id numarasi sahip ucak %d saatine inis talep etmektedir.\n",ucak_id_final[i],inis_saati_final[i]);
  	add(oncelik_sirasi_final[i],ucak_id_final[i],inis_saati_final[i]);
  	takeoffUpdate();
  	printTakeoff();
  	scanf("%c",&aaa);
  }
  
	
	return 0;
}
