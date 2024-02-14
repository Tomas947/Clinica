#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "Profesionales.h"
#include "Pacientes.h"
#include "Usuario.h"

typedef struct{
	char nombreProfesional[80];
	int dniProfesional;
	int cantidadAtenciones;
}Auxiliar;

fecha fechaPaciente(int dniPaciente);
static void registarHistorialClinico(Paciente paciente,NuevoProfesional profesional);
static void eliminarTurno(Paciente paciente);
static void eliminarPaciente(Paciente paciente);

void listarPacientes(){
	
	system("cls");
	
	FILE* file = fopen("Pacientes.dat","rb");
	
	Paciente paciente;
	int elementos = 0;
	
	if(file == NULL){
		perror("ERROR, al tratar de abrir el archivo Pacientes.dat:");
		exit(1);
	}
		
	elementos = fread(&paciente, sizeof(Paciente), 1, file);// la funcion fread devuelve la cantidad de elementos leidos en este caso deberia ser 1 
	
	while(!feof(file)){
		//Si la cantidad de elementos es 0 significa que el archivo esta vacio
		if(elementos != 0){
			printf("\n\t\tPaciente = Nombre_Apellido: %s, Dni: %d, area en el cual se tratara: %s.", paciente.apellidoNombre,paciente.dniPaciente,paciente.areaTratar);	
			elementos = fread(&paciente, sizeof(Paciente), 1, file);
		}else{
			puts("\n\t\tNo hay pacientes registrados.\n");
			break;
		}
		
	}
	
	puts("\n\t\tPresione una tecla para continuar.");
	getch();
	
	system("cls");
	
}

void listarhistorialClinico(){
	
	system("cls");
	
	HistorialClinicoPaciente historia;
	fecha fech;
		
	FILE* file = fopen("HistorialClinico.dat","rb");
	
	if(file == NULL){
		perror("ERROR,al agregar el historial clinico de un paciente atendido:");
		exit(1);
	}
	
	int elementos = fread(&historia, sizeof(HistorialClinicoPaciente), 1, file);// la funcion fread devuelve la cantidad de elementos leidos en este caso deberia ser 1 
	
	while(!feof(file)){
		//Si la cantidad de elementos es 0 significa que el archivo esta vacio
		
		if(elementos != 0){
			printf("\n\n\t\tNombre: %s, Dni: %d, Edad: %i.", historia.apellidoNombre,historia.dniPaciente,historia.edad);
			printf("\n\t\tPeso: %i, Talla(cm): %i, Fecha: %d/%d/%d.\n \t\tProfesional: %s.", historia.peso,historia.talla, historia._fecha.dia,historia._fecha.mes, historia._fecha.anio,historia.apellidoNombreProfesional);		
			elementos = fread(&historia, sizeof(HistorialClinicoPaciente), 1, file);
		}else{
			puts("\n\t\tNo hay Historial clinica.\n");
			break;
		}
		
	}
	fclose(file);
	
	puts("\n\n\t\tPresione una tecla para continuar.");
	getch();
	system("cls");
	
}

void atencionesPorProfesional(){
		
	system("cls");
	
	char nombreProfesional[80];
	int dni,cantidadAtenciones = 0;
	HistorialClinicoPaciente historia;
	NuevoProfesional profesional;
	
	FILE *arch = fopen("Profesionales.dat","rb");
	
	if(arch == NULL){
		perror("ERROR, al tratar de abrir el archvo Profesionales.dat:");
		exit(1);
	}
	
	int elementos = fread(&profesional, sizeof(NuevoProfesional), 1,arch);
	if(elementos > 0){
	
		while(!feof(arch)){
			printf("\n\t\tProfesional = Nombre %s, Dni: %d", profesional.apelldioNombre,profesional.dniProfesional);
			fread(&profesional, sizeof(NuevoProfesional), 1,arch);
		}
		
		fclose(arch);
		elementos = 0;
	
		printf("\n\n\t\tIngrese el DNI del profesional:");// verificamos con el dni ya q es unico, a diferencia del nombre que cada persona puede tener el mismo nombre o no 
		scanf("%i",&dni);
		fflush(stdin);
		
		printf("\n\t\tIngrese el nombre del profesional:");
		scanf("%[^\n]",&nombreProfesional);
		fflush(stdin);
		
		system("cls");
	
		FILE* file = fopen("HistorialClinico.dat","rb");
	
		if(file == NULL){
			perror("\n\t\tERROR, al tratar de abrir el archivo HistorialClinico.dat:");
			exit(1);
		}
	
		elementos = fread(&historia, sizeof(HistorialClinicoPaciente),1,file);
	
		if(elementos > 0){

			while(!feof(file)){

				if(historia.dniProfesional == dni){
					cantidadAtenciones++;

				}
				fread(&historia, sizeof(HistorialClinicoPaciente),1,file);
		
			}
		
			if(cantidadAtenciones != 0){
				printf("\n\t\tProfesional: %s, atenciones realizadas hasta el momento: %d", nombreProfesional, cantidadAtenciones);
				
			}
	
		}else{
			puts("\n\t\tNo hay atenciones registradas.");
			getch();
		}
		
		fclose(file);
	
	}else{
		puts("\n\t\tNo hay profesionales registrados.\n");
	}
	
	getch();
	system("cls");
	
}

void ranking_profesionales(){
	system("cls");
	int i = 0, numElementos = 0,elemento = 0,atenciones = 0;

	HistorialClinicoPaciente arrayProfesionales[80],profesional1;
	Auxiliar aux[80];
	
	FILE * file = fopen("HistorialClinico.dat","rb");
	
	if(file == NULL){
		perror("ERROR, al tratar de leer archivo HistorialClinico.dat");
		exit(1);
	}

	printf("\n\t\tListado de todas los Profesionales con sus respectivas atenciones realizadas.\n");
	
	elemento = fread(&profesional1, sizeof(HistorialClinicoPaciente),1,file);
	if(elemento > 0){

		while(!feof(file)){
			
			arrayProfesionales[i] = profesional1;
			
			if(arrayProfesionales[i].dniProfesional == profesional1.dniProfesional){
				atenciones++;
				strcpy(aux[i].nombreProfesional , profesional1.apellidoNombreProfesional);
				aux[i].dniProfesional = profesional1.dniProfesional;
				aux[i].cantidadAtenciones += atenciones;
			}
			
			atenciones = 0;
			numElementos++;
			i++;
			
			fread(&profesional1, sizeof(HistorialClinicoPaciente),1,file);
		
		}				
		fclose(file);

		
/////////////Contamos las atenciobnes///////////////////////////////////////////////////////////////////////////////////
		for (i = 0; i < numElementos; i++) {
        	int repetido = 0;
        	for (int j = 0; j < i; j++) {
            	if (aux[i].dniProfesional == aux[j].dniProfesional) {
            		int atencion = 0;
					atencion += aux[i].cantidadAtenciones;
            		atencion += aux[j].cantidadAtenciones;
            		aux[i].cantidadAtenciones = atencion;
            		aux[j].cantidadAtenciones = atencion;
					repetido = 1;
                	break;
            	}
        	}
		}
		
		//esta para se encarga de no imprimir mas de una vez el profesional ya que en el array aux se encuentran un par de profesionales repetidos 
		// por que hicieron mas de una atencion 
		int j1;
    	for (i = 0; i < numElementos; i++) {
        	int repetido = 0;
        	for (j1 = 0; j1 < i; j1++) {
            	if (aux[i].dniProfesional == aux[j1].dniProfesional) {
					repetido = 1;
                	break;
            	}
        	}
        	if (!repetido) {
            	printf("\n\t\tProfesional = nombre: %s, atenciones: %d", aux[i].nombreProfesional,aux[i].cantidadAtenciones );
        	}
    	}
		
		// Vaciamos a aux por si se vuelve a llamar la funcion ranking
		for(i = 0; i < numElementos; i++){
			aux[i].cantidadAtenciones = 0;
			aux[i].dniProfesional = 0;
			strcpy(aux[i].nombreProfesional, "");		
		}
		
		
/////////////////////////////////////////////////////////////////

	
	}else{
		puts("\n\t\tHistorial clinico vacio.\n\t\tPresione una TECLA para continuar.");
	}
	
	fclose(file);
	getch();
	system("cls");
}

void atenderPacienteConTuno(){
	
	
	system("cls");
	char *usuarioActual = NULL;
	char *contrasenaActual = NULL;
	usuarioActual = obtenerUsuarioActual();
	contrasenaActual = obtenerContrasenaActual();
	
	// toda esta lectura es para obtener la variable estructura del profesional que esta usando el sistema ahora
	FILE* file = fopen("Profesionales.dat","rb");
	NuevoProfesional profesional;
	
	if(file == NULL){
		perror("ERROR, al tratar de abrir el archivo Profesionales.dat:");
		exit(1);
	}
		
	fread(&profesional, sizeof(NuevoProfesional), 1, file);
	
	while(!feof(file)){

		if( strcmp(usuarioActual , profesional.profesionalData.usuario) == 0 &&  strcmp(contrasenaActual , profesional.profesionalData.contrasena) == 0){//si son iguales
			break;	
		}	
		fread(&profesional, sizeof(NuevoProfesional), 1, file);	
	}
		
	fclose(file);
//	printf("Usuario actual:%s",usuarioActual);
//	printf("contrasena actual:%s",contrasenaActual);
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// toda esta lectura en el archivo turnos es para hacer una lista de los turnos registrados en el sistema
	file = NULL;
	Turno turno,vectorTurnos[80];
	bool bandera = false;
	int i = 0,numero = 0 ;
	
	file = fopen("Turnos.dat","rb");
	
	if(file == NULL){
		perror("ERROR, al tratar de abrir el archivo Turnos.dat:");
		exit(1);
	}
	
	int aux = fread(&turno, sizeof(Turno), 1, file);
	
	if(aux > 0){
		bandera = true;
		while(!feof(file)){
			vectorTurnos[i] = turno;
			numero++;
			// esta sera la lista de turnos en el cual devemos verifiacar cual de los pacientes que se registraron en ella son del area del profesional
			i++;
			fread(&turno, sizeof(Turno), 1, file);				
		}
		
	}else{
		puts("\n\t\tNo hay turnos registrados.\n");
		getch();
	}
	

	fclose(file);
	
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	// y ahora con la lista de turnos usaremos los dni's que guardan para saber cunatos y que pasientes tienen un turno asignado
	
	if(bandera == true){// esto significa que por lo menos hay un turno registrado y recien ahi hay que hacer todo esto
	
		file = fopen("Pacientes.dat","rb");
		
		int cantidad = 0;
		Paciente paciente;
		Paciente vectorPacientesConTurnos[80];
		aux = 0;
		i = 0;
	
		aux = fread(&paciente, sizeof(Paciente), 1, file);
				
		if(aux > 0){

			while(!feof(file)){
			/*
				printf("area paciente: %s, area profesional: %s\n",paciente.areaTratar,profesional.areaProfesional);
				printf("area paciente: %s, area profesional: %s\n",vectorTurnos[i].dniPaciente,paciente.dniPaciente);
		*/		
				if( vectorTurnos[i].dniPaciente == paciente.dniPaciente ){//hacemos esto para saber cual de todos los pacientes en el archivo poseen un turno
					
					if( strcmp(paciente.areaTratar, profesional.areaProfesional) == 0){//ahora verificamos si ese paciente que si esta en nuestro vectorTurnos coinciden con el area del profesional
						vectorPacientesConTurnos[i] = paciente;
						cantidad = cantidad + 1;	
						i++;
					}
				}
			
				
				aux += fread(&paciente, sizeof(Paciente), 1, file);				
			}	
		}

		rewind(file);
		i = 0;
		int v;
		
		if(cantidad != 0){
			fecha fech;
			printf("\n\t\t    Pacientes a atender \n");

			for(i = 0; i < cantidad; i++){
				v = vectorPacientesConTurnos[i].dniPaciente;
				fech = fechaPaciente(v);		
				printf("\n\t\t  Paciente = Nombre_Apellido: %s, Dni: %d, Fecha: %d/%d/%d", vectorPacientesConTurnos[i].apellidoNombre, v, fech.dia,fech.mes,fech.anio);	
			}
			
	 		fclose(file);
			
			FILE * file1 = fopen("Pacientes.dat","rb");
		
			char cadena[80];
			bool nombreValido = false;
		
			do{
			
				printf("\n\n\t\t  Ingrese el nombre y apellido del paciente a atender tal cual se encuentra registrado: ");
				scanf("%s[^\n]", &cadena);
			
		
				fread(&paciente, sizeof(Paciente), 1, file1);
				while(!feof(file1)){				
					
					if( strcmpi(paciente.apellidoNombre, cadena)  == 0){// hacemos esto para que el profesional ingrese bien el nombre del paciente a atender
						nombreValido = true;// en el caso de cumplirse la condicion en la variable estructura paciente tenemos el paciente a atender
						break;
					}
					
					fread(&paciente, sizeof(Paciente), 1, file1);
				}
			
			
				if(nombreValido == false){
					puts("\n\t\t  El nombre del paciente fue mal ingresado o no existe, intente de nuevo.\n");
				}
		
			}while(nombreValido == false);
		
			fclose(file1);
		
			registarHistorialClinico(paciente,profesional);
			puts("\n\t\t  !!!El paciente se atendio con exito!!!\n");
		}else{
			printf("\n\t\t  No hay turno refistrados para el profesional actual.");
		}
	}
	
	puts("\n\t\tPresione una TECLA para continuar.");
	getch();
		
	usuarioActual = NULL;//Hacemos esto por que la memoria que estan usuando es dinamica y para no tener problemas de que apunten aun cuando ya fue liberada 
	contrasenaActual = NULL;//
	
	system("cls");
}

void atencionesProfesionalFecha(){
	
	system("cls");
	
	NuevoProfesional profesional;
	HistorialClinicoPaciente historia;
	char nombreProfesional[80];
	int dni,cantidadAtenciones = 0;
	
	FILE *arch = fopen("Profesionales.dat","rb");
	
	if(arch == NULL){
		perror("ERROR, al tratar de abrir el archvo Profesionales.dat:");
		exit(1);
	}
	
	int elementos = fread(&profesional, sizeof(NuevoProfesional), 1,arch);
	if(elementos > 0){
	
		while(!feof(arch)){
			printf("\n\t\tProfesional = Nombre %s, Dni: %d", profesional.apelldioNombre,profesional.dniProfesional);
			fread(&profesional, sizeof(NuevoProfesional), 1,arch);
		}
		
		fclose(arch);
		elementos = 0;
	
	
		printf("\n\n\t\tIngrese el DNI del profesional:");// verificamos con el dni ya q es unico, a diferencia del nombre que cada persona puede tener el mismo nombre o no 
		scanf("%i",&dni);
	
		printf("\n\t\tIngrese el nombre del profesional:");
		scanf("%s[^\n]",&nombreProfesional);
		
		system("cls");
	
		FILE* file = fopen("HistorialClinico.dat","rb");
	
		if(file == NULL){
			perror("\n\t\tERROR, al tratar de abrir el archivo HistorialClinico.dat:");
			exit(1);
		}
		
		elementos = fread(&historia, sizeof(HistorialClinicoPaciente),1,file);
		
		if(elementos != 0){
			while(!feof(file)){

				if(historia.dniProfesional == dni){
					cantidadAtenciones++;
					
				}
				fread(&historia, sizeof(HistorialClinicoPaciente),1,file);
		
			}
		
			if(cantidadAtenciones != 0){
				printf("\n\t\tProfesional: %s, atenciones realizadas: %d, fecha de la ultima atencion: %i/%i/%i.", nombreProfesional, cantidadAtenciones,historia._fecha.dia, historia._fecha.mes, historia._fecha.anio);
				
			}
	
		}else{
			puts("\n\t\tNo hay atenciones realizadaz.");
		}
		
		fclose(file);

	}
	
	getch();
	system("cls");
	
}

fecha fechaPaciente(int dniPaciente){
	
	FILE *file = fopen("Turnos.dat","rb");
	
	if(file == NULL){
		perror("ERROR, al abrir el archivo paciente para extraer la fecha de registracion:");
		exit(1);
	}
	Turno turnoFecha;
	fread(&turnoFecha,sizeof(Turno),1,file);

	
	while(!feof(file)){
		
		if(dniPaciente == turnoFecha.dniPaciente){
			fclose(file);
			return turnoFecha.fecha;
		}
		fread(&turnoFecha,sizeof(Turno),1,file);
	}
	
	fecha fechaCasoError;
	fechaCasoError.dia = fechaCasoError.mes = fechaCasoError.anio = 0;
	fclose(file);
	
	return fechaCasoError;
}

static void registarHistorialClinico(Paciente paciente,NuevoProfesional profesional){
	
	HistorialClinicoPaciente historia_clinica;
	int edad;
	fecha fech = hoy();
	
	printf("\n\t\t  Detalles del problema del paciente:\n");
	printf("\n\t\t  %s",paciente.problemaTratar);
	
	printf("\n\n\t\t  Peso del paciente: ");
	scanf("%i",&historia_clinica.peso);
	
	printf("\n\t\t  Talla del paciente(ej:181 que es 1,81 metros, ingrese un numero entero): ");
	scanf("%i",&historia_clinica.talla);
		
	edad = fech.anio - paciente.fechaNacimiento;
	
	strcpy(historia_clinica.apellidoNombre, paciente.apellidoNombre);
	strcpy(historia_clinica.domicilio, paciente.domicilio);	
	strcpy(historia_clinica.apellidoNombreProfesional, profesional.apelldioNombre);
	historia_clinica.dniPaciente = paciente.dniPaciente;
	historia_clinica.edad = edad;
	historia_clinica._fecha = hoy();
	historia_clinica.dniProfesional = profesional.dniProfesional;

	
	FILE* file = fopen("HistorialClinico.dat","ab");
	
	if(file == NULL){
		perror("ERROR,al agregar el historial clinico de un paciente atendido:");
		exit(1);
	}
	fwrite(&historia_clinica, sizeof(HistorialClinicoPaciente), 1,file);
	fflush(file);
	fclose(file);
	
	getch();
	eliminarTurno(paciente);
	eliminarPaciente(paciente);
	
}

static void eliminarTurno(Paciente paciente){
	
	Turno turno, vectorTurnos[80];
	int i = 0,numElementos = 0;
	
	
	FILE* file = fopen("Turnos.dat","rb");
	if(file == NULL){
		perror("ERROR,al agregar al tratar de eliminar el turno:");
		exit(1);
	}
	
	fread(&turno,sizeof(Turno),1,file);
	
	while(!feof(file)){
		
		if(turno.dniPaciente != paciente.dniPaciente){
			vectorTurnos[i] = turno;
			numElementos++;
			i++;
		}
		
		fread(&turno,sizeof(Turno),1,file);
	}
	
	fclose(file);	
	remove("Turnos.dat");
	
	i = 0;
	file = fopen("Turnos.dat","ab");
	
	if(file == NULL){
		perror("ERROR,al agregar al tratar de eliminar el turnO:");
		exit(1);
	}
	
	while( i < numElementos){
		fwrite(&vectorTurnos[i], sizeof(Turno),1,file);
		fflush(file);
		i++;
	}
	
	if(i == numElementos){
		puts("\n\t\t  El paciente ya fue atendido por lo tanto se elimino el turno con exito.");
	}	
	
}

static void eliminarPaciente(Paciente paciente){
	
	Paciente paciente1, vectorPacientes[80];
	int i = 0,numElementos = 0;
	
	FILE* file = fopen("Pacientes.dat","rb");
		
	if(file == NULL){
		perror("ERROR,al agregar al tratar de eliminar el paciente:");
		exit(1);
	}
	
	fread(&paciente1, sizeof(Paciente), 1, file);
		
	while(!feof(file)){
		
		if(paciente1.dniPaciente != paciente.dniPaciente ){
			vectorPacientes[i] = paciente1;
			numElementos++;
			i++;
			getch();
		}

		fread(&paciente1, sizeof(Paciente), 1, file);	
		
	}
	
	fclose(file);	
	i = 0;
	// con esto truncamos el contenido del archivo
	file = fopen("Pacientes.dat","wb");
	fclose(file);
	
	
	file = fopen("Pacientes.dat","ab");
	
	if(file == NULL){
		perror("ERROR,al agregar al tratar de eliminar el pacientE:");
		exit(1);
	}

	
	for(i = 0; i < numElementos; i++){
		fwrite(&vectorPacientes[i], sizeof(Paciente), 1, file);
		fflush(file);
	}
	
	
	if(i == numElementos){
		puts("\n\t\t  El paciente ya fue atendido por lo tanto se lo elimino de la lista de espera con exito.");
	}
	fclose(file);	
		
}






















































