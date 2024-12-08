/*
 * Fahrzeug.h
 *
 *  Created on: 15 окт. 2024 г.
 *      Author: maxai
 */

#ifndef FAHRZEUG_H_
#define FAHRZEUG_H_

#include <iostream>
#include <limits>
#include <string>
#include "Simulationsobjekt.h"
#include <memory>
#include"SimuClient.h"

extern double dGlobaleZeit;

class Weg;
class Verhalten;

class Fahrzeug : public Simulationsobjekt
{
public:
	//Konstruktor mit keine eingabenparameter
	Fahrzeug();

	//Konstruktor mit Name als eingabenparameter
	Fahrzeug(const std::string& sName);

	//Konstruktor mit Name und Geschwindigkeit eingabenparameter
	Fahrzeug(const std::string& sName, double dGeschwindigkeit);

	//Destruktor
	virtual ~Fahrzeug();

	//Standart Funktion um die Eingabe in Console Auszugeben
	void printf();

	//Funktion, die alle Daten vom Fahrzeuge in die Console ausgibt
	virtual void vAusgeben(std::ostream&) const override;

	//Funktion die Tabellenkopf ausgibt
	static void vKopf();

	//Funktion, die simuliert die bewegung von Fahrzeuge
	virtual void vSimulieren() override;

	//Funktion, die Fahrzeuge mit dem Tank tankt
	virtual double dTanken(double dMenge =  std::numeric_limits<double>::infinity());

	//Funktion, diegibt aktuelle Geschwindigkeit zurueck
	virtual double dGeschwindigkeit()const;

	//Getter fuer Gesamtstrecke
	double dGetGesamtStrecke() const;

	//Verbietet den Copy-Konstruktor
	Fahrzeug(const Fahrzeug&) = delete;

	//Ueberladung von Operator =, die Daten von anderen Objekt kopiert. Es  endert ein Objekt und braucht protected Member, deswegen steht in Klasse und nicht von Ausen
	Fahrzeug& operator=(const Fahrzeug& andere);

	//Funktion die Fahrzeuge auf neues Weg setzen //ein geeignetes Objekt erzeugt und in p pVerhalten speichert hat 1 Parameter (reference auf obj Weg)
	void vNeueStrecke(Weg&);

	//Funktion die Fahrzeuge auf neues Weg setzen //ein geeignetes Objekt erzeugt und in p pVerhalten speichert hat 2 Parameter (reference auf obj Weg und Start zeit)
	void vNeueStrecke(Weg&, double dStartZeit);

	//virtual Funktion, um Fahrzeuge bewegung zu zeichnen
	virtual void vZeichnen(const Weg& weg) const = 0;

	//Getter Abschnitt Strecke
	double dGetAbschnittStrecke() const;

	//Liesst die Engaben von Datei uber Fahrzeug an
	void vEinlesen(std::istream& is) override;

private:

protected:

	//Geschwindigkeit von Fahrzeug
	double p_dMaxGeschwindigkeit;

	//Gesamte Strecke, die den Fahrzeug gefahren hast
	double p_dGesamtStrecke ;

	//Gesamtzeit die den Fahrzeug gefahren hast
	double p_dGesamtZeit;

	//Diese speichert immer nur die auf dem aktuellen Weg zur¨uckgelegte Strecke
	double p_dAbschnittStrecke;

	//Unique pointer von klasse verhalten um zustand zu endern ohne neue objekt zu erstellen
	std::unique_ptr<Verhalten> p_pVerhalten;


};
//Ueberladung von Operator <<, um die Objekte nur mit std::cout ausgeben zu koennen. Es  endert ein Objekt nicht und braucht keine proteckted member, deswegen steht auser klasse
std::ostream& operator<<(std::ostream& os, const Fahrzeug& f);

//Ueberladung von Operator <, um die Gesamt gefahrene Strecke von Objekte zu vergleichen. Es  endert ein Objekt nicht keine proteckted member, deswegen steht auser klasse
bool operator<(const Fahrzeug& x, const Fahrzeug& y);


#endif /* FAHRZEUG_H_ */
