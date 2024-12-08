/*
 * Simulation.h
 *
 *  Created on: 6 дек. 2024 г.
 *      Author: maxai
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include<iostream>
#include<fstream>
#include "SimuClient.h"
#include"SimuClientSocket.h"
#include<vector>
#include <memory>
#include <map>
class Kreuzung;


class Simulation
{
public:
	//Funktion, die alle Daten vom Simulationsobjekt aus datie Einliest mit 2 parameter stream und Mit Grafik
	void vEinlesen(std::istream& is, bool bMitGrafik = false);

	//Simuliert die daten von File mit 2 param(dauer von simulation, Zeitschritte von simulation)
	void vSimulieren(double dDauer, double dZeitschritt);

private:
	//Zeilennummer von file
	int iZeilennummer = 0;

	//map fuer Kreuzungen mit key als Name von Kreuzung
	std::map<std::string, std::shared_ptr<Kreuzung>> mapKreuzungen;

	//Mit grafik oder ohne zu simulieren
	bool bMitGrafik;
};



#endif /* SIMULATION_H_ */
