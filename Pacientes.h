#ifndef PACIENTES_H_INCLUDED  // Directiva de preprocesador para evitar inclusiones múltiples
#define PACIENTES_H_INCLUDED

void registrar_paciente();
void registrar_turno();


typedef struct Paciente{	
	char apellidoNombre[80];
	char domicilio[80];
	int dniPaciente;
	int fechaNacimiento;
	char localidad[80];
	char telefono[25];	
	char areaTratar[80];
	char problemaTratar[380];
	
}Paciente;

typedef struct fecha{
	int dia;
	int mes;
	int anio;
}fecha;

typedef struct Turno{
	int idProfesional;
	fecha fecha;
	int dniPaciente;
	char detallesAtencion[380];	
}Turno;

fecha hoy(void);

#endif 
