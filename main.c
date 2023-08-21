#include <stdio.h>
#include <stdlib.h>
#include "Envio.h"

int main()
{
    printf("Hello world!\n");

    // TEST
    Envio prueba;
    Envio_init(&prueba);

    printf("%s\n%u\n%s\n%s\n%u\n%s\n%s\n%s\n\n",
           Envio_get_codigo_envio(&prueba),
           Envio_get_dni_receptor(&prueba),
           Envio_get_nombre_apellido_receptor(&prueba),
           Envio_get_domicilio_receptor(&prueba),
           Envio_get_dni_remitente(&prueba),
           Envio_get_nombre_apellido_remitente(&prueba),
           Envio_get_fecha_envio(&prueba),
           Envio_get_fecha_recepcion(&prueba)
           );

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
