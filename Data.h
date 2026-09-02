#ifndef DATA_H//serve para que o arquivo data.h não seja executado mais de uma vez
#define DATA_H

#define INFINITE 0//criando a constante ifinite que assume o valor 0

//bibliotecas
#include <iostream>//cout e cin
#include <string>//string
#include <fstream>//ler e abrir arquivos
#include <math.h>//funções matematica
#include <memory>//usado para shared_ptr
using namespace std;

//uma classe é basicamente uma struct que guarda dados e funções relacionadas a esses dados
class Data{
public://tudo que estiver no public pode ser usado em outras partes do algoritimo
	Data( int, char * );//é o contrutor da classe que basicamente permite a inicialização de objetos criados da classe data

	void read();//ler as instancias
	void printMatrixDist();//imprime a matriz distancia
	//inline é uma característica da função, relacionada à forma como ela pode ser definida/otimizada
	inline int getDimension(){ return dimension; };//pegar a dimensão/quantidade de cidades utilizadas no tsp
	inline double getDistance(int i, int j){return distMatrix[i-1][j-1]; };//serve para consultar na matriz qual é a distância entre as cidades i e j
	//distMatrix é a matriz de custos/distâncias entre as cidades
	inline double **getMatrixCost(){return distMatrix.get(); }//serve para entregar a matriz de custos/distâncias para outra parte do algoritimo
	//cordenadas cartesianas da cidade
	inline double getXCoord(int i){return xCoord[i-1];}//guarda a coordenada x
	inline double getYCoord(int i){return yCoord[i-1];}//guarda a coordenada y
	inline bool getExplicitCoord(){return explicitCoord; };//pergunta se a instância possui coordenadas explícitas
	// Explícita → arquivo fornece X e Y das cidades.
	// Implícita → arquivo fornece diretamente as distâncias/custos.

	string getInstanceName();//Get instance's name

private://os dados ficam protegidos dentro da classe e você fornece funções para acessá-los
	string instaceName;//nome da instancia
	int nbOfPar;//provavelmente numero de parametros

	int dimension;//dimensao da instancia

	shared_ptr<double*[]> distMatrix;//matriz
	shared_ptr<double[]> xCoord, yCoord;//cordenadas

	//Computing Distances
	static double CalcDistEuc ( double *, double *, int , int );//calcula distância Euclidiana entre dois pontos d = sqrt((x1-x2)² + (y1-y2)²)
	static double CalcDistAtt ( double *, double *, int , int );// ATT: distância pseudo-Euclidiana da TSPLIB r = sqrt((Δx² + Δy²) / 10); arredonda para cima quando necessário.
	static double CalcDistGeo ( double *, double *, int , int );// GEO: distância geográfica entre duas cidades usa latitude/longitude e calcula a distância sobre a superfície da Terra
	static void CalcLatLong ( double *, double *, int , double *, double* );//conversão das coordenadas para latitude/longitude em radianos, que depois será usada pela CalcDistGeo()

	bool explicitCoord;//boleano para cooredenadas explicitas
};

#endif//#endif é o fechamento do #ifndef do include guard