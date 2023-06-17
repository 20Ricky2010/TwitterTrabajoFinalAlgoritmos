#pragma once
#include "Usuario.h"

class Tweet
{
private:
	USUARIO* usuario_e;
	string fecha_p;
	string Escritura;
	string Likes;
	string retweets;
public:
	Tweet(USUARIO* U,string escritura,string fecha,string likes,string retweets) {
		this->Escritura = escritura;
		this->fecha_p = fecha;
		this->Likes = likes;
		this->retweets = retweets;
		this->usuario_e = U;
	};
	~Tweet();

	USUARIO* get_usuario() {
		return this->usuario_e;
	}
	string get_fecha() {
		return this->fecha_p;
	}
	string get_escritura() {
		return this->Escritura;
	}
	string get_likes() {
		return this->Likes;
	}
	string get_retweets() {
		return this->retweets;
	}


};



Tweet::~Tweet()
{
}