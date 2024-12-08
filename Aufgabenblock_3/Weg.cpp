/*
 * Weg.cpp
 *
 *  Created on: 4 нояб. 2024 г.
 *      Author: maxai
 */

#include<iostream>
#include"Weg.h"
#include "Fahrzeug.h"
#include<iomanip>
#include<ostream>
#include <memory>
#include"Fahrausnahme.h"
#include"Losfahren.h"
#include "Streckenende.h"
#include "Kreuzung.h"



double Weg::dGetTempolimit() const
{
	switch(p_eTempolimit){
	case Tempolimit::Innerorts:
		return 50.0;
	case Tempolimit::Landstraße:
		return 100.0;
	case Tempolimit::Autobahn:
		return std::numeric_limits<int>::max();
	default:
		return 0.0;

	}
}

Weg::Weg()
:p_dLaenge(0.0), p_eTempolimit(Tempolimit::Autobahn)
{}

Weg::Weg(const std::string& sName, double dLaenge, Tempolimit eTempolimit,bool bUeberholverbot, const std::shared_ptr<Kreuzung> kZielKreuzung)
:Simulationsobjekt(sName), p_dLaenge(dLaenge), p_eTempolimit(eTempolimit), p_bUeberholverbot(bUeberholverbot), p_kZielKreuzung(kZielKreuzung)
{
}
Weg::~Weg(){}

void Weg::vSimulieren()
{

	p_dVirtuelleSchranke = p_dLaenge;
	for (const auto& fahrzeug : p_pFahrzeuge) {
		try{
			fahrzeug->vSimulieren();
		}
		catch (const Fahrausnahme& exeption) {
			exeption.vBearbeiten();
		}
	}
	p_pFahrzeuge.vAktualisieren();
	for (const auto& fahrzeug : p_pFahrzeuge){
		fahrzeug->vZeichnen(*this);
	}

}


void Weg::vKopf()
{
	std::cout<<setiosflags(std::ios::left)<<std::setw(3)<<"ID"
			<<std::setw(2)<<"|"
			<<std::setw(14)<<"Name"
			<<std::setw(2)<<"|"
			<<std::setw(10)<<"Laenge"
			<<std::setw(2)<<"|"
			<<std::setw(15)<<"Fahrzeuge"
			<<std::endl;
	std::cout<<"------------------------------------------------------"<<std::endl;
}

void Weg::vAusgeben(std::ostream& os) const
{
	Simulationsobjekt::vAusgeben(os);
	std::cout<<std::setw(1)<<":"
			<<std::setprecision(0)
			<<std::setw(9)<< p_dLaenge
			<<std::setw(4)<<"(";
	for (const auto& fahrzeug : p_pFahrzeuge) {
		std::cout << " "<< fahrzeug->sGetName() << " ";
	}
	std::cout<<std::setw(1)<<")"
			<<std::endl<<std::endl;

}
std::ostream& operator<<(std::ostream& os, const Weg& f) {
	f.vAusgeben(os);
	return os;
}
double Weg::dGetLaenge() const
{
	return p_dLaenge;
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg)
{
	if(fzg !=nullptr){
		// der Link zu Neuem weg
		fzg->vNeueStrecke(*this);
		//add to the List und besitzt nicht mehr wegen move
		p_pFahrzeuge.push_back(std::move(fzg));
	}
}

void Weg::vAnnahme(std::unique_ptr<Fahrzeug> fzg, double dStartZeit)
{
	if(fzg !=nullptr){
		// der Link zu Neuem weg
		fzg->vNeueStrecke(*this, dStartZeit);
		//add to the List und besitzt nicht mehr wegen move
		p_pFahrzeuge.push_front(std::move(fzg));
	}
}
std::unique_ptr<Fahrzeug> Weg::pAbgabe(const Fahrzeug& fzg)
{
	for (auto it = p_pFahrzeuge.begin(); it != p_pFahrzeuge.end(); ++it) {

		if (**it == fzg) {//ein stern um std::unique_ptr<Fahrzeug> zu kriegen, und andere fuer Fahrzeug zu kriegen

			std::unique_ptr<Fahrzeug> gefundeneFzg = std::move(*it);//Wenn Sie das Fahrzeug in der Liste gefunden haben, verschieben (move) Sie den unique ptr in eine lokale Variable

			p_pFahrzeuge.erase(it);//loeschen dann das Fahrzeug aus der Liste

			return gefundeneFzg;//Anschließend koeonnen  Sie den zuvor lokal gespeicherten Pointer zurueckgeben.
		}
	}

	return nullptr;
}
const  vertagt::VListe<std::unique_ptr<Fahrzeug>>& Weg::lGetFahrzeuge() const
						{
	return p_pFahrzeuge;
						}
bool Weg::bGetUeberholverbot() const
{
	return p_bUeberholverbot;
}

double Weg::dGetVirtuelleSchranke() const
{
	if(p_bUeberholverbot){
		return p_dVirtuelleSchranke;}
	else{
		return p_dLaenge;
	}
}
void Weg::vSetVirtuelleSchranke(double dVirtuelleSchranke)
{
	p_dVirtuelleSchranke = dVirtuelleSchranke;
}
std::shared_ptr<Weg> Weg::wGetRueckWeg() const
{
	return p_wRueckWeg.lock();
}

std::shared_ptr<Kreuzung> Weg::kGetZielKreuzung() const
{
	return p_kZielKreuzung.lock();
}

void Weg::vSetRueckWeg(std::weak_ptr<Weg> wRueckWeg)
{
	wRueckWeg = p_wRueckWeg;
}
