/*
 * Streckenende.cpp
 *
 *  Created on: 14 нояб. 2024 г.
 *      Author: maxai
 */
#include"Streckenende.h"
#include<iostream>
#include "Fahrzeug.h"
#include "Weg.h"
#include"Kreuzung.h"
#include<iomanip>

Streckenende::Streckenende(Fahrzeug& fahrzeug, Weg& weg)
:Fahrausnahme(fahrzeug, weg)
{}

void Streckenende::vBearbeiten() const
{

	std::cout<<"Die Ausnahme (Streckenende) fuer Fahrzeug: "<<p_fahrzeug.sGetName()<<" auf dem: "<<p_weg.sGetName()<<" Weg"<<std::endl<<std::endl;

	Weg& wAktuellWeg = p_weg;
	std::shared_ptr<Kreuzung> kZielKreuzung = wAktuellWeg.kGetZielKreuzung();//Ziel Kreuzung finden

	std::shared_ptr<Weg> wNeuenWeg = kZielKreuzung->pZufaelligerWeg(wAktuellWeg);// random Weg finden

	kZielKreuzung->vTanken(p_fahrzeug);//Tanken von Fahrzeuge

	std::cout<<std::setiosflags(std::ios::fixed)<<resetiosflags(std::ios::right)<<std::setprecision(2)<<setiosflags(std::ios::left)
																							<<std::setw(15)<<"ZEIT"
																							<<std::setw(3)<<":"
																							<<dGlobaleZeit
																							<<"\n"
																							<<std::setw(15)<<"KREUZUNG"
																							<<std::setw(3)<<":"
																							<<kZielKreuzung->sGetName()
																							<<"\n"
																							<<std::setw(15)<<"WECHSEL"
																							<<std::setw(3)<<":"
																							<<wAktuellWeg.sGetName()<<" → "<<wNeuenWeg->sGetName()
																							<<"\n"
																							<<std::setw(15)<<"FAHRZEUG"
																							<<std::setw(3)<<":"
																							<<resetiosflags(std::ios::left);
	Fahrzeug::vKopf();
	std::cout<<"		  ";
	p_fahrzeug.vAusgeben(std::cout);
	std::cout << std::endl<< std::endl;

	wNeuenWeg->vAnnahme(p_weg.pAbgabe(p_fahrzeug));
}
