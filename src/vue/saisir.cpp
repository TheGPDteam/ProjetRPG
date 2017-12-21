#include "saisir.h"

Saisir::Saisir():buffer {""},
    rec{x_position,y_position, TAILLE_NOM_MAX*20, 50},
    m_bufferSDL{new TexteSDL(buffer, SDL_Color{0,0,0,255}, POLICE_COLLEGED, 12, std::make_pair(x_position+10, y_position+20))}
{

}

std::string Saisir::obtenirBuffer(){
    return buffer;
}

void Saisir::setBuffer(std::string buffer){
    this->buffer = buffer;
}

void Saisir::ajouterChar(char *c){
    if(buffer.size()<=TAILLE_NOM_MAX){
        buffer = buffer + *c;
        setbufferSDL();
    }
}

void Saisir::setbufferSDL() {
    m_bufferSDL = new TexteSDL(buffer, SDL_Color{255,255,255,255}, POLICE_COLLEGED, 20, std::make_pair(rec.x+20, rec.y+20));
}
void Saisir::afficher(SDL_Surface *fenetre_affichage){

    SDL_FillRect(fenetre_affichage, &rec, SDL_MapRGB(fenetre_affichage->format, 170, 170, 170));
    m_bufferSDL->afficherTexte(fenetre_affichage);
}

void Saisir::enleverChar(){
    if(!buffer.empty()){
        buffer.erase(buffer.end()-1);
        setbufferSDL();
    }
}

Saisir::~Saisir(){
    delete m_bufferSDL;
}
