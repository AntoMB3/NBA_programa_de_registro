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
struct equipo *next;
}equipos[MAX_EQ]; 
equipo *teams;
equipo *list = NULL, *primero = NULL;

//funciones:
int menu(); 
void mostrardatos();
bool searchrank(int);
void pdpe();
void archivoteranking(int );
void creararchivoporequipo();
void showteamfile();
void bestplayer();
void topten(int );
void lista(int);
equipo *crearnodo(int);
void printlist();
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
  cout<<"Ingresa el nombre del equipo"<<endl;
  fflush(stdin);
  getline(cin,equipos[i].nombre_equipo);
  fflush(stdin);//esto ahorita solo guarda el numero tiene que guardar un nombre aleatorio asi que hay que arreglar eso 
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
       case 5: creararchivoporequipo();
       showteamfile();
     break;
       case 6: bestplayer();
               break;
    case 7:
               break;
       case 8: 
               break;
       case 9: topten(count);
     break;
       case 10: cout<<"Que equipo quieres ver?"<<endl;
       int z;
       cin>>z;
       lista(z);
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
/*Recorremos el arreglo ordenado del ranking para tener los mejores hasta arriba, luego buscamos en todos los equipos
  el jugador que tenga el mismo ranking y agregamos sus datos al archvio, después rompemos el ciclo para buscar a ese jugador
  y vovlemos a comenzar con el segundo pueso del ranking */
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
//Una función para crear archivos de texto de cada equipo
void creararchivoporequipo(){
ofstream file;
string temp;
for(int i=0; i<MAX_EQ; i++){
  temp = equipos[i].nombre_equipo + ".txt";
  file.open(temp.c_str(),ios::out);
  if(file.fail()){
    cout<<"No se pudo abrir el archivo"<<endl;
    system("pause");
    return;
  }
  file<<"Nombre del equipo: "<<equipos[i].nombre_equipo<<endl;
  file<<"Jugadores: \n"<<endl;
  for(int j=0; j<12; j++){
    file<<equipos[i].info_jugador[j].ranking<<" ";
    file<<equipos[i].info_jugador[j].nombre_jugador<<" ";
    file<<equipos[i].info_jugador[j].peso<<" ";
    file<<equipos[i].info_jugador[j].edad<<"\n"<<endl;
  }
  file.close();
}
}
/*La función en base a un nombre dado, busca el archvio de texto correspondiente y muestra sus datos en pantalla */
void showteamfile(){
  string team_temp, team_info;
  int temp;
  
  bool exist = false;
  //Se repite el ciclo mientras el equipo no se encuentre
  do{
    //Obtenemos el equipo a buscar información
  cout<<"Que equipo deseas consultar"<<endl;
  fflush(stdin);
  getline(cin,team_temp);
  fflush(stdin);
    for(int i=0; i<MAX_EQ; i++){
      if(equipos[i].nombre_equipo == team_temp){
        exist = true;
        temp = i;
      }
    }
    if(exist==false){
      cout<<"El equipo no se encuentra"<<endl;
    }

  }while(exist == false);
  system("cls");
  //Abrimos el archivo de lectura
  ifstream file;
  team_temp += ".txt";
  file.open(team_temp.c_str(),ios::in);
  if(file.fail()){
    cout<<"ERROR: El archivo no se pudo abrir"<<endl;
    system("pause");
    return;
  }
  //Mostramos cada linea del archivo mientras no sea el final del mismo
  while(!file.eof()){
    getline(file,team_info);
    cout<<team_info<<endl;
  }
  file.close();
  system("pause");
}
//Esta funcion va a obtener la informacion del mejor jugador del equipo elegido
void bestplayer(){
  string team_temp;
  int temp, temp2;
  bool exist = false;
  //Volvemos a aplciar la de la anterior, de buscar si existe o no el equipo
  do{
  cout<<"De que equipo deseas consultar"<<endl;
  fflush(stdin);
  getline(cin,team_temp);
  fflush(stdin);
  for(int i=0; i<MAX_EQ; i++){
      if(equipos[i].nombre_equipo == team_temp){
        exist = true;
        temp = i;
      }
    }
    if(exist==false){
      cout<<"El equipo no se encuentra"<<endl;
    }
  }while(exist == false);
  system("cls");
  //Comparamos el ranking de cada uno de los jugadores para obtener el mejor
  int mejor = equipos[temp].info_jugador[0].ranking;
  temp2 = 0;
  for(int i =1; i<12;i++){
    if(equipos[temp].info_jugador[i].ranking < mejor){
      mejor = equipos[temp].info_jugador[i].ranking;
      temp2 = i;
    }
  }
  cout<<"El mejor jugador del equipo es: "<<equipos[temp].info_jugador[temp2].nombre_jugador<<endl;
  cout<<"Peso: "<< equipos[temp].info_jugador[temp2].peso<<endl;
  cout<<"Edad: "<< equipos[temp].info_jugador[temp2].edad<<endl;
  system("pause");

}
//La funcion va a imprimir los mejores 10 jugadores de la liga
//aplicamos el mismo procediemiento que la funcion donde guardamos el ranking en un archivo
void topten(int count){
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
  cout<<"Top 10 jugadores de la liga"<<endl;
  for(int i = 0; i<10; i++){
    for(int j = 0; j<MAX_EQ;j++){
      for(int k = 0; k<12; k++){
        if(rankings[i] == equipos[j].info_jugador[k].ranking){
          cout<<equipos[j].info_jugador[k].ranking<<" ";
          cout<<equipos[j].info_jugador[k].nombre_jugador<<" ";
          cout<<equipos[j].info_jugador[k].peso<<" ";
          cout<<equipos[j].info_jugador[k].edad<<"\n"<<endl;
          j = MAX_EQ;
          break;
          system("pause");
        }
      }
    }
  }
}
//Funcion para crear la lista enlazada con la informacion de los jugadoras
void lista(int x){
  equipo *s = crearnodo(x);
  if(list == NULL){
    list = primero = s;
  }
  else{
    list->next = s;
    list = s;
  }
  printlist();
}

equipo *crearnodo(int y){
  teams = new equipo;
  teams->nombre_equipo = equipos[y].nombre_equipo;
  for (int i= 0; i<12;i++){
    teams->info_jugador[i].nombre_jugador = equipos[y].info_jugador[i].nombre_jugador;
    teams->info_jugador[i].peso = equipos[y].info_jugador[i].peso;
    teams->info_jugador[i].edad = equipos[y].info_jugador[i].edad;
    teams->info_jugador[i].ranking = equipos[y].info_jugador[i].ranking;
}
      teams-> next = NULL;
      return teams;
}
void printlist(){
  list = primero;
  do{
    cout<<"Equipo: "<<list->nombre_equipo<<endl;
    cout<<"Jugadores :"<<endl;
    for(int i = 0; i <12; i++)
    {
      cout<<"Nombre: "<<list->info_jugador[i].nombre_jugador<<endl;
      cout<<"Edad: "<<list->info_jugador[i].edad<<endl;
      cout<<"Peso: "<<list->info_jugador[i].peso<<endl;
      cout<<"Ranking: "<<list->info_jugador[i].ranking<<endl;
    }
    list = list->next;

  }while(list != NULL);
  system("pause");
}