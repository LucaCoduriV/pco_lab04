//    ___  _________    ___  ___  ___   __ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  | / / //
//  / ___/ /__/ /_/ / / __// // / __/ / /  //
// /_/   \___/\____/ /____/\___/____//_/   //
//                                         //


#ifndef SHAREDSECTION_H
#define SHAREDSECTION_H

#include <QDebug>

#include <pcosynchro/pcosemaphore.h>

#include "locomotive.h"
#include "ctrain_handler.h"
#include "sharedsectioninterface.h"

struct request{
    SharedSectionInterface::EntryPoint entryPoint;
    SharedSectionInterface::LocoId locoId;
};

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
    SharedSection():entryMutex(1), accessing(1), isWaiting(0) {
        // TODO
    }

    /**
     * @brief request Méthode a appeler pour indiquer que la locomotive désire accéder à la
     * section partagée (deux contacts avant la section partagée).
     * @param loco La locomotive qui désire accéder
     * @param locoId L'identidiant de la locomotive qui fait l'appel
     * @param entryPoint Le point d'entree de la locomotive qui fait l'appel
     */
    void request(Locomotive& loco, LocoId locoId, EntryPoint entryPoint) override {
        // TODO
        entryMutex.acquire();
        if(entryPoint == EntryPoint::EA){
            isEA = true;
            entryALocoId = (int)locoId;
        }else{
            isEB = true;
            entryBLocoId = (int)locoId;
        }
        entryMutex.release();
        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 requested the shared section.").arg(loco.numero())));
    }

    /**
     * @brief getAccess Méthode à appeler pour accéder à la section partagée, doit arrêter la
     * locomotive et mettre son thread en attente si la section est occupée ou va être occupée
     * par une locomotive de plus haute priorité. Si la locomotive et son thread ont été mis en
     * attente, le thread doit être reveillé lorsque la section partagée est à nouveau libre et
     * la locomotive redémarée. (méthode à appeler un contact avant la section partagée).
     * @param loco La locomotive qui essaie accéder à la section partagée
     * @param locoId L'identidiant de la locomotive qui fait l'appel
     */
    void getAccess(Locomotive &loco, LocoId locoId) override {
        // TODO

        entryMutex.acquire();

        if(!priorityCheck(locoId)){
            loco.arreter();
            locoWaiting = true;
            entryMutex.release();
            isWaiting.acquire();
        }else{
            entryMutex.release();
        }


        accessing.acquire();

        entryMutex.acquire();
        if (locoWaiting) {
            locoWaiting = false;
            entryMutex.release();
            isWaiting.release();
        }


        loco.demarrer();
        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 accesses the shared section.").arg(loco.numero())));
    }

    /**
     * @brief leave Méthode à appeler pour indiquer que la locomotive est sortie de la section
     * partagée. (reveille les threads des locomotives potentiellement en attente).
     * @param loco La locomotive qui quitte la section partagée
     * @param locoId L'identidiant de la locomotive qui fait l'appel
     */
    void leave(Locomotive& loco, LocoId locoId) override {
        // TODO
        entryMutex.acquire();
        if((int)locoId == entryALocoId){
            isEA = false;
            entryALocoId = -1;
        }else{
            isEB = false;
            entryBLocoId = -1;
        }
        entryMutex.release();
        accessing.release();
        // Exemple de message dans la console globale
        afficher_message(qPrintable(QString("The engine no. %1 leaves the shared section.").arg(loco.numero())));
    }

    /* A vous d'ajouter ce qu'il vous faut */

private:
    // Méthodes privées ...
    bool priorityCheck(LocoId locoId){
        if(isEA && isEB){
            return locoId == LocoId::LB;
        } else if (!isEA && !isEB) {
            return true;
        } else{
            return locoId == LocoId::LA;
        }
    }
    // Attributes privés ...
    bool isEA = false;
    bool isEB = false;
    int entryALocoId = -1;
    int entryBLocoId = -1;
    bool locoWaiting = false;
    PcoSemaphore entryMutex;
    PcoSemaphore isWaiting;
    PcoSemaphore accessing;
};


#endif // SHAREDSECTION_H
