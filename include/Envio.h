#ifndef ENVIO_H
#define ENVIO_H

// Tamanos de arreglos
#define ENVIO_TAM_CODIGO_DE_ENVIO 10
#define ENVIO_TAM_NOMBRE_APELLIDO 50
#define ENVIO_TAM_DOMICILIO 50
#define ENVIO_TAM_FECHA 12

// Limites de algunos campos
#define ENVIO_DNI_MINIMO 1000000
#define ENVIO_FECHA_MINIMA "2000-01-01"


// Definicion de objeto Envio
typedef struct {
    char codigo_envio[ENVIO_TAM_CODIGO_DE_ENVIO];
    unsigned int dni_receptor;
    char nombre_apellido_receptor[ENVIO_TAM_NOMBRE_APELLIDO];
    char domicilio_receptor[ENVIO_TAM_DOMICILIO];
    unsigned int dni_remitente;
    char nombre_apellido_remitente[ENVIO_TAM_NOMBRE_APELLIDO];
    char fecha_envio[ENVIO_TAM_FECHA];
    char fecha_recepcion[ENVIO_TAM_FECHA];
} Envio;

// Funciones para el objeto Envio
void Envio_init(Envio *);



#endif // ENVIO_H
