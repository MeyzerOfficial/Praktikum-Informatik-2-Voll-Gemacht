/*
 * Simulationsobjekt.cpp
 *
 *  Created on: 4 нояб. 2024 г.
 *      Author: maxai
 */
#include<iostream>
#include"Simulationsobjekt.h"
#include<iomanip>
#include<ostream>

int Simulationsobjekt::p_iMaxID = 0;

Simulationsobjekt::Simulationsobjekt(const std::string& sName)
:p_sName(sName), p_iID(++p_iMaxID)
{std::cout<<" Neue Fahrzeug : Name = "<<p_sName<<", ID = "<<p_iID<<std::endl;
}

Simulationsobjekt::Simulationsobjekt()
:p_sName(""),p_iID(++p_iMaxID)
{std::cout<<" Neue Simulationsobjekt : Name = "<<p_sName<<", ID = "<<p_iID<<std::endl;
}


Simulationsobjekt:: ~Simulationsobjekt() {
	std::cout << "Simulationsobjekt geloescht : " << p_sName << std::endl;
}

void Simulationsobjekt::vAusgeben(std::ostream& ) const
{
	std::cout<<std::setiosflags(std::ios::fixed)<<resetiosflags(std::ios::right)<<std::setprecision(2)<<setiosflags(std::ios::left)
															<<std::setw(4)<<p_iID
															<<std::setw(15)<<p_sName
															<<resetiosflags(std::ios::left)<<setiosflags(std::ios::right);
}

void Simulationsobjekt::vSimulieren(){}

bool Simulationsobjekt::operator==(const Simulationsobjekt& andere) const
									{
	if (!this) {
		return false;}

	if(this->p_iID == andere.p_iID){
		return true;
	}
	else {
		return false;
	}
									}
std::string Simulationsobjekt::sGetName() const
{
	return p_sName;
}

double Simulationsobjekt::dGetdZeit() const
{
	return p_dZeit;
}

void Simulationsobjekt:: vEinlesen(std::istream& is )
{
	if(p_sName != ""){//nur falls Name ist leer
		throw std::runtime_error("Fehlermeldung, das objekt hat schon eine Name");
	}
	is>>p_sName;


}

std::istream& operator>>(std::istream& is, Simulationsobjekt& obj) {
	obj.vEinlesen(is);
	return is;
}


