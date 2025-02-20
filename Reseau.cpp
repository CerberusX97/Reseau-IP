
/** \file Reseau.cpp
 * \brief Définition de l'interface pour un reseau informatique
 * \author TE
*/
#include <algorithm>
#include "Reseau.h"
#include "ContratException.h"
#include <vector>
#include <fstream>

using namespace std;

/**
 * \brief Constructeur par d�faut
 * \post Un r�seau vide est instanci�.
 */
Reseau::Reseau () { };

/**
 * \brief Constructeur à partir d'un fichier en entrée.
 * \param[in, out] p_fichierEntree fichierEntree un flux sur un fichier d'entrée
 * \pre Il y a assez de mémoire pour charger tous les routeur de la liste.
 * \pre	Le fichier p_fichierEntree est ouvert corectement.
 * \post Le fichier p_fichierEntree n'est pas fermé par la fonction.
 * Si les préconditions sont respectées, les données du réseau contenu
 * dans le fichier en entrée sont organis�es dans un graphe en m�moire.

 */
Reseau::Reseau(std::ifstream& p_fichierEntree)
{
    //Lecture des données sur les routeurs
    string nom; //Pour le nom des routeurs
    string adresseIP;
    string localisation;
    int numero = 1;
    vector<string> tabNomRouteurs;

    bool sentinelle = false;

    while (!p_fichierEntree.eof () && sentinelle == false)
    {
        getline(p_fichierEntree, nom);
        cout << nom << endl;
        if (nom == "$")//limite de la première partie du fichier
        {
            sentinelle = true;
        }
        else
        {
            getline(p_fichierEntree, adresseIP);
            getline(p_fichierEntree, localisation);
            Routeur lRouteur (nom, adresseIP, localisation);
            m_graphe.ajouterSommet(numero, lRouteur);
            ++numero;
            tabNomRouteurs.push_back(nom);
        }
    }

    int tempsTransmission;
    string nomD; //nom du routeur de destination
    int indiceSource;
    int indiceDestination;
    char buff[255];
    vector<string>::iterator location;
    while (!p_fichierEntree.eof())
    {
        p_fichierEntree.getline(buff, 100);
        nom = buff;
        location = find(tabNomRouteurs.begin (), tabNomRouteurs.end (), nom);
        indiceSource = location - tabNomRouteurs.begin ();
        p_fichierEntree.getline(buff, 100);
        nomD = buff;
        location = find(tabNomRouteurs.begin (), tabNomRouteurs.end (), nomD);
        indiceDestination = location - tabNomRouteurs.begin ();
        p_fichierEntree >> tempsTransmission;
        p_fichierEntree.ignore();

        m_graphe.ajouterArc(indiceSource + 1, indiceDestination + 1,
                             tempsTransmission);
    }

    cout << "********Graphe lu: ********" << std::endl;
    cout << m_graphe;
    cout << "***************************" << std::endl;

}

/**
 * \brief Affiche une liste de routeurs du réseau � l'ecran.
 * @param p_vRouteurs Une liste de routeurs dans un vector.
 * \post Le contenu de la liste v est affiché.
 */
void
Reseau::afficherRouteurs (std::vector<Routeur> & p_vRouteurs)
{
    if (p_vRouteurs.size () == 0)
    {
        std::cout << "La liste est vide\n";
        return;
    }

    for (unsigned int i = p_vRouteurs.size (); i > 0; i--)
    {
        std::cout << p_vRouteurs[i - 1] << std::endl;
    }
}

/**
 * \brief Affiche la liste de tous les routeurs du réseau � l'écran
 * \pre	Le reseau est non vide
 * \post La liste de tous les routeurs du r�seau sont affich�es.
 */
void
Reseau::afficherRouteurs()
{
    PRECONDITION(!m_graphe.estVide());
    std::vector<Routeur> lListeRouteur = m_graphe.listerEtiquetteSommets ();
    afficherRouteurs (lListeRouteur);
}

/**
 *
 * @param p_vRouteurs liste des routeurs enregistrés dans le réseau
 */
void
Reseau::getRouteurs (std::vector<Routeur>& p_vRouteurs) const
{
    p_vRouteurs = m_graphe.listerEtiquetteSommets ();
}

/**
 * \brief Vérifie si tous les routeurs du graphe sont accessibles (si le graphe est fortement connexe).
 * \pre Le graphe ne doit pas être vide.
 * \return true si le graphe est fortement connexe, false sinon.
 * \post Aucune modification n'est effectuée sur le graphe.
 */
bool Reseau::routeursAccessibles() {
    PRECONDITION(!m_graphe.estVide())
    return m_graphe.estFortementConnexe();
}

/**
 * \brief Retourne les points d'articulation du graphe.
 * \pre Le graphe ne doit pas être vide.
 * \return Un vecteur de `Routeur` représentant les points d'articulation du graphe.
 * \post Le graphe original n'a pas été modifié après l'exécution de cette méthode.
 * \post Le nombre de sommets dans le graphe reste inchangé.
 */
std::vector<Routeur> Reseau::routeursCritiques() {
    PRECONDITION(m_graphe.listerSommets().size() != 0);
    Graphe<Routeur> copie(m_graphe);
    std::vector<Routeur> critiques;
    m_graphe.getPointsArticulation(critiques);
    return critiques;
    POSTCONDITION(m_graphe.listerSommets().size() == copie.listerSommets().size());
}

/**
 * \brief Détermine le plus court chemin entre deux routeurs à l'aide de l'algorithme de Dijkstra.
 * \pre Les deux routeurs spécifiés (origine et destination) doivent exister dans le graphe.
 * \param[in] p_routeurOrigine Le routeur d'origine.
 * \param[in] p_routeurDestination Le routeur de destination.
 * \param[out] nbSec Le temps de transmission total en secondes. Si aucun chemin n'est trouvé, la valeur sera -1.
 * \return Un vecteur contenant les routeurs du plus court chemin, ou un vecteur vide si aucun chemin n'existe.
 * \post Le graphe original ne doit pas avoir été modifié après l'exécution de l'algorithme.
 *       La taille de la liste des sommets du graphe avant et après l'exécution doit être identique.
 *       Si aucun chemin n'existe, le vecteur retourné sera vide et nbSec sera égal à -1.
 * \exception std::bad_alloc Si la mémoire est insuffisante pour calculer le chemin.
 */
std::vector<Routeur> Reseau::determinerMinParcours(const Routeur& p_routeurOrigine, const Routeur& p_routeurDestination, int& nbSec) {
    PRECONDITION(this->m_graphe.sommetExiste(this->m_graphe.getNumeroSommet(p_routeurOrigine)));
    PRECONDITION(this->m_graphe.sommetExiste(this->m_graphe.getNumeroSommet(p_routeurDestination)));
    Graphe<Routeur> copie(this->m_graphe);
    std::vector<int> sommetsAvant = this->m_graphe.listerSommets();
    try {
        std::vector<Routeur> chemin;
        int distance = m_graphe.dijkstra(p_routeurOrigine, p_routeurDestination, chemin);
        nbSec = distance;
        return chemin;

    } catch (const std::bad_alloc&) {
        std::cerr << "Erreur : mémoire insuffisante pour calculer le chemin." << std::endl;
    }
    POSTCONDITION(copie.listerSommets() == sommetsAvant);
}