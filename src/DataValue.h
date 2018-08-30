#ifndef VALUE_H_
#define VALUE_H_

#include <string>
using std::string;

/*Precondicion: -
 * Postcondicion: devuelve true si @value es una cadena formada por numeros enteros
 */
bool IsInteger(string value);

namespace UndavDataValue{
	struct DataValue;
	enum ValueType{String, Number, Boolean, Null, Object};

	DataValue* Create(string value);
	/* Precondicion: Ninguna
	 * Postcondicion: Crea una instancia valida de Value de tipo Number
	 * con valor @value
	 */
	DataValue* CreateNumber(int value);

	/* Precondicion: Ninguna
	 * Postcondicion: Crea una instancia valida de Value de tipo string
	 * con valor @value
	 */
	DataValue* CreateString(string value);

	/* Precondicion: Ninguna
	 * Postcondicion: Crea una instancia valida de Value de tipo Number
	 * con valor @value
	 */
	DataValue* CreateBoolean(bool value);

	/* Precondicion: Ninguna
	 * Postcondicion: Crea una instancia valida de Value de tipo Null
	 */
	DataValue* CreateNull();

	/* Precondicion: @value fue creado con alguna de las primitivas
	 * creacionales
	 * Postcondicion: Devuelve la representacion en formato string del valor encapsulado en
	 * @value. Para los casos que el tipo es bolean se espera recibir los valores: "True" o "False"
	 * Para los casos en que el tipo es NULL se espera recibir el valor: "--NULL--"
	 */
	string	Get(const DataValue* value);

	/* Precondicion: @value fue creado con alguna de las primitivas
	 * creacionales
	 * Postcondicion: Devuelve el tipo de dato de @value
	 */
	ValueType GetType(const DataValue* value);

	/* Precondicion: @leftValue y @rigthValue fue creado con alguna de las primitivas
	 * creacionales
	 * Postcondicion: Devuelve una instancia de Value que representa el resultado de la suma
	 * Para los casos que los dos tipos son Number, devuelve un tipo Number con la suma algebraica
	 * Para los casos que los dos tipos son String, devuelve un tipo String con la contatenacion de leftValue y rigthValue
	 * Para los casos que los dos tipos son Boolean, devuelve un tipo Boolean con el resultado del operador || (or)
	 * Para los casos que uno es String y otro es Number, devuelve un tipo String con la concatenacion de la representacion en string del que es Number y el otro tipo string
	 * Para todos los otros casos devuelve un tipo NULL
	 */
	DataValue* Add(const DataValue* leftValue, const DataValue* rigthValue);

	/* Precondicion: @leftValue y @rigthValue fueron creados con alguna de las primitivas
	 * creacionales
	 * Postcondicion: Devuelve true si @leftValue y @rigthValue son del mismo tipo y tienen el mismo valor
	 */
	bool Equals(const DataValue* leftValue,const DataValue* rigthValue);

	/* Precondicion: @leftValue y @rigthValue fueron creados con alguna de las primitivas
	 * creacionales
	 * Postcondicion: Transforma @valueToReplace en @newValue (establece el tipo y valor de @newValue en @valueToReplace)
	 */
	void Replace(DataValue* valueToReplace,const DataValue* newValue);

	/* Precondicion: @leftValue y @rigthValue fueron creados con alguna de las primitivas
	 * creacionales
	 * Postcondicion: Si son del mismo tipo devuelve true si @leftValue es estrictamente menor que @rigthValue
	 * si son de distinto tipo devuelve false.
	 */
	bool IsLess(const DataValue* leftValue,const DataValue* rigthValue);

	/* Precondicion: @value fue creado con alguna de las primitivas creacionales y no fue destruido anteriormente
	 * Postcondicion: Libera todos los recursos asociados en @value
	 */
	void DestroyDataValue(DataValue* value);
}

#endif
