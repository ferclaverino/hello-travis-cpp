#ifndef INDEX_H_
#define INDEX_H_
#include <string>
using std::string;


namespace UndavIndex{
	struct Index;

	/*
	 * Precondicion: Ninguna
	 * Postcondicion: Crea un indice numerico que comienza en 0 y termina en countElements - 1
	 */
	Index* CreateIndex(unsigned int countElements);

	/*
	 * Precondicion: @labelsCsvFormat es un string en formato CSV
	 * Postcondicion: Crea un indice "custom" donde cada elemento/label es un string
	 */
	Index* CreateIndex(string labelsCsvFormat);

	/*
	 * Precondicion: @index es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve la cantidad de elementos de @index
	 */
	int CountLabels(Index* index);

	/*
	 * Precondicion: @index es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve la cantidad de elementos de @index
	 */
	string GetLabel(const Index* index, int position);

	/*
	 * Precondicion: @left y @right son instancias validas creadas con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve true si @left y @rigth tienen los mismos labels en el mismo orden
	 */
	bool Equals(const Index* left, const Index* right);

	/*
	 * Precondicion: @index es una instancia valida creada con alguna de las primitivas creacionales
	 * Postcondicion: Libera los recursos asociados de @index
	 */
	void DestroyIndex(Index* index);
}


#endif
