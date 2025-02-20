/**
 *  \file Routeur.h
 *  \brief	Déclaration de l'interface pour un routeur
 *  \author Thierry
 *  \version 2.0
 */


#ifndef ROUTEUR_H_
#define ROUTEUR_H_

#include <string>
#include <iostream>

class Routeur
{
public:
    Routeur(){};
    Routeur(const std::string& p_nom, const std::string& p_adresseIP,
            const std::string& p_localisation);

    bool operator==(const Routeur& p_routeur) const;
    bool operator!=(const Routeur& p_routeur) const;
    friend std::ostream& operator <<(std::ostream& out, const Routeur& p_routeur);
    const std::string& reqAdresseIP() const;
    const std::string& reqLocalisation() const;
    const std::string& reqNom() const;

private:
    std::string m_nom; /**< Le nom du routeur */
    std::string m_adresseIP; /**< L'adresse IP du routeur */
    std::string m_localisation;

    void verifieInvariant() const;
    bool validerAdresseIP(const std::string& p_adresseIP) const;
};


#endif /* ROUTEUR_H_ */
