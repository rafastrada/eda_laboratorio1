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


// --- DEFINICION DE MACROS
// controla si una variable tipo 'char' es distinta de 's' y 'n' (util para entradas de tipo SI o NO)
#define entradaDistintaSino(X) ((X) != 's' && (X) != 'n')
// impresion de un envio en el formato por defecto (debe recibir un ENVIO por valor, NO puntero)
#define imprimirEnvio(E) printf("Codigo de Envio:\t\t\t%s\n"\
                                 "DNI del Receptor:\t\t\t%u\n"\
                                 "Nombre y Apellido del Receptor:\t\t%s\n"\
                                 "Domicilio del Receptor:\t\t\t%s\n"\
                                 "DNI del Remitente:\t\t\t%u\n"\
                                 "Nombre y Apellido del Remitente:\t%s\n"\
                                 "Fecha de Envio:\t\t\t\t%s\n"\
                                 "Fecha de Recepcion:\t\t\t%s\n",\
                                 (E).codigo_envio,(E).dni_receptor,\
                                 (E).nombre_apellido_receptor,(E).domicilio_receptor,\
                                 (E).dni_remitente,(E).nombre_apellido_remitente,\
                                 (E).fecha_envio,(E).fecha_recepcion);

int main()
{
    // Declaracion e inicializacion de la estructura LISTA
    Lista lista_envios; Lista_init(&lista_envios);

    // INICIO DEL PROGRAMA
    char seleccion_usuario_menu_principal = ' '; // variable para guardar la opcion elegida por usuario
    do {
        system("cls");  // limpa la pantalla

        printf("%sEL REVOLEO\tAdministracion de envios\n%s"
               "MENU PRINCIPAL\nElija una operacion:\n\n"
               "%s\n"
               ">> ",
               PANTALLA_BARRA,PANTALLA_BARRA,
               PANTALLA_PRINCIPAL_OPERACIONES);

        // Se captura la opcion ingresada por el usuario
        fflush(stdin); seleccion_usuario_menu_principal = getchar();

        // SELECCION DE OPERACION
        // ----------------------------------------------------------
        switch (seleccion_usuario_menu_principal) {

            // Buscar un envio por CODIGO DE ENVIO
            case '1': {
                // variables para ambito de funcion de consulta
                char seleccion_usuario_menu_buscar, codigo_envio[ENVIO_TAM_CODIGO_DE_ENVIO];
                int resultado_consulta, entrada_correcta;
                Envio envio_consultado;

                do {
                    // Imprime pantalla
                    system("cls");
                    printf(PANTALLA_BARRA
                           "Buscar un ENVIO por su CODIGO\n"
                           PANTALLA_BARRA
                           "Ingrese el CODIGO del ENVIO que desea consultar >>\t");

                    // Captura de codigo ingresado por usuario
                    do {
                        fflush(stdin); scanf("%s",codigo_envio);
                        strcpy(codigo_envio,strupr(codigo_envio)); // pasa a mayusculas


                        // Control de Codigo de envio correcto
                        entrada_correcta = Envio_esCorrecto_codigo(codigo_envio);
                        if (!entrada_correcta)
                            printf("Debe ingresar un CODIGO valido! (7 caracteres alfanumericos) >> ");

                    } while (!entrada_correcta);


                    // Proceso de consulta a la LISTA
                    resultado_consulta = Lista_consulta(&lista_envios,codigo_envio,&envio_consultado);
                    // CASO existe el elemento buscado
                    if (resultado_consulta == CONSULTA_EXITOSA) {
                        printf("\nEnvio encontrado! Se imprime a continuacion...\n\n");
                        imprimirEnvio(envio_consultado);
                        printf("\nDesea realizar otra busqueda? [S/N] >> ");
                    }
                    // CASO NO existe el elemento
                    else printf("\n\nNo existe un Envio registrado con el Codigo %s!\n"
                               "Desea probar con un Codigo de Envio diferente? [S/N] >> ",
                               codigo_envio);

                    //Captura de respuesta de usuario
                    fflush(stdin); seleccion_usuario_menu_buscar = getchar();
                    while (entradaDistintaSino(seleccion_usuario_menu_buscar)) {
                        printf("\nDebe ingresar una entrada valida!\n[S/N] >> ");
                        fflush(stdin); seleccion_usuario_menu_buscar = getchar();
                    }
                } while (seleccion_usuario_menu_buscar == 's'); break; // termina el switch
            }
            // Agregar un nuevo ENVIO
            case '2': {
                // variable para respuesta de usuario
                char seleccion_usuario_menu_alta;
                int entrada_correcta;     // para controles
                do {
                    // Variables para crear ENVIO
                    char codigo_envio[ENVIO_TAM_CODIGO_DE_ENVIO];
                    unsigned int dni_receptor, dni_remitente;
                    char nombre_apellido_receptor[ENVIO_TAM_NOMBRE_APELLIDO],
                    domicilio_receptor[ENVIO_TAM_DOMICILIO],
                    nombre_apellido_remitente[ENVIO_TAM_NOMBRE_APELLIDO],
                    fecha_envio[ENVIO_TAM_FECHA],
                    fecha_recepcion[ENVIO_TAM_FECHA];

                    Envio nuevo_envio; Envio_init(&nuevo_envio);    // variable temporal

                    system("cls");  // limpia la pantalla

                    // Se captura codigo de envio
                    printf(
                           "%sAgregar un nuevo Envio\n%s\n"
                           "Ingrese el CODIGO DE ENVIO >>\t\t\t",
                           PANTALLA_BARRA,PANTALLA_BARRA);
                    do {
                        fflush(stdin); scanf("%s",codigo_envio);
                        strcpy(codigo_envio,strupr(codigo_envio));
                        // Control
                        entrada_correcta = Envio_esCorrecto_codigo(codigo_envio);
                        if (!entrada_correcta)
                            printf("Debe ingresar un CODIGO valido! (7 caracteres alfanumericos) >> ");
                    } while (!entrada_correcta);

                    // captura - dni de receptor
                    printf("\nIngrese el DNI del RECEPTOR >>\t\t\t");
                    do {
                        fflush(stdin); scanf("%u",&dni_receptor);
                        //control
                        entrada_correcta = Envio_esCorrecto_dni(dni_receptor);
                        if (!entrada_correcta)
                            printf("Debe ingresar un DNI valido! >> ");
                    } while (!entrada_correcta);

                    // captura - nombre y apellido de receptor
                    printf("\nIngrese el NOMBRE Y APELLIDO del RECEPTOR >>\t");
                    fflush(stdin); scanf("%[^\n]s",nombre_apellido_receptor);
                    strcpy(nombre_apellido_receptor,strupr(nombre_apellido_receptor));

                    // captura - domicilio de receptor
                    printf("\nIngrese el DOMICILIO del RECEPTOR >>\t\t");
                    fflush(stdin); scanf("%[^\n]s",domicilio_receptor);
                    strcpy(domicilio_receptor,strupr(domicilio_receptor));

                    // captura - dni de remitente
                    printf("\nIngrese el DNI del REMITENTE >>\t\t\t");
                    do {
                        fflush(stdin); scanf("%u",&dni_remitente);
                        //control
                        entrada_correcta = Envio_esCorrecto_dni(dni_remitente);
                        if (!entrada_correcta)
                            printf("Debe ingresar un DNI valido! >> ");
                    } while (!entrada_correcta);


                    // captura - nombre y apellido de remitente
                    printf("\nIngrese el NOMBRE Y APELLIDO del REMITENTE >>\t");
                    fflush(stdin); scanf("%[^\n]s",nombre_apellido_remitente);
                    strcpy(nombre_apellido_remitente,strupr(nombre_apellido_remitente));

                    // captura - fecha envio
                    printf("\nIngrese la FECHA de ENVIO >>\t\t\t");
                    do {
                        fflush(stdin); scanf("%s",fecha_envio);
                        //control
                        entrada_correcta = Envio_esCorrecto_fecha(fecha_envio);
                        if (!entrada_correcta)
                            printf("Debe ingresar un formato de FECHA valida! (AAAA-MM-DD) >> ");
                    } while (!entrada_correcta);

                    // captura - fecha recepcion
                    printf("\nIngrese la FECHA de RECEPCION >>\t\t");
                    do {
                        fflush(stdin); scanf("%s",fecha_recepcion);
                        //control
                        entrada_correcta = Envio_esCorrecto_fecha(fecha_recepcion);
                        if (!entrada_correcta)
                            printf("Debe ingresar un formato de FECHA valida! (AAAA-MM-DD) >> ");
                    } while (!entrada_correcta);

                    // Se crea la variable temporal
                    strcpy(nuevo_envio.codigo_envio,codigo_envio);
                    nuevo_envio.dni_receptor = dni_receptor;
                    strcpy(nuevo_envio.nombre_apellido_receptor,nombre_apellido_receptor);
                    strcpy(nuevo_envio.domicilio_receptor,domicilio_receptor);
                    nuevo_envio.dni_remitente = dni_remitente;
                    strcpy(nuevo_envio.nombre_apellido_remitente,nombre_apellido_remitente);
                    strcpy(nuevo_envio.fecha_envio,fecha_envio);
                    strcpy(nuevo_envio.fecha_recepcion,fecha_recepcion);

                    // @todo: FALTAN CONTROLES
                    // @fixme : nombres y domicilio se guardan en blanco


                    // Se realiza la operacion de ALTA
                    int resultado_alta = Lista_alta(&lista_envios,nuevo_envio);

                    // @todo : permitir confirmar el alta

                    // CASO de ALTA exitosa
                    if (resultado_alta == ALTA_EXITOSA) printf("\n\nEl nuevo ENVIO se guardo correctamente!\n"
                                                               "Desea agregar un nuevo ENVIO mas?\n[S/N] >> ");
                    else {
                        // CASO de CODIGO DE ENVIO ya existente
                        if (resultado_alta == ALTA_ERROR_CODIGO_EXISTENTE)
                            printf("\n\nEl CODIGO de ENVIO \"%s\" ya existe! No se puede guardar el ENVIO ingresado.\n"
                                   "Desea intentar de nuevo con un CODIGO de ENVIO diferente?\n[S/N] >> ",
                                   codigo_envio);
                        else {
                            printf("\n\nNo se pudo guardar el ENVIO, la memoria esta LLENA!\n\n");
                            system("pause");
                            break;  // se termina el bucle y se vuelve al menu principal
                        }
                    }

                    // Captura de respuesta del usuario
                    fflush(stdin); seleccion_usuario_menu_alta = getchar();
                    while (entradaDistintaSino(seleccion_usuario_menu_alta)) {
                        printf("\nDebe ingresar una entrada valida!\n[S/N] >> ");
                        fflush(stdin); seleccion_usuario_menu_alta = getchar();
                    }
                } while (seleccion_usuario_menu_alta == 's'); break; // termina el switch
            }
        }

    } while (seleccion_usuario_menu_principal != '4');


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
