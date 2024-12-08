/*
 * Simulation.cpp
 *
 *  Created on: 6 дек. 2024 г.
 *      Author: maxai
 */
#include "Simulation.h"
#include "Kreuzung.h"
#include"PKW.h"
#include"Fahrzeug.h"
#include"Weg.h"
#include"Fahrrad.h"
#include"SimuClient.h"

void Simulation::vEinlesen(std::istream& is, bool bMitGrafik) {
	if (bMitGrafik) {
		bInitialisiereGrafik(1000, 1000);
	}
	while (!is.eof()) // Zeilen zu lesen
	{
		++iZeilennummer;
		std::string sSchluesselwort = "";
		is >> sSchluesselwort;

		if (sSchluesselwort == "KREUZUNG")
		{

			std::string sName;
			double dTankstelle;
			double posX;
			double posY;
			is >> sName >> dTankstelle;

			if (bMitGrafik) {
				is >> posX >> posY;
				bZeichneKreuzung(posX, posY);
			}

			if (mapKreuzungen.find(sName) != mapKreuzungen.end())//sucht nach Kreuzung mit name(key) und wenn es nicht exestiert geht weiter
			{
				throw std::runtime_error("Fehlermeldung, Kreuzung mit der Name " + sName + " existiert schon. Zeilennummer: " + std::to_string(iZeilennummer));
			}
			auto kr = std::make_shared<Kreuzung>(sName, dTankstelle);
			mapKreuzungen[sName] = kr;


		}
		else if(sSchluesselwort == "STRASSE"){
			std::string sNameQ;
			std::string	sNameZ;
			std::string	sNameW1;
			std::string	sNameW2;
			double dLaenge;
			int iTempolimit;
			int iUeberholverbot;
			Tempolimit tempolimit;
			bool bUeberholverbot;

			is >> sNameQ >> sNameZ >> sNameW1 >> sNameW2 >> dLaenge >> iTempolimit >> iUeberholverbot;

			if (bMitGrafik) {
				int iAnzahlDerKoordinatenPaare;
				is >> iAnzahlDerKoordinatenPaare;
				int *iKoordinaten = new int[2 * iAnzahlDerKoordinatenPaare]; // Nutzen Array mit dynamischer Grosse, weil bZeichneStrasse braucht(mal 2, weil es Anzahl von Paare ist und nicht von koordinaten)

				for (int i = 0; i < iAnzahlDerKoordinatenPaare; i++)
				{
					is >> iKoordinaten[2 * i] >> iKoordinaten[2 * i + 1];
				}

				bZeichneStrasse(sNameW1, sNameW2, dLaenge, iAnzahlDerKoordinatenPaare, iKoordinaten);

				delete[] iKoordinaten;
			}

			if (mapKreuzungen.find(sNameQ) == mapKreuzungen.end())//sucht nach Kreuzung mit name(key) und wenn es  exestiert geht weiter
			{
				throw std::runtime_error("Fehlermeldung, Quellkreuzung mit der Name " + sNameQ + " existiert nicht. Zeilennummer: " + std::to_string(iZeilennummer));
			}

			if (mapKreuzungen.find(sNameZ) == mapKreuzungen.end())//sucht nach Kreuzung mit name(key) und wenn es  exestiert geht weiter
			{
				throw std::runtime_error("Fehlermeldung, Zielkreuzung mit der Name " + sNameZ + " existiert nicht.Zeilennummer: " + std::to_string(iZeilennummer));
			}

			switch (iTempolimit)
			{
			case 1: tempolimit = Tempolimit::Innerorts; break;
			case 2: tempolimit = Tempolimit::Landstraße; break;
			case 3: tempolimit = Tempolimit::Autobahn; break;
			default: throw std::invalid_argument("Tempolimit war falsch gegeben. Zeilennummer: " + std::to_string(iZeilennummer)); break;
			}

			switch (iUeberholverbot)
			{
			case 0: bUeberholverbot = false; break;
			case 1: bUeberholverbot = true;  break;
			default: throw std::invalid_argument("Ueberholverbot war falsch gegeben. Zeilennummer: " + std::to_string(iZeilennummer)); break;
			}

			Kreuzung::vVerbinde(sNameW1, sNameW2, dLaenge, mapKreuzungen[sNameQ], mapKreuzungen[sNameZ], tempolimit, bUeberholverbot);//verbindet 2 Strassen


		}
		else if(sSchluesselwort == "PKW"){
			auto pkw = std::make_unique<PKW>();
			std::string sNameS;
			double dStartZeitPunkt;

			is >> *pkw >> sNameS >> dStartZeitPunkt;

			if (mapKreuzungen.find(sNameS) == mapKreuzungen.end())
			{
				throw std::runtime_error("Fehlermeldung, Quellkreuzung mit der Name " + sNameS + " existiert nicht. Zeilennummer: " + std::to_string(iZeilennummer));
			}

			mapKreuzungen[sNameS]->vAnnahme(std::move(pkw),dStartZeitPunkt);//nimmt fzg auf weg



		}
		else if(sSchluesselwort == "FAHRRAD"){
			auto frd = std::make_unique<Fahrrad>();
			std::string sNameS;
			double dStartZeitPunkt;

			is >> *frd >> sNameS >> dStartZeitPunkt;

			if (mapKreuzungen.find(sNameS) == mapKreuzungen.end())
			{
				throw std::runtime_error("Fehlermeldung, Quellkreuzung mit der Name " + sNameS + " existiert nicht. Zeilennummer: " + std::to_string(iZeilennummer));
			}

			mapKreuzungen[sNameS]->vAnnahme(std::move(frd),dStartZeitPunkt);//nimmt fzg auf weg



		}
		else
		{
			throw std::runtime_error("Ein unbekanntes Schluesselwort. Zeilennummer " + std::to_string(iZeilennummer));
		}

	}
}


void Simulation::vSimulieren(double dDauer, double dZeitschritt)
{

	if (dDauer <= 0 || dZeitschritt <= 0) {
		throw std::invalid_argument("dDauer und dZeitschritt müssen >=0 sein");//nicht runntime_error, weil man dieses fehler vor Kompilierung finden kann
	}
	std::cout<<"Dauer von Simulation: "<<dDauer<<" , Zeitschritt: "<<dZeitschritt<<std::endl<<std::endl;

	while (dGlobaleZeit < dDauer)
	{
		vSetzeZeit(dGlobaleZeit);
		std::cout<<"Globale Zeit : "<<dGlobaleZeit<<std::endl<<std::endl;

		for (auto& [sName, pKreuzung] : mapKreuzungen) {
			if (pKreuzung) {
				pKreuzung->vSimulieren();
			}
		}
		dGlobaleZeit+= dZeitschritt;
	}
}
