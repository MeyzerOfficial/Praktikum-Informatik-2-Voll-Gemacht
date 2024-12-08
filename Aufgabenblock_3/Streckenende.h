/*
 * Streckenende.h
 *
 *  Created on: 14 нояб. 2024 г.
 *      Author: maxai
 */

#ifndef STRECKENENDE_H_
#define STRECKENENDE_H_
#include<iostream>
#include"Fahrausnahme.h"

class Fahrzeug;
class Weg;



class Streckenende : public Fahrausnahme
{
public:
	//Konstruktor mit 2 parameter (reference auf obj FAhrzeug und reference auf obj Weg)
	Streckenende(Fahrzeug& fahrzeug, Weg& weg);

	//Funktion, die Ausnahme bearbeitet
	void vBearbeiten() const override;
};



#endif /* STRECKENENDE_H_ */
