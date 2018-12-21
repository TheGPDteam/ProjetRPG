#include "zonetexte.h"
#include <iostream>
#include <assert.h>

void decouper(const std::string& str, std::vector<std::string>& jetons, const std::string& delimiteurs = " ") {
    if (str.length() == 0) return;
    std::string::size_type prevPos = 0;//str.find_first_not_of(delimiteurs, 0);
    std::string::size_type pos     = str.find_first_of(delimiteurs, prevPos);
    while (std::string::npos != pos || std::string::npos != prevPos) {
        jetons.push_back(str.substr(prevPos, pos - prevPos));
        std::string::size_type pos_tmp = str.find_first_of(delimiteurs, pos+1);
        if(pos_tmp - pos == 1){
            prevPos = pos_tmp;
            pos = pos_tmp;
        }
        else {
            prevPos = str.find_first_not_of(delimiteurs, pos);
            pos = str.find_first_of(delimiteurs, prevPos);
        }
    }
    if(str[str.size()-1]=='\t')
        jetons.push_back("");
}



ZoneTexte::ZoneTexte(const std::string chemin_police, const int taille_police, SDL_Rect r,
                     std::string texte, const SDL_Color couleur_texte, COMPORTEMENT_TEXTE ct, ALIGNEMENT_TEXTE at)
    : Affichable(r), m_texte{texte}, m_comportement{ct}, m_alignement{at}, m_cheminPolice{chemin_police}, M_TAILLE_POLICE_MAX{taille_police},
      m_taillePolice{taille_police}, m_couleur{couleur_texte}
{
    adapterTexte();
}

ZoneTexte::~ZoneTexte(){
    for(TexteSDL * t : m_texteSDL)
        delete t;
}

void ZoneTexte::afficher(SDL_Surface *surface_affichage)
{

    for (TexteSDL * t : m_texteSDL)
    {
        t->afficher(surface_affichage);
    }
}

void ZoneTexte::redimensionner(SDL_Rect nouvelleDimension)
{
    m_rectangle = nouvelleDimension;
    adapterTexte();
}

std::string ZoneTexte::obtenirTexte(){
    return m_texte;
}

void ZoneTexte::adapterTexte()
{
    for (TexteSDL * t : m_texteSDL)
    {
        delete t;
    }
    m_texteSDL.clear();
    switch (m_comportement) {
    case COMPORTEMENT_TEXTE::REDIMENTIONNE :
    {
        //Modification de la taille pour que le texte rentre dans sa zone
        int tailleLettre = std::min(M_TAILLE_POLICE_MAX, (int) (m_rectangle.w/m_texte.length())); // A verifier
        TexteSDL * t = new TexteSDL(m_texte, m_couleur, m_cheminPolice, tailleLettre,std::make_pair<int,int>(m_rectangle.x, m_rectangle.y));
        t->redimensionner(m_rectangle);

        m_texteSDL.insert(m_texteSDL.begin(), t);
        break;
    }
    case COMPORTEMENT_TEXTE::SAUT_DE_LIGNE :
    {
        //On regarde mot par mot si le texte rentre dans la zone, sinon on crée un nouveau texte SDL qu'on ajoute au vector
        std::string tmpTexte = m_texte;
        std::vector<std::string> paragraphes;
        decouper(tmpTexte, paragraphes, "\n");
        TexteSDL * t = new TexteSDL("Fake", m_couleur, m_cheminPolice, m_taillePolice,
                                    std::make_pair<int,int>(m_rectangle.x, m_rectangle.y));
        TTF_Font * font = t->obtenirPolice();
        delete t;
        for(unsigned int i = 0; i < paragraphes.size(); ++i){
            tmpTexte = paragraphes[i];
            std::vector<std::string> jetons;
            decouper(tmpTexte, jetons, " ");
            int motCourant = 0;
            while(motCourant < jetons.size()){
                std::string lignePrec = "";
                std::string ligneCourante = jetons[motCourant];
                motCourant++;
                int largeur, hauteur;
                TTF_SizeText(font, ligneCourante.c_str(), &largeur, &hauteur);
                while(motCourant < jetons.size() && largeur < m_rectangle.w){
                    if(lignePrec.size() != 0)
                        lignePrec += " ";
                    lignePrec += jetons[motCourant-1];
                    ligneCourante += " " + jetons[motCourant];
                    motCourant++;
                    TTF_SizeText(font, ligneCourante.c_str(), &largeur, &hauteur);
                }
                std::string affichage = ligneCourante ;
                if(largeur >= m_rectangle.w) {
                    affichage = lignePrec ;
                    motCourant--;
                }
                TTF_SizeText(font, affichage.c_str(), &largeur, &hauteur);
                t = new TexteSDL(affichage, m_couleur, m_cheminPolice, m_taillePolice,
                                 std::make_pair<int,int>(m_rectangle.x + (m_rectangle.w-largeur)/2., m_rectangle.y + ((m_taillePolice+5)*m_texteSDL.size())));
                m_texteSDL.push_back(t);
            }
        }
        break;
    }
    case COMPORTEMENT_TEXTE::TRONQUE :
    {
        TexteSDL * t = new TexteSDL(m_texte, m_couleur, m_cheminPolice, m_taillePolice,
                                    std::make_pair<int,int>(m_rectangle.x, m_rectangle.y));
        std::pair<int, int>  tailleTexte = t->obtenirRectTexte();
        if(tailleTexte.first > m_rectangle.w){
            assert(m_texte.size() > 0);
            int positionCourante = 0;
            do {
                delete t;
                positionCourante++;
                std::string texteCourant = m_texte.substr(0, positionCourante)+ "...";
                t = new TexteSDL(texteCourant, m_couleur, m_cheminPolice, m_taillePolice,
                                 std::make_pair<int,int>(m_rectangle.x, m_rectangle.y));
                tailleTexte = t->obtenirRectTexte();

            } while(tailleTexte.first < m_rectangle.w && positionCourante < m_texte.size());
            delete t;
            std::string texteCourant = m_texte.substr(0, positionCourante-1)+ "...";
            t = new TexteSDL(texteCourant, m_couleur, m_cheminPolice, m_taillePolice,
                             std::make_pair<int,int>(m_rectangle.x, m_rectangle.y));
        }
        m_texteSDL.push_back(t);

        break;
    }
    default:
    {
        break;
    }
    }

    assert(m_texte.size() > 0);
    int yMin = m_rectangle.y;
    int yMax = m_texteSDL[m_texteSDL.size()-1]->obtenirRectTexte().second + m_texteSDL[m_texteSDL.size()-1]->rectangle().y;
    int decalageY = (m_rectangle.h - (yMax-yMin))/2.;
    for(unsigned int i = 0; i < m_texteSDL.size(); ++i){
        TexteSDL * t = m_texteSDL[i];
        SDL_Rect rectTexte = t->rectangle();
        std::pair<int, int > tailleTexte = t->obtenirRectTexte();
        std::pair<int, int> nouvellePosition ;
        if(m_alignement == ALIGNEMENT_TEXTE::GAUCHE)
            nouvellePosition = std::make_pair<int,int>(m_rectangle.x, rectTexte.y + decalageY);
        else if(m_alignement == ALIGNEMENT_TEXTE::CENTRE)
            nouvellePosition = std::make_pair<int,int>(m_rectangle.x+ (m_rectangle.w - tailleTexte.first)/2., rectTexte.y + decalageY);
        t->positionner(nouvellePosition);
    }
}

void ZoneTexte::mettreAJourTexte(std::string texte)
{
    m_texte = texte;
    adapterTexte();
}
