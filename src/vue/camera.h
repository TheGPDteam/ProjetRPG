#ifndef CAMERA_H
#define CAMERA_H


#include <SDL/SDL.h>
#include <utility>

#include "affichable.h"


class Camera {
protected:
    float m_positionX;
    float m_positionY;
    bool m_suitAffichable;

    Affichable* m_affichableSuivi;

    static bool m_instancie;
    static Camera m_instance;

public:
    Camera();
    ~Camera();

    void definirPosition(float x, float y);
    void definirPositionX(float x);
    void definirPositionY(float y);

    float obtenirPositionX();
    float obtenirPositionY();
    std::pair<float, float> obtenirPosition();

    void definirAffichableSuivi(Affichable* affichable);
    void detacheAffichableSuivi();

    void vaAffichableSuivi();

    static Camera* ObtenirInstance();

};

bool Camera::m_instancie = false;
Camera Camera::m_instance;

#endif // CAMERA_H
