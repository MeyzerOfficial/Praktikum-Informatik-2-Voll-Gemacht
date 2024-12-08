/*
 * main.cpp
 *
 *  Created on: 4 нояб. 2024 г.
 *      Author: maxai
 */
#include<iostream>
#include"Simulationsobjekt.h"
#include"Weg.h"
#include "Fahrzeug.h"
#include "PKW.h"
#include"Fahrrad.h"
#include<cmath>
#include<string>
#include<iomanip>
#include<ostream>
#include <list>
#include <memory>
#include <limits>
#include<cmath>
#include <algorithm>
#include"SimuClient.h"
#include <random>
#include"vertagt_aktion.h"
#include"vertagt_liste.h"
#include"Kreuzung.h"
#include"Simulation.h"

//Globale Zeit Uhr
double dGlobaleZeit = 0.00;
double maindEpsilon = 0.00001;

using namespace std;
void vAufgabe_4()
{
	Weg *weg1 = new Weg("Kreml", 400);
	Weg::vKopf();
	std::cout<<*weg1<<std::endl;
}
void vAufgabe_5()
{
	//	 std::list<std::unique_ptr<Fahrzeug>> fahrzeuge;
	Weg *weg1 = new Weg("Kreml", 405);

	std::unique_ptr<PKW> pkw1 = std::make_unique<PKW>("Mazda", 140, 6, 120);
	std::unique_ptr<PKW> pkw2 = std::make_unique<PKW>("Bently", 200, 5, 100);
	std::unique_ptr<Fahrrad> frd = std::make_unique<Fahrrad>("BMX", 40);

	weg1->vAnnahme(std::move(pkw1));
	weg1->vAnnahme(std::move(pkw2),0.9);
	weg1->vAnnahme(std::move(frd));

	//	 fahrzeuge.push_back(std::move(fzg)); nicht funktioniert, weil unique ptr kann nicht in zwei liste sein
	//	 fahrzeuge.push_back(std::move(pkw));
	//	 fahrzeuge.push_back(std::move(frd));
	for(int i; i<8; i++){

		weg1->vSimulieren();

		Fahrzeug::vKopf();
		for(const auto& fahrzeug : weg1->lGetFahrzeuge()){
			fahrzeug ->vAusgeben(std::cout);
			//					std::cout<<std::endl;
		}
		dGlobaleZeit+=0.3;
	}

	Weg::vKopf();
	std::cout<<*weg1<<std::endl;

};
void vAufgabe_6()
{
	//	 std::list<std::unique_ptr<Fahrzeug>> fahrzeuge;
	bInitialisiereGrafik(800, 500);
	int iKoordinaten[] = { 700, 250, 100, 250 };
	Weg *weg1 = new Weg("Lenina", 500, Tempolimit::Innerorts);
	Weg *weg2 = new Weg("Kreml", 500);
	bZeichneStrasse("Kreml" ,"Lenina", 500, 2, iKoordinaten);
	std::unique_ptr<PKW> pkw1 = std::make_unique<PKW>("Mazda", 140, 6, 120);
	std::unique_ptr<PKW> pkw2 = std::make_unique<PKW>("Bently", 200, 5, 100);
	std::unique_ptr<Fahrrad> frd = std::make_unique<Fahrrad>("BMX", 40);

	weg1->vAnnahme(std::move(pkw1));
	weg1->vAnnahme(std::move(pkw2),0.9);
	weg2->vAnnahme(std::move(frd));

	for(int i; i<30; i++){
		vSetzeZeit(dGlobaleZeit);
		weg1->vSimulieren();
		weg2->vSimulieren();

		vSleep(300);

		Fahrzeug::vKopf();
		for(const auto& fahrzeug : weg1->lGetFahrzeuge()){
			fahrzeug ->vAusgeben(std::cout);
			//					std::cout<<std::endl;
		}
		for(const auto& fahrzeug : weg2->lGetFahrzeuge()){
			fahrzeug ->vAusgeben(std::cout);
			//					std::cout<<std::endl;
		}
		dGlobaleZeit+=0.3;
		std::cout<<dGlobaleZeit<<std::endl<<std::endl;
	}

	Weg::vKopf();
	std::cout<<*weg1<<std::endl;
	Weg::vKopf();
	std::cout<<*weg2<<std::endl;
	vBeendeGrafik();
};

void vAufgabe_6a()
{
	static std::mt19937 device(5);
	std::uniform_int_distribution<int> dist(1, 10);
	vertagt::VListe<int> liste;

	for (int i = 0; i < 10; ++i) {
		liste.push_back(dist(device));}

	liste.vAktualisieren();

	std::cout<<"Anfang Liste "<<std::endl;
	for( const auto& numer : liste){
		std::cout<<numer<<",  ";
	}
	std::cout<<std::endl;

	for( auto it = liste.begin(); it != liste.end();it++){
		if(*it > 5){
			liste.erase(it);//weil erase nur mit iterator arbeitet
		}

	}
	std::cout<<"Liste nach erase() alle >5 "<<std::endl;
	for( const auto& numer : liste){
		std::cout<<numer<<",  ";
	}
	std::cout<<std::endl;

	liste.vAktualisieren();

	std::cout<<"Liste nach vAktualisieren() "<<std::endl;
	for( const auto& numer : liste){
		std::cout<<numer<<",  ";
	}
	std::cout<<std::endl;

	liste.push_front(5);
	liste.push_back(10);

	liste.vAktualisieren();

	std::cout<<"Liste nach Zahlen Fuegung "<<std::endl;
	for( const auto& numer : liste){
		std::cout<<numer<<",  ";
	}
	std::cout<<std::endl;


};


void vAufgabe_TestVorAufgaben()
{
	//	 std::list<std::unique_ptr<Fahrzeug>> fahrzeuge;
	bInitialisiereGrafik(800, 500);
	int iKoordinaten[] = { 700, 250, 100, 250 };
	Weg *weg1 = new Weg("Lenina", 500, Tempolimit::Autobahn);
	Weg *weg2 = new Weg("Kreml", 500);
	bZeichneStrasse("Kreml" ,"Lenina", 500, 2, iKoordinaten);
	std::unique_ptr<PKW> pkw1 = std::make_unique<PKW>("Mazda", 15, 6, 120);
	std::unique_ptr<PKW> pkw2 = std::make_unique<PKW>("Bently", 50, 5, 100);
	std::unique_ptr<Fahrrad> frd = std::make_unique<Fahrrad>("BMX", 100);

	weg1->vAnnahme(std::move(pkw1));
	weg1->vAnnahme(std::move(pkw2),3);
	weg2->vAnnahme(std::move(frd));


	bool bWeg1 = false;
	bool bWeg2 = false;

	for(; dGlobaleZeit<30; dGlobaleZeit+=1){

		vSetzeZeit(dGlobaleZeit);


		for(const auto& fahrzeug : weg1->lGetFahrzeuge()){
			int counter;
			if(std::abs(fahrzeug->dGetGesamtStrecke() - weg1->dGetLaenge()) < maindEpsilon){
				counter ++;

			}
			if(counter == 2){
				bWeg1 = true;

			}

		}
		for(const auto& fahrzeug : weg2->lGetFahrzeuge()){
			if(std::abs(fahrzeug->dGetGesamtStrecke() - weg1->dGetLaenge()) < maindEpsilon){
				bWeg2 = true;
			}
		}
		if(bWeg1 == true && bWeg2 == true){

			break;}
		else{

			weg1->vSimulieren();
			weg2->vSimulieren();

			vSleep(500);

			Fahrzeug::vKopf();
			for(const auto& fahrzeug : weg1->lGetFahrzeuge()){
				fahrzeug ->vAusgeben(std::cout);
				//					std::cout<<std::endl;

			}
			for(const auto& fahrzeug : weg2->lGetFahrzeuge()){
				fahrzeug ->vAusgeben(std::cout);
				std::cout<<std::endl;
			}


		}
		std::cout<<dGlobaleZeit<<std::endl<<std::endl;
	}
	Weg::vKopf();
	std::cout<<*weg1<<std::endl;
	Weg::vKopf();
	std::cout<<*weg2<<std::endl;
	vBeendeGrafik();


};

void vAufgabe_7()
{
	std::unique_ptr<PKW> pkw1 = std::make_unique<PKW>("Mazda", 100, 6, 120);
	std::unique_ptr<PKW> pkw2 = std::make_unique<PKW>("Bently", 90, 5, 100);
	std::unique_ptr<Fahrrad> frd = std::make_unique<Fahrrad>("BMX", 40);

	auto kr1 = std::make_shared<Kreuzung>("Kr1", 0);
	auto kr2 = std::make_shared<Kreuzung>("Kr2", 1000); //mit 1000 liter Tankstelle
	auto kr3 = std::make_shared<Kreuzung>("Kr3", 0);
	auto kr4 = std::make_shared<Kreuzung>("Kr4", 0);

	Kreuzung::vVerbinde("W12", "W21", 40, kr1, kr2, Tempolimit::Innerorts , true);//Strasse 1

	Kreuzung::vVerbinde("W23a", "W32a", 115, kr2, kr3, Tempolimit::Autobahn , false);//Strasse 2

	Kreuzung::vVerbinde("W23b", "W32b", 40, kr2, kr3, Tempolimit::Innerorts , true);//Strasse 3

	Kreuzung::vVerbinde("W24", "W42", 55, kr2, kr4, Tempolimit::Innerorts , true);//Strasse 4

	Kreuzung::vVerbinde("W34", "W43", 85, kr3, kr4, Tempolimit::Autobahn , false);//Strasse 5

	Kreuzung::vVerbinde("W44a", "W44b", 130, kr4, kr4, Tempolimit::Landstraße , false);//Strasse 6

	bInitialisiereGrafik(1000, 1000);

	bZeichneKreuzung(680, 40);//Kr1
	bZeichneKreuzung(680, 300);//Kr2
	bZeichneKreuzung(680, 570);//Kr3
	bZeichneKreuzung(320, 300);//Kr4


	int iKoordinaten_W12_W21[] = { 680, 40, 680, 300 };//Strasse 1

	int iKoordinaten_W23a_W32a[] = { 680, 300, 850, 300, 970, 390, 970, 500, 850, 570, 680, 570 };;//Strasse 2

	int iKoordinaten_W23b_W32b[] = { 680, 300, 680, 570 };;//Strasse 3

	int iKoordinaten_W24_W42[] = { 680, 300, 320, 300 };//Strasse 4

	int iKoordinaten_W34_W43[] = { 680, 570, 500, 570, 350, 510, 320, 420, 320, 300 };//Strasse 5

	int iKoordinaten_W44a_W44b[] = { 320, 300, 320, 150, 200, 60, 80, 90, 70, 250, 170, 300, 320, 300 };//Strasse 6

	bZeichneStrasse("W12", "W21", 40, 2, iKoordinaten_W12_W21);
	bZeichneStrasse("W23a", "W32a", 115, 6, iKoordinaten_W23a_W32a);
	bZeichneStrasse("W23b", "W32b", 40, 2, iKoordinaten_W23b_W32b);
	bZeichneStrasse("W24", "W42", 55, 2, iKoordinaten_W24_W42);
	bZeichneStrasse("W34", "W43", 85, 5, iKoordinaten_W34_W43);
	bZeichneStrasse("W44a", "W44b", 130, 7, iKoordinaten_W44a_W44b);


	kr1->vAnnahme(std::move(pkw1), 0.9);
	kr1->vAnnahme(std::move(pkw2), 3);
	kr1->vAnnahme(std::move(frd), 1.8);

	for(; dGlobaleZeit<40; dGlobaleZeit+=0.3){

		vSetzeZeit(dGlobaleZeit);// um Zeit im fenster zu zeigen
		std::cout<<"GlobaleZeit: "<<dGlobaleZeit<<std::endl<<std::endl;

		kr1->vSimulieren();
		kr2->vSimulieren();
		kr3->vSimulieren();
		kr4->vSimulieren();


		vSleep(100);

	}
	vBeendeGrafik();
};

void vAufgabe_8()
{
	try{
		std::ifstream infile("Vo.dat");// Öffnen des Files zum Lesen
		if (!infile.is_open()) {
			throw std::runtime_error("Fehlermeldung, VO.dat kann nicht geoeffnet werden ");
		}

		infile.exceptions(std::ios::eofbit | std::ios::failbit | std::ios::badbit);



		PKW pkw;
		Fahrrad fahrrad;
		Kreuzung kreuzung;

		infile>>pkw;
		infile>>fahrrad;
		infile>>kreuzung;

		std::cout<<pkw<<std::endl;
		std::cout<<fahrrad<<std::endl;
		std::cout<<kreuzung<<std::endl;
	}catch (const std::exception& e){
		std::cerr << "Fehler: " << e.what() << std::endl;
		std::exit(1);
	}


};
void vAufgabe_9()
{
	try{
		std::ifstream infile("Simu.dat");// Öffnen des Files zum Lesen
		if (!infile.is_open()) {
			throw std::runtime_error("Fehlermeldung, Simu.dat kann nicht geoeffnet werden ");//runtime_error nutzen, wenn es nicht mit programm logik verbunden ist, sondern von daten, die man von ausen bekommt(daten einlesen oder cin
		}

		infile.exceptions(std::ios::failbit | std::ios::badbit);

		Simulation probe;

		probe.vEinlesen(infile);
		if (infile.eof()) {
			std::cout << "Ende der Datei erreicht." << std::endl;
		}

	}catch (const std::exception& e){
		std::cerr << "Fehler: " << e.what() << std::endl;
		std::exit(1);
	}
	vBeendeGrafik();
};
void vAufgabe_9a()
{
	try{
		std::ifstream infile("SimuDisplay.dat");// Öffnen des Files zum Lesen
		if (!infile.is_open()) {
			throw std::runtime_error("Fehlermeldung, Simu.dat kann nicht geoeffnet werden ");
		}

		infile.exceptions(std::ios::failbit | std::ios::badbit);

		Simulation probe;

		probe.vEinlesen(infile,true);
		probe.vSimulieren(20,0.1);
		if (infile.eof()) {
			std::cout << "Ende der Datei erreicht." << std::endl;
		}

	}catch (const std::exception& e){
		std::cerr << "Fehler: " << e.what() << std::endl;
		std::exit(1);
	}
};
int main()
{
	//vAufgabe_6();
	//vAufgabe_TestVorAufgaben();
	//vAufgabe_7();
	//vAufgabe_8();
	//vAufgabe_9();
	//vAufgabe_9a();
	return 0;
}
