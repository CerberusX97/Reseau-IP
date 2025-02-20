/**
 * \file Routeur.cpp
 * Created by Kim on 2024-10-17.
 */

#include "Routeur.h"
#include "ContratException.h"
#include <regex>

/**
 * \brief constructeur
 * @param p_nom le nom du routeur
 * \pre nom non vide
 * @param p_adresseIP l'addresse IP du routeur
 * \pre adresse valide
 * @param p_localisation
 * \pre localisation non vide
 */
Routeur::Routeur(const std::string& p_nom, const std::string& p_adresseIP,
                 const std::string& p_localisation) :
        m_nom(p_nom),
        m_adresseIP(p_adresseIP),
        m_localisation(p_localisation)
{
    PRECONDITION(validerAdresseIP(p_adresseIP));
    PRECONDITION(!p_nom.empty());
    PRECONDITION(!p_localisation.empty());

    INVARIANTS();

    PRECONDITION(p_nom == m_nom);
    PRECONDITION(p_localisation == m_localisation);
    PRECONDITION(p_adresseIP == m_adresseIP);
}
/**
 * \brief vérifie l'égalité entre 2 routeurs tous les attributs doivent être identiques
 * @param p_routeur
 * @return vrai si tous les attributs sont identiques, faux sinon
 */
bool Routeur::operator==(const Routeur& p_routeur) const
{
    return p_routeur.m_adresseIP == m_adresseIP && p_routeur.m_localisation == m_localisation && p_routeur.m_nom == m_nom;
}

/**
 * \brief vérifie si 2 routeurs sont différents
 * @param p_routeur
 * @return vrai si un des attributs est différent, faux sinon
 */
bool Routeur::operator!=(const Routeur& p_routeur) const
{
    return !(p_routeur == *this);
}
/**
 * \brief surcharge pour formater l'état d'un routeur
 * @param out flux de sortie
 * @param p_routeur
 * @return le flux de sortie contenant la concaténation de l'état du routeur
 */
std::ostream& operator<<(std::ostream& out, const Routeur& p_routeur)
{
    out << p_routeur.m_nom << std::endl;
    out << p_routeur.m_adresseIP << std::endl;
    out << p_routeur.m_localisation << std::endl;
    return out;
}

//accesseurs
const std::string& Routeur::reqAdresseIP() const
{
    return m_adresseIP;
}

const std::string& Routeur::reqLocalisation() const
{
    return m_localisation;
}

const std::string& Routeur::reqNom() const
{
    return m_nom;
}

void Routeur::verifieInvariant() const
{
    INVARIANT(!m_nom.empty());
    INVARIANT(validerAdresseIP(m_adresseIP));
    INVARIANT(!m_localisation.empty());
}

/**
 * \brief valide une adresse IP
 * @param p_adresseIP adresse IP à valider
 * @return true si adresse valide false sinon
 */
bool Routeur::validerAdresseIP(const std::string& p_adresseIP) const {
    const std::regex regexIP(R"((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\.(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?))");
    return std::regex_match(p_adresseIP,regexIP);
}
