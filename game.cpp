//  Student:Philippe Voet
//  Rolnummer: s0183222
//  Opmerkingen:
//
//  Ik wist niet zeker hoe de locatie aan het schaakstuk moest worden meegegeven.
//  in de code die we hebben gekregen van jullie hield een schaakstuk zijn eigen locatie niet bij.
//  Ik heb een schaakstuk wel zijn eigen locatie late bijhouden aangezien het in mijn ogen anders
//  onmogelijk waas om dit te verplaatsen volgens de code die jullie hebben meegegeven.

#include "game.h"
#include "Positie.h"
#include <vector>
#include <array>

Game::Game() {
    setStartBord();
}

Game::~Game() {}


// Zet het bord klaar; voeg de stukken op de jusite plaats toe
void Game::setStartBord() {

    //Zwarte stukken
    blub[0][3].setColor(Piece::Black); blub[0][3].setType(Piece::Queen); // todo betere naam
    blub[0][4].setColor(Piece::Black); blub[0][4].setType(Piece::King);
    blub[0][2].setColor(Piece::Black); blub[0][2].setType(Piece::Bishop); blub[0][5] = blub[0][2];
    blub[0][1].setColor(Piece::Black); blub[0][1].setType(Piece::Knight); blub[0][6] = blub[0][1];
    blub[0][0].setColor(Piece::Black); blub[0][0].setType(Piece::Rook); blub[0][7] = blub[0][0];

    //Witte stukken
    blub[7][3].setColor(Piece::White); blub[7][3].setType(Piece::Queen);
    blub[7][4].setColor(Piece::White); blub[7][4].setType(Piece::King);
    blub[7][2].setColor(Piece::White); blub[7][2].setType(Piece::Bishop); blub[7][5] = blub[7][2];
    blub[7][1].setColor(Piece::White); blub[7][1].setType(Piece::Knight); blub[7][6] = blub[7][1];
    blub[7][0].setColor(Piece::White); blub[7][0].setType(Piece::Rook); blub[7][7] = blub[7][0];

    //Pionnen
    for (int i = 0; i < 8; i++){
        blub[1][i].setType(Piece::Pawn); blub[1][i].setColor(Piece::Black);
        blub[6][i].setType(Piece::Pawn); blub[6][i].setColor(Piece::White);
    }
    kleur_aan_zet = Piece::White;
    s=new None(wit, new Positie(4,4));
    this->s->piece().setType(Piece::None);
    this->s->piece().setColor(Piece::White);



}


SchaakStuk* Game::getSchaakstuk(Positie* positie){
    auto p = blub[positie->get_y()][positie->get_x()];
    zw kleur = wit;

    if (p.color() == Piece::White){
         kleur = wit;
    }else{
         kleur = zwart;
    }
    if (p.type() == Piece::Pawn){
        SchaakStuk* l=new Pion(kleur, positie);
        l->piece() = p;
        return l;
    }
    if (p.type() == Piece::Rook){
        SchaakStuk* s= new Toren(kleur, positie);
        return s;
    }
    if (p.type() == Piece::None){ //gebruik ik om aan te duiden dat er geen stuk staat op dit vakje
        SchaakStuk* s=new None(kleur, positie );
        return s;
    }
    if (p.type() == Piece::Queen){
        SchaakStuk* s= new Koningin(kleur, positie);
        return s;
    }
    if (p.type() == Piece::King){
        SchaakStuk* s= new Koning(kleur, positie);
        return s;
    }
    if (p.type() == Piece::Bishop){
        SchaakStuk* s= new Loper(kleur, positie);
        return s;
    }
    if (p.type() == Piece::Knight){
        SchaakStuk* s= new Paard(kleur, positie);
        return s;
    }
}

// Verplaats stuk s naar positie p
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven

bool Game::move(SchaakStuk* s, Positie* p) {
    if (s->piece().type() != Piece::None) {
        vector<Positie*> v= this->s->geldige_zetten(*this);
        if (v.empty()){return false;}
        for (int e = 0; e < v.size(); e++) {
            if (v[e]->get_x() == p->get_x() and v[e]->get_y() == p->get_y()) {

                Zet z;
                z.beginpositie = s;
                z.eindpositie = p;
                z.geslagen = blub[p->get_y()][p->get_x()];
                zetten.push_back(z);
                undone.clear();


                blub[p->get_y()][p->get_x()].setType(s->piece().type());
                blub[p->get_y()][p->get_x()].setColor(s->piece().color());

                return true;
            }
        }
    }
    return false;
}

bool Game::undo(Zet z){
    blub[z.beginpositie->getPos()->get_y()][z.beginpositie->getPos()->get_x()] = z.beginpositie->piece();
    if ( z.geslagen.type() != Piece::None){
        blub[z.eindpositie->get_y()][z.eindpositie->get_x()] = z.geslagen;
    }else {
        blub[z.eindpositie->get_y()][z.eindpositie->get_x()].setType(Piece::None);
    }

}
bool Game::redo(Zet z){
    blub[z.eindpositie->get_y()][z.eindpositie->get_x()].setType(z.beginpositie->piece().type());
    blub[z.eindpositie->get_y()][z.eindpositie->get_x()].setColor(z.beginpositie->piece().color());
    zetten.push_back(z);
    blub[z.beginpositie->getPos()->get_y()][z.beginpositie->getPos()->get_x()].setType(Piece::None);
}

// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {

    return false;
}

// Geeft true als kleur schaakmat staat
bool Game::schaakmat(zw kleur) {
    return false;
}

// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    return false;
}
