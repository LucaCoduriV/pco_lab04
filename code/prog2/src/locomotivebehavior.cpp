//    ___  _________    ___  ___  ___   __ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  | / / //
//  / ___/ /__/ /_/ / / __// // / __/ / /  //
// /_/   \___/\____/ /____/\___/____//_/   //
//                                         //


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
    //sharedSection->request(loco);
    //sharedSection->getAccess(loco);
    //sharedSection->leave(loco);

    while(1) {

        attendre_contact(bornesDebut.borneRequest);
        sharedSection->request(loco, locoId, entryPoint);
        loco.afficherMessage(QString("%1").arg(bornesDebut.borneAcces));
        attendre_contact(bornesDebut.borneAcces);
        sharedSection->getAccess(loco, locoId);
        way->changeWay(bornesDebut.borneAcces);

        attendre_contact(bornesFin.borneAcces);
        sharedSection->leave(loco, locoId);


        attendre_contact(borneDepart);
        nbTours++;

        if (nbTours % 2 == 0) {

            BornesInfo temp = bornesDebut;
            bornesDebut = bornesFin;
            bornesFin = temp;

            entryPoint = entryPoint == SharedSectionInterface::EntryPoint::EA ? SharedSectionInterface::EntryPoint::EB : SharedSectionInterface::EntryPoint::EA;
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
