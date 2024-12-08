/*
 * Fahren.cpp
 *
 *  Created on: 12 нояб. 2024 г.
 *      Author: maxai
 */
#include <iostream>
#include"Verhalten.h"
#include  "Fahrzeug.h"
#include"Weg.h"
#include<cmath>
#include "Fahren.h"
#include"Streckenende.h"


Fahren::Fahren(Weg& weg)
:Verhalten(weg)
{}


Fahren::~Fahren(){}

double Fahren::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const
{
	//berechnet gefahrene  Strecke
	double dTeilStrecke = aFzg.dGeschwindigkeit()*dZeitIntervall;
	Weg& weg = dGetWeg();
	double dVirtuelleSchrank = weg.dGetVirtuelleSchranke();
	//berechnet rest von  Strecke
	double dRestVonStrecke = p_Weg.dGetLaenge() - aFzg.dGetAbschnittStrecke();
	//falls am ende ist Ausnahme Streckenende
	if(dRestVonStrecke- dEpsilon <= 0 ){
		//std::cout<<"Das Fahrzeug: "<<aFzg.sGetName()<<" steht, weil das die Ende von Weg ist "<<std::endl<<std::endl;
		throw Streckenende(aFzg, p_Weg);}
	//falls Reststrecke kleiner als die Strecke, die Fahrzeug fahren kann, dann faehrt Fahrzeug nur Rest von Strecke
	else if(dRestVonStrecke< dTeilStrecke){
		std::cout<<" Rest von Strecke fuer: "<<aFzg.sGetName()<<" ist: "<< dRestVonStrecke<<std::endl<<std::endl;
		return dRestVonStrecke;}

	else if(aFzg.dGetAbschnittStrecke() + dTeilStrecke  > dVirtuelleSchrank - dEpsilon  ){//wenn Fahrzeug Ueberholt wills kann er nicht
		return dVirtuelleSchrank - aFzg.dGetAbschnittStrecke();//kann nur bis zum Schranke Fahren
	}
	else{
		weg.vSetVirtuelleSchranke(aFzg.dGetAbschnittStrecke() + dTeilStrecke );//Set Virtual Schranke fuer Ueberholverbot am Erste in Reiche Fahrzeug
		return dTeilStrecke;
	}
}
