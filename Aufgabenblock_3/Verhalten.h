/*
 * Verhalten.h
 *
 *  Created on: 10 нояб. 2024 г.
 *      Author: maxai
 */

#ifndef VERHALTEN_H_
#define VERHALTEN_H_
#include<iostream>

class Fahrzeug;
class Weg;

class Verhalten {
public:
	//virtual Destruktor
	virtual ~Verhalten();

	//Konstruktor mit 1 parametrer(referens auf weg )
	Verhalten(Weg& weg);

	//virtual Funktion, gibt gefahrene Strecke zurueck, hast 2 parameter obj vin Klasse Fahrzeug und Zeitinterval, die verpasst hast)
	virtual double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const ;

	//Konstante um double Zahlen zu vergleichen
	static constexpr double dEpsilon = 0.00001;

	//getter von Weg
	Weg& dGetWeg() const;
protected:
	// reference auf Weg
	Weg& p_Weg;
};


#endif /* VERHALTEN_H_ */
