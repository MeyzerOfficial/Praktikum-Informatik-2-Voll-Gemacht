/*
 * PKW.cpp
 *
 *  Created on: 22 окт. 2024 г.
 *      Author: maxai
 */

#include "PKW.h"
#include<iomanip>
#include"Verhalten.h"
#include"Fahrausnahme.h"
#include"Weg.h"
#include"Algorithm"
double dEpsilon = 0.00001;

PKW::PKW(const std::string& sName, double dGeschwindigkeit, double dVerbrauch, double dTankvolumen)
:Fahrzeug(sName,dGeschwindigkeit), p_dVerbrauch(dVerbrauch), p_dTankvolumen(dTankvolumen), p_dTankinhalt(dTankvolumen/2)//Initialisiert Tankinhalt wie 1/2 von Tankvolumen
{}
PKW::~PKW()
{}


double PKW::dTanken(double dMenge)
{
	if(!dMenge ){//std::numeric_limits<double>::infinity()){
		p_dTankinhalt = p_dTankvolumen;
		return p_dTankinhalt;
	}
	else if(p_dTankinhalt + dMenge >= p_dTankvolumen){
		p_dTankinhalt = p_dTankvolumen;
		return p_dTankinhalt;//Verhindert Tanken mehr, als moglich
	}
	else{
		p_dTankinhalt += dMenge;
		return p_dTankinhalt;
	}

}


void PKW::vSimulieren()
{

	if(p_dTankinhalt <= 0){
		std::cout<<"Die Tankinhalt von diesem Fahrzeug ist leer, deswegen kann es nicht weiterfahren."<<std::endl;
		p_dZeit = dGlobaleZeit;
		return;//Kein fuel kein Fahrt
	}
	//falls hat Fuel, dann simuliert
	if(p_dTankinhalt>0){
		double dTeilStrecke = p_dGesamtStrecke;
		Fahrzeug::vSimulieren();
		p_dTankinhalt -= (p_dGesamtStrecke - dTeilStrecke) * p_dVerbrauch/100;
		if(p_dTankinhalt < 0){
			p_dTankinhalt = 0;
		}
	}

}



void PKW::vAusgeben(std::ostream& os) const
{
	Fahrzeug::vAusgeben(os);
	std::cout<<std::setw(20)<<p_dVerbrauch*p_dGesamtStrecke/100
			<<std::setw(20)<<p_dTankinhalt
			<<std::setw(20)<<"Andere daten"
			<<std::setw(20)<<" Verbrauch in l/100 km: "<<p_dVerbrauch//Nur fuer Aufgabe 8
			<<std::setw(20)<<"Tankvolumen: "<<p_dTankvolumen//Nur fuer Aufgabe 8
			<<resetiosflags(std::ios::right)
			<<setiosflags(std::ios::left)
			<<std::endl<<std::endl;

}

double PKW::dGeschwindigkeit()const
{
	if (p_pVerhalten) {
		const Weg& weg = p_pVerhalten->dGetWeg();//pointer
		double tempolimit = weg.dGetTempolimit();//reference


		return std::min(tempolimit, p_dMaxGeschwindigkeit);//return minimale von beiden um begrenzung vin Geschwindigkeit limit zu vermeiden
	}

	return p_dMaxGeschwindigkeit;

}
void PKW::vZeichnen(const Weg& weg) const{
	double RelPosition = dGetAbschnittStrecke() / weg.dGetLaenge();//Position bezueglich dem Weg in bruch
	bZeichnePKW(p_sName, weg.sGetName(),RelPosition, dGeschwindigkeit(), p_dTankinhalt);
}

double PKW::dGetTankinhalt() const
{
	return p_dTankinhalt;
}

void PKW::vEinlesen(std::istream& is) {
	Fahrzeug::vEinlesen(is);
	is >>p_dVerbrauch>>p_dTankvolumen;
	p_dTankinhalt = p_dTankvolumen/2;
}
