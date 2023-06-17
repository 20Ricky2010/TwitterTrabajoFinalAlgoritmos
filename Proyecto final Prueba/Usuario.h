#pragma once
#include <iostream>
#include <string>
using namespace std;

class USUARIO
{
private:
	string Nombre_U; //Nombre de Usuario
	string cumpleaños; //Fecha de cumpleaños del usuario
	string dia_u; //Fecha de union a la plataforma
	string id; //Nombre de usuario mas su id
	string descripcion; // breve descripcion 
public: 
	USUARIO(string nombre,string cumpleaños,string dia,string id,string descrpicion) {
		this->Nombre_U = nombre;
		this->cumpleaños = cumpleaños;
		this->dia_u = dia;
		this->id = id;
		this->descripcion = descrpicion;

	};
	~USUARIO();

	string get_Nombre_U() {
		return this->Nombre_U;
	}
	string get_dia_u(){
		return this->dia_u;
	}
	string get_id() {
		return this->id;
	}
	string get_descripcion() {
		return this->descripcion;
	}
	string get_cumpleaños() {
		return this->cumpleaños;
	}

};



USUARIO::~USUARIO()
{
}