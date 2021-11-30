//    ___  _________    ___  ___  ___   __ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  | / / //
//  / ___/ /__/ /_/ / / __// // / __/ / /  //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#include "locomotivebehavior.h"
#include "ctrain_handler.h"

void LocomotiveBehavior::countContact(int borne) {
    while(1){
        attendre_contact(borne);
        nbTours++;

        if (nbTours % 2 == 0) {
            mutexBorne.acquire();
            int temp = borneEntreeZC;
            borneEntreeZC = borneSortieZC;
            borneSortieZC = temp;
            mutexBorne.release();
            loco.inverserSens();

        }
    }
}

void LocomotiveBehavior::run()
{
    //Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Ready!");

    /* A vous de jouer ! */

    // Vous pouvez appeler les méthodes de la section partagée comme ceci :

    PcoThread counterThread(&LocomotiveBehavior::countContact,this, borneDepart);

    while(1) {
        int borne;

        mutexBorne.acquire();
        borne = borneEntreeZC;
        mutexBorne.release();

        attendre_contact(borne);

        loco.afficherMessage("had contact\n");
        sharedSection->access(loco);
        way->changeWay(borneEntreeZC);

        mutexBorne.acquire();
        borne = borneSortieZC;
        mutexBorne.release();

        attendre_contact(borne);

        sharedSection->leave(loco);
    }
}

void LocomotiveBehavior::printStartMessage()
{
    qDebug() << "[START] Thread de la loco" << loco.numero() << "lancé";
    loco.afficherMessage("Je suis lancée !");
}

void LocomotiveBehavior::printCompletionMessage()
{
    qDebug() << "[STOP] Thread de la loco" << loco.numero() << "a terminé correctement";
    loco.afficherMessage("J'ai terminé");
}
