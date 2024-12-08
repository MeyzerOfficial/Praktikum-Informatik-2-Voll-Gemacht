/*
 * Fahren.h
 *
 *  Created on: 12 нояб. 2024 г.
 *      Author: maxai
 */

#ifndef FAHREN_H_
#define FAHREN_H_

#include <iostream>


class Verhalten;
class Fahrzeug;
class Weg;

class Fahren : public Verhalten
{
public:
	//Konstruktor mit 1 parametrer(referens auf weg )
	Fahren( Weg& weg);

	//Destruktor
	~Fahren();

	// Gibt gefahrene Strecke zurueck, hast 2 parameter obj vin Klasse Fahrzeug und Zeitinterval, die verpasst hast)
	double dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const override;

private:

};



#endif /* FAHREN_H_ */
