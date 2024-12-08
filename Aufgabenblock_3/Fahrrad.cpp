/*
 * Fahrrad.cpp
 *
 *  Created on: 22 окт. 2024 г.
 *      Author: maxai
 */
#include"Fahrrad.h"
#include<cmath>
#include<iomanip>
#include"Weg.h"
double Fahrrad::dGeschwindigkeit() const
{
	double dTempGeschwindigkeit = p_dMaxGeschwindigkeit*pow(0.9, p_dGesamtStrecke/20);
	if(dTempGeschwindigkeit <= 12){//Falls die Geschwindigkeit von Fahrrad kleiner gleich 12 km/h ist, dann ist es weniger/gleich minimale moegliche Geschwindigkeit, deswegen muss 12 km/h sein(bro muss echt schneller fahren)
		//std::cout<<"Die geschwindigkeit von der Fahrrad ist 12km/h und kann nicht weiniger sein"<<std::endl<<std::endl;
		dTempGeschwindigkeit = 12;
		return dTempGeschwindigkeit;
	}
	else if( dTempGeschwindigkeit>= 12){//Falls die Geschwindigkeit von Fahrrad mehr als 12 km/h ist, dann muss es um 10% pro 20 km kleiner sein(aber nur bis 12 km/h)

		return dTempGeschwindigkeit;
	}
	else{
		//std::cout<<"Die geschwindigkeit von der Fahrrad jetzt 12km/h und kann nicht weiniger sein"<<std::endl<<std::endl;
		dTempGeschwindigkeit = 12;
		return dTempGeschwindigkeit;
	}

}
Fahrrad::Fahrrad(){}
Fahrrad::~Fahrrad(){}
Fahrrad::Fahrrad(const std::string& sName, double dGeschwindigkeit)
:Fahrzeug(sName,dGeschwindigkeit)
{

}

void Fahrrad::vAusgeben(std::ostream& os) const
{
	Fahrzeug::vAusgeben(os);
	std::cout<<resetiosflags(std::ios::right)
										<<setiosflags(std::ios::left)
										<<std::endl<<std::endl;

}

void Fahrrad::vZeichnen(const Weg& weg) const{
	double RelPosition = dGetAbschnittStrecke() / weg.dGetLaenge();//Position bezueglich dem Weg in bruch
	bZeichneFahrrad(p_sName, weg.sGetName(),RelPosition, dGeschwindigkeit());
}

void Fahrrad::vEinlesen(std::istream& is) {
	Fahrzeug::vEinlesen(is);
}
