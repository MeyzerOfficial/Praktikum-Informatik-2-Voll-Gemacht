/*
 * PKW.h
 *
 *  Created on: 22 окт. 2024 г.
 *      Author: maxai
 */

#ifndef PKW_H_
#define PKW_H_

#include"Fahrzeug.h"
#include"SimuClient.h"

class PKW : public Fahrzeug
{
public:
	//default Konstruktor
	PKW()= default;

	//Destruktor
	virtual ~PKW();

	//Konstruktor mit Name, Geschwindigkeit, Verbrauch und Tankvolumen
	PKW(const std::string& sName, double dGeschwindigkeit, double dVerbrauch, double dTankvolumen = 55);

	//Funktion, die Fahrzeuge mit dem Tank tankt
	double dTanken(double dMenge =  std::numeric_limits<double>::infinity()) override;

	//Funktion, die alle Daten vom Fahrzeuge in die Console ausgibt
	void vAusgeben(std::ostream& ) const override;

	//Funktion, die simuliert die bewegung von Fahrzeuge
	void vSimulieren() override;

	//Funktion, die Tempolimit anpasst und gibt die Geschwindigkeit zurueck
	double dGeschwindigkeit()const override;

	//Funktion, die ganze weg von PKW Zeichnet mit ein parameter (reference auf obj Weg)
	void vZeichnen(const Weg& weg) const override;
	//Getter TankInhalt
	double dGetTankinhalt() const ;
	//Funktion, die alle Daten vom Fahrzeuge aus datie Einliest
	void vEinlesen(std::istream& is) override;

private:
	//Verbrauch von PKW(fuel)
	double p_dVerbrauch;

	//Volumen von PKWs Tank
	double  p_dTankvolumen;

	//Fuel in Tank
	double p_dTankinhalt;
};



#endif /* PKW_H_ */
