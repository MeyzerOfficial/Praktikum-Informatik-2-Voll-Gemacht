/*
 * Parken.cpp
 *
 *  Created on: 12 нояб. 2024 г.
 *      Author: maxai
 */

#include<iostream>
#include"Verhalten.h"
#include"Parken.h"
#include "Fahrzeug.h"
#include"Weg.h"
#include "Fahren.h"
#include"Losfahren.h"

//Globale Uhr
extern double dGlobaleZeit;

Parken::Parken(Weg& weg, double dStartZeitPunkt )
:Verhalten(weg), p_dStartZeitPunkt(dStartZeitPunkt)
{}
Parken::~Parken(){}
double Parken::dStrecke(Fahrzeug& aFzg, double dZeitIntervall) const
{
	//wenn fertig zu fahren dann faehrt
	if(dGlobaleZeit+ dEpsilon >= p_dStartZeitPunkt && dGlobaleZeit-dEpsilon <= p_dStartZeitPunkt){

		throw Losfahren(aFzg, p_Weg);
	}else{
		//wenn nich steht
		return 0.00;
	}
}
