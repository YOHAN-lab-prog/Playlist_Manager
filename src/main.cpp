#include <iostream>
#include <string>
#include "Playlist.h"
using namespace std;

int main() {
    Playlist playlist("Ma Playlist");
    int choice;

    do {
        cout << "==== MENU ====" << endl;
        cout << "1. Ajouter un morceau" << endl;
        cout << "2. Supprimer un morceau" << endl;
        cout << "3. Déplacer un morceau" << endl;
        cout << "4. Afficher la playlist" << endl;
        cout << "5. Lecture suivante" << endl;
        cout << "6. Lecture précédente" << endl;
        cout << "7. Lecture en boucle" << endl;
        cout << "8. Lecture aléatoire" << endl;
        cout << "9. Rechercher par artiste" << endl;
        cout << "10. Rechercher par titre" << endl;
        cout << "11. Sauvegarder" << endl;
        cout << "12. Charger" << endl;
        cout << "0. Quitter" << endl;
        cout << "\nChoix : ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string title, artist;
            int duration;
            cout << "Titre : ";
            getline(cin, title);
            cout << "Artiste : ";
            getline(cin, artist);
            cout << "Duree (secondes) : ";
            cin >> duration;
            playlist.addSong(title, artist, duration);

        } else if (choice == 2) {
            string title;
            cout << "Titre a supprimer : ";
            getline(cin, title);
            playlist.removeSong(title);

        } else if (choice == 3) {
            int from, to;
            cout << "Index actuel : ";
            cin >> from;
            cout << "Nouvel index : ";
            cin >> to;
            playlist.moveSong(from, to);

        } else if (choice == 4) {
            playlist.display();

        } else if (choice == 5) {
            playlist.nextSong();

        } else if (choice == 6) {
            playlist.prevSong();

        } else if (choice == 7) {
            playlist.loopPlay();

        } else if (choice == 8) {
            playlist.shufflePlay();

        } else if (choice == 9) {
            string artist;
            cout << "Artiste : ";
            getline(cin, artist);
            playlist.searchByArtist(artist);

        } else if (choice == 10) {
            string query;
            cout << "Extrait du titre : ";
            getline(cin, query);
            playlist.searchByTitle(query);

        } else if (choice == 11) {
            playlist.saveToFile("data/playlist.txt");

        } else if (choice == 12) {
            playlist.loadFromFile("data/playlist.txt");
        }

    } while (choice != 0);

    cout << "Au revoir !" << endl;
    return 0;
}