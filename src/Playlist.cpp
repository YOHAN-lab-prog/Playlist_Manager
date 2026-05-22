#include "Playlist.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
using namespace std;

// Constructeur
Playlist::Playlist(string name) {
    this->name = name;
    head = nullptr;
    tail = nullptr;
    current = nullptr;
    size = 0;
}

// Destructeur
Playlist::~Playlist() {
    clear();
}

bool Playlist::isEmpty() {
    return head == nullptr;
}
//================================================================//
// METHODE: NETTOYER LA PLAYLIST //
//================================================================// 
void Playlist::clear() {
    Song* current = head;
    while (current != nullptr) {
        Song* next = current->next;
        delete current;
        current = next;
    }
    head = tail = nullptr;
    size = 0;
}
//================================================================//
// METHODE: AJOUTER UNE CHANSON A LA PLAYLIST //
//================================================================//
void Playlist::addSong(string title, string artist, int duration) {
    Song* newSong = new Song(title, artist, duration);

    if (isEmpty()) {
        head = tail = current = newSong; // Ajout direct en cas de playlist vide
    } else {
        newSong->prev = tail;
        tail->next = newSong;
        tail = newSong;
    }
    size++;
}
//================================================================//
// METHODE: SUPPRIMER UNE CHANSON DE LA PLAYLIST //
//================================================================//
void Playlist::removeSong(string title) {
    if (isEmpty()) {
        cout << "La playlist est vide !" << endl;
        return;
    }

    Song* temp = head;

    while (temp != nullptr) { // Parcours de la liste pour trouver la chanson a supprimer
        if (temp->title == title) {
        // Cas de suppression d'un element
            // Cas 1 : seul élément
            if (temp == head && temp == tail) {
                head = tail = current = nullptr; // Nettoyage de la playlist si c'est le seul élément
            }
            // Cas 2 : c'est la tête
            else if (temp == head) {
                head = head->next;
                head->prev = nullptr;
            }
            // Cas 3 : c'est la queue
            else if (temp == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            }
            // Cas 4 : au milieu
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }

            if (current == temp) current = head;
            delete temp;
            size--;
            cout << title << "supprimé !" << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Morceau introuvable !" << endl;
}
//================================================================//
// METHODE: DEPLACER UNE CHANSON DANS LA PLAYLIST //
//================================================================//
// Cette methode getNodeAt sert a recuperer la position d'une chanson dans la playlist a partir de son index. 
Song* Playlist::getNodeAt(int index) {
    if (index < 0 || index >= size){return nullptr;}
    Song* temp = head;
    for (int i = 0; i < index; i++) {
        temp = temp->next; // Parcours de la liste jusqu'a l'index voulu
    }
    return temp;
}

void Playlist::moveSong(int from, int to) {
    if (from == to) {return;}
    if (from < 0 || from >= size || to < 0 || to >= size) { // index invalide
        std::cout << "Index invalide !" << std::endl;
        return;
    }

    Song* song = getNodeAt(from);

    // Detacher le nœud
    // Cas 1 : La chanson est la seule dans la playlist.
    if (song == head && song == tail) return;
    else if (song == head) {
        head = song->next;
        head->prev = nullptr;
    }
    // Cas 2 : La chanson est la queue.
    else if (song == tail) {                    // Dans cette premiere partie, l'on trouve l'index de la chanson a deplacer et on la detache (supprime) de la liste.
        tail = song->prev;
        tail->next = nullptr;
    }
    // Cas 3 : La chanson est au milieu.
    else {
        song->prev->next = song->next;
        song->next->prev = song->prev;
    }
    song->prev = song->next = nullptr;
    size--;

    // Reinserer à la position "to"
    if (isEmpty()) {
        head = tail = song;
        size++;
        return;
    }
    // Cas 1 : insertion en tete
    if (to <= 0) {
        song->next = head;                   
        head->prev = song;
        head = song;
    }
    // Cas 2 : insertion en queue
    else if (to >= size) {
        song->prev = tail;
        tail->next = song;
        tail = song;
    }
    // Cas 3 : insertion au milieu
    else {
        Song* target = getNodeAt(to);
        song->next = target;                   // Echange d'elements pour inserer la chanson a la position voulue
        song->prev = target->prev;
        target->prev->next = song;
        target->prev = song;
    }
    size++;
}
//================================================================//
// METHODE: AFFICHER LA PLAYLIST //
//================================================================//
void Playlist::display() {
    if (isEmpty()) {
        std::cout << "La playlist est vide !" << std::endl;
        return;
    }

    std::cout << "Playlist : " << name << " = " << std::endl;
    std::cout << "Total : " << size << " morceaux" << std::endl;

    Song* temp = head;
    int index = 0;

    while (temp != nullptr) {
        int minutes = temp->duration / 60;
        int seconds = temp->duration % 60;

        std::cout << index << ". ";

        if (temp == current) std::cout << "> "; // Current == chanson en cours de lecture

        std::cout << temp->title << " — " << temp->artist << " [" << minutes << "m" << seconds << "s]" << std::endl;

        temp = temp->next;
        index++;
    }
    std::cout << std::endl;
}
//================================================================//
// METHODE: LIRE LA PLAYLIST //
//================================================================//
// Methode pour l'affichage de la lecture.
void Playlist::play() {
    if (isEmpty()) {
        std::cout << "La playlist est vide !" << std::endl;
        return;
    }
    int minutes = current->duration / 60;
    int seconds = current->duration % 60;

    std::cout << "En cours : " << current->title << " — " << current->artist << " [" << minutes << "m" << seconds << "s]" << std::endl;
}
/// Methode pour passer a la chanson suivante dans la playlist.
void Playlist::nextSong() {
    if (isEmpty()) {return;}

    if (current->next != nullptr) {
        current = current->next;
    } else {
        std::cout << "C'est le dernier morceau !" << std::endl;
        return;
    }
    play();
}
// Methode pour revenir a la chanson precedente dans la playlist.
void Playlist::prevSong() {
    if (isEmpty()) {return;}

    if (current->prev != nullptr) {
        current = current->prev;
    } else {
        std::cout << "C'est le premier morceau !" << std::endl;
        return;
    }
    play();
}
//================================================================//
// METHODE: DIFFERENTES LECTURES //
//================================================================//
// Lecture en boucle.
void Playlist::loopPlay() {
    if (isEmpty()) {return;}

    if (current->next != nullptr) {
        current = current->next;
    } else {
        current = head; // Retourne au debut
    }
    play();
}

void Playlist::shufflePlay() {
    if (isEmpty()) {return;}

    int randomIndex = rand() % size; // Generation d'un index aleatoire pour la lecture shuffle
    current = getNodeAt(randomIndex);
    play();
}
//================================================================//
// METHODE: RECHERCHER DANS LA PLAYLIST //
//================================================================//
// Methode pour rechercher des chansons par artiste.                                                                            
void Playlist::searchByArtist(std::string artist) {
    if (isEmpty()) {
        std::cout << "La playlist est vide !" << std::endl;
        return;
    }

    std::cout << "Resultats pour l'artiste : " << artist << " =" << std::endl;

    Song* temp = head;
    int count = 0;  // Compteur pour le nombre de morceaux trouves

    while (temp != nullptr) {
        if (temp->artist == artist) { // Si l'artiste correspond, on affiche les details de la chanson
            int minutes = temp->duration / 60;
            int seconds = temp->duration % 60;
            std::cout << "- " << temp->title << " [" << minutes << "m" << seconds << "s]" << std::endl;
            count++;
        }
        temp = temp->next;
    }

    if (count == 0) {
        std::cout << "Aucun morceau trouver !" << std::endl;
    } else {
        std::cout << count << " morceau(x) trouve(s)" << std::endl;
    }
}
// Methode pour rechercher des chansons par titre.
void Playlist::searchByTitle(std::string title) {
    if (isEmpty()) {
        std::cout << "La playlist est vide !" << std::endl;
        return;
    }

    std::cout << "Resultats pour : "<< title << " =" << std::endl;

    Song* temp = head;
    int count = 0;

    while (temp != nullptr) {
        if (temp->title == title) { 
            int minutes = temp->duration / 60;
            int seconds = temp->duration % 60;
            std::cout << "- " << temp->title << " — " << temp->artist << " [" << minutes << "m" << seconds << "s]" << std::endl;
            count++;
        }
        temp = temp->next;
    }

    if (count == 0) {
        std::cout << "Aucun morceau trouve !" << std::endl;
    } else {
        std::cout << count << " morceau(x) trouve(s)" << std::endl;
    }
}
//================================================================//
// METHODE: SAUVEGARDER ET CHARGER LA PLAYLIST DANS UN FICHIER //
//================================================================//
// Methode pour sauvegarder la playlist dans un fichier texte.
void Playlist::saveToFile(std::string filename) {
    std::ofstream file(filename); // ofstream pour ecrire dans le fichier

    if (!file.is_open()) { // Verifie si le fichier a ete ouvert correctement
        std::cout << "Erreur : impossible d'ouvrir le fichier !" << std::endl;
        return;
    }

    Song* temp = head;
    while (temp != nullptr) {
        file << temp->title << "|" << temp->artist << "|" << temp->duration << "\n"; // Ecriture dans le fichier
        temp = temp->next;
    }

    file.close();
    std::cout << "Playlist sauvegardee dans " << filename << " !" << std::endl;
}
// Methode pour charger une playlist depuis un fichier texte.
void Playlist::loadFromFile(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Erreur : fichier introuvable !" << std::endl;
        return;
    }

    clear(); // Vide la playlist avant de charger

    std::string line;
    while (std::getline(file, line)) { // Lecture d'une ligne entiere du fichier 
        std::stringstream ss(line);  // stringstream pour parser la ligne en utilisant le caractere '|' comme separateur
        std::string title, artist, durationStr;

        std::getline(ss, title, '|');
        std::getline(ss, artist, '|');
        std::getline(ss, durationStr, '|');

        addSong(title, artist, std::stoi(durationStr));
    }

    file.close();
    std::cout << "Playlist chargee depuis " << filename << " !" << std::endl;
}