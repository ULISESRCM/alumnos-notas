#include <iostream>
#include <string>
#include <stdio.h>
using namespace std;

#define path_alumnos  "./alumnos.dat"
#define path_materias  "./materias.dat"
#define path_inscripciones  "./inscripciones.dat"

struct t_alumnos
{
	int legajo;
	char nombre[30];
	int antiguedad;
};

struct t_materias
{
	int codigo;
	char nombre_mat[30];
	int capacidad;
};

struct t_inscripciones
{
	int legajo;
	int codigo_mat;
};

struct Nodo
{
	Nodo* sig;
	t_alumnos info_alumno;
};


void Menu();


void generar_archivo_alumnos();
void generar_archivo_materias();


void cargar_vec_alumnos(t_alumnos *vec_alumnos, int &cant_elementos);
void cargar_vec_materias(t_materias *vec_materias, int &cant_materias);
void cargar_vec_inscripcion(t_inscripciones *vec_inscripciones, int &cant_inscripcion);


void buscar_indice_mat(t_materias vec_mat[], int cant_materias, int codigo_buscar, int &indice_mat) ;
void buscar_indice_leg(t_alumnos vec_alumnos[], int cant_alumnos, int legajo_buscar, int &indice_leg);


void analisis_pedidos();


void imprimir_materias();
void imprimir_alumnos();
void imprimir_inscripciones();


void insertar_ordenado(Nodo* &inicio, t_alumnos r_info);
void mostrar_lista(Nodo* inicio);



int main()
{
	int opcion;
	
	Menu();
    cin >> opcion;
	
    while( opcion != 0 )
    {
    	switch (opcion) 
	  	{ 
        	case 1:
            	generar_archivo_alumnos();
            	break;
            
            case 2:
            	generar_archivo_materias();
            	break;
            
            case 3:
            	analisis_pedidos();
				break;
			
			case 4:
				imprimir_alumnos();
				break;
			
			case 5:
				imprimir_materias();
				break;
			
			case 6:
				imprimir_inscripciones();
				break;
				
         	default:
            	system("cls");
            	cout <<"ERROR! La opcion seleccionada es invalida"<<endl;
               	break;
        }
        Menu();
        cin >> opcion;
   	}
	return 0;
}



void Menu()
{
	cout << endl << endl << "------------MENU-------------" << endl;
	cout << "| 0) Salir                               |"<<endl;
	cout << "| 1) Generar Archivo de Alumnos          |"<<endl;
	cout << "| 2) Generar Archivo de Materias         |"<<endl;
	cout << "| 3) Analisis de los pedidos             |"<<endl;
	cout << "| 4) Visualizar archivo de Alumnos       |"<<endl;
	cout << "| 5) Visualizar archivo de Materias      |"<<endl;
	cout << "| 6) Visualizar archivo de Inscripciones |"<<endl;
	cout << "| 0) Salir                               |"<<endl;
	cout << "-----------------------" << endl;
	cout <<"Ingrese la opcion deseada: ";
}



void generar_archivo_alumnos()
{
	t_alumnos r_alumnos;
	t_materias r_materias;

	//Creo los archivos para escrituro
	FILE* file = fopen(path_alumnos, "w+b"); 	
	
   //Primero cargo el archivo de Alumnos
   cout <<endl<<endl <<"-----------------------------------------------" << endl;
   cout << "CARGANDO EL ARCHIVO DE ALUMNOS"<<endl;
   cout << "-----------------------------------------------" << endl;
   
   cout<<"Ingrese su Legajo de Alumno (0 para cortar): ";
   cin>> r_alumnos.legajo;
	
   while (r_alumnos.legajo != 0) //corto cuando el legajo sea 0
   {
      	cout << "Ingrese su Nombre: ";
      	cin >> r_alumnos.nombre;
		
      	cout << "Ingrese su Antiguedad: ";
      	cin >> r_alumnos.antiguedad;

		//Escribo el registro
      	fwrite (&r_alumnos, sizeof(r_alumnos), 1, file);
		
      	cout<<endl<<endl<<"Ingrese su Legajo de Alumno (0 para cortar): ";
   		cin>> r_alumnos.legajo;
	}

   fclose(file);
}

void generar_archivo_materias()
{
	t_materias r_materias;

	//Creo los archivos para escrituro
	FILE* file = fopen(path_materias, "w+b");	
	
	//Segundo cargo el archivo de Materias
	cout <<endl<<endl<< "-----------------------------------------------" << endl;
   	cout << "CARGANDO EL ARCHIVO DE MATERIAS"<<endl;
	cout << "-----------------------------------------------" << endl;
	   
   	cout<<"Ingrese el Codigo de la materia (0 para cortar): ";
   	cin>> r_materias.codigo;
	
   	while (r_materias.codigo != 0) //corto cuando el Codigo sea 0
   	{

    	cout << "Ingrese el Nombre de la materia: ";
      	cin >> r_materias.nombre_mat;
		
      	cout << "Ingrese la Capacidad de la materia: ";
      	cin >> r_materias.capacidad;

		//Escribo el registro
      	fwrite (&r_materias, sizeof(r_materias), 1, file);
		
      	cout<<endl<<"Ingrese su Codigo de la materia (0 para cortar): ";
   		cin>> r_materias.codigo;
	}

   fclose(file);
}



void cargar_vec_alumnos(t_alumnos *vec_alumnos, int &cant_alumnos)
{
	FILE* file = fopen(path_alumnos, "r+b"); //abro el archivo como lectura
   	cant_alumnos = 0;

   	if (file == NULL) 
	{
      	cout << "ERROR! no existe el archivo" << endl;
   	}
   else 
   {
   //Armo un vector cargando cada posicion, cuando no tenga que leer sale del while
		while(  fread( &vec_alumnos[cant_alumnos], sizeof(*vec_alumnos), 1, file)  )
		{	
    		cant_alumnos++; //cunto los elementos
    	}
    	
      	fclose(file);
   }
}

void cargar_vec_materias(t_materias *vec_materias, int &cant_materias)
{
	FILE* file = fopen(path_materias, "r+b"); //abro el archivo como lectura
   	cant_materias = 0;

   	if (file == NULL) 
	{
      	cout << "ERROR! no existe el archivo" << endl;
   	}
   else 
   {
   //Armo un vector cargando cada posicion, cuando no tenga que leer sale del while
		while(  fread( &vec_materias[cant_materias], sizeof(*vec_materias), 1, file)  )
		{	
    		cant_materias++; //cunto los elementos
    	}
    	
      	fclose(file);
   }
}

void cargar_vec_inscripcion(t_inscripciones *vec_inscripciones, int &cant_inscripcion)
{
	FILE* file = fopen(path_inscripciones, "r+b"); //abro el archivo como lectura
   	cant_inscripcion = 0;

   	if (file == NULL) 
	{
      	cout << "ERROR! no existe el archivo" << endl;
   	}
   else 
   {
   		//Armo un vector cargando cada posicion, cuando no tenga que leer sale del while
		while(  fread( &vec_inscripciones[cant_inscripcion], sizeof(*vec_inscripciones), 1, file)  )
		{	
    		cant_inscripcion++; //cuento los elementos
    	}
      	fclose(file);
   }
}



void buscar_indice_mat(t_materias vec_mat[], int cant_materias, int codigo_buscar, int &indice_mat) 
{
   int i;
   indice_mat= -1;
   
   //Recorro el vector y comparo con el dato a buscar
   for (i = 0; i<cant_materias; i++)
	{
      if (vec_mat[i].codigo == codigo_buscar)
	  {
         indice_mat = i;
      }
   }
}

void buscar_indice_leg(t_alumnos vec_alumnos[], int cant_alumnos, int legajo_buscar, int &indice_leg)
{  
	int i;
	
   	indice_leg= -1;
	
	//Recorro el vector y comparo con el dato a buscar
  	for(i = 0; i < cant_alumnos; i++)
	{
      if (vec_alumnos[i].legajo == legajo_buscar)
	  {
         indice_leg = i;
      }
   	}
}	




void analisis_pedidos()
{
	Nodo* lista= NULL; //Variable para la lista
	
	t_alumnos r_alumnos[1000]; 
	t_materias r_materias[40];
	t_materias r_materias_insc[40];
	t_inscripciones r_inscripciones;
	
	t_inscripciones vec_inscripciones[1000]; //lo uso en el punto 3
	
	int cant_alumnos=0, cant_materias=0, cant_inscripcion=0;
	
	int cant_rechazados=0, cant_materias_sin_inscriptos=0, suma_antiguedad=0, cant_promedio=0; 
	
	int codigo_buscar, legajo_buscar, indice_mat, indice_leg;
	
	float promedio_antiguedad;
	
	
	//Abro el archivo de inscripciones para escribir
	FILE* file = fopen(path_inscripciones, "w+b");
	
	
	//Cargo los vectores
	cargar_vec_alumnos(r_alumnos, cant_alumnos);
	cargar_vec_materias(r_materias, cant_materias);
	cargar_vec_materias(r_materias_insc, cant_materias); //lo uso en el punto 2
	
	
	// Empiezo a cargar el archivo de inscripciones
	cout <<endl<<endl<< "-----------------------------------------------" << endl;
   	cout <<"Cargando el archivo de inscripciones"<<endl;
   	cout << "-----------------------------------------------" << endl;
   
   
   	cout<<"Ingrese su Legajo de Alumno (0 para cortar): ";
   	cin>> r_inscripciones.legajo;
   	
   	//Busco el legajo en el vector de alumnos para ver si existe y tener el indice
   	legajo_buscar= r_inscripciones.legajo;
	buscar_indice_leg(r_alumnos, cant_alumnos, legajo_buscar, indice_leg);	
	
	
	//corto cuando el legajo sea 0
   	while (r_inscripciones.legajo != 0) 
   	{
   		
    	if( indice_leg == -1 ) //NO EXISTE EL LEGAJO
    	{
    		cout<<"_________________________________________________________"<<endl;
    		cout<<endl<<endl<<"No existe el legajo, ingrese uno correcto"<<endl<<endl;
    		cout<<"_________________________________________________________"<<endl;
		}
		else
		{
			//EXISTE EL LEGAJO
				
				
			cout << "Ingrese el Codigo de la materia: "; 
      		cin >> r_inscripciones.codigo_mat;
      	
      	
			//Busco si Existe la MATERIA y el INDICE en el vector
      		codigo_buscar= r_inscripciones.codigo_mat;      		
      		buscar_indice_mat(r_materias, cant_materias, codigo_buscar, indice_mat);
		
			
			if( indice_mat == -1 ) //LA MATERIA NO EXISTE
			{
				cout<<"_________________________________________________________";
				cout<<endl<<"No existe la materia, ingrese una correcta "<<endl;
				cout<<"_________________________________________________________"<<endl;
			}
			else
			{
				//LA MATERIA Y EL LEGAJO EXISTEN
				
				//Me fijo si la materia tiene capacidad para inscribirse
				if( r_materias[indice_mat].capacidad > 0)
				{
					//HAY CAPACIDAD PARA INSCRIBIRSE
					
					//Escribo el registro
      				fwrite(&r_inscripciones, sizeof(r_inscripciones), 1, file);
      				
					  //Actualizo la capacidad de la materia
      				r_materias[indice_mat].capacidad -= 1;
					

					cout<<"_________________________________________________________";
					cout<<endl<<endl<<"Usted fue inscrito satisfactoriamente"<<endl<<endl;
					cout<<"_________________________________________________________"<<endl;
					
					
					//Podria mantener el contador para el vector inscripciones en el Punto 3
					//cant_inscripcion++;
		
				}
				else
				{	
					//NO HAY CAPACIDAD PARA INSCRIBIRSE
					cant_rechazados++;	
					
					cout<<"_________________________________________________________";
					cout<<endl<<"No hay capacidad en la materia para inscribirse"<<endl;
					cout<<"_________________________________________________________";
					
					insertar_ordenado(lista, r_alumnos[indice_leg] ); //inserto en una lista
				}
			}
		}
		
		//Analizo el proximo legajo
		cout<<endl<<"Ingrese su Legajo de alumno (0 para cortar): ";
   		cin>> r_inscripciones.legajo;
   			
   		legajo_buscar= r_inscripciones.legajo;
		buscar_indice_leg(r_alumnos, cant_alumnos, legajo_buscar, indice_leg);	
	}
	
	fclose(file);
	
	cout<<endl<<"_______________________________________________"<<endl;
	cout<<endl<<"Imprimiendo la LISTA de los Rechazados";
	cout<<endl<<"_______________________________________________"<<endl;
	
	mostrar_lista(lista); //Imprimo la lista
	
	cout<<endl<<"_______________________________________________"<<endl;
	cout<<endl<<"_______________________________________________"<<endl;
	
	//1) CANTIDAD DE RECHAZADOS
	cout<<endl<<"_______________________________________________"<<endl;
	cout<<endl<<"_______________________________________________"<<endl;
	
	cout<<endl<<endl<<"1) Cantidad de Cupos rechazados: "<<cant_rechazados<<endl;
	
	cout<<endl<<"_______________________________________________"<<endl;
	cout<<endl<<"_______________________________________________"<<endl;
	
	
	//2) CANTIDAD DE MATERIAS SIN INSCRIPCIONES
	
	//Recorro las materias y me fijo si tienen la misma capacidad con la que ingresaron
	for(int i=0; i < cant_materias ; i++)
	{
		if( r_materias[i].capacidad == r_materias_insc[i].capacidad )
		{
			cant_materias_sin_inscriptos++;
		}
	}
	cout<<endl<<endl<<"2) Cantidad de materias sin inscripciones: "<<cant_materias_sin_inscriptos<<endl;
	
	cout<<endl<<"_______________________________________________"<<endl;
	cout<<endl<<"_______________________________________________"<<endl;
	
	
	//3) Por cada materia, promedio de antigüedad de alumnos inscriptos en ella.
	
	cargar_vec_inscripcion(vec_inscripciones, cant_inscripcion); //En realidad ya tengo la cantidad
	
	cout<<"\n\n3) Imprimo por materia el promedio de antiguedad de lo inscriptos "<<endl<<endl;
	
	//Recorro cada materia
	for(int i_materia = 0; i_materia < cant_materias ; i_materia++)
	{	
		//Recorro cada inscripcion
		for(int j_insc = 0; j_insc < cant_inscripcion ; j_insc++)
		{	
		
			//Si un codigo de la inscripcion coincide
			if( r_materias[i_materia].codigo == vec_inscripciones[j_insc].codigo_mat )
			{
			
			
				//Tengo que relacionar el legajo de Inscripcion con el de Alumnos
				legajo_buscar= vec_inscripciones[j_insc].legajo;
				buscar_indice_leg(r_alumnos, cant_alumnos, legajo_buscar, indice_leg);
				
				//Sumo para los calculos
				suma_antiguedad += r_alumnos[indice_leg].antiguedad;
				cant_promedio++;
				
			
			}
		}
		
		//Aca ya termino de Analizar una materia completa, asique imprimo
		promedio_antiguedad= (suma_antiguedad /cant_promedio);
		
		cout<<endl<<endl<<" Codigo de la Materia: "<<r_materias[i_materia].codigo;
		cout<<endl<<" Promedio de Antiguedad: "<<promedio_antiguedad;
		
		//Reinicio
		suma_antiguedad=0;
		cant_promedio=0;
		
	}
	cout<<endl<<"_______________________________________________"<<endl;
	cout<<endl<<"_______________________________________________"<<endl;
	
	
}




void insertar_ordenado(Nodo* &inicio, t_alumnos r_info)
{
	Nodo* nuevo_nodo= new Nodo(); // creo un nodo apuntando a NULL
	
	
	nuevo_nodo -> info_alumno = r_info; //Asigno la info al nodo A AGREGAR
		
	
	Nodo* aux1= inicio;	//Como lista empieza en NULL, aux1=NULL
	Nodo* aux2;
	
	
	//Es un while para tener Ordenada la lista
	while(  (aux1 != NULL)  &&  (aux1->info_alumno.antiguedad < r_info.antiguedad) )
	{	
		aux2 = aux1;	//No se inserta al principio
		aux1= aux1 -> sig;	//Busco la posicion a agregar
	}
	
	
	//Se cumple si insertamos al principio de la lista
	if( inicio == aux1 )
	{
		inicio = nuevo_nodo;	//Copio el nodo nuevo al inicio de la lista y es el nuevo inicio
		nuevo_nodo -> sig= aux1;	//y el siguiente es donde "estaba el inicio"
	}
	
	else
	{
		//Entonces entro al While y inserta adelante
		
		aux2 -> sig = nuevo_nodo;	//Inserto el nuevo_nodo Adelante de aux2
		nuevo_nodo -> sig= aux1;	//El que sigue al nuevo_nodo es aux1
	}
	
}

void mostrar_lista(Nodo* inicio)
{
	Nodo* actual= new Nodo();

	actual= inicio;
	
	cout<<endl<<"IMPRIMIENDO LA LISTA"<<endl<<endl;
	
	while( actual != NULL)
	{
		cout<<"Legajo: "<<actual->info_alumno.legajo<<endl;
		cout<<"Nombre: "<<actual->info_alumno.nombre<<endl;
		cout<<"Antiguedad: "<<actual->info_alumno.antiguedad<<endl<<endl;
		
		actual= actual->sig;
	}
}





void imprimir_alumnos()
{
	t_alumnos r_alumno;
	
	FILE* file= fopen(path_alumnos, "r+b");
	
	fread(&r_alumno, sizeof(r_alumno), 1, file);
	
	cout<<"\n\n IMPRIMIENDO ARCHIVO DE ALUMNOS "<<endl;
	
	while( !feof(file) )
	{
		cout<<"Legajo: "<<r_alumno.legajo<<endl;
		cout<<"Nombre: "<<r_alumno.nombre<<endl;
		cout<<"Antiguedad: "<<r_alumno.antiguedad<<endl<<endl;
		
		fread(&r_alumno, sizeof(r_alumno), 1, file);
	}
	
	fclose(file);
}
	
void imprimir_materias()
{
	t_materias r_materia;
	
	FILE* file= fopen(path_materias, "r+b");
	
	fread(&r_materia, sizeof(r_materia), 1, file);
	
	cout<<endl<<endl<<"IMPRIMIENTO ARCHIVO DE MATERIAS";
	cout<<"------------------------"<<endl;
	
	while( !feof(file) )
	{
		cout<<"Codigo: "<<r_materia.codigo<<endl;
		cout<<"Nombre: "<<r_materia.nombre_mat<<endl;
		cout<<"Capacidad: "<<r_materia.capacidad<<endl<<endl;
		
		fread(&r_materia, sizeof(r_materia), 1, file);
	}
	
	fclose(file);
}

void imprimir_inscripciones()
{
	t_inscripciones r_inscripciones;
	
	FILE* file= fopen(path_inscripciones, "r+b");
	
	fread(&r_inscripciones, sizeof(r_inscripciones), 1, file);
	
	cout<<endl<<endl<<"IMPRIMIENTO ARCHIVO DE INSCRIPCIONES";
	cout<<"------------------------"<<endl;
	
	while( !feof(file) )
	{
		cout<<"Codigo: "<<r_inscripciones.legajo<<endl;
		cout<<"Nombre: "<<r_inscripciones.codigo_mat<<endl<<endl;

		
		fread(&r_inscripciones, sizeof(r_inscripciones), 1, file);
	}
	
	fclose(file);
}
	


