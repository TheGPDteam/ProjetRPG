#ifndef OBSERVATEUR_H
#define OBSERVATEUR_H

#include <vector>

class Observable;

class Observateur
{
private:
public:
    //!
    //! \brief Methode de mise à jour
    //!
    void virtual obtenirChangement(Observable &obj) = 0;
};

#endif // OBSERVATEUR_H
