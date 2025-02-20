/**
 * \file	Graphe.h
 * \brief	interface pour un patron de classe graphe
 */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include <unordered_map>

#ifndef GRAPHE__H
#define GRAPHE__H

/**
 * \class Graphe
 * \brief Classe représentant un graphe orienté, pondéré dont les �tiquettes sont des comparables
 */

template<typename Objet>
class Graphe
{
    class Arc;
    class Sommet;

public:

    Graphe ();
    Graphe (const Graphe& p_source);
    ~Graphe ();


    void ajouterSommet(int p_numero, const Objet& p_etiquette);
    void enleverSommet(int p_numero);

    void ajouterArc(int p_numOrigine, int p_numDestination, int p_cout);
    void enleverArc(int p_numOrigine, int p_numDestination);


    int nombreSommets() const;
    bool estVide() const;
    std::vector<int> listerSommets() const;
    std::vector<Objet> listerEtiquetteSommets() const;


    int getNumeroSommet(const Objet& p_etiquette) const;
    bool sommetExiste(int p_numero) const;
    Objet getEtiquetteSommet(int p_numero) const;
    int ordreSortieSommet(int p_numero) const;
    int ordreEntreeSommet(int p_numero) const;
    std::vector<int> listerSommetsAdjacents(int p_numeroSommetsAdjacents) const;


    bool arcExiste(int p_numOrigine, int p_numDestination) const;
    int getCoutArc(int p_numOrigine, int p_numDestination) const;


    const Graphe& operator= (const Graphe& p_source);

    template<class U> friend std::ostream& operator<< (std::ostream& p_out,
                                                       const Graphe<U>& p_g);

    void getComposantesFortementConnexes(std::vector<std::vector<Objet>>& p_composantes) const;

    bool estFortementConnexe() const;

    int dijkstra(const Objet& p_eOrigine, const Objet& p_eDestination, std::vector<Objet>& p_chemin);

    void getPointsArticulation(std::vector<Objet>& p_sommets);

private:

    // Classes internes

    /**
     * \class	Sommet
     * \brief	Classe représentant un sommet dans un graphe
     */
    class Sommet
    {
    public:
        Sommet(int p_numero, const Objet& p_etiquette);
        Sommet(Sommet* p_source);
        ~Sommet();

        int m_numero; /**< Le num�ro du sommet */
        Objet m_etiquette;
        Arc* m_listeDest; /**< La liste des arcs entre le sommet et les sommets qui lui sont adjacents */
        bool m_etat; /**< Pour marquer un routeur */
        Sommet* m_predecesseur; /**< Pour Dijkstra */
        int m_cout; /**< Pour Dijkstra */
        Sommet *m_precedent; /**< le sommet précédent dans la liste des sommets */
        Sommet *m_suivant; /**< Le prochain sommet dans la liste */

        void verifieInvariant() const;
    };

    /**
     * \class Arc
     * \brief Classe représentant un arc entre deux sommets dans le graphe
     */

    class Arc
    {
    public:

        Arc(Sommet* p_dest, int p_cout);
        ~Arc();

        Sommet* m_dest; /**< Un pointeur sur le sommet de destination */
        int m_cout; /**< Le cout entre les deux sommets reliés par l'arc */
        Arc* m_suivDest; /**< Le prochain sommet de destination */

        void verifieInvariant() const;
    };

    /**
     * \class ComparateurCoutSommet
     *   \brief Classe interne servant à définir un "functor" à la STL pour classer les sommets selon leur coût.
     */

    class ComparateurCoutSommet
    {
    public:
        bool operator()(const Sommet* p_S0, const Sommet* p_S1);
    };

    //	Méthodes auxiliaires
    Sommet *_getSommet(int p_numero) const;
    Arc * _getArc(Sommet* p_sommet1, Sommet* p_sommet2) const;
    void _detruireGraphe();
    void _copierGraphe(const Graphe &p_source);
    void _enleverSommet(Sommet* p_sommetAEnlever);

    //Méthodes auxiliaires (path finding)

    void _initPathFinding(const Objet& p_eOrigine,
                           const Objet& p_eDestination, Sommet*& p_origine,
                           Sommet*& p_destination);

    void _recupererChemin(Sommet* p_destination,
                           std::vector<Objet>& chemin);

    void _parcoursDFS(Sommet* p_Origine, std::list<Sommet*>& p_ListeSommetsVisites) const;
    void _initEtatSommets(bool p_Etat) const;

    // Attributs Graphe
    int m_nbSommets; /**< Le nombre de sommets dans le graphe */
    Sommet* m_listSommets; /**< Liste des sommets du graphe */
};
#include "Graphe.hpp"
#endif