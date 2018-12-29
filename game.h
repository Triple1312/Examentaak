//  Student:Philippe Voet
//  Rolnummer: s0183222
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H

#include <vector>
#include <array>
#include "SchaakStuk.h"

class Positie;
class Zet{
public:
    SchaakStuk* beginpositie;
    Positie* eindpositie;
    Piece geslagen;
};

class Game {
// variabelen om de status van het spel/bord te bewaren

public:
    vector<Zet> zetten; //deze vector houdt bij welke zetten er al zijn gemaakt en kan deze omgekeerd uitvoeren
    vector<Zet> undone; // dit houdt de zetten die zijn teruggezet bij
    Piece::Color kleur_aan_zet;
    Game();
    ~Game();
    array< array<Piece, 8>, 8>  blub; // maakt een matrix van 8 op 8
    SchaakStuk* getSchaakstuk(Positie*);
    bool move(SchaakStuk*,Positie*);
    bool undo(Zet);
    bool redo(Zet);
    SchaakStuk* s;
    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    void setStartBord();
};


#endif SCHAKEN_GAME_H
