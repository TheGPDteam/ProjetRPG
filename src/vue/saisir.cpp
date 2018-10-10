#include "saisir.h"

Saisir::Saisir():buffer {""},
    m_rec{x_position-TAILLE_NOM_MAX*10,y_position-10, TAILLE_NOM_MAX*20, 50},
    m_bufferSDL{new TexteSDL(buffer, SDL_Color{0,0,0,255}, POLICE_COLLEGED, 12, std::make_pair(x_position, y_position))}
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
//    if(m_bufferSDL != nullptr) delete m_bufferSDL;
    m_bufferSDL = new TexteSDL(buffer, SDL_Color{0,0,0,0}, POLICE_COLLEGED, 20, std::make_pair(m_rec.x+20, m_rec.y+15));
}

void Saisir::afficher(SDL_Surface *fenetre_affichage){
    SDL_FillRect(fenetre_affichage, &m_rec, SDL_MapRGB(fenetre_affichage->format, 170, 170, 170));
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
