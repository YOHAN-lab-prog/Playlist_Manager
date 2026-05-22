#pragma once // Utilise pour eviter les inclusions multiples du meme fichier
#include <string>

struct Song {
    std::string title;
    std::string artist;
    int duration;   // en secondes

    Song* prev;
    Song* next;

    // Constructeur
    Song(std::string t, std::string a, int d)
        : title(t), artist(a), duration(d),
          prev(nullptr), next(nullptr) {}
};