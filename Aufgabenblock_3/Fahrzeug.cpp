/*
 * Fahrzeug.cpp
 *
 *  Created on: 15 окт. 2024 г.
 *      Author: maxai
 */
#include<iostream>
#include"Fahrzeug.h"
#include<iomanip>
#include<ostream>
#include"Weg.h"
#include "Verhalten.h"
#include"Fahren.h"
#include"Parken.h"
#include"Fahrausnahme.h"

Fahrzeug::Fahrzeug() :
Simulationsobjekt() {
	std::cout << " Neue Fahrzeug : Name = " << p_sName << ", ID = " << p_iID
			<< std::endl;
}

Fahrzeug::Fahrzeug(const std::string &sName) :
						Simulationsobjekt(sName) {
	std::cout << " Neue Fahrzeug : Name = " << p_sName << ", ID = " << p_iID
			<< std::endl;
}

Fahrzeug::~Fahrzeug() {
	std::cout << "Fahrzeug geloescht: Name = " << p_sName << ", ID = " << p_iID
			<< std::endl;
}

Fahrzeug::Fahrzeug(const std::string &sName, double dGeschwindigkeit) :
						Simulationsobjekt(sName), p_dMaxGeschwindigkeit(dGeschwindigkeit) {

	int GrosserGleichANull = (p_dMaxGeschwindigkeit >= 0) ? 0 : 1; //Prueft ob die Geschwindigkeit groesser gleich Null ist
	if (GrosserGleichANull == 0) {
		std::cout << "Neue Fahrzeug : Name = " << p_sName
				<< ", Geschwindigkeit = " << p_dMaxGeschwindigkeit << std::endl;
	} else {
		std::cout << "Die Geschwindigkeit muss Grosser Gleich 0 sein "
				<< std::endl;
	}

}

void Fahrzeug::printf() {
	std::cout << " Fahrzeug Name = " << p_sName << ", ID = " << p_iID
			<< std::endl;
}

void Fahrzeug::vAusgeben(std::ostream &os) const {
	Simulationsobjekt::vAusgeben(os);
	std::cout << std::setw(13) << dGeschwindigkeit() << std::setw(16)
							<< p_dGesamtStrecke << std::setw(16) << p_dAbschnittStrecke;

}

void Fahrzeug::vKopf() {
	std::cout << setiosflags(std::ios::left) << std::setw(5) << "ID"
			<< std::setw(10) << "Name" << std::setw(20) << "MaxGeschwindigkeit"
			<< std::setw(20) << "Gesamtstrecke" << std::setw(20)
			<< "AbschnittStrecke" << std::setw(20) << "Gesamtverbrauch"
			<< std::setw(20) << "Tankinhalt" << std::endl;
	std::cout
	<< "-----------------------------------------------------------------------------------------------------------"
	<< std::endl;
}

void Fahrzeug::vSimulieren() {
	if (dGlobaleZeit > p_dZeit) { //prueft ob man die Globale Zeit nicht kleiner als die Zeit von Letzte simulation gemacht hast (also z.B. nicht dGlobaleZeit -= 1)

		double dZeitunterschied = dGlobaleZeit - p_dZeit; //Wie viel Zeit gelaufen war
		p_dGesamtZeit += dZeitunterschied;
		double dTeilStrecke;
		try {
			dTeilStrecke = p_pVerhalten->dStrecke(*this, dZeitunterschied);
		} catch (Fahrausnahme &exeption) {
			exeption.vBearbeiten();
		}
		p_dGesamtStrecke += dTeilStrecke;
		p_dAbschnittStrecke += dTeilStrecke;

		p_dZeit = dGlobaleZeit;

	}
}

double Fahrzeug::dTanken(double dMenge) {
	return 0.0;
}

double Fahrzeug::dGeschwindigkeit() const {
	return p_dMaxGeschwindigkeit;
}
double Fahrzeug::dGetGesamtStrecke() const {
	return p_dGesamtStrecke;
}

std::ostream& operator<<(std::ostream &os, const Fahrzeug &f) {
	f.vAusgeben(os);
	return os;
}
bool operator<(const Fahrzeug &x, const Fahrzeug &y) {
	if (x.dGetGesamtStrecke() < y.dGetGesamtStrecke()) {
		std::cout << "die GesamtStrecke von Erstem Fahrzeug ist grosser "
				<< std::endl;
		return true; //gibt True zurueck,falls die bisher zur¨uckgelegte Gesamtstrecke vom aktuellen Objekt kleiner als die vom Vergleichsobjekt ist.
	} else if (x.dGetGesamtStrecke() == y.dGetGesamtStrecke()) {
		std::cout << "die GesamtStrecke  Fahrzeuge sind gleich " << std::endl;
		return false;
	} //gibt False zurueck, falls die bisher zur¨uckgelegte Gesamtstrecke vom aktuellen Objekt gleich die vom Vergleichsobjekt ist.
	else {
		std::cout << "die GesamtStrecke Zweitem Objekt ist grosser  "
				<< std::endl;
		return false; //gibt False zurueck, falls die bisher zur¨uckgelegte Gesamtstrecke vom aktuellen Objekt groesser als die vom Vergleichsobjekt ist.
	}
}
Fahrzeug& Fahrzeug::operator=(const Fahrzeug &andere) {
	this->p_sName = andere.p_sName;
	this->p_dMaxGeschwindigkeit = andere.p_dMaxGeschwindigkeit;
	return *this; //Kopiert die Name und Geschwindigkeit von ein Objekt zu anderen
}

void Fahrzeug::vNeueStrecke(Weg &weg) {
	p_dAbschnittStrecke = 0.0; //AbschnittStrecke = 0, weil das Anfang von weg ist
	p_pVerhalten = std::make_unique<Fahren>(weg); //keine Startzeit gegeben => das Fahrzeug faehrt schon seit Anfang
}
void Fahrzeug::vNeueStrecke(Weg &weg, double dStartZeit) {
	p_dAbschnittStrecke = 0.0; //AbschnittStrecke = 0, weil das Anfang von weg ist
	p_pVerhalten = std::make_unique<Parken>(weg, dStartZeit); // Startzeit gegeben => das Fahrzeug Parken bis StartZeit
}

double Fahrzeug::dGetAbschnittStrecke() const {
	return p_dAbschnittStrecke;
}

void Fahrzeug::vEinlesen(std::istream& is) {
	Simulationsobjekt::vEinlesen(is);
	is >>p_dMaxGeschwindigkeit;
}
