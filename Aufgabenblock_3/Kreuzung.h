/*
 * Kreuzung.h
 *
 *  Created on: 30 нояб. 2024 г.
 *      Author: maxai
 */

#ifndef KREUZUNG_H_
#define KREUZUNG_H_

#include<iostream>
#include"Simulationsobjekt.h"
#include <vector>
#include <memory>
#include"Tempolimit.h"

class Fahrzeug;
class Weg;

class Kreuzung : public Simulationsobjekt
{
public:
	//Default Konstruktor
	Kreuzung();

	//Default Destruktor
	~Kreuzung() = default;

	//Konstruktor mit 2 Parameter(name, Tankstelle)
	Kreuzung(const std::string& sName, double dTankstelle);

	//Verbindet hin- und rueckweg miteinander und mit Start- und Zielkreuzungen
	static void vVerbinde(const std::string& sHinWegName, const std::string& sRueckWegName, double dWegLaenge, std::shared_ptr<Kreuzung> kStart, std::shared_ptr<Kreuzung> kZiel, Tempolimit eTempolimit =Tempolimit::Autobahn,bool bUeberholverbot = true);

	//Nimmt getankte menge von Tankstelle und Tankt das Auto
	void vTanken(Fahrzeug& fzg) ;

	//Nimmt fzg auf weg
	void vAnnahme(std::unique_ptr<Fahrzeug>, double dStartZeit);

	//Weg Simulation ruft
	void vSimulieren() override;

	//Funktion um das random Strasse zu waehlen
	std::shared_ptr<Weg> pZufaelligerWeg (Weg& wAktuellWeg) const;

	//Getter Tankstelle
	double dGetTankstelle() const;

	//Liesst die Engaben von Datei
	void vEinlesen(std::istream& is) override;

	//Kreuzung Daten im Console Auszugeben
	void vAusgeben(std::ostream& ) const override;

protected:


private:
	//Vector mit Wege
	std::vector<std::shared_ptr<Weg>> p_pWege;

	//Anzahl von fuel in Tankstelle
	double p_dTankstelle;
};

//Ueberladung von Operator <<, um die Objekte nur mit std::cout ausgeben zu koennen. Es  endert ein Objekt nicht und braucht keine proteckted member, deswegen steht auser klasse
std::ostream& operator<<(std::ostream& os, const Kreuzung& k);

#endif /* KREUZUNG_H_ */
