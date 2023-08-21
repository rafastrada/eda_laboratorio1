#include <stdio.h>
#include <stdlib.h>
#include "Envio.h"
#include "ListaSO.h"


// --- CADENAS GLOBALES
#define PANTALLA_BARRA "-----------------------------------------------------------------------\n"
#define PANTALLA_PRINCIPAL_OPERACIONES "\
1. Buscar un Envio por su codigo\n\
2. Agregar un nuevo Envio\n\
3. Cargar Envios desde el archivo \"Envios.txt\"\n\
4. Salir del programa\n"



int main()
{
    // Declaracion e inicializacion de la estructura LISTA
    Lista lista_envios; Lista_init(&lista_envios);

    // INICIO DEL PROGRAMA
    int seleccion_usuario = -1; // variable para guardar la opcion elegida por usuario
    do {
        system("cls");  // limpa la pantalla

        printf("%sEL REVOLEO\tAdministracion de envios\n%s"
               "MENU PRINCIPAL\nElija una operacion:\n\n"
               "%s\n"
               ">> ",
               PANTALLA_BARRA,PANTALLA_BARRA,
               PANTALLA_PRINCIPAL_OPERACIONES);

        // Se captura la opcion ingresada por el usuario
        fflush(stdin); scanf("%d",&seleccion_usuario);

        // ACA OPERACIONES

    } while (seleccion_usuario != 4);


    return 0;
}

/*void a_mayuscula(Envio dato){
    int i, largo;
    largo = strlen(dato->);
    for (i = 0; i < largo; i++){
        nombre[i] = toupper(nombre[i]);
    }
}

//memorizacion previa
//tipo_orden es la forma de la estructura

enum Memorizacion_previa {ERROR_DE_FICHERO, ERROR_NO_EXISTE};
/*int Memorizacion_previa(Lista *lista, int *cant_repetidos, int *cargados, int tipo_orden){
    FILE *fichero;
    int resultado_alta = 1, repetidos = 0, indice = 0;
    Envio nuevo;
    fichero = fopen("Envios.txt","r");
    if (fichero == NULL)
        return ERROR_DE_FICHERO;
    else {
        while(!feof(fichero)){
            fscanf(fichero,"%s",nuevo->codigo_envio);
            fscanf(fichero,"%d",&nuevo->dni_receptor);
            fscanf(fichero," %[^\n]",nuevo->nombre_apellido_receptor);
            fscanf(fichero," %[^\n]",nuevo->domicilio_receptor);
            fscanf(fichero,"%d",&nuevo->dni_remitente);
            fscanf(fichero," %[^\n]",nuevo->nombre_apellido_remitente);
            fscanf(fichero,"%s",nuevo->fecha_envio);
            fscanf(fichero,"%s",nuevo->fecha_receptcion);
            a_mayuscula(nuevo);
            if(tipo_orden == 1)
                resultado_alta = alta_lso(lista, nuevo);
            else
                resultado_alta = alta_lsobb(lista, nuevo);
            if (resultado_alta == -1){
                fclose(fichero);
                break;
            }
            if (resultado_alta == 0){
                repetidos ++;
            }
            indice ++;
        }
    }

    *cargados = indice;
    *cant_repetidos = repetidos;
    fclose(fichero);

    if(resultado_alta == -1){
        return 0;
    }
    return 1;
}*/
