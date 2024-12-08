/*
 * Simulationsobjekt.h
 *
 *  Created on: 4 нояб. 2024 г.
 *      Author: maxai
 */

#ifndef SIMULATIONSOBJEKT_H_
#define SIMULATIONSOBJEKT_H_

#include<iostream>
#include<string>


class Simulationsobjekt
{
public:
	//Konstruktor mit 1 Parameter (reference auf Name)
	Simulationsobjekt(const std::string& sName);

	virtual ~Simulationsobjekt();
	//Standart Konstruktor
	Simulationsobjekt();

	//Virtual Funktion, die Daten von Obj in console ausgibt
	virtual void vAusgeben(std::ostream& ) const;

	//Um copy obj zu vermeiden
	Simulationsobjekt(const Simulationsobjekt&) = delete;

	//um Zuweisung(присваивание) zu vermeiden
	Simulationsobjekt& operator=(const Simulationsobjekt&) = delete;

	//Uberladung von operator, um die Fahrzeuge nach ID zu vergleichen//endert das object, deswegen drin in klasse
	bool operator==(const Simulationsobjekt& andere) const;

	//Virtual Feunktion, um die Simulation von Simulations Objekte  zu fuhren
	virtual void vSimulieren();

	//Getter fuer die Name
	std::string sGetName() const;

	//Getter fuer die aktuelle Zeit
	double dGetdZeit() const;

	//Virtual Funktion, die alle Daten vom Simulationsobjekt aus datie Einliest
	virtual void vEinlesen(std::istream& is );


private:
	//Max current ID von Fahrzeug
	static int p_iMaxID;

protected:
	//Name von fahrzeug
	std::string p_sName;

	//ID von Fahrzeug
	int p_iID;

	//Zeit von letztes Simulation
	double p_dZeit = 0;

};
//Ueberladen von operator >> um die daten von File einlesen zu koennen und in variablen setzen
std::istream& operator>>(std::istream& is, Simulationsobjekt& obj);





#endif /* SIMULATIONSOBJEKT_H_ */
