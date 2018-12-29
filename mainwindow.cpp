#include "mainwindow.h"
#include "SchaakStuk.h"
#include "game.h"
#include <QMessageBox>
#include <QtWidgets>
#include <array>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    scene = new ChessBoard;
    QGraphicsView *view = new QGraphicsView(scene);
    setCentralWidget(view);

    connect(scene,SIGNAL(clicked(int,int)),this,SLOT(clicked(int,int)));

    createActions();
    createMenus();
    update();
}


// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom

void MainWindow::clicked(int r, int k) {
    //SchaakStuk* s;
    Positie* p =new Positie(k, r);

        if( g.s->piece().type() != Piece::None ){
            if (g.move(g.s, p)){
                scene->setItem(r, k, g.s->piece());
                g.s->piece().setType(Piece::None);
                scene->setItem(g.s->getPos()->get_y(), g.s->getPos()->get_x(), g.s->piece() );
                g.blub[g.s->getPos()->get_y()][g.s->getPos()->get_x()].setType(Piece::None);
                //delete g.s;
                if (g.kleur_aan_zet == Piece::White){
                    g.kleur_aan_zet = Piece::Black;
                } else{
                    g.kleur_aan_zet = Piece::White;
                }
            };
            g.s=new None(wit, new Positie(4,4));
            scene->removeAllFocus();
            update();
            return;
        }
    g.s = g.getSchaakstuk(p);
        if(g.s->piece().color() == g.kleur_aan_zet) {
            if (g.s->piece().type() != Piece::None) {
                //scene->setTileFocus(r, k, !scene->hasTileFocus(r, k));
                scene->setPieceFocus(r, k, !scene->hasPieceFocus(r, k));
                auto f = g.s->geldige_zetten(g);
                for( int i = 0; i < f.size(); i++ ){
                    scene->setTileFocus(f[i]->get_y(), f[i]->get_x(), !scene->hasTileFocus(f[i]->get_y(), f[i]->get_x()));
                }

            }
            scene->setItem(r,k,g.s->piece());
        }else{
            g.s=new None(wit, new Positie(4,4));
        }
}


void MainWindow::newGame()
{}

void MainWindow::save() {
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save game"), "",
                                                    tr("Chess File (*.chs);;All Files (*)"));

    if (fileName.isEmpty())
        return;
    else {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }
        QDataStream out(&file);
        out << QString("Rb") << QString("Hb") << QString("Bb") << QString("Qb") << QString("Kb") << QString("Bb") << QString("Hb") << QString("Rb");
        for  (int i=0;i<8;i++) {
            out << QString("Pb");
        }
        for  (int r=3;r<7;r++) {
            for (int k=0;k<8;k++) {
                out << QString(".");
            }
        }
        for  (int i=0;i<8;i++) {
            out << QString("Pw");
        }
        out << QString("Rw") << QString("Hw") << QString("Bw") << QString("Qw") << QString("Kw") << QString("Bw") << QString("Hw") << QString("Rw");
    }
}

void MainWindow::open() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Load game"), "",
                                                    tr("Chess File (*.chs);;All Files (*)"));
    if (fileName.isEmpty())
        return;
    else {

        QFile file(fileName);

        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::information(this, tr("Unable to open file"),
                                     file.errorString());
            return;
        }

        try {
            QDataStream in(&file);
            QString debugstring;
            for (int r=0;r<8;r++) {
                for (int k=0;k<8;k++) {
                    QString piece;
                    in >> piece;
                    debugstring += "\t" + piece;
                    if (in.status()!=QDataStream::Ok) {
                        throw QString("Error reading file "+fileName);
                    }
                }
                debugstring += "\n";
            }
            QMessageBox::information(this, tr("Debug"),
                                     debugstring);
        } catch (QString& Q) {
            QMessageBox::information(this, tr("Error reading file"),
                                     Q);
        }
    }
    //g = Game();
    update();
}


void MainWindow::undo() {
    if (g.zetten.empty()){
        QMessageBox box;
        box.setText(QString("Je hebt alle zetten al ongedaan gemaakt"));
        box.exec();
        return;}
    Zet z = g.zetten.back();
    g.undo(z);
    g.undone.push_back(z);
    g.zetten.pop_back();
    if (g.kleur_aan_zet == Piece::White){
        g.kleur_aan_zet = Piece::Black;
    } else{
        g.kleur_aan_zet = Piece::White;
    }
    update();

}
void MainWindow::redo() {
    if (g.undone.empty()){
        QMessageBox box;
        box.setText(QString("Je hebt alle zetten al teruggezet"));
        box.exec();
        return;}
    Zet z = g.undone.back();
    g.redo(z);
    g.undone.pop_back();
    update();

}

// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.


void MainWindow::update(){

    for (int y = 0; y<8; y++){
        for (int x = 0; x<8;x++){

            scene->setItem(y, x, g.blub[y][x]);
        }
    }

}



////////////////






void MainWindow::createActions() {
    newAct = new QAction(tr("&New"), this);
    newAct->setShortcuts(QKeySequence::New);
    newAct->setStatusTip(tr("Start a new game"));
    connect(newAct, &QAction::triggered, this, &MainWindow::newGame);

    openAct = new QAction(tr("&Open"), this);
    openAct->setShortcuts(QKeySequence::Open);
    openAct->setStatusTip(tr("Read game from disk"));
    connect(openAct, &QAction::triggered, this, &MainWindow::open);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcuts(QKeySequence::Save);
    saveAct->setStatusTip(tr("Save game to disk"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::save);

    exitAct = new QAction(tr("&Exit"), this);
    exitAct->setShortcuts(QKeySequence::Quit);
    exitAct->setStatusTip(tr("Abandon game"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::on_actionExit_triggered);

    undoAct = new QAction(tr("&Undo"), this);
    undoAct->setShortcuts(QKeySequence::Undo);
    undoAct->setStatusTip(tr("Undo last move"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(tr("&redo"), this);
    redoAct->setShortcuts(QKeySequence::Redo);
    redoAct->setStatusTip(tr("Redo last undone move"));
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);
}

void MainWindow::createMenus() {
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(newAct);
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(exitAct);

    gameMenu = menuBar()->addMenu(tr("&Game"));
    gameMenu->addAction(undoAct);
    gameMenu->addAction(redoAct);
}

void MainWindow::on_actionExit_triggered() {
    if (QMessageBox::Yes == QMessageBox::question(this,
                                                  tr("Spel verlaten"),
                                                  tr("Bent u zeker dat u het spel wil verlaten?\nNiet opgeslagen wijzigingen gaan verloren.")))
    {
        QApplication::quit();
    }
}

