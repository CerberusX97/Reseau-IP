#include <iostream>
#include <sstream>
#include "Routeur.h"
#include "Graphe.h"
#include "Reseau.h"

using namespace std;

void executerAlgorithmes(Reseau &reseau, const Routeur &r1, const Routeur &r2) {
    int tempsTransmission = 0;
    vector<Routeur> route;
    route = reseau.determinerMinParcours(r1, r2, tempsTransmission);

    cout<<"Temps entre "<< r1.reqNom() << " et "<< r2.reqNom() << " est : " << tempsTransmission << endl;
    cout<<"Les sommets parcourus sont : ";

    for (auto it = route.begin(); it != route.end() - 1; ++it)
    {
        cout<< it->reqNom() << ", ";
    }

    cout<< (route.end()-1)->reqNom() << endl;

    if (reseau.routeursAccessibles())
    {
        cout << "Le graphe est fortement connexe."<< endl;
        cout << "Les routeurs critiques sont : ";

        vector<Routeur> routeursCritiques;
        routeursCritiques = reseau.routeursCritiques();

        for (auto it = routeursCritiques.begin(); it != routeursCritiques.end() - 1; ++it)
        {
            cout<< it->reqNom() << ", ";
        }

        cout<< (routeursCritiques.end()-1)->reqNom() << endl;
    }
    else
    {
        cout << "Le graphe n'est pas fortement connexe. Il n'y a pas de routeur critique"<< endl;

    }
}


int main()
{
    ifstream fichier("../trace.txt");
    Reseau reseau(fichier);
    Routeur r1("c4-mon01.canet4.net", "205.189.32.226", "OTTAWA");
    Routeur r4("sl-gw31-nyc-4-0.sprintlink.net8", "160.81.43.177", "New York");
    executerAlgorithmes(reseau, r1, r4);



    ifstream fichier2("../traceFC.txt");
    Reseau reseau2(fichier2);

    executerAlgorithmes(reseau2, r1, r4);
}

