//    ___  _________    ___  ___  ___   __ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  | / / //
//  / ___/ /__/ /_/ / / __// // / __/ / /  //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#include "locomotivebehavior.h"
#include "ctrain_handler.h"

void LocomotiveBehavior::run()
{
    //Initialisation de la locomotive
    loco.allumerPhares();
    loco.demarrer();
    loco.afficherMessage("Ready!");

    /* A vous de jouer ! */

    // Vous pouvez appeler les méthodes de la section partagée comme ceci :

    while(1) {
        int borne;

        borne = borneEntreeZC;

        attendre_contact(borne);

        loco.afficherMessage("had contact\n");
        sharedSection->access(loco);
        way->changeWay(borneEntreeZC);

        borne = borneSortieZC;

        attendre_contact(borne);

        sharedSection->leave(loco);

        attendre_contact(borneDepart);
        nbTours++;

        if (nbTours % 2 == 0) {

            int temp = borneEntreeZC;
            borneEntreeZC = borneSortieZC;
            borneSortieZC = temp;
            loco.inverserSens();
        }

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
