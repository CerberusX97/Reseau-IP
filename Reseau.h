/**
 * \file Reseau.h
 * \brief	D�finition de l'interface pour un reseau informatique
 * \author Thierry
 * \version 2.0
 */

#ifndef RESEAU_H_
#define RESEAU_H_

#include <fstream>		// Pour les fichiers
#include <stdexcept>
#include <string>
#include <vector>
#include "Graphe.h"
#include "Routeur.h"
#include <fstream>

class Reseau
{
public:

    Reseau();
    Reseau(std::ifstream& p_fichierEntree);
    void afficherRouteurs(std::vector<Routeur>& p_vRouteurs);
    void afficherRouteurs();

    bool routeursAccessibles(); 
    std::vector<Routeur> routeursCritiques(); 
    std::vector<Routeur> determinerMinParcours(const Routeur& p_routeurOrigine,
                                               const Routeur& p_routeurDestination, int& nbSec); 
    void getRouteurs(std::vector<Routeur>& p_vRouteurs) const;

private:

    Graphe<Routeur> m_graphe; //< Le graphe du réseau
};

#endif // RESEAU_H_
