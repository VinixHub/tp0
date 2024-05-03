#include "client.h"
#include <readline/readline.h>
#include <readline/history.h>

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */
/*
	logger = iniciar_logger();
	logger = log_create("tp0.log", "logging", true, LOG_LEVEL_INFO);
	log_info(logger, "Hola soy un log!");
	

	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();
	
	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	config = config_create("/home/utnso/Desktop/tp0/client/cliente.config");
	ip = config_get_string_value(config, "IP");
	valor = config_get_string_value(config, "CLAVE");
	puerto = config_get_string_value(config, "PUERTO");

	// Loggeamos el valor de config
	
	
	/* ---------------- LEER DE CONSOLA ---------------- */
//	leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él; Asegurado macho!

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor, conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void) { // Parte 2
	t_log* nuevo_logger;
	return nuevo_logger;
}

t_config* iniciar_config(void){ // Parte 2
	t_config* nuevo_config;
	return nuevo_config;
}

void leer_consola(t_log* logger) { // Parte 2
	char* leido;
	while(1) {
	// La primera te la dejo de yapa
		leido = readline("> ");
		if (!leido) {
            break;
        }
		if(strcmp(leido, "") == 0) {
			break;
		}
	// El resto, las vamos leyendo y logueando hasta recibir un string vacío
		log_info(logger, leido);

	// ¡No te olvides de liberar las lineas antes de regresar!
		free(leido);
	}
}

void paquete(int conexion) {
	// Ahora toca lo divertido!
	char* leido;
	t_paquete* paquete = crear_paquete();
	// Leemos y esta vez agregamos las lineas al paquete
	while(1) {
		leido = readline("> ");
		if (!leido) {
            break;
        }
		if(strcmp(leido, "") == 0) {
			break;
		}
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
		free(leido);
	}
	enviar_paquete(paquete, conexion);
	eliminar_paquete(paquete);
	// ¡No te olvides de liberar las líneas y el paquete antes de regresar!
	
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	log_destroy(logger);

	config_destroy(config);

	liberar_conexion(conexion);
}
