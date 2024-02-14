#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>
#include "Usuario.h"
#include "Profesionales.h"

typedef struct Nodo{
	NuevoProfesional profesionalNodo;
	Nodo *next;
	
}Nodo;

typedef struct Nodo1{
	user recepcionistaNodo;
	Nodo1 *next;
	
}Nodo1;

Nodo *top = NULL;
Nodo1 *topR = NULL;

static bool tieneDosCaracteresSeguidos(char cadena[]);
static bool numerosConsecutivos(const char *contrasena, int *i,int *contadorNumeros);
static void insertarRecepcionista(user usuarios[], int);
static int insertarProfesional(NuevoProfesional profesional[],int);
static int generarId();
static void liberarMemoriaListaRecep(Nodo1 *topR);
static void push(NuevoProfesional profesional);
static void pushRecepcionista(user recepcionista);
static void escribirEnArchivo(FILE *file, Nodo *nodo);
static void escribirEnArchivoRecepcionista(FILE *file, Nodo1 *nodo);
static void liberarMemoriaLista(Nodo *top);
static void imprimirLista(Nodo1 *topR);

char *usuarioActual = (char*)malloc(80 * sizeof(char));
char *contrasenaActual = (char*)malloc(80 * sizeof(char));


int verificarExistenciaUsuarioProfesional(char usuario[80],char contrasena[80]){
	
	int existe = 0;// si no hay usuarios es igual a 0
	NuevoProfesional profesional;
	
	FILE *file = fopen("Profesionales.dat","rb");
	
	if(file == NULL){
		perror("\n\t\tERROR, al abrir el archivo:");
		exit(1);
	}
	
	fread(&profesional, sizeof(NuevoProfesional),1,file);
	
	//lo recoreremos al archivo hasta que finalize o hasta que se encuentre el usuario
	while(!feof(file)){
		//en el caso de que ambas cadenas de texto sean iguales la funcion strcmp devlvera 0 por eso lo comparamos de esta manera
		//(0 == 0) existe
		if(strcmp(profesional.profesionalData.usuario,usuario) == 0 && strcmp(profesional.profesionalData.contrasena,contrasena) == 0){
			strcpy(usuarioActual,usuario);//esta dos lineas son para la script profecional
			strcpy(contrasenaActual,contrasena);
			existe = 1;// para profesional
			
			break;
		}
		fread(&profesional, sizeof(NuevoProfesional),1,file);
	}
	/*
	if(existe == 0){
		existe = verificarExistenciaUsuarioRecepcionista(usuario,contrasena);
	}
	*/
	fclose(file);
	
	return existe;
}

int verificarExistenciaUsuarioRecepcionista(char usuario[80],char contrasena[80]){
	
	int existe = 0;// si no hay usuarios es igual a 0
	user nuevo_user;
	
	FILE *file = fopen("Recepcionistas.dat","rb");
	
	if(file == NULL){
		perror("\n\t\tERROR, al abrir el archivo:");
		exit(1);
	}
	
	fread(&nuevo_user, sizeof(user),1,file);
	
	//lo recoreremos al archivo hasta que finalize o hasta que se encuentre el usuario
	while(!feof(file)){
		//en el caso de que ambas cadenas de texto sean iguales la funcion strcmp devlvera 0 por eso lo comparamos de esta manera
		//(0 == 0) existe
		if(strcmp(nuevo_user.usuario,usuario) == 0 && strcmp(nuevo_user.contrasena,contrasena) == 0){
			existe = 2;// para recepcionista
			break;
		}
		fread(&nuevo_user, sizeof(user),1,file);
	}
/*	
	if(existe == 0){
		existe = verificarExistenciaUsuarioAdmin(usuario,contrasena);
	}
*/	
	fclose(file);
	return existe;
}

int verificarExistenciaUsuarioAdmin(char usuario[80],char contrasena[80]){
	
	int existe = 0;// si no hay usuarios es igual a 0
	user nuevo_user;
	
	FILE *file = fopen("Admin.dat","rb");
	
	if(file == NULL){
		perror("\n\t\tERROR, al abrir el archivo:");
		exit(1);
	}
	
	fread(&nuevo_user, sizeof(user),1,file);
	
	//lo recoreremos al archivo hasta que finalize o hasta que se encuentre el usuario
	while(!feof(file)){
		//en el caso de que ambas cadenas de texto sean iguales la funcion strcmp devlvera 0 por eso lo comparamos de esta manera
		//(0 == 0) existe
		if(strcmp(nuevo_user.usuario,usuario) == 0 && strcmp(nuevo_user.contrasena,contrasena) == 0){
			existe = 3;// para recepcionista
			break;
		}
		fread(&nuevo_user, sizeof(user),1,file);
	}
	
	fclose(file);
	
	return existe;
}

void crearProfesional(){	
	system("cls");
	
	NuevoProfesional profesional[25],prof;
	char apelldioNombre[80],usuario[80];
	int tamanoNombre,i,ind = 0,contadorMayusculas = 0,contadorMinuscula = 0,contadorNumeros = 0,verificarMayuscula,verificarMinuscula,verificarNumero,verificarEspacios,verificarAlfanumericos;
	bool usuarioValido = false, otroProfesional = false;
	
	FILE* arch = fopen("Profesionales.dat","rb");
	fread(&prof,sizeof(NuevoProfesional),1,arch);
	
	while(!feof(arch)){
		printf("\t\tNombre: %s, id: %d, Dni: %i area: %s\n", prof.apelldioNombre,prof.idProfesional,prof.dniProfesional,prof.areaProfesional);
		fread(&prof,sizeof(NuevoProfesional),1,arch);	
	}
	fclose(arch);

	
	do{
		
		fflush(stdin);
		printf("\n\t\tNombre y apellido del Profesional:");
		scanf("%[^\n]",&apelldioNombre);
		fflush(stdin);
	
		strcpy(profesional[ind].apelldioNombre, apelldioNombre);
		strcpy(profesional[ind].profesionalData.nombreApellido, apelldioNombre);
		
		do{
			printf("\n\t\t  Requerimientos");
			printf("\n\t\t1-El nomrbre de usuario, su primera letra debe comenzar en minusculas.");
			printf("\n\t\t2-Debe poseer por lo menos 2 mayusculas.");
			printf("\n\t\t3-Solo puede tener como maximo 3 digitos numericos.");
			printf("\n\t\t4-Solo puede tener minimo 6 caracteres y maximo 10.");
			printf("\n\t\t!!!!!Recuerde y leea bien para no equivocarse!!!!!");
		
			fflush(stdin);
			printf("\n\n\t\tNombre de usuario Profesional:");
			scanf("%[^\n]",&usuario);
			fflush(stdin);
		
			strcpy(profesional[ind].profesionalData.usuario,usuario);
			
			tamanoNombre = strlen(profesional[ind].profesionalData.usuario);
			//esto nos ayuda mucho a optimizar el ultimo if que servia de verificacion de validez del nombre de usuario 
			if(tamanoNombre < 6 || tamanoNombre > 10){
				puts("\n\t\tNo cumple con el 4 requerimiento, PRESIONE UNA TECLA.");
				getch();
				system("cls");
				continue;
			}
	
			for(i = 0; i < tamanoNombre; i++){
		
				verificarMayuscula = isupper(profesional[ind].profesionalData.usuario[i]);
				verificarNumero = isdigit(profesional[ind].profesionalData.usuario[i]);
		
				if(verificarMayuscula != 0){// si es != 0 significa que es una letra en mayuscula
					contadorMayusculas++;
				}else{
					contadorMinuscula++;
				}
			
				if(verificarNumero != 0){//Valor distinto de cero si el carácter es un carácter numérico; cero en caso contrario.

					contadorNumeros++;
				}
				
			}
			
			int auxiliar = isupper(profesional[ind].profesionalData.usuario[0]);// auxiliar == 0 significa q es minuscula, hacemos esto por que la primera letra del usuario tiene que ser si o si en minusculas
			
			//con este if verificamos todos los requerimientos que debe tener el nombre del usuario
			if( (contadorMayusculas >= 2 && contadorNumeros <= 3) && auxiliar == 0 ){
				usuarioValido = true;// si nombreValido es igual a true el do-while se rompe y se puede continuar caso contrario a volver a ingresar los datos
			}else{
				printf("\n\t\tEl Usuario es invalido.\n");
			//	printf("\n\t\tContadorMinuscula: %d, contadorMayusculas: %d, contadorNumeros: %d, tamano : %d\n", contadorMinuscula,contadorMayusculas,contadorNumeros,tamanoNombre);	
				contadorMayusculas = 0;
				contadorMinuscula = 0;
				contadorNumeros = 0;
				auxiliar = 0;
				getch();
				fflush(stdin);
				system("cls");
			}
		
		
		}while(usuarioValido == false);	

		/*	
		1- Una mayuscula, una minuscula, un numero minimo.
		2- Ningun caracter de puntuacion (ej: ,;.:') ni escpacios solo caracteres alfanumericos.
		3- Debe tener entre 6 a 32 caracteres.
		4- No puede tener mas de 3 caracteres numericos consecutivos.
		5- No puede tener 2 caracteres que esten seguidos alfabeticamente y es aplicable tanto a las mayusculas como a las minusculas
		*/
		
		int tamanoContrasena = 0; 
		i = 0;
		contadorMayusculas = 0;
		contadorMinuscula = 0;
		contadorNumeros = 0;
		verificarEspacios = 0;
		verificarAlfanumericos = 0;
		verificarMayuscula = 0;
		verificarNumero = 0;
		bool contrasenaValida = false, letrasSeguidas = false,numerosSeguidos = false;
		
		do	{
			letrasSeguidas = false;
			numerosSeguidos = false;
			int tamanoContrasena = 0; 
			i = 0;
			contadorMayusculas = 0;
			contadorMinuscula = 0;
			contadorNumeros = 0;
			verificarEspacios = 0;
			verificarAlfanumericos = 0;
			verificarMayuscula = 0;
			verificarNumero = 0;
			
			char contrasena[80];
			
			system("cls");
			fflush(stdin);
			printf("\n\n\t\t    Requerimientos");
			printf("\n\t\t1- Como minimo la contrasena debe poseer una mayuscula, una minuscula y un numero.");
			printf("\n\t\t2- Ningun caracter de puntuacion o especial (ej: ,;.:?¿!#') ni escpacios solo caracteres alfanumericos.");
			printf("\n\t\t3- No puede tener mas de 3 caracteres numericos consecutivos");
			printf("\n\t\t4- Solo puede tener minimo 6 caracteres y maximo 32.");
			printf("\n\t\t5- No puede tener 2 caracteres que esten seguidos alfabeticamente y es aplicable tanto a las mayusculas como a las minusculas.\n");
			printf("\n\t\t!!!!!Recuerde y leea bien para no equivocarse!!!!!");
			
			fflush(stdin);
			printf("\n\n\t\tIngrese la contrasena deseada:");
			scanf("%[^\n]",&contrasena);
			fflush(stdin);
			tamanoContrasena = strlen(contrasena);
			
			strcpy(profesional[ind].profesionalData.contrasena,contrasena);
		
			for(i = 0; i < tamanoContrasena; i++){
				
				verificarMayuscula = isupper(profesional[ind].profesionalData.contrasena[i]);
				verificarNumero = isdigit(profesional[ind].profesionalData.contrasena[i]);
				verificarEspacios = isspace(profesional[ind].profesionalData.contrasena[i]);
				verificarAlfanumericos = isalnum(profesional[ind].profesionalData.contrasena[i]);
				
				if(tamanoContrasena < 6 || tamanoContrasena > 32){
					puts("\n\t\tLa contrasena ingresada no cumple con el 3 requerimiento, PRESIONE UNA TECLA.");
					getch();
					system("cls");
					break;
				}
		
			
				numerosSeguidos = numerosConsecutivos(profesional[ind].profesionalData.contrasena,&i,&contadorNumeros);
			
				if(numerosSeguidos == true){
					puts("\n\t\tLa contrasena ingresada posee mas de 3 numeros consecutivos, intente de nuevo.\n");
					getch();
					numerosSeguidos = false;
					system("cls");
					break;
				}
			

				if(verificarEspacios != 0){//Valor distinto de cero si el carácter es un carácter de espacio en blanco; cero en caso contrario.
					puts("\n\t\tLa contrasena ingresada posee espacios, intente de nuevo.\n");
					getchar();
					system("cls");
					break;
				}
			
				// esto es para que el usuario no ingrese caracteres raros como ,;.:?¿ etc.
				if(verificarAlfanumericos == 0){
					puts("\n\t\tLa contrasena ingresada posee caracteres no aceptables, intente de nuev o    .\n");
					getch();
					system("cls");
					break;
				}
			
				letrasSeguidas = tieneDosCaracteresSeguidos(profesional[ind].profesionalData.contrasena);
			
				if(letrasSeguidas == true){
					printf("\n\t\tLa contrasena posee dos letras alfabeticamente seguidas.\n");
					getch();
					break;
				}
			
				if(verificarMayuscula != 0){
					contadorMayusculas++;
				}else{
					contadorMinuscula++;
				}
							
			}
		
			//if final con el cual se verificara si la contraseña es valida o no
			if( contadorMayusculas > 0 && contadorMinuscula > 0 && contadorNumeros > 0) {
				contrasenaValida = true;
			}else{
				//printf("\n\t\tContadorMinuscula: %d, contadorMayusculas: %d, contadorNumeros: %d\n", contadorMinuscula,contadorMayusculas,contadorNumeros);
				getch();
				fflush(stdin);
				system("cls");
			}
		
		}while(contrasenaValida == false);	
	
		system("cls");

		if( verificarExistenciaUsuarioProfesional(profesional[ind].profesionalData.usuario , profesional[ind].profesionalData.contrasena) == 1){// significa que  ya hay un usuario registrado con ese usuario y contraseña
			printf("\n\t\tYa se encuentra registrado un usuario Profesional con esa misma contrasena y usuario.\n");
			getch();
			crearProfesional();
		}
	
	/*
	Datos que faltan registrar
	
	int idProfesional;
	int dniProfesional;
	int telefono;
	char areaProfesional
	
	*/

		printf("\n\t\tIngrese el dni del profesional: ");
		scanf("%d",&profesional[ind].dniProfesional);	
		
		printf("\n\t\tIngrese el telefono del profesional: ");
		scanf("%d",&profesional[ind].telefono);
	
		int opcion;
	
		bool bandera = false;
	
		do{
		
			printf("\n\t\tAreas posibles a elegir ");
			printf("\n\t\t1- Ginecologia.");
			printf("\n\t\t2- Traumatologia.");
			printf("\n\t\tOpcion:");
			scanf("%i", &opcion);

			switch(opcion){
				case 1:
					strcpy(profesional[ind].areaProfesional,"Ginecologia");
					bandera = true;
					break;
				case 2:
					strcpy(profesional[ind].areaProfesional,"Traumatologia");
					bandera = true;
					break;
				default:
					puts("\n\t\tLa opcion ingresada no existe, intente de nuevo.\n");
			}
    	}while(!bandera);// bandera != true; es equivalente
    
    	int eleccion;
    	printf("\n\t\tDesea agregar otro profesional?");
    	printf("\n\t\t1: Si.");
    	printf("\n\t\totro numero: No");
    	printf("\n\t\tIngrese:");
    	scanf("%d",&eleccion);
    	
    	if(eleccion == 1){
    		otroProfesional = true;
    		ind++;
    		system("cls");
		}else{
			otroProfesional = false;
		}
		
	}while(otroProfesional == true);
	
	insertarProfesional(profesional, ind);
	liberarMemoriaLista(top);
	top = NULL;
	system("cls");
		
}

void crearRecpcionista(){
	system("cls");
	
	FILE* arch = fopen("Recepcionistas.dat","rb");
	user aux1;
	
	
	if(arch == NULL){
		perror("ERROR, al tratrar de leer el archivo Recepcionistas.dat:");
		exit(1);
	}
	fread(&aux1, sizeof(user),1,arch);
	
	while(!feof(arch)){
		printf("\t\tNombre: %s\n", aux1.nombreApellido);
		fread(&aux1, sizeof(user),1,arch);
	}
	
	fclose(arch);
	fflush(stdout);
	
	user usuarios[25];
	int ind = 0;
	int eleccion = 0;
	bool otroRecepcionista = false;
	
	char nombre_apellido[80],usuario[80],contrasena[80];
	int tamanoNombre,i,contadorMayusculas = 0,contadorMinuscula = 0,contadorNumeros = 0,verificarMayuscula,verificarMinuscula,verificarNumero,verificarEspacios,verificarAlfanumericos;
	bool usuarioValido = false;
		
	do{
	
		printf("\n\t\tNombre del nuevo usuario Recepcionista:");
		scanf("%s[^\n]",&nombre_apellido);
		fflush(stdin);
	
		strcpy(usuarios[ind].nombreApellido , nombre_apellido);
	
		do{
			printf("\n\t\t  Requerimientos");
			printf("\n\t\t1-El nomrbre de usuario, su primera letra debe comenzar en minusculas.");
			printf("\n\t\t2-Debe poseer por lo menos 2 mayusculas.");
			printf("\n\t\t3-Solo puede tener como maximo 3 digitos numericos.");
			printf("\n\t\t4-Solo puede tener minimo 6 caracteres y maximo 10.");
			printf("\n\t\t!!!!!Recuerde y leea bien para no equivocarse!!!!!");
	
			printf("\n\n\t\tNombre de usuario Recepcionista:");
			scanf("%s[^\n]",&usuario);
			fflush(stdin);
		
			strcpy(usuarios[ind].usuario , usuario);
			tamanoNombre = strlen(usuario);
		
			//esto nos ayuda mucho a optimizar el ultimo if que servia de verificacion de validez del nombre de usuario 
			if(tamanoNombre < 6 || tamanoNombre > 10){
				puts("\n\t\tNo cumple con el 4 requerimiento, PRESIONE UNA TECLA.");
				getch();
				system("cls");
				continue;
			}
	
			for(i = 0; i < tamanoNombre; i++){
		
				verificarMayuscula = isupper(usuario[i]);
				verificarNumero = isdigit(usuario[i]);
		
				if(verificarMayuscula != 0){// si es != 0 significa que es una letra en mayuscula
					contadorMayusculas++;
				}
				if(verificarNumero != 0){//Valor distinto de cero si el carácter es un carácter numérico; cero en caso contrario.
					contadorNumeros++;
				}
				
			}
		
			int auxiliar = isupper(usuario[0]);// auxiliar == 0 significa q es minuscula, hacemos esto por que la primera letra del usuario tiene que ser si o si en minusculas
		
			//con este if verificamos todos los requerimientos que debe tener el nombre del usuario
			if( (contadorMayusculas >= 2 && contadorNumeros <= 3) && auxiliar == 0 ){
				usuarioValido = true;// si nombreValido es igual a true el do-while se rompe y se puede continuar caso contrario a volver a ingresar los datos
			}else{
				printf("\n\t\tEl Usuario es invalido.\n");
				contadorMayusculas = 0;
				contadorNumeros = 0;
				auxiliar = 0;
				getch();
				fflush(stdin);
				system("cls");
			}
		
		
		}while(usuarioValido == false);
	
	
	

		/*	
		1- Una mayuscula, una minuscula, un numero minimo.
		2- Ningun caracter de puntuacion (ej: ,;.:') ni escpacios solo caracteres alfanumericos.
		3- Debe tener entre 6 a 32 caracteres.
		4- No puede tener mas de 3 caracteres numericos consecutivos.
		5- No puede tener 2 caracteres que esten seguidos alfabeticamente y es aplicable tanto a las mayusculas como a las minusculas
		*/
	
		int tamanoContrasena = 0; 
		i = 0;
		contadorMayusculas = 0;
		contadorMinuscula = 0;
		contadorNumeros = 0;
		verificarEspacios = 0;
		verificarAlfanumericos = 0;
		verificarMayuscula = 0;
		verificarNumero = 0;
		bool contrasenaValida = false, letrasSeguidas = false,numerosSeguidos = false;
	
		do{
			letrasSeguidas = false;
			numerosSeguidos = false;
			int tamanoContrasena = 0; 
			i = 0;
			contadorMayusculas = 0;
			contadorMinuscula = 0;
			contadorNumeros = 0;
			verificarEspacios = 0;
			verificarAlfanumericos = 0;
			verificarMayuscula = 0;
			verificarNumero = 0;
		
			system("cls");
			fflush(stdin);
			printf("\n\n\t\t    Requerimientos");
			printf("\n\t\t1- Como minimo la contrasena debe poseer una mayuscula, una minuscula y un numero.");
			printf("\n\t\t2- Ningun caracter de puntuacion o especial (ej: ,;.:?¿!#') ni escpacios solo caracteres alfanumericos.");
			printf("\n\t\t3- No puede tener mas de 3 caracteres numericos consecutivos");
			printf("\n\t\t4- Solo puede tener minimo 6 caracteres y maximo 32.");
			printf("\n\t\t5- No puede tener 2 caracteres que esten seguidos alfabeticamente y es aplicable tanto a las mayusculas como a las minusculas.\n");
			printf("\n\t\t!!!!!Recuerde y leea bien para no equivocarse!!!!!");
		
			printf("\n\n\t\tIngrese la contrasena deseada:");
			scanf("%s",&contrasena);
	
			tamanoContrasena = strlen(contrasena);
			strcpy(usuarios[ind].contrasena , contrasena);
		
			for(i = 0; i < tamanoContrasena; i++){
			
				verificarMayuscula = isupper(contrasena[i]);
				verificarNumero = isdigit(contrasena[i]);
				verificarEspacios = isspace(contrasena[i]);
				verificarAlfanumericos = isalnum(contrasena[i]);
				
				if(tamanoContrasena < 6 || tamanoContrasena > 32){
					puts("\n\t\tLa contrasena ingresada no cumple con el 3 requerimiento, PRESIONE UNA TECLA.");
					getch();
					system("cls");
					break;
				}
		
			
				numerosSeguidos = numerosConsecutivos(contrasena,&i,&contadorNumeros);
				
				if(numerosSeguidos == true){
					puts("\n\t\tLa contrasena ingresada posee mas de 3 numeros consecutivos, intente de nuevo.\n");
					getch();
					numerosSeguidos = false;
					system("cls");
					break;
				}
			

				if(verificarEspacios != 0){//Valor distinto de cero si el carácter es un carácter de espacio en blanco; cero en caso contrario.
					puts("\n\t\tLa contrasena ingresada posee espacios, intente de nuevo.\n");
					getchar();
					system("cls");
					break;
				}
			
				// esto es para que el usuario no ingrese caracteres raros como ,;.:?¿ etc.
				if(verificarAlfanumericos == 0){
					puts("\n\t\tLa contrasena ingresada posee caracteres no aceptables, intente de nuev o    .\n");
					getch();
					system("cls");
					break;
				}
			
				letrasSeguidas = tieneDosCaracteresSeguidos(contrasena);
			
				if(letrasSeguidas == true){
					printf("\n\t\tLa contrasena posee dos letras alfabeticamente seguidas.\n");
					getch();
					break;
				}
			
				if(verificarMayuscula != 0){
					contadorMayusculas++;
				}else{
					contadorMinuscula++;
				}
							
			}
		
				//if final con el cual se verificara si la contraseña es valida o no
			if( contadorMayusculas > 0 && contadorMinuscula > 0 && contadorNumeros > 0) {
				contrasenaValida = true;
			}else{
				printf("\n\t\tContadorMinuscula: %d, contadorMayusculas: %d, contadorNumeros: %d\n", contadorMinuscula,contadorMayusculas,contadorNumeros);
				getch();
				fflush(stdin);
				system("cls");
			}
		
		}while(contrasenaValida == false);	
		
		system("cls");
	


		if( verificarExistenciaUsuarioRecepcionista(usuario,contrasena) == 2){// significa que  ya hay un usuario registrado con ese usuario y contraseña
			printf("\n\t\tYa se encuentra registrado un usuario rescepcionista con esa misma contrasena y usuario.\n");
			getch();
			crearRecpcionista();
		}
	
		printf("\n\t\tDesear registrar otro recepcionista?\n");
		printf("\n\t\t1: Si");
		printf("\n\t\tOtro numero: No\n");
		printf("\t\tElija: ");
		scanf("%d",&eleccion);
	
		if(eleccion == 1){
			otroRecepcionista = true;
			eleccion = 0;
			ind++;
			system("cls");
		}else{
			otroRecepcionista = false;
		}
	
	}while(otroRecepcionista == true);
	
	system("cls");
	insertarRecepcionista(usuarios, ind);
	liberarMemoriaListaRecep(topR);
	topR = NULL;
	system("cls");
	
}

static bool tieneDosCaracteresSeguidos(char cadena[]) {
    int longitud = strlen(cadena);  
    char cadenaAux[80] = "";
    int i = 0;
    
    for(i = 0; i < longitud; ++i){
    	cadenaAux[i] = tolower(cadena[i]);
	}
		
    for (int i = 0; i < longitud - 1; ++i) {
    	
        if (isalpha(cadenaAux[i]) && isalpha(cadenaAux[i + 1])) {
            // Verificar si los caracteres están alfabéticamente seguidos
            if (abs(cadenaAux[i] - cadenaAux[i + 1]) == 1) {
                return true; // Dos caracteres alfabéticamente seguidos encontrados
            }
        }
    }
    // No se encontraron dos caracteres alfabéticamente seguidos
    return false;
}

static bool numerosConsecutivos(const char *contrasena, int *i, int *contadorNumeros){
	
	if( isdigit(contrasena[*i]) != 0){// si es != 0 es un numero
		*contadorNumeros = *contadorNumeros + 1;
		if(contrasena[*i+1] != '\0' && contrasena[*i+2] != '\0' && contrasena[*i+3] != '\0'){				
			if(isdigit(contrasena[*i+1]) != 0 && contrasena[*i+2] != 0 && isdigit(contrasena[*i+3]) != 0){
				*contadorNumeros = 0;
				return true;
			}
		}
	}
	
	return false;
}

static void insertarRecepcionista(user usuarios[], int i){
	
	FILE *file = fopen("Recepcionistas.dat","ab");
	
	if(file == NULL){
		perror("ERROR, al abrir archvio Recepcionista.dat:");
		exit(1);
	}
	
	
	for(int in = 0; in <= i; in++){
		pushRecepcionista(usuarios[in]);
	}

	escribirEnArchivoRecepcionista(file, topR);
			
	fclose(file);
	
			
}

static int insertarProfesional(NuevoProfesional profesional[],int ind) {
	
	int id, i = 0;
			
	FILE *file = fopen("Profesionales.dat","ab");
		
	if(file == NULL){
		perror("ERROR, al abrir archvio Profesionales.dat:");
		return 0;
	}
	
	srand(time(NULL));
	
	for(i = 0; i <= ind; i++){
		id = generarId();	
		profesional[i].idProfesional = (id / 5);
			
	}
	rewind(file);
	
	for (i = 0; i <= ind; i++) {
        push(profesional[i]);
    }
    
	escribirEnArchivo(file, top);

	fclose(file);
	
			
}

char* obtenerUsuarioActual(){
	return usuarioActual;
}

char* obtenerContrasenaActual(){
	return contrasenaActual;
}

void liberarMemoria(){
	free(usuarioActual);
	free(contrasenaActual);
	usuarioActual = NULL;
	contrasenaActual = NULL;
	
}

static void liberarMemoriaLista(Nodo *top) {
    Nodo *aux;
    while (top != NULL) {
        aux = top;
        top = top->next;
        free(aux);
    }
}

static void push(NuevoProfesional profesional) {
	
    Nodo *nuevoNodo = (Nodo*)malloc(sizeof(Nodo));
    
    if (nuevoNodo == NULL) {
        perror("ERROR, al asignar memoria para el nuevo nodo:");
        return;
    }
    nuevoNodo->profesionalNodo = profesional;
    nuevoNodo->next = top;
    top = nuevoNodo;
}

static void escribirEnArchivo(FILE *file, Nodo *nodo) {
    if (nodo == NULL) {
        return;
    }
    fwrite(&(nodo->profesionalNodo), sizeof(NuevoProfesional), 1, file);
    escribirEnArchivo(file, nodo->next);
}

static int generarId() {
	
    return rand() % 500 + 1; // Genera un número aleatorio en el rango [1, 500]
}

static void escribirEnArchivoRecepcionista(FILE *file, Nodo1 *nodo) {
    if (nodo == NULL) {
        return;
    }
    fwrite(&(nodo->recepcionistaNodo), sizeof(user), 1, file);
    escribirEnArchivoRecepcionista(file, nodo->next);
}

static void pushRecepcionista(user recepionista) {
	
	Nodo1 *nuevoNodo = (Nodo1*)malloc(sizeof(Nodo1));
    
    if (nuevoNodo == NULL) {
        perror("ERROR, al asignar memoria para el nuevo nodo:");
        return;
    }
    
    nuevoNodo->recepcionistaNodo = recepionista;
    nuevoNodo->next = topR;
    topR = nuevoNodo;
}

static void liberarMemoriaListaRecep(Nodo1 *topR){
	Nodo1 *aux;
    while (topR != NULL) {
        aux = topR;
        topR = topR->next;
        free(aux);
    }
}





























