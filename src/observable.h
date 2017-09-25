#ifndef OBSERVABLE_H
#define OBSERVABLE_H

#include <vector>

class Observateur;

class Observable
{
private:
    std::vector<Observateur*> m_listeObservateur;
    bool m_aChange;
public:
    Observable();
    virtual ~Observable()=default;
    bool aChange();
    void mettreAChange();
    void notifier(Observateur &obs);
    void notifierTous();
    void ajouterObservateur(Observateur &obs);
};

#endif // OBSERVABLE_H
