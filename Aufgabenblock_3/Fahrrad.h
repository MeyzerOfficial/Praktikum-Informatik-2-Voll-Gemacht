/*
 * Fahrrad.h
 *
 *  Created on: 22 окт. 2024 г.
 *      Author: maxai
 */

#ifndef FAHRRAD_H_
#define FAHRRAD_H_

#include"Fahrzeug.h"
#include"SimuClient.h"

class Fahrrad : public Fahrzeug
{
public:
	//Konstruktor mit keine Eingabenparameter
	Fahrrad();

	//Konstruktor mit Name und Geschwindigkeit eingabenparameter
	Fahrrad(const std::string& sName, double dGeschwindigkeit);

	//Destruktor
	virtual ~Fahrrad();

	//Funktion, die Geschwindigkeit von Fahhraeder aendert
	double dGeschwindigkeit() const override;

	//Ausgeben Funktion fuer Fahrzeug
	void vAusgeben(std::ostream& ) const override;

	//Funktion, die ganze weg von Fahrrad Zeichnet mit ein parameter (reference auf obj Weg)
	void vZeichnen(const Weg& weg) const override;

	//Liesst die Engaben von Datei uber Fahrrad an
	void vEinlesen(std::istream& is) override;
private:
};





#endif /* FAHRRAD_H_ */
