#include "Pacientes.h"
#include "Profesionales.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctime>
#include <conio.h>

//Encabezados/Definiciones de las funciones privadas de esta script 

static void crearArchivoPaciente(Paciente paciente);
static void crearArchivoTruno(int idProfesional,fecha fechaAux,int dniPaciente, char problemaTratar[80]);



void registrar_paciente(){
	system("cls");
		
	char historialClinico[380];
	int indice = 0,opcion = 0;
		
	Paciente paciente1;
	
	char apellidoNombre[80],localidad[80],domicilio[80],telefono[25],problemaTratar[380];
	int dniPaciente, fechaNacimiento;
	
	fflush(stdin);
	
	printf("\n\t\tDigiete el nombre y apellido del paciente a registrar:");
	scanf("%[^\n]", &apellidoNombre);
	fflush(stdin);
	
	printf("\n\t\tDigiete su localidad de residencia:");
	scanf("%[^\n]", &localidad);
	fflush(stdin);
	
	printf("\n\t\tSu domicilio:");
	scanf("%[^\n]", &domicilio);
	fflush(stdin);
		
	printf("\n\t\tDigiete su telefono:");
	scanf("%[^\n]", &telefono);
	fflush(stdin);
	
	printf("\n\t\tSu Dni:");
	scanf("%d", &dniPaciente);
	fflush(stdin);
	
	printf("\n\t\tSu fecha de nacimiento:");
	scanf("%d", &fechaNacimiento);
	fflush(stdin);
	
	strcpy(paciente1.apellidoNombre, apellidoNombre);
	strcpy(paciente1.localidad, localidad);
	strcpy(paciente1.domicilio, domicilio);
	strcpy(paciente1.telefono, telefono);
	paciente1.dniPaciente = dniPaciente;
	paciente1.fechaNacimiento = fechaNacimiento;

	do{
	
		printf("\n\n\t\tAreas de la clinica\n");
		printf("\n\t\t1. Ginecologia.");
		printf("\n\t\t2. Traumatologia.");
		printf("\n\n\t\tElige una opcion: ");
		scanf("%d", &opcion);
		fflush(stdin);
	
		if(opcion == 1){
			strcpy(paciente1.areaTratar,"Ginecologia");
		}else if(opcion == 2){
			strcpy(paciente1.areaTratar, "Traumatologia");
		}else{
			printf("\n\t\tOpcion inexistente intenta de nuevo.\n");
		}
	 
	 
	}while(opcion < 0 || opcion > 2);
	
	fflush(stdin);
	printf("\n\t\tIngrese el problema a tratar: ");
	scanf("%[^\n]", &problemaTratar);
	fflush(stdin);	
	
	strcpy(paciente1.problemaTratar, problemaTratar);

	// esto en un futuro se hara cuando se valla a cerrar el programa
	crearArchivoPaciente(paciente1);
	system("cls");
}

static void crearArchivoPaciente(Paciente paciente){
	
	int i = 0;
	FILE *file = fopen("Pacientes.dat","ab");
	
	if(file == NULL){
		perror("Hubo un error, no se pudo crear o anexar informacion al archivo Pacientes.dat");
		exit(1);
	}

	fwrite(&paciente, sizeof(Paciente),1,file);		
	fflush(file);
	fclose(file);
	
}
//Funcion para optener la fecha del dia
fecha hoy(){
	time_t t;
	t = time(NULL);
	struct tm *f;
	f = localtime(&t);
	fecha aux;
	aux.dia = f->tm_mday;
	aux.mes = f->tm_mon;
	aux.anio = f->tm_year + 1900;//lo sumamos con este numero por que esta funcion cuenta los años desde 1900 hasta ahora entonces lo sumamos
	
	return aux;
}

void registrar_turno(){
	system("cls");
	
	fecha fechaAux;
	int dni,elementos = 0;
	bool existe = false;
	Paciente paciente;
	
	FILE *file = fopen("Pacientes.dat","rb");
	
	if(file == NULL){
		perror("\n\t\tERROR, al abrir el archivo:");
		exit(1);
	}
	
	elementos = fread(&paciente,sizeof(Paciente),1,file);
	
	if(elementos != 0){
				
		printf("\n\t\tPacientes Registrados: \n");
		
		while(!feof(file)){
			printf("\t\tPaciente = Nombre: %s , DNI: %d \n", paciente.apellidoNombre,paciente.dniPaciente);
			fread(&paciente,sizeof(Paciente),1,file);

		}
	
	
		memset(&paciente, 0, sizeof(Paciente));//Limpiamos la variable de tipo estructura paciente
		rewind(file);//volvemos al inicio del archivo(devuelve el puntero a la posicion 0 del archvio)
		
		do{
		
			printf("\n\n\t\tIngrese el DNI del paciente al cual se le quiere reservar un turno: ");
			scanf("%d",&dni);
		
			while(!feof(file)){
				fread(&paciente,sizeof(Paciente),1,file);
			
			
			
				if(dni == paciente.dniPaciente){
					existe = true;
					printf("\n\t\tDNi: %d\n",paciente.dniPaciente);
					break;
				}
			}
			getch();
		
			if(!existe){
				printf("\n\t\tNo se encontro ningun paciente con ese DNI, intente de nuevo.\n");
				rewind(file);
				getch();
			
			}
		
		}while(!existe);
	
		fclose(file);
	
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
		if(existe){
			system("cls");
			int contador = 0;
			existe = false;
	
			file = fopen("Profesionales.dat","rb");
	
			if(file == NULL){
				perror("\n\t\tERROR, al abrir el archivo:");
				exit(1);
			}
				
			printf("\n\t\tProfesionales Disponibles: \n");
		
			NuevoProfesional profesional;
			fread(&profesional,sizeof(NuevoProfesional),1,file);
		
			while(!feof(file)){
					
				if(strcmp(profesional.areaProfesional,paciente.areaTratar) == 0){//esto lo hacemos para que el paciente sea tratado por un profional de la especializad que escogio
					printf("\t\tProfesional = Nombre: %s , DNI: %d \n", profesional.apelldioNombre,profesional.dniProfesional);
					contador++;
				}		
				fread(&profesional,sizeof(NuevoProfesional),1,file);
			}
		
			if(contador == 0){
				printf("\n\t\tNo hay ningun profesionales disponibles.\n");
				getch();
			}else{
			
				memset(&profesional, 0, sizeof(NuevoProfesional));//Limpiamos la variable de tipo estructura profesional
				rewind(file);//volvemos al inicio del archivo(devuelve el puntero a la posicion 0 del archvio)
		
				do{
				
			
					printf("\n\n\t\tIngrese el DNI del profesional al cual se quiere ser atendido: ");
					scanf("%d",&dni);
		
					while(!feof(file)){
						fread(&profesional,sizeof(NuevoProfesional),1,file);
				
					//	printf("\n\t\tDNi: %d\n",profesional.dniProfesional);
				
						if(dni == profesional.dniProfesional){
							existe = true;
							break;
						}
					}
		
					if(!existe){
						printf("\n\t\tNo se encontro ningun profesional con ese DNI, intente de nuevo.\n");
						rewind(file);
						dni = 0;
						getch();
					}
		
				}while(!existe);
		
				fclose(file);
		
				fechaAux = hoy();
				printf("\n\t\t%d/%d/%d",fechaAux.dia,fechaAux.mes,fechaAux.anio);	
				crearArchivoTruno(profesional.idProfesional,fechaAux,paciente.dniPaciente,paciente.problemaTratar);
			}
		
			/*	int idProfesional;
				fecha fecha;
				Paciente pacienteDni;
				char detallesAtencion[380];	*/
		}
	
	}else{
		puts("\n\t\tNo hay pacientes registrados.");
	}
	getch();
	system("cls");
}

static void crearArchivoTruno(int idProfesional,fecha fechaAux,int dniPaciente,char problemaTratar[80]){
	
	FILE *file;
	file = fopen("Turnos.dat","ab");
	
	if(file == NULL){
		perror("Hubo un error, no se pudo crear o anexar informacion al archivo Turnos.dat");
		exit(1);
	}
	
	Turno turno;
	strcpy(turno.detallesAtencion,problemaTratar);
	turno.fecha = fechaAux;
	turno.idProfesional = idProfesional;
	turno.dniPaciente = dniPaciente;
	
	
	fwrite(&turno,sizeof(Turno),1,file);
	fflush(file);
	fclose(file);
	
	puts("\n\t\t!!Se reservo un turno con exito.!!\n");
	getch();
}



















