/*
 * Parken.h
 *
 *  Created on: 12 нояб. 2024 г.
 *      Author: maxai
 */

#ifndef PARKEN_H_
#define PARKEN_H_


#include <iostream>

class Verhalten;
class Fahrzeug;
class Weg;

class Parken : public Verhalten
{
public:
	//Konstruktor mit 2 parametrer(referens auf weg und Startpunkt des Gefahr
	Parken(Weg& weg, double dStartZeitPunkt );

	//Destruktor
	~Parken();

	// gibt gefahrene Strecke zurueck, hast 2 parameter obj vin Klasse Fahrzeug und Zeitinterval, die verpasst hast)
	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override;
private:
	//Start punkt, wenn Fahrzeug sich bewegen laesst
	double p_dStartZeitPunkt;
};


#endif /* PARKEN_H_ */
