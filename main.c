#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

typedef struct
{
  char nombre[101];
  char tipo[101];
  char direccion[101];
  char horario[101];
  char descripcion[101];
} Punto;

typedef struct LugarFavorito
{
  char nombre[101];
  struct LugarFavorito *siguiente;
} LugarFavorito;

typedef struct
{
  char pasaporte[101];
  char nombre[101];
  char pais[101];
  LugarFavorito *lugares_fav;
} Turista;

typedef struct
{
  Punto *datos[101];
  int cantidad;
} ListaPuntos;

typedef struct 
{
    char clave[101];
    void *valor;
} ParClaveValor;

typedef struct 
{
    ParClaveValor pares[101];
    int cantidad;
} Map;

typedef struct 
{
    void *elementos[101];
    int cantidad;
    int indice_actual;
} List;

Map* crearMapa() 
{
    Map *mapa = malloc(sizeof(Map));
    if (mapa == NULL) 
    {
        exit(1);
    }
    mapa->cantidad = 0;
    return mapa;
}

List* createList() 
{
    List *lista = malloc(sizeof(List));
    if (lista == NULL) 
    {
        exit(1);
    }
    lista->cantidad = 0;
    lista->indice_actual = -1;
    return lista;
}

//Función para insertar un par clave-valor en el mapa, primero el caso en el que ya está para sobreescribir, y luego en el que no esta para insertarlo como nuevo mantiendo un límite de 100.
void insertar(Map *mapa, const char *clave, void *valor) 
{
    for (int i = 0; i < mapa->cantidad; i++) 
    {
        if (strcmp(mapa->pares[i].clave, clave) == 0) 
        {
            mapa->pares[i].valor = valor;
            return;
        }
    }

    if (mapa->cantidad < 100) 
    {
        strcpy(mapa->pares[mapa->cantidad].clave, clave);
        mapa->pares[mapa->cantidad].valor = valor;
        mapa->cantidad++;
    } 
    else 
    {
        printf("El mapa está lleno. No se pueden agregar más elementos.\n");
    }
}

int tamanno(const Map *mapa) 
{
    return mapa->cantidad;
}

//Con esta función buscamos un valor en el mapa a través de una clave (nombre)
void *buscar(const Map *mapa, const char *clave)
{
  for (int i = 0 ; i < mapa->cantidad ; i++)
    {
      if (strcmp(mapa->pares[i].clave, clave) == 0)
      {
        return mapa->pares[i].valor;
      }
    }
  return NULL;
}

//Función para registrar un punto en la que se piden los datos correspondientes del struct, la luego llamar a la función insertar, la cuál decidirá la forma en la que se trabajen las entradas.
void registrarPuntoDeInteres(Map *mapa_puntos) 
{
    if (tamanno(mapa_puntos) >= 100) 
    {
        printf("El mapa de puntos de interés está lleno. No se pueden agregar más lugares.\n");
        return;
    }

    Punto nuevo_punto;

    printf("Ingrese el nombre del punto de interés: ");
    scanf("%s", nuevo_punto.nombre);

    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    printf("Ingrese el tipo del punto de interés: ");
    scanf("%s", nuevo_punto.tipo);

    while ((c = getchar()) != '\n' && c != EOF);

    printf("Ingrese la dirección del punto de interés: ");
    scanf("%s", nuevo_punto.direccion);

    while ((c = getchar()) != '\n' && c != EOF);

    printf("Ingrese el horario del punto de interés: ");
    fgets(nuevo_punto.horario, sizeof(nuevo_punto.horario), stdin);

    size_t len = strlen(nuevo_punto.horario);
    if (len > 0 && nuevo_punto.horario[len - 1] == '\n') 
    {
        nuevo_punto.horario[len - 1] = '\0';
    }

    printf("Ingrese la descripción del punto de interés: ");
    fgets(nuevo_punto.descripcion, sizeof(nuevo_punto.descripcion), stdin);

    len = strlen(nuevo_punto.descripcion);
    if (len > 0 && nuevo_punto.descripcion[len - 1] == '\n') 
    {
        nuevo_punto.descripcion[len - 1] = '\0';
    }

    insertar(mapa_puntos, nuevo_punto.nombre, &nuevo_punto);

    printf("Punto de interés registrado con éxito.\n");
}

//Función para mostrar los datos del punto, en la que llamamos a la función buscar para 
void mostrarDatosPuntoDeInteres(const Map *mapa_puntos, const char *nombre) 
{
  Punto *punto = (Punto *) buscar (mapa_puntos, nombre);
        
  if (punto != NULL) 
  {
    printf("Nombre: %s\n", punto->nombre);
    printf("Tipo: %s\n", punto->tipo);
    printf("Dirección: %s\n", punto->direccion);
    printf("Horario: %s\n", punto->horario);
    printf("Descripción: %s\n", punto->descripcion);
  }
  else
  {
    printf("No se encontró un punto de interés con el nombre '%s'.\n", nombre);
  }
}

//Función para eliminar el punto dado su nombre recorriendo el mapa hasta encontrar coincidencia. Si ya está, se borra el punto y se disminuye el tamaño del mapa, si no está, imprime la linea correspondiente.
void eliminarPuntoDeInteres(Map *mapa_puntos, const char *nombre) 
{
    int encontrado = 0;
    for (int i = 0; i < mapa_puntos->cantidad; i++) 
    {
        Punto *punto = (Punto *)mapa_puntos->pares[i].valor;
        if (strcmp(punto->nombre, nombre) == 0) 
        {
            for (int j = i; j < mapa_puntos->cantidad - 1; j++) 
            {
                mapa_puntos->pares[j] = mapa_puntos->pares[j + 1];
            }
            mapa_puntos->cantidad--;
            encontrado = 1;
            printf("Punto de interés '%s' eliminado con éxito.\n", nombre);
            break;
        }
    }

    if (!encontrado)
    {
        printf("No se encontró un punto de interés con el nombre '%s'.\n", nombre);
    }
}

//Función para trabajar el mapa de turistas tal como la de registrar punto, se piden los datos, y se llama a la función insertar.
void registrarTurista(Map *mapaTuristas) 
{
    if (tamanno(mapaTuristas) >= 100) 
    {
        printf("El mapa de turistas está lleno. No se pueden agregar más turistas.\n");
        return;
    }

    Turista *nuevoTurista = malloc(sizeof(Turista));
    if (nuevoTurista == NULL) 
    {
        printf("Error al asignar memoria para el nuevo turista.\n");
        return;
    }

    printf("Ingrese el número de pasaporte del turista: ");
    scanf("%s", nuevoTurista->pasaporte);
    printf("Ingrese el nombre del turista: ");
    scanf("%s", nuevoTurista->nombre);
    printf("Ingrese el país del turista: ");
    scanf("%s", nuevoTurista->pais);

    char clave[101];
    strcpy(clave, nuevoTurista->pasaporte);
    insertar(mapaTuristas, clave, nuevoTurista);

    printf("Turista registrado con éxito.\n");
}

void agregarLugarFavoritoATurista(Map *mapa_turistas, const char *pasaporte, const char *nombre_lugar) 
{
  Turista *turista = buscar(mapa_turistas, pasaporte);
  
  if (turista != NULL) 
  {
    strcat(turista->lugares_fav, ";");
    strcat(turista->lugares_fav, nombre_lugar);
    printf("Lugar favorito '%s' agregado al turista con pasaporte '%s'.\n", nombre_lugar, pasaporte);
  }
  else
  {
    printf("No se encontró un turista con el pasaporte '%s'. No se pudo agregar el lugar favorito.\n", pasaporte);
  }
}

//Dado un nombre de país, se recorre el mapa de turistas mostrando a todos los turistas del páis con sus datos, y separando a cada uno de los turistas por una línea de "-". Esta función trabaja con una lista de lugares favoritos para cada turista.
void mostrarTuristasPorPais(const Map *mapa_turistas, const char *pais) 
{
    printf("Turistas de %s:\n", pais);
    for (int i = 0; i < mapa_turistas->cantidad; i++) 
    {
        Turista *turista = (Turista *)mapa_turistas->pares[i].valor;
        if (strcmp(turista->pais, pais) == 0) 
        {
            printf("Número de pasaporte: %s\n", turista->pasaporte);
            printf("Nombre: %s\n", turista->nombre);
            printf("Lugares favoritos:\n");
            
            LugarFavorito *lugar_fav_actual = turista->lugares_fav;
            while (lugar_fav_actual != NULL) 
            {
                printf("%s\n", lugar_fav_actual->nombre);
                lugar_fav_actual = lugar_fav_actual->siguiente;
            }
            
            printf("-----------------------\n");
        }
    }
}

//Dado una entrada para el tipo, se recorre el mapa y se obtienen todos los del tipo correspondiente, mostrando todos los datos del struct y separado los puntos por una linea de "-".
void mostrarPuntosDeInteresPorTipo(const Map *mapa_puntos, const char *tipo) 
{
    printf("Puntos de interés de tipo %s:\n", tipo);

    for (int i = 0; i < mapa_puntos->cantidad; i++) 
    {
        Punto *punto = (Punto *)mapa_puntos->pares[i].valor;
        if (strcmp(punto->tipo, tipo) == 0) 
        {
            printf("Nombre: %s\n", punto->nombre);
            printf("Tipo: %s\n", punto->tipo);
            printf("Dirección: %s\n", punto->direccion);
            printf("Horario: %s\n", punto->horario);
            printf("Descripción: %s\n", punto->descripcion);
            printf("-----------------------\n");
        }
    }
}

//Con un nombre, se crea una lista de lugares favoritos.
LugarFavorito *crearLugarFavorito(const char *nombre) 
{
  LugarFavorito *nuevoLugar = malloc(sizeof(LugarFavorito)); //Se reserva memoria para poder crear el lugar favorito.
  if (nuevoLugar == NULL)
  { 
    exit(1); //Si no se logra reservar la memoria, termina la ejecución del programa.
  }
  strcpy(nuevoLugar->nombre, nombre);
  nuevoLugar->siguiente = NULL;
  return nuevoLugar;
}

void agregarLugarFavorito(Turista *turista, const char *nombre_lugar)
{ //Función agregarLugarFavorito recibe como argumento el puntero *turista y se busca agregar al mapa un lugar favorito de este. Con la función crearLugarFavorito y el argumento que recibe (nombre_lugar), se crea nuevoLugar, el cual se agrega a turista->lugares_fav.

  LugarFavorito *nuevoLugar = crearLugarFavorito(nombre_lugar);
  nuevoLugar->siguiente = turista->lugares_fav;
  turista->lugares_fav = nuevoLugar;
}

void mostrarLugaresFavoritos(const Turista *turista)
{ // Función mostrarLugaresFavoritos recibe como argumento el puntero *turista y se busca imprimir los lugares favoritos de este. Se ocupa un bucle while para iterar dentro del mapa, y con el puntero actual se imprime los lugares y avanza al siguiente elemento hasta llegar a un nodo NULL

    printf("Lugares favoritos del turista:\n");
    LugarFavorito *actual = turista->lugares_fav;
    while (actual != NULL)
    {
        printf("%s\n", actual->nombre);
        actual = actual->siguiente;
    }
}


int main() 
{
    Map *mapaPuntos = crearMapa();
    Map *mapaTuristas = crearMapa();
    
    int opcion;
    do {
        printf("\nMenú Principal\n");
        printf("1. Registrar punto de interés\n");
        printf("2. Mostrar datos de punto de interés\n");
        printf("3. Eliminar punto de interés\n");
        printf("4. Registrar turista\n");
        printf("5. Agregar lugar favorito a turista\n");
        printf("6. Mostrar turistas por país\n");
        printf("7. Mostrar puntos de interés por tipo\n");
        printf("0. Salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                registrarPuntoDeInteres(mapaPuntos);
                break;
            case 2:
                {
                    char nombre[101];
                    printf("Ingrese el nombre del punto de interés: ");
                    scanf("%s", nombre);
                    mostrarDatosPuntoDeInteres(mapaPuntos, nombre);
                }
                break;
            case 3:
                {
                    char nombre[101];
                    printf("Ingrese el nombre del punto de interés a eliminar: ");
                    scanf("%s", nombre);
                    eliminarPuntoDeInteres(mapaPuntos, nombre);
                }
                break;
            case 4:
                registrarTurista(mapaTuristas);
                break;
            case 5:
                {
                    char pasaporte[101];
                    char nombreLugar[101];
                    printf("Ingrese el pasaporte del turista: ");
                    scanf("%s", pasaporte);
                    printf("Ingrese el nombre del lugar favorito: ");
                    scanf("%s", nombreLugar);
                    Turista *turista = buscar(mapaTuristas, pasaporte);
                    if (turista != NULL)
                    {
                      agregarLugarFavorito(turista, nombreLugar);
                      printf("Lugar favorito añadido con éxito.\n");
                    }
                    else
                    {
                      printf("No se encontró un turista con el pasaporte '%s'. No se pudo agregar el lugar favorito.\n", pasaporte);
                    }
                }
                break;
            case 6:
                {
                    char pais[101];
                    printf("Ingrese el país para mostrar turistas: ");
                    scanf("%s", pais);
                    mostrarTuristasPorPais(mapaTuristas, pais);
                }
                break;
            case 7:
                {
                    char tipo[101];
                    printf("Ingrese el tipo para mostrar puntos de interés: ");
                    scanf("%s", tipo);
                    mostrarPuntosDeInteresPorTipo(mapaPuntos, tipo);
                }
                break;
            case 0:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 0);

    for (int i = 0; i < mapaPuntos->cantidad; i++) 
    {
        free(mapaPuntos->pares[i].valor);
    }
    free(mapaPuntos);
    
    for (int i = 0; i < mapaTuristas->cantidad; i++) 
    {
        free(mapaTuristas->pares[i].valor);
    }
    free(mapaTuristas);

    return 0;
}
