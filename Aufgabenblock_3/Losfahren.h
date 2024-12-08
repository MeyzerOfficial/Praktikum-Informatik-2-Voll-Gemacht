/*
 * Losfahren.h
 *
 *  Created on: 14 нояб. 2024 г.
 *      Author: maxai
 */

#ifndef LOSFAHREN_H_
#define LOSFAHREN_H_
#include<iostream>
#include"Fahrausnahme.h"

class Fahrzeug;
class Weg;



class Losfahren : public Fahrausnahme
{
public:
	//Konstruktor mit 2 parameter (reference auf obj FAhrzeug und reference auf obj Weg)
	Losfahren(Fahrzeug& fahrzeug, Weg& weg);

	//virtual Funktion, die Ausnahme bearbeitet
	void vBearbeiten() const override;
};



#endif /* LOSFAHREN_H_ */
