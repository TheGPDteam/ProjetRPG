#include "camera.h"


// Constructeur et destructeur

Camera::Camera(){
    m_suitAffichable = false;
    m_positionX = 0;
    m_positionY = 0;
    m_affichableSuivi = nullptr;
}


Camera::~Camera(){
   delete(m_affichableSuivi);
}


// Definir

void Camera::definirPosition(float x, float y){
    definirPositionX(x);
    definirPositionY(y);
}


void Camera::definirPositionX(float x){
   m_positionX = x;
}


void Camera::definirPositionY(float y){
   m_positionY = y;
}


// Obtenir

std::pair<float, float> Camera::obtenirPosition(){
    return std::pair<float, float> (obtenirPositionX(), obtenirPositionY());
}


float Camera::obtenirPositionX(){
    return m_positionX;
}


float Camera::obtenirPositionY(){
    return m_positionY;
}



// Methodes affichable suivi

void Camera::definirAffichableSuivi(Affichable* affichable){
    m_suitAffichable = true;
    m_affichableSuivi = affichable;
}


void Camera::detacheAffichableSuivi(){
    m_suitAffichable = false;
    m_affichableSuivi = nullptr;
}


void Camera::vaAffichableSuivi(){
    if (m_suitAffichable && m_affichableSuivi != nullptr){
        SDL_Rect renduAffichable = m_affichableSuivi->obtenirRectangle();
        definirPositionX(renduAffichable.x - renduAffichable.w / 2.0);
        definirPositionY(renduAffichable.y - renduAffichable.h / 2.0);
    }
}


// Obtenir Camera

Camera* Camera::ObtenirInstance(){
    if(!m_instancie){
        m_instance = Camera();
        m_instancie = true;
    }

    return &m_instance;
}
