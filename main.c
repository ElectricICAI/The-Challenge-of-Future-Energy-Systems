#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 20
//estructuras
typedef struct{
	int codigo;
	float ingresos;
	int hijos;
}T_EMPLEADO;
//funciones
int Contar(FILE *pf);
void Copiar(FILE *pf,T_EMPLEADO v[],int n);
void RellenarHijos(FILE *pf,T_EMPLEADO v[],int n);
void MostrarYCrearBinarios(T_EMPLEADO v[],int n,char *nombre_archivo);
int Buscar(int codigo,T_EMPLEADO *emp, char *nombre_archivo);
void Actualizar(int posicion,T_EMPLEADO *emp,char *nombre_archivo);
int main(int argc, char **argv)
{
	FILE *pf;
	FILE*pf2;
	int num_empleados;
	T_EMPLEADO *v;
	T_EMPLEADO emp;
	char nombre[N];
	int pos,codigo;
	
	pf=fopen("empleados.txt","w+");
	if(pf==NULL){
		printf("Error al abrir el fichero");
	}else{
		num_empleados=Contar(pf);
		v=(T_EMPLEADO*)calloc(num_empleados,sizeof(T_EMPLEADO));
		if(v==NULL){
			printf("Error al abrir el fichero");
		}else{
			pf2=fopen("hijos.txt","r");
			if(pf2==NULL){
				printf("Error al abrir el fichero");
			}else{
				Copiar(pf,v,num_empleados);
				RellenarHijos(pf2,v,num_empleados);
				printf("Introduzca el nombre del archivo binario: ");
				fflush(stdin);
				fgets(nombre,N,stdin);
				if(nombre[strlen(nombre)-1]=='\n'){
					nombre[strlen(nombre)-1]='\0';
				}
				
				MostrarYCrearBinarios(v,num_empleados,nombre);
				printf("Introduzca el codigo que desea buscar: ");
				scanf("%d",&codigo);
				pos=Buscar(codigo,&emp,nombre);
				if(pos==-1){
					printf("\nNo se ha encontrado ningun empleado con dicho codigo");
				}else{
					printf("\nCodigo %d",emp.codigo);
					printf("\nIngresos: %f",emp.ingresos);
					printf("\nHijos: %d",emp.hijos);
				}
				Actualizar(pos,&emp,nombre);
				}
			}
		}
	//if(){...}else{...};
	fclose(pf);
	fclose(pf2);
	free(v);
	return 0;
}
int Contar(FILE *pf){
	T_EMPLEADO l;
	int crtl;
	int i;
	do{
		crtl=fscanf(pf,"%d %f %d",&l.codigo,&l.ingresos,&l.hijos);
		if(crtl==3){
			i++;
		}
	}while(crtl==3);
	return i;
}
void Copiar(FILE *pf,T_EMPLEADO v[],int n){
	
	rewind(pf);
	int i,crtl;
	i=0;
	do{
		crtl = fscanf(pf,"%d %f %d",&v[i].codigo,&v[i].ingresos,&v[i].hijos);
		if(crtl==3){
			i++;
		}
	}while(crtl==3);
	
	return;
}
void RellenarHijos(FILE *pf,T_EMPLEADO v[],int n){
	
	rewind(pf);
	int i,crtl;
	int codigo;
	int hijos;
	for(i=0;i<n;i++){
		do{
			crtl=fscanf(pf,"%d %d",&codigo,&hijos);
			if(crtl==2){
				if(v[i].codigo==codigo){
					v[i].hijos=hijos;
					crtl=3;
				}
			}
		}while(crtl==2);
	}
	return;
}
void MostrarYCrearBinarios(T_EMPLEADO v[],int n,char *nombre_archivo){
	
	int i;
	FILE*pf;
	pf=fopen(nombre_archivo,"w+");
	if(pf==NULL){
		printf("Error");
	}else{
		for(i=0;i<n;i++){
			fwrite(&v[i],sizeof(T_EMPLEADO),1,pf);
			if(v[i].hijos>3){
				printf("\nCodigo: %d",v[i].codigo);
				printf("\nIngresos: %f",v[i].ingresos);
				printf("\nHijos: %d",v[i].hijos);
			}
		}
	}
	fclose(pf);
	return;
}
int Buscar(int codigo,T_EMPLEADO *emp, char *nombre_archivo){
	
	int i,crtl;
	T_EMPLEADO l;
	FILE *pf;
	
	pf=fopen(nombre_archivo,"r");
	if(pf==NULL){
		printf("Error");
	}else{
		i=-1;
		do{
			crtl=fread(&l,sizeof(T_EMPLEADO),1,pf);
			if(crtl==1){
				i++;
				if(codigo==l.codigo){
					emp->codigo=l.codigo;
					emp->ingresos=l.ingresos;
					emp->hijos=l.hijos;
				}
			}
			
		}while(crtl==1);
	}
	fclose(pf);
	return i;
}
void Actualizar(int posicion,T_EMPLEADO *emp,char *nombre_archivo){
	
	
	T_EMPLEADO l;
	FILE *pf;
	pf=fopen(nombre_archivo,"w+");
	rewind(pf);
	if(pf==NULL){
		printf("Error");
	}else{
		printf("Introduzca el nuevo codigo: ");
		scanf("%d",&l.codigo);
		printf("Introduzca nuevos Ingresos: ");
		scanf("%f",&l.ingresos);
		printf("Introduzca nuevo numero de hijos: ");
		scanf("%d",&l.hijos);
		fseek(pf,posicion*sizeof(T_EMPLEADO),SEEK_SET);
		fwrite(&l,sizeof(T_EMPLEADO),1,pf);
		emp->codigo=l.codigo;
		emp->ingresos=l.ingresos;
		emp->hijos=l.hijos;
	}
	fclose(pf);
	return;
}