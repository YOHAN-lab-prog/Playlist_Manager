#pragma once
#include <string>
#include "Song.h"
using namespace std;

class Playlist {
private:
    Song* head;
    Song* tail;
    Song* current;
    int size;
    std::string name;

public:
    // Constructeur / Destructeur
    Playlist(std::string name);
    ~Playlist();

    // Gestion
    void addSong(string title, string artist, int duration);
    void removeSong(string title);
    void moveSong(int from, int to);
    void display();

    // Lecture
    void play();
    void nextSong();
    void prevSong();
    void loopPlay();
    void shufflePlay();

    // Recherche
    void searchByArtist(string artist);
    void searchByTitle(string query);

    // Fichier
    void saveToFile(string filename);
    void loadFromFile(string filename);

    // Utilitaires
    bool isEmpty();
    void clear();
    Song* getNodeAt(int index);
};