#include <iostream> //Libreria principal de c++
#include <string> //Libreria para poder trabajar con strings
#include <fstream>
#include <iomanip>
#include <windows.h>
using namespace std;

const int MAX = 20; //Variable global

struct tPartidos {
	int votos, dHondt, escanos = 0, division = 1;
	string nombrePartido;
	bool entra;
};

typedef tPartidos tArrayVotos[MAX];

double sumaTotal(tArrayVotos partidos, double coeficiente, int contador); 
void compruebaPartido(tArrayVotos partidos, double techo, int contador);
int calculaMayor(tArrayVotos partidos, int contador);
void calculaEscanos(tArrayVotos partidos, int contador, int numEscanos);

int main() {
	tArrayVotos partidos;
	int contador = 0, escanos, contparlamento = 0;
	double coeficiente, total;

	cout << "Nombre del partido: ";
	getline(cin, partidos[contador].nombrePartido);

	while (partidos[contador].nombrePartido != "0") {
		cout << "Numero de votos: ";
		cin >> partidos[contador].votos;
		contador++;
		cout << "Nombre del partido: ";
		cin.ignore();
		getline(cin, partidos[contador].nombrePartido);
	}
	
	cout << "Coeficiente: ";
	cin >> coeficiente;
	system("cls");

    total = sumaTotal(partidos, coeficiente, contador);
	compruebaPartido(partidos, total, contador);

	cout << endl << setw(10) << left << "PARTIDOS" << setw(9) << right << "VOTOS" << endl;
	for (int i = 0; i < contador; i++) {
		if (partidos[i].entra == true) {
			cout << setw(10) << left << partidos[i].nombrePartido << setw(9) << right << partidos[i].votos << endl;
			contparlamento++;
		}
	}

	cout << endl << "Numero de escanos: ";
	cin >> escanos;

	calculaEscanos(partidos, contparlamento, escanos);

	cout << endl << setw(10) << left << "PARTIDOS" << setw(9) << right << "ESCANOS" << endl;
	for (int p = 0; p < contparlamento; p++)
		cout << setw(10) << left << partidos[p].nombrePartido << setw(9) << right << partidos[p].escanos << endl;

	cout << endl;
	system("pause");

	return 0;
}

double sumaTotal(tArrayVotos partidos, double coeficiente, int contador) { //sumamos el total de los votos de los partidos
	int total = 0; //Variables locales
	double resultado;

	for (int n = 0; n < contador; n++) 
		total += partidos[n].votos; //vamos acumulando el total de los votos

	resultado = total * coeficiente; //lo multiplicamos por un coeficente

	return resultado;
}

void compruebaPartido(tArrayVotos partidos, double techo, int contador) {
	for (int i = 0; i < contador; i++) {
		if (partidos[i].votos < techo)
			partidos[i].entra = false;
		else
			partidos[i].entra = true;
	}
}

int calculaMayor(tArrayVotos partidos, int contador) { //Calcula el partido con mas votos
	int temporal = 0, temporal1 = 0;
	for (int i = 0; i < contador - 1; i++) {
		if (partidos[i].dHondt < partidos[i + 1].dHondt)
			temporal = i + 1;
		else
			temporal1 = i;

		if (partidos[temporal].dHondt > partidos[temporal1].dHondt)
			temporal1 = temporal;
		else
			temporal1 = temporal1;
	}

	return temporal1;
}

void calculaEscanos(tArrayVotos partidos, int contador, int numEscanos) {
	int pos;

	for (int i = 0; i < numEscanos; i++) {
		for (int j = 0; j < contador; j++)
			partidos[j].dHondt = partidos[j].votos / (partidos[j].division);

		pos = calculaMayor(partidos, contador);
		partidos[pos].escanos++;
		partidos[pos].division++;
	}
}

//Const significa que es una constante, no se puede cambiar el valor
//int = numero entero
//double = decimal
//bool = true / false
//void = no va a devolver nada
//for --> bucle del que no se puede salir
// while --> bucle del que si se puede salir
//typedef tPartidos tArrayVotos[MAX] esto es la lista
//struct el partido con votos, nombre y otras variables