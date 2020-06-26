// Programa NBA
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string.h>
#define MAX_EQ 4 //cantidad maxima de equipos la puedes modificar a gusto cadda equipo tiene 12 jugadores
#define MAX_CAD 40 // lo mas largo que puede ser la cadena de caracteres para guardar la info

using namespace std;

/*struct jugador{
char nombre_jugador[MAX_CAD];
int peso;
int edad;
int ranking;
}jugadores[12];*/
int maxrank = 4 * 12;
int rankings [MAX_EQ * 12]; //creamos el ranking 
struct equipo{ // toda la informacion que vas a guardad de cada equipo
 unsigned long clave_registro; 
 string nombre_equipo;
 struct jugador{
string nombre_jugador;
int peso;
int edad;
int ranking;
}info_jugador[12];
   // unsigned long guarda 32 bits le caben 10 digitos 
}equipos[MAX_EQ];

//funciones:
int menu(); 
void mostrardatos();
bool searchrank(int);
void pdpe();
void archivoteranking(int );

int main(){
  for(int i=0; i<(MAX_EQ * 12); i++){
    rankings[i] = 0;
  }
int opcion; 
bool ranks;
int count = 0; //LLeva la cuenta del ranking
cout<<"--------------programa iniciado---------------"<<endl; 
srand(time(NULL));  

for(int i=0;i<MAX_EQ;i++){
  equipos[i].clave_registro=10000000+rand()%(99999999-10000000);//genera numero aleatorio de registro
  equipos[i].nombre_equipo = "Nombre " ;//esto ahorita solo guarda el numero tiene que guardar un nombre aleatorio asi que hay que arreglar eso 
  for(int j=0;j<12;j++){
 equipos[i].info_jugador[j].nombre_jugador = "jugador" ;//igual aqui tiene que ir un nombre aleatorio ahorita es solo para poder avanzar
 equipos[i].info_jugador[j].peso=65+rand()%(111-65);//peso aleatorio
 equipos[i].info_jugador[j].edad=21+rand()%(37-21);//edad aleatoria
 do{
  equipos[i].info_jugador[j].ranking=65+rand()%(114-65);
  ranks = searchrank(equipos[i].info_jugador[j].ranking); //Checamos si el rank no se ha repetido
  }while(ranks == false);
  rankings[count] = equipos[i].info_jugador[j].ranking;
  count++;//no se debe repetir el ranking en ningun jugador de toda la liga( yo creo que con un vector y hacer random shuffle
  //todos los nombre que no se repiten y el ranking van a nececitar 3 vectores con nombres aleatorios, creo que lo mas facil para los nombres de jugadores
  //es hacer 1 vector con 15 nombres y 15 apellidos y que se mezclen aleatoriamente sin repetirse.
} 
}
  
do{
    system("cls");// limpia la pantalla para volver a imprimir el menu 
    opcion=menu();// en automatico agarra como el primer caso al menu y lo selecciona como la primer funcion a llamar en menu da la opcion de seleccionar el caso y regresa a main
    fflush(stdin);// limpia el espacio para que exista basura de algo mas
    switch(opcion)// una vez dado el valor de opcion en la funcion menu toma en caso seleccionado y llama a la funcion respectiva 
     {
       case 1: mostrardatos();
               break;
       case 2: pdpe();
               break;
       case 3: 
     break;
       case 4: archivoteranking(count);
               break;
       case 5: 
     break;
       case 6: 
               break;
    case 7:
               break;
       case 8: 
               break;
       case 9: 
     break;
       case 10: 
               break;
       case 11: // acaba con el do-while
               break;
       default: cout<<"Opcion no valida"<<endl;
     }
    getch();  
  }while(opcion!=11); 
  
  
return 0;
}


int menu()// imprime la opciones de los casos para llamar funciones 
{
  int opcion;
  cout<<"1- IMPRIMIR TODO "<<endl;
  cout<<"2- IMPRIMIR PESO Y EEDAD PROMEDIO DE LOS EQUIPOS "<<endl;
  cout<<"3- IMPRIMIR PESO Y EEDAD PROMEDIO DE LOS JUGADORES "<<endl;
  cout<<"4- GUARDAR EN ARCHIVO DE TEXTO POR RANKING "<<endl;
  cout<<"5- LEER ARCHIVO DE TEXTO DATOS DE EQUIPO DADO "<<endl;
  cout<<"6- IMPRIMIR MEJOR JUGADOR DE UN EQUIPO DADO "<<endl;
  cout<<"7- GUARDAR EN ARCHIVO BINARIO NOMBRE Y EDAD DE JUGADORES "<<endl;
  cout<<"8- LEER ARCHIVO BINARIO CON NOMBRE Y EDAD DE JUGADORES "<<endl;
  cout<<"9- TOP 10 JUGADDORES "<<endl;
  cout<<"10- LISTA ENLAZADA DE EQUIPO"<<endl;
  cout<<"11- SALIR DEL PROGRAMA"<<endl;
  cin>>opcion;
  
  return opcion; //regresa en numero del caso 
}
//Esta funcion se encargará de imprimir en consola los datos de todos los equipos y jugadores
void mostrardatos(){
  system("cls");
  for(int i=0; i<MAX_EQ;i++){
    cout<<"Equipo: "<<equipos[i].nombre_equipo<<endl;
    cout<<"Clave de registro: "<<equipos[i].clave_registro<<endl;
    cout<<"Jugadores: "<<endl;
    for(int j=0; j<12; j++){
       cout<<"Nombre: "<<equipos[i].info_jugador[j].nombre_jugador<<endl;
       cout<<"Peso: "<<equipos[i].info_jugador[j].peso<<endl;
       cout<<"Edad: "<<equipos[i].info_jugador[j].edad<<endl;
       cout<<"Ranking: "<<equipos[i].info_jugador[j].ranking<<endl;
    }
    system("pause");
    cout<<"\n"<<endl; //Salto de linea
  }
}

bool searchrank(int y){
  for(int i=0; i<maxrank; i++){
    if(rankings[i] == y){
      return false;
    }
  }
  return true;
}
//La función va a calcular el peso y edad promedio de los equipos en pantalla
void pdpe(){
  system("cls");
  int peso_general=0, edad_general=0, peso_temp=0, edad_temp=0; //Creamos variables para guardar el peso medio de cada equipo y después sacar uno general
  for(int i = 0; i<MAX_EQ; i++){
    cout<<"Equipo: "<<equipos[i].nombre_equipo <<endl;
    peso_temp = 0;
    edad_temp = 0;
    for(int j = 0; j<12; j++){
      //Le sumamos a las variables temporales el peso y edad de cada jugador
      peso_temp += equipos[i].info_jugador[j].peso;
      edad_temp += equipos[i].info_jugador[j].edad;
    }
    //Agregamos las medeias a la general
    peso_general += peso_temp/12;
    edad_general += edad_temp/12;
    cout<<"Peso promedio del equipo: "<<peso_temp/12<<endl;
    cout<<"Edad promedio del equipo: "<<edad_temp/12<<endl;
    system("pause");
  }
  system("cls");
  cout<<"Peso promedio de la liga: "<<peso_general/MAX_EQ<<endl;
  cout<<"Edad promedio de la liga: "<<edad_general/MAX_EQ<<endl;
  system("pause");
}
//Función para crear el archvio de texto
void archivoteranking(int count){
  ofstream archvio_ranking;
  archvio_ranking.open("Ranking.txt", ios::out);
  //Comprobamos que el archivo no de error al crearse
  if(archvio_ranking.fail()){
    cout<<"No se pudo abrir el archivo"<<endl;
    system("pause");
    return;
  }
  //Ordenamos el ranking con el método de la burbuja
  for(int i=0;i<count;i++){
    for(int j = i+1;j<count;j++){
      if(rankings[i] > rankings[j]){
        int aux = rankings[i];
        rankings[i] = rankings[j];
        rankings[j] = aux;
      }
    }
  }

  for(int i = 0; i<count; i++){
    for(int j = 0; j<MAX_EQ;j++){
      for(int k = 0; k<12; k++){
        if(rankings[i] == equipos[j].info_jugador[k].ranking){
          archvio_ranking<<equipos[j].info_jugador[k].ranking<<" ";
          archvio_ranking<<equipos[j].info_jugador[k].nombre_jugador<<" ";
          archvio_ranking<<equipos[j].info_jugador[k].peso<<" ";
          archvio_ranking<<equipos[j].info_jugador[k].edad<<"\n"<<endl;
          j = MAX_EQ;
          break;
        }
      }
    }
  }

  archvio_ranking.close();
}