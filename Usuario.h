#ifndef USUARIO_H_INCLUDED  // Directiva de preprocesador para evitar inclusiones múltiples
#define USUARIO_H_INCLUDED

int verificarExistenciaUsuarioProfesional(char usuario[80],char contrasena[80]);
int verificarExistenciaUsuarioRecepcionista(char usuario[80],char contrasena[80]);
int verificarExistenciaUsuarioAdmin(char usuario[80],char contrasena[80]);
void liberarMemoria();
char* obtenerUsuarioActual();
char* obtenerContrasenaActual();
void crearRecpcionista();
void crearProfesional();

typedef struct usuario{
	char usuario[80];
	char contrasena[80];
	char nombreApellido[80];
	
}user;

#endif 
