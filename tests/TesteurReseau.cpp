//
// Created by Vincent on 11/12/2024.
//
#include <gtest/gtest.h>
#include "Reseau.h"
#include <fstream>


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

                        //cout<< (route.end()-1)->reqNom() << endl;

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
class TestDijkstra : public ::testing::Test {
        public:
                Reseau reseau;
                Reseau reseau2;

        void SetUp() override {
                std::ifstream fichier("../../traceFC.txt");
                reseau = Reseau(fichier);
                std::ifstream fichier2("../../trace.txt");
                reseau2 = Reseau(fichier2);
        }
        int nbSec = 0;
};

class TestRouteursAccessibles : public ::testing::Test {
public:
        Reseau reseau;
        Reseau reseau2;

        void SetUp() override {
                std::ifstream fichier("../../traceFC.txt");
                reseau = Reseau(fichier);
                std::ifstream fichier2("../../trace.txt");
                reseau2 = Reseau(fichier2);
        }
        int nbSec = 0;
};

class TestRouteursCritiques : public ::testing::Test {
public:
        Reseau reseau;
        Reseau reseau2;

        void SetUp() override {
                std::ifstream fichier("../../traceFC.txt");
                reseau = Reseau(fichier);
                std::ifstream fichier2("../../trace.txt");
                reseau2 = Reseau(fichier2);
        }
        int nbSec = 0;
};

TEST_F(TestRouteursAccessibles, RouteursAccessible) {
        EXPECT_EQ(reseau.routeursAccessibles(), true);
}

TEST_F(TestRouteursAccessibles, RouteursNonAccessible) {
        EXPECT_EQ(reseau2.routeursAccessibles(), false);
}

TEST_F(TestDijkstra, OTTAWA_NEWYORK) {
        Routeur r1("c4-mon01.canet4.net", "205.189.32.226", "OTTAWA");
        Routeur r4("sl-gw31-nyc-4-0.sprintlink.net8", "160.81.43.177", "New York");

        std::vector<Routeur> chemin = reseau.determinerMinParcours(r1, r4, nbSec);

        EXPECT_EQ(nbSec, 10);

        EXPECT_EQ(chemin.size(), 2);
}

TEST_F(TestDijkstra, porttheud_OTTAWA) {
        Routeur r1("port-theud", "132.203.120.179", "Quebec");
        Routeur r4("c4-mon01.canet4.net", "205.189.32.226", "OTTAWA");

        std::vector<Routeur> chemin = reseau.determinerMinParcours(r1, r4, nbSec);

        EXPECT_EQ(nbSec, 25);

        EXPECT_EQ(chemin.size(), 4);
}

TEST_F(TestDijkstra, porttheud_NEWYORK) {
        Routeur r1("port-theud", "132.203.120.179", "Quebec");
        Routeur r4("sl-gw31-nyc-4-0.sprintlink.net8", "160.81.43.177", "New York");

        std::vector<Routeur> chemin = reseau.determinerMinParcours(r1, r4, nbSec);

        EXPECT_EQ(nbSec, 35);

        EXPECT_EQ(chemin.size(), 5);
}

TEST_F(TestRouteursCritiques, FC) {
        // Création des routeurs attendus
        Routeur r1("port-theud", "132.203.120.179", "Quebec");
        Routeur r2("gw541a.n.ulaval.ca4", "132.203.244.145", "Quebec");
        Routeur r3("sl-gw31-nyc-4-0.sprintlink.net8", "160.81.43.177", "New York");

        // Liste attendue des routeurs critiques
        std::vector<Routeur> routeursAttendus = {r1, r2, r3};

        // Calcul des routeurs critiques
        std::vector<Routeur> routeursCritiques = reseau.routeursCritiques();

        // Vérification des égalités
        EXPECT_EQ(routeursCritiques, routeursAttendus);
}