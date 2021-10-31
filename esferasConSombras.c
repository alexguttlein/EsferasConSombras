#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct{
	float x, y, z;
} vector_t;

typedef struct{
	float r, g, b;
} color_t;

typedef struct{
	vector_t centro;
	float radio;
	color_t color;
	float ka, kd;
} esfera_t;

typedef struct {
	vector_t posicion;
	color_t color;
	bool es_puntual;
} luz_t;

typedef struct {
	void **v;
	size_t n;
}arreglo_t;


float vector_producto_interno(vector_t a, vector_t b){
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vector_norma(vector_t a){
	return sqrt(vector_producto_interno(a,a));
}

vector_t vector_resta(vector_t a, vector_t b){
	vector_t resta;
	resta.x = a.x - b.x;
	resta.y = a.y - b.y;
	resta.z = a.z - b.z;
	return resta;
}

vector_t vector_normalizar(vector_t a){
	vector_t normalizar;
	normalizar.x = a.x / vector_norma(a);
	normalizar.y = a.y / vector_norma(a);
	normalizar.z = a.z / vector_norma(a);
	return normalizar;
}

vector_t vector_interpolar_recta(vector_t o, vector_t d, float t){
	vector_t interpolado;
	interpolado.x = o.x + t*d.x;
	interpolado.y = o.y + t*d.y;
	interpolado.z = o.z + t*d.z;
	return interpolado;
}

color_t color_sumar(color_t c, color_t m, color_t p){
	color_t color;
	color.r = c.r + m.r * p.r;
	color.g = c.g + m.g * p.g;
	color.b = c.b + m.b * p.b;
	return color;
}

color_t color_absorber(color_t b, color_t c){
	color_t color_resultante;
	color_resultante.r = b.r * c.r;
	color_resultante.g = b.g * c.g;
	color_resultante.b = b.b * c.b;
	return color_resultante;
}


void color_imprimir(color_t c){
	float r,g,b;
	if(c.r < 0)
		r = 0;
	else if(c.r > 1)
		r = 255;
	else r = 255 * c.r;

	if(c.g < 0)
		g = 0;
	else if(c.g > 1)
		g = 255;
	else g = 255 * c.g;

	if(c.b < 0)
		b = 0;
	else if(c.b > 1)
		b = 255;
	else b = 255 * c.b;

	printf("%.0f %.0f %.0f ", r, g, b);
}


esfera_t* esfera_crear(vector_t centro, float radio, color_t color, float ka, float kd){
	esfera_t* esfera = NULL;
	esfera = malloc(sizeof(esfera_t));
	esfera->radio = radio;
	esfera->ka = ka;
	esfera->kd = kd;
	esfera->centro.x = centro.x;
	esfera->centro.y = centro.y;
	esfera->centro.z = centro.z;
	esfera->color.r = color.r;
	esfera->color.g = color.g;
	esfera->color.b = color.b;
	return esfera;
}

void esfera_destruir(esfera_t* esfera){
	if(esfera){
		free(esfera);
	}
}

luz_t* luz_crear(vector_t posicion, color_t color, bool es_puntual){
	luz_t* luz = NULL;
	luz = malloc(sizeof(luz_t));
	luz->posicion.x = posicion.x;
	luz->posicion.y = posicion.y;
	luz->posicion.z = posicion.z;
	luz->color.r = color.r;
	luz->color.g = color.g;
	luz->color.b = color.b;
	luz->es_puntual = es_puntual;
	return luz;
}

void luz_destruir(luz_t* luz){
	if(luz){
		free(luz);
	}
}

bool arreglo_agregar(arreglo_t* a, void* e){

	if(!a || !e) return false;
	
	//si es el primer elemento que se agrega se reserva memoria
	if(a->n == 0){
		a->v = (void*) malloc (sizeof(a->v) * (a->n+1));
		if(!a->v) return false;
		a->v[a->n] = e;
		a->n += 1;
	}
	//si no es el primer elemento se redimensiona
	else{
		a->v = (void*) realloc(a->v, sizeof(a->v) * (a->n+1));
		a->v[a->n] = e;
		a->n += 1;
	}

	return true;
}




int main(void){
	//PRUEBA VECTOR
	vector_t vector1 = {
		.x = 2.0,
		.y = 1.0,
		.z = 2.0,
	};

	vector_t vector2 = {
		.x = 4.9,
		.y = 4.0,
		.z = 2.0,
	};

	printf("El vector es %.2f %.2f %.2f\n", vector1.x, vector1.y, vector1.z);
	printf("El producto interno es %.2f\n", vector_producto_interno(vector1, vector2));
	vector_t resta = vector_resta(vector1, vector2);
	printf("La resta es: %.2f %.2f %.2f\n", resta.x, resta.y, resta.z);
	printf("La norma es %.2f\n", vector_norma(vector1));
	vector_t v_normalizado = vector_normalizar(vector1);
	printf("El vector normalizado es %.2f %.2f %.2f\n", v_normalizado.x, v_normalizado.y, v_normalizado.z);
	vector_t interpolado = vector_interpolar_recta(vector1, vector2, 2);
	printf("El vector interpolado es %.2f %.2f %.2f\n", interpolado.x, interpolado.y, interpolado.z);

	//PRUEBA COLOR
	color_t color1 = {
		.r = 1.0,
		.g = 0.4,
		.b = -1.0,	
	};

	color_t color2 = {
		.r = 3.0,
		.g = 0.8,
		.b = 0.0,	
	};

	
/*
	color_t color3 = {
		.r = 1.0,
		.g = 0.3,
		.b = 0.0,	
	};
*/

//	color4 = color_sumar(color1, color2, color3);
//	color4 = color_absorber(color1, color2);
//	color_imprimir(color4);

/*	esfera_t esfera1 = {
		.centro = vector1,
		.radio = 3.0,
		.color = color1,
		.ka = 2.2,
		.kd = 1.2,
	};
*/
	//PRUEBA ESFERA
	esfera_t* esfera2;
	esfera2 = esfera_crear(vector1, 3.0, color1, 1.0, 2.1);

	printf("\nESFERA\nCENTRO = (%.1f, %.1f, %.1f)\nRADIO = %.1f\nCOLOR = (%.1f, %.1f, %.1f)\nKa = %.1f / Kb = %.1f\n", 
		esfera2->centro.x, esfera2->centro.y, esfera2->centro.z, esfera2->radio, esfera2->color.r, 
		esfera2->color.g, esfera2->color.b, esfera2->ka, esfera2->kd);


	//PRUEBA LUZ
	luz_t* luz1;
	luz1 = luz_crear(vector2, color2, true);
	printf("\nLUZ\nPOSICION = (%.1f, %.1f, %.1f)\nCOLOR = (%.1f, %.1f, %.1f)\n", 
		luz1->posicion.x, luz1->posicion.y, luz1->posicion.z, 
		luz1->color.r, luz1->color.g, luz1->color.b);

	//PRUEBA ARREGLO
	arreglo_t luces = {NULL, 0};
	arreglo_agregar(&luces, luz1);
	arreglo_agregar(&luces, luz1);
	arreglo_agregar(&luces, luz1);

//	if(luces.v[2] != NULL) printf("Si!!!\n");
//	else printf("No!!!\n");

//	if(luces.n == 3) printf("cantidad correcta\n\n");
	esfera_destruir(esfera2);
	luz_destruir(luz1);
	free(luces.v);
	return 0;
}


//gcc tp3.c -o tp3 -lm -g -std=c99 -Wall -Wtype-limits -pedantic -Werror -O0
//valgrind --leak-check=full --track-origins=yes --show-reachable=yes ./tp3