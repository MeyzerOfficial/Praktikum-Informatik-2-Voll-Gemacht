/*
 * Kreuzung.cpp
 *
 *  Created on: 30 нояб. 2024 г.
 *      Author: maxai
 */

#include"Kreuzung.h"
#include "Weg.h"
#include"Fahrzeug.h"
#include <vector>
#include <memory>
#include<random>
#include"PKW.h"

double dEpsilon1 = 0.00001;
Kreuzung::Kreuzung()
:p_dTankstelle(0.0)
{}

Kreuzung::Kreuzung(const std::string& sName, double dTankstelle)
:Simulationsobjekt(sName), p_dTankstelle(dTankstelle)
{}

/////////////////////////////////
void Kreuzung::vTanken(Fahrzeug& fzg)
{
	if(p_dTankstelle  >0 ){//nur wenn fuel in Tankstelle gibt
		PKW* pkw = dynamic_cast<PKW*>(&fzg);//wir Arbeiten mit Fahrzeug, aber wir nutzen funktionen von Pkw, deswegen dynamic_cast
		if (pkw != nullptr) {
			double dTempAutoTankvolumen = pkw->dGetTankinhalt();//Bekommt Tankinhalt
			double dTankVolumen = pkw->dTanken();
			double dMenge = dTankVolumen - dTempAutoTankvolumen;//Kalkulieren Menge von benutzte fuel
			if (p_dTankstelle >= dMenge) {
				p_dTankstelle -= dMenge;}//Tankstell fuel aendern
		}

		else {
			p_dTankstelle = 0.0;//letzte Auto soll vollgetankt sein, sogar wenn kein fuel mehr gibt

		}
	}
	std::cout<<"p_dTankstelle: "<< p_dTankstelle<<std::endl<<std::endl;

}

void Kreuzung::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double dStartZeit)
{
	vTanken(*fzg);//Tankt das Auto
	if (!p_pWege.empty()) {//Prueft ob das Weg gibt
		p_pWege.front()->vAnnahme(std::move(fzg), dStartZeit);}//Nimmt das Auto auf Weg
}

void Kreuzung::vSimulieren()
{
	for(const auto& weg: p_pWege){
		weg->vSimulieren();
	}
}
void Kreuzung::vVerbinde(const std::string& sHinWegName, const std::string& sRueckWegName, double dWegLaenge, std::shared_ptr<Kreuzung> kStart, std::shared_ptr<Kreuzung> kZiel, Tempolimit eTempolimit, bool bUeberholverbot)
{
	auto hinWeg = std::make_shared<Weg>(sHinWegName, dWegLaenge, eTempolimit, bUeberholverbot,  kZiel);//Strasse bauen
	auto rueckWeg = std::make_shared<Weg>(sRueckWegName, dWegLaenge, eTempolimit, bUeberholverbot, kStart);

	hinWeg->vSetRueckWeg(rueckWeg);//Strasse verbinden, kann nutzlich sein, wenn kein kreuzung gibt zum beispiel
	rueckWeg->vSetRueckWeg(hinWeg);

	kStart->p_pWege.push_back(hinWeg);//Addiert Weg zu p_pWege fuer diese Kreuzung(Kreuzung Weiss, welche Weg das Fahrzeug weiter Fahren muss
	kZiel->p_pWege.push_back(rueckWeg);
}
std::shared_ptr<Weg> Kreuzung::pZufaelligerWeg (Weg& wAktuellWeg) const
{
	std::vector<std::shared_ptr<Weg>> wWegeAmKreuzung;
	for ( const auto& weg: p_pWege){
		if(weg.get() != &wAktuellWeg){//Nicht Aktuelle weg in vector speichern
			wWegeAmKreuzung.push_back(weg);
		}
	}

	if(wWegeAmKreuzung.empty())//Falls nur rueckweg vorhanden, dann faehrt das Fahrzeug zurueck
	{
		return wAktuellWeg.wGetRueckWeg();
	}
	static std::mt19937 device(std::random_device{}());//um full random bewegund von Fzg zu bekommen
	std::uniform_int_distribution<int> dist(0, wWegeAmKreuzung.size() -1);//von erzte bis letzte weg in vector(aber wegen size ist dieses Interval in int)
	int zuf = dist(device);//random (Strasse nummer so zu sagen)
	return wWegeAmKreuzung[zuf];//diese Strasse zurueck gibt
}

double Kreuzung::dGetTankstelle() const {
	return p_dTankstelle;
}
void Kreuzung::vEinlesen(std::istream& is) {
	Simulationsobjekt::vEinlesen(is);
	is >>p_dTankstelle ;
}
void Kreuzung::vAusgeben(std::ostream& os) const
{
	Simulationsobjekt::vAusgeben(os);
	std::cout<<"  Tankstelle: " << p_dTankstelle<<std::endl;
}
std::ostream& operator<<(std::ostream& os, const Kreuzung& k)
{
	k.vAusgeben(os);
	return os;
}
