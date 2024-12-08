/*
 * Tempolimit.h
 *
 *  Created on: 8 нояб. 2024 г.
 *      Author: maxai
 */

#ifndef TEMPOLIMIT_H_
#define TEMPOLIMIT_H_

#include<limits>
//classe die Geschwindigkeit begrenzungen erhaelt
enum class Tempolimit : int
{
	Innerorts = 50,
	Landstraße = 100,
	Autobahn = std::numeric_limits<int>::max()
};


#endif /* TEMPOLIMIT_H_ */
