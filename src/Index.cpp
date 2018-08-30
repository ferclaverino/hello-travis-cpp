#include "Index.h"
#include "DataValue.h"

int TotalCampCSV(string csvFormat);
void ParsearCsv(string labels[],string csvFormat);


struct UndavIndex::Index
{
	string *labels;
	int  *range;
	int totalElements;
};

UndavIndex::Index* UndavIndex::CreateIndex(unsigned int countElements)
{
	Index* newIndex = new Index;
	newIndex->labels= NULL;
	newIndex->range = new int[countElements];
	newIndex->totalElements = countElements;
	for(int iRange = 0; iRange < countElements ; iRange++)
	{
		newIndex->range[iRange] = iRange;
	}
	return newIndex;
}

UndavIndex::Index* UndavIndex::CreateIndex(string labelsCsvFormat)
{
	Index *newIndex = new Index;
	newIndex->range = NULL;
	int totalCamps = TotalCampCSV(labelsCsvFormat);
	newIndex->totalElements = totalCamps;
	newIndex->labels = new string[totalCamps];
	ParsearCsv(newIndex->labels,labelsCsvFormat);
	return newIndex;

}

int UndavIndex::CountLabels(Index* index)
{
	return (index->totalElements);
}


string UndavIndex::GetLabel(const Index* index, int position)
{
	if(index->range != NULL)
	{
		return std::to_string(index->range[position]);
	}
	return (index->labels[position]);
}

	/*
	 * Precondicion: @left y @right son instancias validas creadas con alguna de las primitivas creacionales
	 * Postcondicion: Devuelve true si @left y @rigth tienen los mismos labels en el mismo orden
	 */

bool UndavIndex::Equals(const Index* left, const Index* right)
{
	bool equals = (left->totalElements == right->totalElements);

	for(int iLabels = 0; iLabels < left->totalElements && equals; iLabels++)
	{
		if(left->labels != NULL)
		{
			equals = (left->labels[iLabels] == right->labels[iLabels]);
		}
		else
		{
			equals = (left->range[iLabels] == right->range[iLabels]);
		}
	}
	return equals;

}

void UndavIndex::DestroyIndex(Index* index)
{
	if(index->labels != NULL)
	{

		delete []index->labels;
	}
	else
	{
		delete []index->range;
	}
	delete index;
}

int ContarApariciones(string csvFormat, char caracter) {
	int cantidadApariciones = 0;
	for (int iCsv = 0; iCsv < csvFormat.size(); iCsv++) {
		if (csvFormat[iCsv] == caracter) {
			cantidadApariciones++;
		}
	}

	return cantidadApariciones;
}

int TotalCampCSV(string csvFormat)
{
	//Obtiene la cantidad total de caracteres dentro de @csvFormat
	int cantidadApariciones = ContarApariciones(csvFormat, ',');
	return csvFormat.empty() ? 0: cantidadApariciones+1;
}

void ParsearCsv(string labels[], string csvFormat)
{
	int totalCharacters = csvFormat.size();
	int iLabels = 0;
	for (int iCsv = 0; iCsv < totalCharacters; )
	{
		if(csvFormat[iCsv] != ',')
		{
			labels[iLabels] += csvFormat[iCsv];
			iCsv ++;
		}
		else
		{
			iLabels++;
			iCsv ++;
		}

	}
}


