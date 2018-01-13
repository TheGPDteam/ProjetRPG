#include "ecrangeneral.h"


//!
//! \brief Constructeur écran général
//! \author pgutierrez
//! \date 23/11/16
//! \version 1.0
//!

EcranGeneral::EcranGeneral(Controleur *controleur) :
    m_controleur{controleur}, DictionnaireDeBoutons(controleur)
{
}


//!
//! \brief Destructeur écran général
//! \author pgutierrez
//! \date 23/11/16
//! \version 1.0
//!

EcranGeneral::~EcranGeneral()
{

}
