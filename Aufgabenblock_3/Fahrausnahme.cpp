/*
 * Fahrausnahme.cpp
 *
 *  Created on: 14 нояб. 2024 г.
 *      Author: maxai
 */
#include "Fahrausnahme.h"
#include<iostream>
#include"Weg.h"
#include"Fahrzeug.h"


Fahrausnahme::Fahrausnahme(Fahrzeug& fahrzeug, Weg& weg)
:p_fahrzeug(fahrzeug),  p_weg(weg)
{}
