#include <iostream>
#include "DataValue.h"
#include "Index.h"
#include "Series.h"

using namespace std;
using UndavDataValue::DataValue;
using UndavSeries::Series;
using UndavIndex::Index;

void DataValueExamples();
void IndexExamples();
void SeriesExample();

void LoadDataValues(DataValue * numbers[2], DataValue * booleans[2]);
void LoadMixedDataValues(DataValue* values[4]);
void ShowAdd(DataValue* left, DataValue* rigth);
void DestroyDataValues(DataValue* values[], int countValues);

void ShowIndex(Index* index);

int main() {
	//DataValueExamples();
	//IndexExamples();
	SeriesExample();

	return 0;
}

void DataValueExamples(){
	cout<<"Ejemplo de uso del TDA DataValue"<<endl;
	DataValue* numbers[2];
	DataValue* booleans[2];
	DataValue* mixed[4];
    LoadMixedDataValues(mixed);
    LoadDataValues(numbers, booleans);
    for(int mixedIndex =0; mixedIndex<4; ++mixedIndex)
	{
		for(int notMixedIndex =0 ; notMixedIndex<2; ++notMixedIndex)
		{
			ShowAdd(numbers[notMixedIndex], mixed[mixedIndex]);
			ShowAdd(booleans[notMixedIndex], mixed[mixedIndex]);
		}
	}
    cout<<endl;
	DestroyDataValues(numbers, 2);
	DestroyDataValues(booleans, 2);
	DestroyDataValues(mixed, 4);
}

void IndexExamples(){
	cout<<"Ejemplo de uso del TDA Index"<<endl;
	Index* indexRange = UndavIndex::CreateIndex(5);
	Index* indexLabeled = UndavIndex::CreateIndex("Argentina,Brasil,Peru,Bolivia,Chile");
	ShowIndex(indexRange);
	ShowIndex(indexLabeled);
	UndavIndex::DestroyIndex(indexRange);
	UndavIndex::DestroyIndex(indexLabeled);
}

void SeriesExample(){
	cout<<"Ejemplo de uso de TDA Series"<<endl;
	Index* index = UndavIndex::CreateIndex("Cuba,Uruguay,Estados Unidos,Rusia,Argentina");
	Series* deportesPopulares = UndavSeries::CreateSeries("Beisbol,Futbol,Beisbol,Ajedrez,Futbol", index, "Deportes mas populares");
	//Series* valueCounts= UndavSeries::GetValueCounts(deportesPopulares);
	UndavSeries::Print(deportesPopulares);
	//UndavSeries::Print(valueCounts);
	UndavSeries::DestroySeries(deportesPopulares);
	//UndavSeries::DestroySeries(valueCounts);
}

void LoadMixedDataValues(DataValue* values[4])
{
	values[0] = UndavDataValue::CreateNumber(1000);
	values[1] = UndavDataValue::CreateString(" Algoritmos ");
	values[2] = UndavDataValue::CreateNull();
	values[3] = UndavDataValue::CreateBoolean(true);
}

void LoadDataValues(DataValue * numbers[2], DataValue * booleans[2])
{
    for(int i = 0;i < 2;++i){
        numbers[i] = UndavDataValue::CreateNumber((i + 1) * 10);
        booleans[i] = UndavDataValue::CreateBoolean((bool)((i)) % 2);
    }
}

void DestroyDataValues(DataValue* values[], int countValues)
{
	for(int i=0; i < countValues;++i)
	{
		UndavDataValue::DestroyDataValue(values[i]);
	}
}

void ShowAdd(DataValue* left, DataValue* rigth){
	DataValue* result = UndavDataValue::Add(left, rigth);
	cout<<"["<<UndavDataValue::Get(left)<<"] + ["<<UndavDataValue::Get(rigth)<<"] = ["<<UndavDataValue::Get(result)<<"]"<<endl;
	UndavDataValue::DestroyDataValue(result);
}

void ShowIndex(Index* index){
	int countLabels = UndavIndex::CountLabels(index);
	cout<<"(";
	if(countLabels>0){
		cout<<UndavIndex::GetLabel(index, 0);
		for(int i = 1; i <countLabels;++i)
		{
			cout<<","<<UndavIndex::GetLabel(index, i);
		}
	}
	cout<<")"<<endl;
}
