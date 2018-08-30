#ifndef SERIES_H_
#define SERIES_H_
#include "DataValue.h"
#include "Index.h"
#include <string>

using std::string;
using UndavIndex::Index;
using UndavDataValue::DataValue;
using UndavDataValue::ValueType;

/* Precondicion: @countElements corresponde a la cantidad de elementos que posee @value
 * Postcondicion: devuelve true si todos los elementos dentro de @value tienen el mismo tipo
 */
bool EqualType(DataValue ** value, int countElements);

namespace UndavSeries{
	struct Series;

	typedef DataValue* (*MapFunction)(const DataValue*);
	typedef DataValue* (*MapInPlaceFunction)(DataValue*);

	/*
	 * Precondicion: Ninguna
	 * Postcondicion: Crea una serie vacia de nombre @name
	 */
	Series* CreateSeries(string name);

	/* Precondicion: @valuesCsvFormat es un string en formato csv que representa un registro csv.
	 * Postcondicion: Crea una serie de nombre @name que contiene:
	 *	- Un indice numerico que empieza en cero.
	 *	- En cada posicion del indice tiene asociado un Value que se corresponde al numero de campo en @valuesCsvFormat, comenzando en cero.
	 *	Ademas por cada campo de @valuesCsvFormat se debe inferir su tipo de la siguiente forma
	 *	- Si es la cadena "True" o "False" el Value creado debe ser de tipo boolean
	 *	- Si la cadena es un numero entero ("1983") el Value creado debe ser de tipo Number
	 *	- Si es un campo vacio ("") el Value creado debe ser de tipo boolean es de tipo NULL
	 *	- Para el resto de los valores posibles el Value creado debe ser de tipo String
	 */
	Series* CreateSeries(string valuesCsvFormat, string name);

	/*
	 * Precondicion: @valuesCsvFormat es un string en formato csv que representa un registro csv.
	 * @index es una instancia valida de Index
	 * Postcondicion: Misma postcondicion que CreateSeries pero en lugar de crear un indice por defecto, le asocia @index.
	 * Si la cantidad de elementos de @index es distinta a la cantidad de campos de @valuesCsvFormat devuelve NULL.
	 */
	Series* CreateSeries(string valuesCsvFormat, Index* index, string name);

	/*
	 * Precondicion: @series fue creado con alguna de las primitivas creacionales de series.
	 * Postcondicion: Devuelve el nombre de @series
	 */
	string GetName(const Series* series);

	/*
	 * Precondicion: @series es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve un instancia de Index que representa el indice de @series
	 */
	Index* GetIndex(Series* series);

	/*
	 * Precondicion: @series es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve el valor de @series localizado en la posicion @indexLocation.
	 * Si @indexLocation esta fuera de rango devuelve NULL
	 */
	DataValue* GetValueByIndexLocation(Series* series, unsigned int indexLocation);

	/*
	 * Precondicion: @series es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve el valor de @series localizado en la posicion en donde el label del indice (o su representacion en string) es igual a @name.
	 * Si no existe ese index name en @series devuelve NULL.
	 * Si existen varios elementos en @series que poseen el mismo index name devuelve el valor del primer elemento de @series
	 */
	DataValue* GetValueByIndexLabel(Series* series, string indexLabel);

	/*
	 * Precondicion: @series es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve una instancia valida de Series la cual
	 * - Tiene como Index el conjunto (valores sin repetir) de Values de @series
	 * - Tiene como elementos de la serie instancias de Value de tipo Number con el valor que cuenta la cantidad de repeticiones de su indice en @series
	 * - Se encuentra ordenado por el valor de la nueva serie
	 */
	Series* GetValueCounts(const Series* series);

	/*
	 * Precondicion: @series es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Imprime en salida estandar dos columnas. En la primer columna el label del index y en la segunda columna el valor del dato.
	 * Luego en una nueva linea imprime el tipo de dato de la siguiente forma:
	 * type [Number]
	 * Donde Number es el label (string) que representa GetType
	 */
	void Print(const Series* series);

	/*
	 * Precondicion: @series es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Si los indices de @left y @rigth no son iguales devuelve NULL.
	 * Caso contrario devuelve una instancia valida de Series la cual
	 * - Tiene como Index el mismo Index que @left y @right
	 * - Tiene como elementos Values que son la suma de los values en @left y @rigth
	 */
	Series* Add(const Series* left, const Series* right);

	/*
	 * Precondicion: @series es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve una nueva instancia de Series que tiene las siguientes caracteristicas
	 * - Tiene un indice equivalente a @series
	 * - Cada elemento en la posicion sub i de la nueva instancia es el resultado de aplicar @function con el elemento sub i de @series
	 */
	Series* Map(const Series* series, MapFunction function);

	/*
	 * Precondicion: @series es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Modifica los valores de @series de la siguiente forma
	 * - Cada elemento en la posicion sub i @series es el resultado de aplicar @function con el elemento sub i
	 */
	void Map(Series* series, MapInPlaceFunction function);

	/* Precondicion: @series es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion:
	 * - Si todos los valores son de tipo Number devuelve Number
	 * - Si todos los valores son de tipo String devuelve String
	 * - Si todos los valores son de tipo Boolean devuelve Boolean
	 * Caso contrario devuelve Object
	 */
	ValueType GetType(const Series* series);

	/* Precondicion: @series fue creado con alguna de las primitivas creacionales y no fue destruido anteriormente
	 * Postcondicion: Libera todos los recursos asociados en @series
	 */
	void DestroySeries(Series* series);
}

#endif
