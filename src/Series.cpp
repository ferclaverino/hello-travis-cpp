#include "Series.h"
#include "Index.h"
#include "DataValue.h"
#include <iostream>
using namespace std;

using UndavDataValue::DataValue;
using UndavIndex::Index;

int TotalCampCSV(string csvFormat);
void ParsearCsv(string labels[],string csvFormat);


struct UndavSeries::Series
{
	string name;
	Index * index;
	DataValue **values;
};



UndavSeries::Series* UndavSeries::CreateSeries(string name){
	Series* newSeries = new Series;
	newSeries->name = name;
	newSeries->index = NULL;
	newSeries->values = NULL;
	return newSeries;

}

UndavSeries::Series*  UndavSeries::CreateSeries(string valuesCsvFormat, string name)
{
	Series* newSeries = new Series;
	newSeries->name = name;
	int totalElements = TotalCampCSV(valuesCsvFormat);
	newSeries->index = UndavIndex::CreateIndex(totalElements);
	newSeries->values = new	DataValue *[totalElements];

	string auxiliary[totalElements];
	ParsearCsv(auxiliary,valuesCsvFormat);

	for(int iAuxiliary = 0; iAuxiliary < totalElements; iAuxiliary++)
	{
		newSeries->values[iAuxiliary] = UndavDataValue::Create(auxiliary[iAuxiliary]);
	}
	return newSeries;
}

UndavSeries::Series* UndavSeries::CreateSeries(string valuesCsvFormat, Index* index, string name)
{
	int totalElements = TotalCampCSV(valuesCsvFormat);
	if (totalElements != CountLabels(index))
	{
		return NULL;
	}
	else
	{
		Series* newSeries = new Series;
		newSeries->name = name;
		newSeries->index = index;
		newSeries->values = new	DataValue *[totalElements];

		string auxiliary[totalElements];
		ParsearCsv(auxiliary,valuesCsvFormat);

		for(int iAuxiliary = 0; iAuxiliary < totalElements; iAuxiliary++)
		{
			newSeries->values[iAuxiliary] = UndavDataValue::Create(auxiliary[iAuxiliary]);
		}
		return newSeries;
	}

}

string UndavSeries::GetName(const Series* series)
{
	return series->name;
}


Index* UndavSeries::GetIndex(Series* series)
{
	return series->index;
}


DataValue* UndavSeries::GetValueByIndexLocation(Series* series, unsigned int indexLocation)
{
	return (indexLocation < CountLabels(series->index) ? series->values[indexLocation] : NULL);
}


DataValue* UndavSeries::GetValueByIndexLabel(Series* series, string indexLabel)
{
	int cantElements = CountLabels(series->index);
	for(int iLabels = 0; iLabels < cantElements; iLabels++)
	{
		if (indexLabel == GetLabel(series->index, iLabels))
		{
			return series->values[iLabels];
		}
	}
	return NULL;
}

/*
 * Precondicion: @series es una instancia valida creada con alguna de las primitivas creacionales
 * Postcondicion: Devuelve una instancia valida de Series la cual
 * - Tiene como Index el conjunto (valores sin repetir) de Values de @series
 * - Tiene como elementos de la serie instancias de Value de tipo Number con el valor que cuenta la cantidad de repeticiones de su indice en @series
 */
UndavSeries::Series* UndavSeries::GetValueCounts(const Series* series)
{



}


void UndavSeries::Print(const Series* series)
{
	int totalElements = CountLabels(series->index);
	for(int indice = 0; indice < totalElements; indice++)
	{
		cout << GetLabel(series->index, indice) << "\t" << Get(series->values[indice]) << endl;
	}
	cout << "Name: " << GetName(series);


}

UndavSeries::Series* UndavSeries::Add(const Series* left, const Series* right)
{
	Series* newSerie = new Series;
	if(Equals(left->index, right->index))
	{
		newSerie->index = left->index;
		int countElements = CountLabels(newSerie->index);
		for(int iLabels = 0; iLabels < countElements ;iLabels++)
		{
			newSerie->values[iLabels] = Add(left->values[iLabels], right->values[iLabels]);
		}
	}
	else
	{
		newSerie = NULL;
	}
	return newSerie;
}

UndavSeries::Series*  UndavSeries::Map(const Series* series, MapFunction function)
{
	Series* newSeries = new Series;
	newSeries->index = series->index;
	int countElements =CountLabels(newSeries->index);
	for (int iValue  = 0; iValue < countElements; iValue++)
	{
		newSeries->values[iValue] = function(series->values[iValue]);
	}
	return newSeries;
}

void  UndavSeries::Map(Series* series, MapInPlaceFunction function)
{
	int countElements = CountLabels(series->index);
	for (int iValues = 0; iValues < countElements; iValues++)
	{
		series->values[iValues] = function(series->values[iValues]);
	}

}

ValueType  UndavSeries::GetType(const Series* series)
{
	int countElements = CountLabels(series->index);
	if(EqualType(series->values,countElements))
	{
		return (GetType(series->values[0]));
	}
	return UndavDataValue::Object;
}

bool EqualType(DataValue ** value, int countElements)
{
	bool equal = true;
	int iValue = 0;
	while(iValue < countElements && equal)
	{
		if( iValue +1 < countElements)
		{
			equal = GetType(value[iValue]) == GetType(value[iValue +1]) ;
		}
		iValue++;
	}
	return equal;
}


void UndavSeries::DestroySeries(Series* series)
{
	int countElements = CountLabels(series->index);
	for(int iLabels = 0; iLabels < countElements ;iLabels++)
	{
		DestroyDataValue(series->values[iLabels]);
	}
	DestroyIndex(series->index);
	delete series;
}
