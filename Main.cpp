#include <iostream>
#include <cstring>
#include <cstdlib>

using std::cin;
using std::cout;
using std::endl;

void Juego(char**,char**,int ,int);
void Matching(char**,char**,char**,int ,int,int);
void Reorganize(char**,char**,int ,int);

int main(int argc,char* argv[]){
	srand(time(0));
	char resp='s';
	while(resp=='s'||resp=='S'){
		int palabrasA,palabrasB;
		cout<<"Ingrese cuantas palabras desea ingresar a la columna A: ";
		cin>>palabrasA;
		cout<<"Ingrese cuantas palabras desea ingresar a la columna B: ";
		cin>>palabrasB;
		char** columnaA=new char*[palabrasA];
		char** columnaB=new char*[palabrasB];
		char palabra[80];
		
		cout<<"Palabras columna A: "<<endl;
		for (int i = 0; i < palabrasA; ++i)
		{
			cout<<"Ingrese la palabra "<<i+1 <<". para la columna A: ";
			cin>>palabra;
			columnaA[i]=new char[strlen(palabra)+1];
			strcpy(columnaA[i],palabra);
		}
		cout<<"Palabras columna B: "<<endl;
		for (int i = 0; i < palabrasB; ++i)
		{
			cout<<"Ingrese la palabra "<<i+1 <<". para la columna B: ";
			cin>>palabra;
			columnaB[i]=new char[strlen(palabra)+1];
			strcpy(columnaB[i],palabra);
		}

		Juego(columnaA,columnaB,palabrasA,palabrasB);

		for (int i = 0; i < palabrasA; ++i)
		{
			delete columnaA[i];
		}
		delete[] columnaA;
		for (int i = 0; i < palabrasB; ++i)
		{
			delete columnaB[i];
		}
		delete[] columnaB;
		cout<<"Desea volver a ingresar?(s/n): ";
		cin>>resp;
	}
	return 0;
}
void Reorganize(char** columnaA,char** columnaB,int palabrasA,int palabrasB){
	int random;
	int arregloA[palabrasA],arregloB[palabrasB];
	for (int i = 0; i < palabrasA; ++i)
	{
		arregloA[i]=i+1;
	}
	for (int i = 0; i < palabrasB; ++i)
	{
		arregloB[i]=i+1;
	}
	
	char* tempA;
	char* tempB;		
	int tempAnum,tempBnum;
	
	for (int j= 0; j < palabrasA; ++j)
	{
		if(arregloA[j]<arregloA[j+1]&&j+1<palabrasA){
			tempAnum=arregloA[j];
			arregloA[j]=arregloA[j+1];
			arregloA[j+1]=tempAnum;
			tempA=new char[strlen(columnaA[j])];
			strcpy(tempA,columnaA[j]);
			strcpy(columnaA[j],columnaA[j+1]);
			strcpy(columnaA[j+1],tempA);
			delete[] tempA;
		}
	}
		

	for (int j= 0; j < palabrasB; ++j)
	{
		if(arregloB[j]<arregloB[j+1]&&j+1<palabrasB-1){
			tempBnum=arregloB[j];
			arregloB[j]=arregloB[j+1];
			arregloB[j+1]=tempBnum;
			tempB=new char[strlen(columnaB[j])];
			strcpy(tempB,columnaB[j]);
			strcpy(columnaB[j],columnaB[j+1]);
			strcpy(columnaB[j+1],tempB);
			delete[] tempB;
		}
	}
	
	
}

void Juego(char** columnaA,char** columnaB,int palabrasA,int palabrasB){
	int matchA,matchB;
		cout<<"Lista de las palabras Columna A: "<<endl;
		for (int i = 0; i < palabrasA; ++i)
		{
			cout<<i+1<<". "<<columnaA[i]<<endl;
		}
		cout<<endl<<"Lista de las palabras Columna B: "<<endl;
		for (int i = 0; i < palabrasB; ++i)
		{
			cout<<i+1<<". "<<columnaB[i]<<endl;
		}

	cout<<endl<<"Ingrese las palabras que quiere match entre la columna A y la columna B: "<<endl;
	
	
	int cont=0;
	int contcomb=0;
	char resp='s';
	int combinaciones[80];
	while(resp=='s'||resp=='S'&&contcomb<40){
		cont++;
		cout<<"Palabra de la columna A: ";
		cin>>matchA;
		while(matchA<1||matchA>palabrasA){
			cout<<"Esa palabra no esta en la columna A\nPalabra de la columna A: ";
			cin>>matchA;
		}
		cout<<"Palabra de la columna B: ";
		cin>>matchB;
		while(matchB<1||matchB>palabrasB){
			cout<<"Esa palabra no esta en la columna B\nPalabra de la columna B: ";
			cin>>matchB;
		}
		matchA-=1;
		matchB-=1;
		combinaciones[contcomb]=matchA;
		combinaciones[contcomb+1]=matchB;
		cout<<"Desea ingresar otra combinacion?(S/N): ";
		cin>>resp;
		contcomb+=2;
	}
	char** matcharray=new char*[cont];
	int contadorwhile=0;
	int contadorcolumna=0;
	while(contadorwhile<cont){
		int nummatchA=0;
		char match[(strlen(columnaA[combinaciones[contadorcolumna]])+strlen(columnaB[combinaciones[contadorcolumna+1]]))+1];
		
		for (int i = 0; i < strlen(match); ++i)
		{
			match[i]=' ';
		}
		
		cout<<endl;
		
		for (int k = 0; k < strlen(columnaA[combinaciones[contadorcolumna]]); ++k)
		{						
			match[nummatchA]=columnaA[combinaciones[contadorcolumna]][k];
			nummatchA++;						
		}
		match[nummatchA]=',';
		int nummatchB=nummatchA+1;
		for (int m = 0; m < strlen(columnaB[combinaciones[contadorcolumna+1]]); ++m)
		{						
			match[nummatchB]=columnaB[combinaciones[contadorcolumna+1]][m];
			nummatchB++;
		}
		matcharray[contadorwhile]=new char[strlen(match)+1];
		strcpy(matcharray[contadorwhile],match);
		contadorwhile++;
		contadorcolumna+=2;
	}
	
	Reorganize(columnaA,columnaB,palabrasA,palabrasB);
	Matching(columnaA,columnaB,matcharray,palabrasA,palabrasB,cont);
	
		
	for (int i = 0; i < cont; ++i)
	{
		delete matcharray[i];
	}
	delete[] matcharray;
}
void Matching(char** columnaA,char** columnaB,char** matcharray,int palabrasA,int palabrasB,int size){
	cout<<"Matching"<<endl;
	int matchA,matchB;
	cout<<"Lista de las palabras Columna A: "<<endl;
	for (int i = 0; i < palabrasA; ++i)
	{
		cout<<i+1<<". "<<columnaA[i]<<endl;
	}
	cout<<endl<<"Lista de las palabras Columna B: "<<endl;
	for (int i = 0; i < palabrasB; ++i)
	{
		cout<<i+1<<". "<<columnaB[i]<<endl;
	}
	char resp='s';
	double correcto=0.0,fail=0.0,contresp=0.0;
	while(resp=='s'||resp=='S'){
		int* posicioncoma;
		int contpalabra=0;
		int* posicionpalabras;
		bool correct=false;
		contresp++;
		cout<<"Elija la palabra de la columna A: ";
		cin>>matchA;
		cout<<"Elija la palabra de la columna B: ";
		cin>>matchB;
		matchA-=1;
		matchB-=1;
		for (int i = 0; i < size; ++i)
		{
			int contletras=0;
			for (int j = 0; j < strlen(columnaA[matchA]); ++j)
			{
				if(matcharray[i][j]==columnaA[matchA][j]&&columnaA[matchA][j]!=' '){
					contletras++;
				}
			}
			if(contletras==strlen(columnaA[matchA])){
				contpalabra++;
			}
		}		
		posicionpalabras=new int[contpalabra];
		posicioncoma=new int[contpalabra];
		for (int k = 0; k < contpalabra; ++k)
		{
			for (int i = 0; i < size; ++i)
			{
				int valorj=0;
				int contletras=0;
				for (int j = 0; j < strlen(columnaA[matchA]); ++j)
				{
					if(matcharray[i][j]==columnaA[matchA][j]&&columnaA[matchA][j]!=' '){
						contletras++;
						valorj++;
					}					
				}

				if(contletras==strlen(columnaA[matchA])){
					posicionpalabras[k]=i;
					posicioncoma[k]=valorj;
				}
			}
		}
		for (int i = 0; i < contpalabra; ++i)
		{
			int contcolumnaB=0,contadorletra=0;
			for (int j = 0; j < strlen(matcharray[posicionpalabras[i]]); ++j)
			{
				if(j>posicioncoma[i]){
					if(matcharray[posicionpalabras[i]][j]==columnaB[matchB][contcolumnaB]&&columnaB[matchB][contcolumnaB]!=' '){
						contadorletra++;
					}
					contcolumnaB++;
				}
			}
			if (contadorletra==strlen(columnaB[matchB]))
			{
				correct=true;
			}
			if (correct==true)
			{
				
				break;
			}
		}
		if(correct==true){
			cout<<"El match si existe!!"<<endl;
			correcto++;
		}else{
			cout<<"El match No existe :("<<endl;
			fail++;
		}
		delete[] posicionpalabras;
		delete[] posicioncoma;
		cout<<"Desea ingresar otro match?(s/n): ";
		cin>>resp;
	}
	cout<<"final"<<endl;
	double porcentaje=0.0;
	porcentaje+=(contresp/100.0);
	porcentaje=correcto/porcentaje;
	cout<<"Su porcentaje de correctas fue de: "<<porcentaje<<"% con "<<(int)correcto<<" matches correctas y "<<fail<<" incorrectas."<<endl;
}
