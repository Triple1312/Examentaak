//  Student:Philippe Voet
//  Rolnummer: s0183222
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include <vector>
#include "mainwindow.h"
#include <array>
//#include "game.h"


vector<Positie*> SchaakStuk::geldige_zetten(Game& g) {
    vector<Positie *> mog;
    auto pos = this->getPos();
    auto col = this->getKleur();

    //KONIGIN is vervangen door LOPER + TOREN

    //KONING
    if (this->piece().type() == Piece::King) {
        if (pos->get_x() + 1 < 8) {
            if (g.blub[pos->get_y()][pos->get_x() + 1].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x() + 1, pos->get_y()));
            } else if (g.blub[pos->get_y()][pos->get_x()].color() != this->piece().color()) {
                mog.push_back(new Positie(pos->get_x() + 1, pos->get_y()));
            }
        }
        if (pos->get_x() - 1 >= 0) {
            if (g.blub[pos->get_y()][pos->get_x() - 1].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x() - 1, pos->get_y()));
            } else if (g.blub[pos->get_y()][pos->get_x()].color() != this->piece().color()) {
                mog.push_back(new Positie(pos->get_x() - 1, pos->get_y()));
            }
        }
        if (pos->get_y() + 1 < 8) {
            if (g.blub[pos->get_y() + 1][pos->get_x()].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x(), pos->get_y() + 1));
            } else if (g.blub[pos->get_y() + 1][pos->get_x()].color() != this->piece().color()) {
                mog.push_back(new Positie(pos->get_x(), pos->get_y() + 1));
            }
        }
        if (pos->get_y() -1 >= 0) {
            if (g.blub[pos->get_y() - 1][pos->get_x()].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x(), pos->get_y() - 1));
            } else if (g.blub[pos->get_y() - 1][pos->get_x()].color() != this->piece().color()) {
                mog.push_back(new Positie(pos->get_x(), pos->get_y() - 1));
            }
        }
        if (pos->get_y() + 1 < 8 and  pos->get_x() + 1 < 8) {
            if (g.blub[pos->get_y() + 1][pos->get_x() + 1].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x() + 1, pos->get_y() + 1));
            } else if (g.blub[pos->get_y() + 1][pos->get_x() + 1].color() != this->piece().color()) {
                mog.push_back(new Positie(pos->get_x() + 1, pos->get_y() + 1));
            }
        }
        if (pos->get_y() + 1 < 8 and pos->get_x() - 1 >= 0) {
            if (g.blub[pos->get_y() + 1][pos->get_x() - 1].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x() - 1, pos->get_y() + 1));
            } else if (g.blub[pos->get_y() + 1][pos->get_x() - 1].color() != this->piece().color()) {
                mog.push_back(new Positie(pos->get_x() - 1, pos->get_y() + 1));
            }
        }
        if (pos->get_y() -1 >= 0 and pos->get_x() - 1 >= 0) {
            if (g.blub[pos->get_y() - 1][pos->get_x() - 1].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x() - 1, pos->get_y() - 1));
            } else if (g.blub[pos->get_y() - 1][pos->get_x() - 1].color() != this->piece().color()) {
                mog.push_back(new Positie(pos->get_x() - 1, pos->get_y() - 1));
            }
        }
        if (pos->get_y() -1 >= 0 and pos->get_x() + 1 < 8) {
            if (g.blub[pos->get_y() - 1][pos->get_x() + 1].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x() + 1, pos->get_y() - 1));
            } else if (g.blub[pos->get_y() - 1][pos->get_x() + 1].color() != this->piece().color()) {
                mog.push_back(new Positie(pos->get_x() + 1, pos->get_y() - 1));
            }
        }
    }

    //PION
    if (this->piece().type() == Piece::Pawn){
        if (this->piece().color() == Piece::White) {
            //eerste zet wnr je nog 2 vakjes naar voor kan
            if (pos->get_y() == 6 and g.blub[pos->get_y() - 1][pos->get_x()].type() == Piece::None and
                g.blub[pos->get_y() - 2][pos->get_x()].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x(), pos->get_y() - 2));
            }
            if (pos->get_y() != 0) {
                mog.push_back(new Positie(pos->get_x(), pos->get_y() - 1));
            }
            if (pos->get_y() == 0 or g.blub[pos->get_y() - 1][pos->get_x()].type() != Piece::None) {
                mog.clear();
            }
            if (pos->get_y() -1 >= 0 and pos->get_x() - 1 >= 0 and g.blub[pos->get_y() - 1][pos->get_x() - 1].color() != this->piece().color() and g.blub[pos->get_y() - 1][pos->get_x() - 1].type() != Piece::None) {
                mog.push_back(new Positie(pos->get_x() - 1, pos->get_y() - 1));
            }
            if (pos->get_y() -1 >= 0 and pos->get_x() < 7 and g.blub[pos->get_y() - 1][pos->get_x() + 1].color() != this->piece().color() and g.blub[pos->get_y() - 1][pos->get_x() + 1].type() != Piece::None) {
                mog.push_back(new Positie(pos->get_x() + 1, pos->get_y() - 1));
            }

        } if (this->piece().color() == Piece::Black) {
            if (pos->get_y() == 1 and g.blub[pos->get_y() + 1][pos->get_x()].type() == Piece::None and
                g.blub[pos->get_y() + 2][pos->get_x()].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x(), pos->get_y() + 2));
            }
            if (pos->get_y() != 7) {
                mog.push_back(new Positie(pos->get_x(), pos->get_y() + 1));
            }
            if (pos->get_y() == 0 or g.blub[pos->get_y() + 1][pos->get_x()].type() != Piece::None) {
                mog.clear();
            }
            if (pos->get_y() +1 >= 0 and pos->get_x() - 1 >= 0 and g.blub[pos->get_y() + 1][pos->get_x() - 1].color() != this->piece().color() and g.blub[pos->get_y() + 1][pos->get_x() - 1].type() != Piece::None) {
                mog.push_back(new Positie(pos->get_x() - 1, pos->get_y() + 1));
            }
            if (pos->get_y() +1 >= 0 and pos->get_x() < 7 and g.blub[pos->get_y() + 1][pos->get_x() + 1].color() != this->piece().color() and g.blub[pos->get_y() + 1][pos->get_x() + 1].type() != Piece::None) {
                mog.push_back(new Positie(pos->get_x() + 1, pos->get_y() + 1));
            }
        }
        return mog;
    };

    //TOREN
    if (this->piece().type() == Piece::Rook or this->piece().type() == Piece::Queen) {
        for (auto x = pos->get_x() + 1; 0 <= x and x < 8; x++) {
            if (g.blub[pos->get_y()][x].type() == Piece::None) {
                mog.push_back(new Positie(x, pos->get_y()));
                continue;
            }
            else if (g.blub[pos->get_y()][x].color() == this->piece().color()) {
                break;
            }
            mog.push_back(new Positie(x, pos->get_y()));
            break;
        }

        for (auto x = pos->get_x() - 1; 0 <= x and x < 8; x--) {
            if (g.blub[pos->get_y()][x].type() == Piece::None) {
                mog.push_back(new Positie(x, pos->get_y()));
                continue;
            }
            else if (g.blub[pos->get_y()][x].color() == this->piece().color()) {
                break;
            }
            mog.push_back(new Positie(x, pos->get_y()));
            break;
        }

        for (auto y = pos->get_y() + 1; 0 <= y and y < 8; y++) {
            if (g.blub[y][pos->get_x()].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x(), y));
                continue;
            }
            else if (g.blub[y][pos->get_x()].color() == this->piece().color()) {
                break;
            }
            mog.push_back(new Positie(pos->get_x(), y));
            break;
        }

        for (auto y = pos->get_y() - 1; 0 <= y and y < 8; y--) {
            if (g.blub[y][pos->get_x()].type() == Piece::None) {
                mog.push_back(new Positie(pos->get_x(), y));
                continue;
            }
            else if (g.blub[y][pos->get_x()].color() == this->piece().color()) {
                break;
            }
            mog.push_back(new Positie(pos->get_x(), y));
            break;
        }
    };

    //PAARD
    if (this->piece().type() == Piece::Knight) {
        if (pos->get_x() < 6 and pos->get_y() < 7 and (g.blub[pos->get_y() +1][pos->get_x() +2].type() == Piece::None or g.blub[pos->get_y() +1][pos->get_x() +2].color() != this->piece().color())){
            mog.push_back(new Positie(pos->get_x() + 2, pos->get_y() + 1));
        }

        if (pos->get_x() < 6 and pos->get_y() > 0 and (g.blub[pos->get_y() -1][pos->get_x() +2].type() == Piece::None or g.blub[pos->get_y() -1][pos->get_x() +2].color() != this->piece().color())){
            mog.push_back(new Positie(pos->get_x() + 2, pos->get_y() - 1));
        }

        if (pos->get_x() < 7 and pos->get_y() < 6 and (g.blub[pos->get_y() +2][pos->get_x() +1].type() == Piece::None or g.blub[pos->get_y() +2][pos->get_x() +1].color() != this->piece().color())){
            mog.push_back(new Positie(pos->get_x() + 1, pos->get_y() + 2));
        }

        if (pos->get_x() < 7 and pos->get_y() > 1 and (g.blub[pos->get_y() -2][pos->get_x() +1].type() == Piece::None or g.blub[pos->get_y() -2][pos->get_x() +1].color() != this->piece().color())){
            mog.push_back(new Positie(pos->get_x() + 1, pos->get_y() - 2));
        }

        if (pos->get_x() > 1 and pos->get_y() < 7 and (g.blub[pos->get_y() +1][pos->get_x() -2].type() == Piece::None or g.blub[pos->get_y() +1][pos->get_x() -2].color() != this->piece().color())){
            mog.push_back(new Positie(pos->get_x() - 2, pos->get_y() + 1));
        }

        if (pos->get_x() > 1 and pos->get_y() > 0 and (g.blub[pos->get_y() -1][pos->get_x() -2].type() == Piece::None or g.blub[pos->get_y() -1][pos->get_x() -2].color() != this->piece().color())){
            mog.push_back(new Positie(pos->get_x() - 2, pos->get_y() - 1));
        }

        if (pos->get_x() > 0 and pos->get_y() < 6 and (g.blub[pos->get_y() +2][pos->get_x() -1].type() == Piece::None or g.blub[pos->get_y() +2][pos->get_x() -1].color() != this->piece().color())){
            mog.push_back(new Positie(pos->get_x() - 1, pos->get_y() + 2));
        }

        if (pos->get_x() > 0 and pos->get_y() > 1 and (g.blub[pos->get_y() -2][pos->get_x() -1].type() == Piece::None or g.blub[pos->get_y() -2][pos->get_x() -1].color() != this->piece().color())){
            mog.push_back(new Positie(pos->get_x() - 1, pos->get_y() - 2));
        }
    };

    //LOPER
    if (this->piece().type() == Piece::Bishop or this->piece().type() == Piece::Queen){
        for (int l = 1; pos->get_x() + l < 8 and pos->get_y() + l <8; l++) {
            if (g.blub[pos->get_y() + l][pos->get_x() +l].type() == Piece::None){
                mog.push_back(new Positie(pos->get_x() + l, pos->get_y() + l));
                continue;
            }
            else if (g.blub[pos->get_y() + l][pos->get_x() +l].color() == this->piece().color()){
                break;
            }
            mog.push_back(new Positie(pos->get_x() + l, pos->get_y() + l));
            break;
        }

        for (int l = 1; pos->get_x() - l >= 0 and pos->get_y() + l <8; l++) {
            if (g.blub[pos->get_y() + l][pos->get_x() -l].type() == Piece::None){
                mog.push_back(new Positie(pos->get_x() -l, pos->get_y() + l));
                continue;
            }
            else if (g.blub[pos->get_y() + l][pos->get_x() -l].color() == this->piece().color()){
                break;
            }
            mog.push_back(new Positie(pos->get_x() -l, pos->get_y() + l));
            break;
        }

        for (int l = 1; pos->get_x() - l >= 0 and pos->get_y() - l >= 0; l++) {
            if (g.blub[pos->get_y() - l][pos->get_x() -l].type() == Piece::None){
                mog.push_back(new Positie(pos->get_x() -l, pos->get_y() - l));
                continue;
            }
            else if (g.blub[pos->get_y() - l][pos->get_x() -l].color() == this->piece().color()){
                break;
            }
            mog.push_back(new Positie(pos->get_x() -l, pos->get_y() - l));
            break;
        }

        for (int l = 1; pos->get_x() + l < 8 and pos->get_y() - l >= 0; l++) {
            if (g.blub[pos->get_y() - l][pos->get_x() + l].type() == Piece::None){
                mog.push_back(new Positie(pos->get_x() +l, pos->get_y() - l));
                continue;
            }
            else if (g.blub[pos->get_y() - l][pos->get_x() +l].color() == this->piece().color()){
                break;
            }
            mog.push_back(new Positie(pos->get_x() +l, pos->get_y() - l));
            break;
        }
    };
    return mog;
};
