#include <stdio.h>
#include <stdlib.h>
#include "Envio.h"
#include "ListaSO.h"


// --- CADENAS GLOBALES
#define PANTALLA_BARRA "-----------------------------------------------------------------------\n"
#define PANTALLA_PRINCIPAL_OPERACIONES "\
1. Buscar un Envio por su codigo\n\
2. Agregar un nuevo Envio\n\
3. Eliminar un Envio\n\
4. Modificar un Envio\n\
5. Cargar Envios desde el archivo \"Envios.txt\"\n\
6. Mostrar Estructura\n\
7. Salir del programa\n"


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

//memorizacion previa


enum Memorizacion_previa {ERROR_ABRIR_FICHERO, MEMORIZACION_EXITOSA, MEMORIZACION_PARCIAL};
int Memorizacion_previa(Lista *lista, int *cant_repetidos, int *cargados){
    FILE *fichero;
    int resultado_alta, repetidos = 0, indice = 0;

    Envio nuevo_envio; Envio_init(&nuevo_envio); //variable temporal

    fichero = fopen("Envios.txt","r"); //abrir el archivo
    if (fichero == NULL)

        return ERROR_ABRIR_FICHERO;

    else {
        while(!feof(fichero)){

            fscanf(fichero," %[^\n]s",nuevo_envio.codigo_envio);
            strcpy(nuevo_envio.codigo_envio,strupr(nuevo_envio.codigo_envio));

            fscanf(fichero,"%u",&nuevo_envio.dni_receptor);

            fscanf(fichero," %[^\n]s",nuevo_envio.nombre_apellido_receptor);
            strcpy(nuevo_envio.nombre_apellido_receptor,strupr(nuevo_envio.nombre_apellido_receptor));

            fscanf(fichero," %[^\n]s",nuevo_envio.domicilio_receptor);
            strcpy(nuevo_envio.domicilio_receptor,strupr(nuevo_envio.domicilio_receptor));

            fscanf(fichero,"%u",&nuevo_envio.dni_remitente);

            fscanf(fichero," %[^\n]s",nuevo_envio.nombre_apellido_remitente);
            strcpy(nuevo_envio.nombre_apellido_remitente,strupr(nuevo_envio.nombre_apellido_remitente));

            fscanf(fichero," %[^\n]s",nuevo_envio.fecha_envio);

            fscanf(fichero," %[^\n]s",nuevo_envio.fecha_recepcion);

            resultado_alta = Lista_alta(lista, nuevo_envio);

            if (resultado_alta == ALTA_ERROR_LISTA_LLENA){
                fclose(fichero);
                break;
            }
            if (resultado_alta == ALTA_ERROR_CODIGO_EXISTENTE){
                repetidos ++;
            }
            indice ++;
        }
    }

    *cargados = indice;
    *cant_repetidos = repetidos;
    fclose(fichero);

    if(resultado_alta == ALTA_ERROR_LISTA_LLENA){
        return MEMORIZACION_PARCIAL;
    }
    return MEMORIZACION_EXITOSA;
}

//Mostrar Lista
void Mostrar_Lista(Lista lista){
    int cantidad_envios = lista.limite_superior, contador = 0;
    if(cantidad_envios > -1){
        for(contador; contador <= cantidad_envios; contador++){
            printf("\nPosicion %d\n%s", contador, PANTALLA_BARRA);
            imprimirEnvio(lista.arreglo[contador]);
            if(contador % 5 == 0 && contador != 0){
                system("pause");
            }
        }
    }else{
    printf("La lista esta vacia\n\n");
    }
}

// Funcion para manejar la confirmacion de una BAJA
int confirmacionBaja(Envio envio) {
    // La funcion devuelve 1 si se ha confirmado la BAJA
    //                      0 si se ha cancelado

    printf("\nSe ha encontrado el Envio solicitado, se imprime a continuacion...\n\n");
    imprimirEnvio(envio);

    printf("\nEsta seguro que quiere eliminarlo? [S/N] >> ");

    //captura de la entrada del usuario
    fflush(stdin);
    char seleccion_usuario = getchar();

    while (entradaDistintaSino(seleccion_usuario)) {
        printf("\nDebe ingresar una entrada valida!\n[S/N] >> ");
        fflush(stdin); seleccion_usuario = getchar();
    }

    if (seleccion_usuario == 's') return 1;
    else return 0;
}

int confirmacionModificacion(Envio *envio) {
    // Devuelve 1 cuando se confirma la modificacion
    //          0 cuando se cancela

    // Variables de control
    int entrada_correcta;
    char seleccion_usuario;

    Envio envio_temporal; envio_temporal = *envio;    // variable temporal


    // captura - dni de receptor
    // -------------------------------------------------------
    printf("\nDNI anterior: %u\n"
           "Nuevo DNI del RECEPTOR >>\t\t\t"
           ,envio_temporal.dni_receptor);
    do {
        fflush(stdin); scanf("%u",&envio_temporal.dni_receptor);
        //control
        entrada_correcta = Envio_esCorrecto_dni(envio_temporal.dni_receptor);
        if (!entrada_correcta)
            printf("Debe ingresar un DNI valido! >> ");
    } while (!entrada_correcta);

    // captura - nombre y apellido de receptor
    // -----------------------------------------------------------------
    printf("\nValor anterior: %s\n"
           "Nuevo NOMBRE Y APELLIDO del RECEPTOR >>\t\t",
           envio_temporal.nombre_apellido_receptor);
    fflush(stdin); scanf("%[^\n]s",envio_temporal.nombre_apellido_receptor);
    strcpy(envio_temporal.nombre_apellido_receptor,strupr(envio_temporal.nombre_apellido_receptor));

    // captura - domicilio de receptor
    // ----------------------------------------------------------------------
    printf("\nValor anterior: %s\n"
           "Nuevo DOMICILIO del RECEPTOR >>\t\t\t",
           envio_temporal.domicilio_receptor);
    fflush(stdin); scanf("%[^\n]s",envio_temporal.domicilio_receptor);
    strcpy(envio_temporal.domicilio_receptor,strupr(envio_temporal.domicilio_receptor));

    // captura - dni de remitente
    // ----------------------------------------------------------------------
    printf("\nDNI anterior: %u\n"
           "Nuevo DNI del REMITENTE >>\t\t\t",
           envio_temporal.dni_remitente);
    do {
        fflush(stdin); scanf("%u",&envio_temporal.dni_remitente);
        //control
        entrada_correcta = Envio_esCorrecto_dni(envio_temporal.dni_remitente);
        if (!entrada_correcta)
            printf("Debe ingresar un DNI valido! >> ");
    } while (!entrada_correcta);


    // captura - nombre y apellido de remitente
    // ----------------------------------------------------------------------
    printf("\nValor anterior: %s\n"
           "Nuevo NOMBRE Y APELLIDO del REMITENTE >>\t",
           envio_temporal.nombre_apellido_remitente);
    fflush(stdin); scanf("%[^\n]s",envio_temporal.nombre_apellido_remitente);
    strcpy(envio_temporal.nombre_apellido_remitente,strupr(envio_temporal.nombre_apellido_remitente));

    // captura - fecha envio
    // ----------------------------------------------------------------------
    printf("\nFecha anterior: %s\n"
           "Nueva FECHA de ENVIO >>\t\t\t\t",
           envio_temporal.fecha_envio);
    do {
        fflush(stdin); scanf("%s",envio_temporal.fecha_envio);
        //control
        entrada_correcta = Envio_esCorrecto_fecha(envio_temporal.fecha_envio);
        if (!entrada_correcta)
            printf("Debe ingresar un formato de FECHA valida! (AAAA-MM-DD) >> ");
    } while (!entrada_correcta);

    // captura - fecha recepcion
    // ----------------------------------------------------------------------
    printf("\nFecha anterior: %s\n"
           "Nueva FECHA de RECEPCION >>\t\t\t",
           envio_temporal.fecha_recepcion);
    do {
        fflush(stdin); scanf("%s",envio_temporal.fecha_recepcion);
        //control
        entrada_correcta = Envio_esCorrecto_fecha(envio_temporal.fecha_recepcion);
        if (!entrada_correcta)
            printf("Debe ingresar un formato de FECHA valida! (AAAA-MM-DD) >> ");
    } while (!entrada_correcta);


    // Confirmacion del usuario
    printf("\n\nDesea aplicar los cambios ingresados? [S/N] >> ");

    fflush(stdin); seleccion_usuario = getchar();
    while (entradaDistintaSino(seleccion_usuario)) {
        printf("\nDebe ingresar una entrada valida!\n[S/N] >> ");
        fflush(stdin); seleccion_usuario = getchar();
    }

    // retorno
    if (seleccion_usuario == 's') {
        // se guardan los cambios en la lista
        *envio = envio_temporal;

        return 1;
    }
    else return 0;
}

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
                           "Ingrese el CODIGO DE ENVIO >>\t\t",
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
                    printf("\nIngrese el DNI del RECEPTOR >>\t\t");
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
                    printf("\nIngrese el DNI del REMITENTE >>\t\t");
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
                    printf("\nIngrese la FECHA de ENVIO >>\t\t");
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
            // Modificacion de un ENVIO
            case '4': {
                // variables
                char seleccion_usuario_menu_modificacion, codigo_envio[ENVIO_TAM_CODIGO_DE_ENVIO];
                int resultado_modificacion, entrada_correcta;

                do {
                    // Imprime pantalla
                    system("cls");
                    printf(PANTALLA_BARRA
                           "Modificar un ENVIO\n"
                           PANTALLA_BARRA
                           "Ingrese el CODIGO del ENVIO que desea modificar >>\t");

                    // Captura de codigo ingresado por usuario
                    do {
                        fflush(stdin); scanf("%s",codigo_envio);
                        strcpy(codigo_envio,strupr(codigo_envio)); // pasa a mayusculas


                        // Control de Codigo de envio correcto
                        entrada_correcta = Envio_esCorrecto_codigo(codigo_envio);
                        if (!entrada_correcta)
                            printf("Debe ingresar un CODIGO valido! (7 caracteres alfanumericos) >> ");

                    } while (!entrada_correcta);


                    // Proceso de modificacion de un ENVIO en la LISTA
                    resultado_modificacion = Lista_modificacion(&lista_envios,codigo_envio,confirmacionModificacion);


                    // Caso de modificacion EXITOSA
                    if (resultado_modificacion == MODIFICACION_EXITOSA) {
                        printf("\nEl Envio %s se modifico correctamente!\n"
                               "Desea modificar otro envio? [S/N] >> ",codigo_envio);
                    }
                    else if (resultado_modificacion == MODIFICACION_ERROR_NO_EXISTE) {
                        printf("\nEl Envio %s no se encuentra en la lista!\n"
                               "Desea buscar con un Codigo diferente? [S/N] >> ",codigo_envio);
                    }
                    // caso que se haya cancelado la modificacion
                    else break; // sale al menu principal

                    //Captura de respuesta de usuario
                    fflush(stdin); seleccion_usuario_menu_modificacion = getchar();
                    while (entradaDistintaSino(seleccion_usuario_menu_modificacion)) {
                        printf("\nDebe ingresar una entrada valida!\n[S/N] >> ");
                        fflush(stdin); seleccion_usuario_menu_modificacion = getchar();
                    }
                } while (seleccion_usuario_menu_modificacion == 's'); break; // termina el switch
            }
            case '5':{
                system("cls");
                int resultado, repetidos = 0, cant, cargas;
                resultado = Memorizacion_previa(&lista_envios, &repetidos, &cargas);

                if(resultado == MEMORIZACION_EXITOSA){
                    printf("La memorizacion fue exitosa.\n\n");
                }
                if(resultado == MEMORIZACION_PARCIAL){
                    printf("La memorizacion fue exitosa parcialmente.\n La cantidad de envios en el archivo era mayor al maximo de la lista\n\n ");
                }
                if(resultado == ERROR_ABRIR_FICHERO) {
                    printf("Existe un problema al intentar abrir el archivo.\n Por favor revisar el archivo \"Envios.txt\" \n");
                }
                if(resultado != ERROR_ABRIR_FICHERO) {
                    printf("Se intentaron cargar %d Envios \n", cargas);
                    printf("De los cuales:\n \t Envios repetidos: %d \n \t Envios cargados correctamente: %d \n ", repetidos, cargas - repetidos);
                }

            system("pause"); break;
            }

            // Dar de Baja un ENVIO
            case '3': {
                    // variable de seleccion de usuario
                    char seleccion_usuario_menu_baja, codigo_envio[ENVIO_TAM_CODIGO_DE_ENVIO];
                    int entrada_correcta;
                    do {
                        // Imprime pantalla
                        system("cls");
                        printf(PANTALLA_BARRA
                               "Eliminar un ENVIO\n"
                               PANTALLA_BARRA
                               "Ingrese el CODIGO del ENVIO que desea eliminar >>\t");

                        // Captura de codigo ingresado por usuario
                        do {
                            fflush(stdin); scanf("%s",codigo_envio);
                            strcpy(codigo_envio,strupr(codigo_envio)); // pasa a mayusculas


                            // Control de Codigo de envio correcto
                            entrada_correcta = Envio_esCorrecto_codigo(codigo_envio);
                            if (!entrada_correcta)
                                printf("Debe ingresar un CODIGO valido! (7 caracteres alfanumericos) >> ");

                        } while (!entrada_correcta);

                        // Procedimiento de baja
                        int resultado_baja = Lista_baja(&lista_envios,codigo_envio,confirmacionBaja);

                        // Si se cancelo la baja, interrumpe directamente y vuelve al menu
                        if (resultado_baja == BAJA_CANCELADA) break;

                        // Caso exitoso
                        else if (resultado_baja == BAJA_EXITOSA) {
                            printf("\n\nEl ENVIO %s se elimino correctamente!\n"
                                   "Desea eliminar otro envio? [S/N] >> ",codigo_envio);
                        } else if (resultado_baja == BAJA_ERROR_NO_EXISTE) {// Caso que el ENVIO no exista
                            printf("\n\nError! El ENVIO %s no existe!\n"
                                   "Desea probar con un CODIGO diferente? [S/N] >> ",codigo_envio);
                        }

                    // Captura de respuesta del usuario
                    fflush(stdin); seleccion_usuario_menu_baja = getchar();
                    while (entradaDistintaSino(seleccion_usuario_menu_baja)) {
                        printf("\nDebe ingresar una entrada valida!\n[S/N] >> ");
                        fflush(stdin); seleccion_usuario_menu_baja = getchar();
                    }

                    } while (seleccion_usuario_menu_baja == 's'); break; // sale del switch
            }
            // Mostrar la Estructura
            case '6':{
                system("cls");

                printf("%sMostrando Estructura\n%s\n",
                       PANTALLA_BARRA,PANTALLA_BARRA);

                Mostrar_Lista(lista_envios);

                printf("\nSe ha llegado al final de la Lista.\n");
                system("pause");
            }
        }

    } while (seleccion_usuario_menu_principal != '7');


    return 0;
}
