/*
 * Fahrausnahme.h
 *
 *  Created on: 14 нояб. 2024 г.
 *      Author: maxai
 */

#ifndef FAHRAUSNAHME_H_
#define FAHRAUSNAHME_H_

#include <exception>
#include <string>
#include <iostream>

class Fahrzeug;
class Weg;

class Fahrausnahme : public std::exception
{
public:
	//Konstruktor mit 2 parameter (reference auf obj FAhrzeug und reference auf obj Weg)
	Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg);

	//virtual default destruktor(ohne das werden die destruktor in unterklassen nicht arbeiten) Und default um direkt zu sehen, das es leer ist, aber kann man auch das in cpp file schreiben
	virtual ~Fahrausnahme() = default;

	//virtual Funktion, die Ausnahme bearbeitet
	virtual void vBearbeiten() const = 0;
protected:
	//reference auf obj fahrzeug
	Fahrzeug& p_fahrzeug;

	//reference auf obj Weg
	Weg& p_weg;

};



#endif /* FAHRAUSNAHME_H_ */
