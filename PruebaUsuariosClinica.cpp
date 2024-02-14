#include <stdio.h>
#include <string.h>

typedef struct usuario{
	char usuario[80];
	char contrasena[80];
	char nombreApellido[80];
}user;

typedef struct profesional{
	char apelldioNombre[80];
	int idProfesional;
	int dniProfesional;
	int telefono;
	char areaProfesional[80];
	user profesionalData;
}NuevoProfesional;


int main(){
	
	NuevoProfesional profesional1;	
    strcpy(profesional1.profesionalData.usuario, "marIO852");
    strcpy(profesional1.profesionalData.contrasena, "maRIo123");
    strcpy(profesional1.profesionalData.nombreApellido,"Mario bustos");
    strcpy(profesional1.apelldioNombre, profesional1.profesionalData.nombreApellido);
    strcpy(profesional1.areaProfesional,"Traumatologia");
    profesional1.dniProfesional = 41321654;
	profesional1.idProfesional = 1;
	profesional1.telefono = 381235689;
	
	FILE* file;
	file = fopen("Profesionales.dat","wb");
	
	if(file == NULL){
		perror("ERROR al crear el archvo profesionales.dat:");
		return 1;
	}
	
	fwrite(&profesional1,sizeof(NuevoProfesional),1,file);
	fflush(file);
	fclose(file);
	//pedRO78

	
	
	user usuario3;
    strcpy(usuario3.usuario, "jPErez321");
    strcpy(usuario3.contrasena, "juANperez123");
    strcpy(usuario3.nombreApellido,"Juan Perez");
    
    file = fopen("Admin.dat","wb");
	
	if(file == NULL){
		perror("ERROR al crear el archvo Admin.dat:");
		return 1;
	}
	fwrite(&usuario3,sizeof(user),1,file);
	fflush(file);
	fclose(file);
	
    
    
	
	
	
	return 0;
}
