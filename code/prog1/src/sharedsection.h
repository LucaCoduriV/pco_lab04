//    ___  _________    ___  ___  ___   __ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  | / / //
//  / ___/ /__/ /_/ / / __// // / __/ / /  //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#ifndef SHAREDSECTION_H
#define SHAREDSECTION_H

#include <QDebug>

#include <pcosynchro/pcosemaphore.h>

#include "locomotive.h"
#include "ctrain_handler.h"
#include "sharedsectioninterface.h"

/**
 * @brief La classe SharedSection implémente l'interface SharedSectionInterface qui
 * propose les méthodes liées à la section partagée.
 */
class SharedSection final : public SharedSectionInterface
{
public:

    /**
     * @brief SharedSection Constructeur de la classe qui représente la section partagée.
     * Initialisez vos éventuels attributs ici, sémaphores etc.
     */
    SharedSection() : accesSection(1), mutexSectionOccupee(1) {
        // TODO
    }

    /**
     * @brief access Méthode à appeler pour accéder à la section partagée, doit arrêter la
     * locomotive et mettre son thread en attente si la section est occupée par une autre locomotive.
     * Si la locomotive et son thread ont été mis en attente,
     * le thread doit être reveillé lorsque la section partagée est à nouveau libre et
     * la locomotive redémarée. (méthode à appeler un contact avant la section partagée).
     * @param loco La locomotive qui essaie accéder à la section partagée
     */
    void access(Locomotive &loco) override {
        // TODO
        mutexSectionOccupee.acquire();
        if (sectionOccupee) {
            loco.arreter();
            loco.afficherMessage("arreté zone critique\n");

        }
        mutexSectionOccupee.release();
        accesSection.acquire();
        loco.afficherMessage("En zone critique\n");

        mutexSectionOccupee.acquire();
        sectionOccupee = true;
        mutexSectionOccupee.release();
        loco.demarrer();


//        loco.arreter();
//        accesSection.acquire();
//        loco.demarrer();
        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 accesses the shared section.").arg(loco.numero())));
    }

    /**
     * @brief leave Méthode à appeler pour indiquer que la locomotive est sortie de la section
     * partagée. (reveille les threads des locomotives potentiellement en attente).
     * @param loco La locomotive qui quitte la section partagée
     */
    void leave(Locomotive& loco) override {
        // TODO
       mutexSectionOccupee.acquire();
       sectionOccupee = false;
       mutexSectionOccupee.release();

       accesSection.release();
       loco.afficherMessage("Hors zone critique\n");

        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 leaves the shared section.").arg(loco.numero())));
    }

    /* A vous d'ajouter ce qu'il vous faut */

private:
    // Méthodes privées ...
    PcoSemaphore accesSection;
    bool sectionOccupee = false;
    PcoSemaphore mutexSectionOccupee;
    // Attribut privés ...
};


#endif // SHAREDSECTION_H
