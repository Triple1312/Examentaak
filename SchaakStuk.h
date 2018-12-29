//  Student:Philippe Voet
//  Rolnummer:s0183222
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H

//#include <game.h>
#include <chessboard.h>
#include <Positie.h>
#include <vector>

class Game;

enum zw{zwart,wit};

//in mijn code is het gebruik van een schaakstuk eigenlijk overbodig door de manier hoe ik stukken bijhoud
//op het bord zelf. Ik heb het hele systeem van Schaakstukken ttoch maar gebruikt omdat er anders geen deel is
//waar ik "virtual functies" gebruik. Maar daarom ziet het gebruik ervan er misschien vreemd uit en heb ik
// een Schaakstuk ook een positie meegegeven.

class SchaakStuk {
public:
    vector<Positie*> geldige_zetten(Game&);
    SchaakStuk(zw kleur, Positie* pos): kleur(kleur), positie(pos)  {}

    virtual Piece piece() const=0;      // Deze functie krijg je cadeau
                                        // Je hebt die nodig om het stuk in de
                                        // GUI te tekenen
                                        // Meer info: kijk naar mainwindow.cpp, lijn 27

    zw getKleur() const { return kleur; }
    Positie* getPos() const { return positie;}
private:
    zw kleur;
    Positie* positie;


};

// ik heb dit nodig om aan te duiden dat er geen schaakstuk is aangeduid.
class None:public SchaakStuk {
public:
    None(zw kleur, Positie* pos):SchaakStuk(kleur,pos){}
    virtual Piece piece() const override {
        return Piece(Piece::None, getKleur()==wit?Piece::White:Piece::Black);
}};

class Pion:public SchaakStuk {
public:
    Pion(zw kleur, Positie* pos):SchaakStuk(kleur, pos) {}
    Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }
};

class Toren:public SchaakStuk {
public:
    Toren(zw kleur, Positie* pos):SchaakStuk(kleur, pos) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }
};

class Paard:public SchaakStuk {
public:
    Paard(zw kleur, Positie* pos):SchaakStuk(kleur, pos) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }
};

class Loper:public SchaakStuk {
public:
    Loper(zw kleur, Positie* pos):SchaakStuk(kleur, pos) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }
};

class Koning:public SchaakStuk {
public:
    Koning(zw kleur, Positie* pos):SchaakStuk(kleur, pos) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }
};

class Koningin:public SchaakStuk {
public:
    Koningin(zw kleur, Positie* pos):SchaakStuk(kleur, pos) {}

    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }
};

#endif //SCHAKEN_SCHAAKSTUK_H
