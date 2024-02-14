#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "Pacientes.h"
#include "Usuario.h"
#include "Profesionales.h"

void moduloRecepcionista();
void moduloAdministracion();
void moduloProfesional();
void moduloUsuario();
//
int main(void){

	moduloUsuario();
	return 0;
}

void moduloUsuario(){
			
	char usuario[80],contrasena[80];
	int opcion;
	int verificacion1,verificacion2,verificacion3;
	bool bandera;	
	bandera = true;
	
	fecha fech;
	fech = hoy();
	
	printf("%d/%d/%d",fech.dia,fech.mes,fech.anio);	
		
	printf("\n\t\t    Modulo Usuario \n");
	printf("\t\t============================================================\n\n");
	printf("\t\t    |Iniciar sesion.\n\n");
	printf("\t\t    |Usuario:");
	scanf("%s", &usuario);
	printf("\n\t\t    |Contrasena:");
	scanf("%s", &contrasena);
	
	verificacion1 = verificarExistenciaUsuarioProfesional(usuario,contrasena);
	verificacion2 = verificarExistenciaUsuarioRecepcionista(usuario,contrasena);
	verificacion3 = verificarExistenciaUsuarioAdmin(usuario,contrasena);

	if(verificacion1 == 1){
		moduloProfesional();
		
	}else if(verificacion2 == 2){
		moduloRecepcionista();
		
	}else if(verificacion3 == 3){	
 		moduloAdministracion();
 		
	}else{
		printf("\n\t\t    |No exite ningun cuenta con nombre de usuario o esa contrasena.\n\n");
		getch();
		system("cls");
	}
	
		
}


void moduloRecepcionista(){
	
	system("cls");
	
	int opcion;
	bool bandera;	
	bandera = true;
	
	while(bandera == true){
			
		printf("\n\t\t    Modulo Recepcionista \n");
		printf("\t\t============================================================\n\n");
		printf("\t\t    1. Iniciar sesion.\n\n");//listo
		printf("\t\t    2. Registrar Paciente.\n\n");//listo
		printf("\t\t    3. Registrar Turno.\n\n");//listo
		printf("\t\t    4. Listado de atenciones por Profesional y fecha.\n\n");//en espera
		printf("\t\t    5. Salir.\n\n");//listo
		printf("\n\t\t    Elija una opcion: ");
		scanf("%i", &opcion);
		
		switch(opcion){
			case 1:
				system("cls");
				moduloUsuario();
				break;			
			case 2:
				system("cls");
				registrar_paciente();
				break;
			case 3:
				system("cls");
				registrar_turno();
				break;
			case 4:
				atencionesProfesionalFecha();
				break;
			case 5:
				bandera = false;
				liberarMemoria();
				exit(1);
				break;
			default:
				printf("\n\t\t    Opcion Inexistente, intentelo de nuevo.\n\n");
				break;	
		}
	}
	
}

void moduloProfesional(){
	system("cls");
	int opcion;
	bool bandera;	
	bandera = true;
	
	do{
	
		printf("\n\t\t    Modulo Profesional \n");
		printf("\t\t============================================================\n\n");
		printf("\t\t    1. Listar pacientes.\n\n");//listo
		printf("\t\t    2. Ver historiales clinicos.\n\n");//listo
		printf("\t\t    3. Atender pasientes.\n\n");//listo
		printf("\t\t    4. Salir.\n\n");//listo
		printf("\n\t\t    Elija una opcion: ");
		scanf("%i", &opcion);
			
		switch(opcion){
			case 1:
				listarPacientes();
				break;			
			case 2:
				listarhistorialClinico();
				break;	
			case 3:
				atenderPacienteConTuno();
				break;
			case 4:
				bandera = false;
				liberarMemoria();
				exit(1);
				break;
			default:
				printf("\n\t\t    |Opcion Inexistente, intentelo de nuevo.\n\n");
				break;	
		}
		
	}while(bandera);
}

void moduloAdministracion(){
	
	system("cls");
			
	int opcion;
	bool bandera;	
	bandera = true;
	
	do{
			
		printf("\n\t\t    Modulo Administrador \n");
		printf("\t\t============================================================\n\n");
		printf("\t\t    1. Registrar usuario Profesional.\n\n");//listo
		printf("\t\t    2. Registrar usuario Recepcionista.\n\n");//listo
		printf("\t\t    3. Atenciones por Profecional.\n\n");//listo
		printf("\t\t    4. Ranking de profesionales por atenciones.\n\n");//listo
		printf("\t\t    5. Salir.\n\n");//listo
		printf("\n\t\t    Elija una opcion: ");
		scanf("%i", &opcion);
		
		switch(opcion){
			case 1:
				crearProfesional();
				break;			
			case 2:
				crearRecpcionista();
				break;	
			case 3:
				atencionesPorProfesional();
				break;
			case 4:
				ranking_profesionales();
				break;
			case 5:
				bandera = false;
				liberarMemoria();
				exit(1);
				break;
			default:
				printf("\n\t\t    |Opcion Inexistente, intentelo de nuevo.\n\n");
				break;	
		}
		
	}while(bandera);
	
}

































