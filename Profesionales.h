#ifndef PROFESIONALES_H_INCLUDED  // Directiva de preprocesador para evitar inclusiones múltiples
#define PROFESIOMALES_H_INCLUDED

#include "Usuario.h"
#include "Pacientes.h"

void listarPacientes();
void listarhistorialClinico();
void atenderPacienteConTuno();
void atencionesPorProfesional();
void ranking_profesionales();
void atencionesProfesionalFecha();

typedef struct profesional{
	char apelldioNombre[80];
	int idProfesional;
	int dniProfesional;
	int telefono;
	char areaProfesional[80];
	user profesionalData;
}NuevoProfesional;

typedef struct {
	char apellidoNombre[80];
	char apellidoNombreProfesional[80];
	char domicilio[80];
	int dniPaciente;
	int dniProfesional;
	fecha _fecha;
	int edad;
	int peso;
	int talla;
}HistorialClinicoPaciente;


#endif 
