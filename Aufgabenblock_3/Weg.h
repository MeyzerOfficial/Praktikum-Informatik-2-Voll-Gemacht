/*
 * Weg.h
 *
 *  Created on: 4 нояб. 2024 г.
 *      Author: maxai
 */

#ifndef WEG_H_
#define WEG_H_

#include<iostream>
#include"Simulationsobjekt.h"
#include <list>
#include <memory>
#include <limits>
#include "Tempolimit.h"
#include<string>
#include"vertagt_aktion.h"
#include"vertagt_liste.h"


class Fahrzeug;
class Kreuzung;

class Weg : public Simulationsobjekt
{
public:
	//Standart Konstruktor
	Weg();

	//Konstruktor mit 3 Parameter( reference auf NAme, Laenge ses Wegs, Geschwindigkeit Limit
	Weg(const std::string& sName, double dLaenge, Tempolimit eTempolimit =Tempolimit::Autobahn,bool bUeberholverbot = true, const std::shared_ptr<Kreuzung> kZielKreuzung = nullptr);

	//Vertuaal Destruktor
	virtual ~Weg();

	//Getterbcon Geschwindigkeit Limit
	double dGetTempolimit() const;

	//Virtual Funktion von Simulation vob Weg
	virtual void vSimulieren() override;

	//Kopf von Tabelle ausgeben
	static void vKopf();

	//virtual Funktion, die daten von Weg Ausgibt
	virtual void vAusgeben(std::ostream& ) const override;

	//Getter fuer Laenge des Wegs
	double dGetLaenge() const;

	// Funktion die Fahrzeug auf dem Weg annimmt und in Liste speichert mit 1 parameter(uniue pointer auf Fzg)
	void vAnnahme(std::unique_ptr<Fahrzeug>);

	// Funktion die Fahrzeug auf dem Weg annimmt und in Liste speichert mit 2 parameter(uniue pointer auf Fzg und Startzeit)
	void vAnnahme(std::unique_ptr<Fahrzeug> fzg, double dStartZeit);

	//Getter fuer Wahrzeuge von Liste
	const  vertagt::VListe<std::unique_ptr<Fahrzeug>>& lGetFahrzeuge() const;

	// Funktion die Fahrzeug von dem Weg Abgibt und von der Liste Loeshcht,  mit 1 parameter(uniue pointer auf Fzg)
	std::unique_ptr<Fahrzeug> pAbgabe(const Fahrzeug&);

	//Getter Uberholverbot
	bool bGetUeberholverbot() const;

	//Getter VirtuelleSchranke
	double dGetVirtuelleSchranke() const;

	//Setter VirtuelleSchranke
	void vSetVirtuelleSchranke(double dVirtuelleSchranke);

	//Getter RueckWeg
	std::shared_ptr<Weg> wGetRueckWeg() const;

	//Getter ZielKreuzung
	std::shared_ptr<Kreuzung> kGetZielKreuzung() const;

	//Setter RueckWeg
	void vSetRueckWeg(std::weak_ptr<Weg> wRueckWeg);

private:
	//Laenge des Wegs
	double p_dLaenge ;

	//Liste von Fahrzeuge
	vertagt::VListe<std::unique_ptr<Fahrzeug>> p_pFahrzeuge;

	//Obj klasse Tempolimit, wo die begrenzungen von Geschwindigkeiten sind
	Tempolimit p_eTempolimit;

	//zeigt ob Ueberhol verboten ist
	bool p_bUeberholverbot;

	//double p_dVirtuelleSchranke = std::numeric_limits<double>::max();
	double p_dVirtuelleSchranke = 0;

	//weak pointer auf RueckWeg
	std::weak_ptr<Weg> p_wRueckWeg;

	//weak pointer auf ZielKreuzung
	std::weak_ptr<Kreuzung> p_kZielKreuzung;

protected:
};
//Ueberladung  von "<<" um das Weg leichter Auszugeben
std::ostream& operator<<(std::ostream& o, const Weg& x);

#endif /* WEG_H_ */
