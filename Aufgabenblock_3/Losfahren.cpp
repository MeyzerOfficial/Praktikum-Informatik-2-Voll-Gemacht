/*
 * Losfahren.cpp
 *
 *  Created on: 14 нояб. 2024 г.
 *      Author: maxai
 */

#include"Losfahren.h"
#include<iostream>
#include "Fahrzeug.h"
#include "Weg.h"
#include<memory>



Losfahren::Losfahren(Fahrzeug& fahrzeug, Weg& weg)
:Fahrausnahme(fahrzeug, weg)
{}

void Losfahren::vBearbeiten() const
{
	std::cout<<"Die Ausnahme (Losfahren) fuer Fahrzeug: "<<p_fahrzeug.sGetName()<<" auf dem: "<<p_weg.sGetName()<<" Weg um: "<<dGlobaleZeit<<" Uhr"<<std::endl<<std::endl;
	p_weg.vAnnahme(p_weg.pAbgabe(p_fahrzeug));// man muss Verhalten von obj aendern, deswegen muss man erstmal fzg von Liste Abgeben und dann mit neur Verhalten Annaehmen


}
