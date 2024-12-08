/*
 * Verhalten.cpp
 *
 *  Created on: 10 нояб. 2024 г.
 *      Author: maxai
 */
#include <iostream>
#include"Verhalten.h"
#include  "Fahrzeug.h"
#include"Weg.h"
#include<cmath>

Verhalten::~Verhalten(){}

double Verhalten::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const
{
	return 0.00;
}
Weg& Verhalten::dGetWeg() const
{
	return p_Weg;
}
Verhalten::Verhalten(Weg& weg)
:p_Weg(weg)
{}

