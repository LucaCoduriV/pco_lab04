//    ___  _________    ___  ___  ___   __ //
//   / _ \/ ___/ __ \  |_  |/ _ \|_  | / / //
//  / ___/ /__/ /_/ / / __// // / __/ / /  //
// /_/   \___/\____/ /____/\___/____//_/   //
//

#ifndef LOCOMOTIVEBEHAVIOR_H
#define LOCOMOTIVEBEHAVIOR_H

#include "locomotive.h"
#include "launchable.h"
#include "sharedsectioninterface.h"
#include "waycontroller.h"
#include "pcosynchro/pcosemaphore.h"

/**
 * @brief La classe LocomotiveBehavior représente le comportement d'une locomotive
 */
class LocomotiveBehavior : public Launchable
{
public:

    struct BornesInfo {
        int borneRequest;
        int borneAcces;
    };

    /*!
     * \brief locomotiveBehavior Constructeur de la classe
     * \param loco la locomotive dont on représente le comportement
     */
    LocomotiveBehavior(Locomotive& loco, std::shared_ptr<SharedSectionInterface> sharedSection, BornesInfo  bornesDebut,  BornesInfo bornesFin, WayController* way, int borneDepart, SharedSectionInterface::LocoId locoId) :
        loco(loco), sharedSection(sharedSection), bornesDebut(bornesDebut), bornesFin(bornesFin), way(way), borneDepart(borneDepart), mutexBorne(1), locoId(locoId) {
        // Eventuel code supplémentaire du constructeur
    }



protected:
    /*!
     * \brief run Fonction lancée par le thread, représente le comportement de la locomotive
     */
    void run() override;

    /*!
     * \brief printStartMessage Message affiché lors du démarrage du thread
     */
    void printStartMessage() override;

    /*!
     * \brief printCompletionMessage Message affiché lorsque le thread a terminé
     */
    void printCompletionMessage() override;

    /**
     * @brief loco La locomotive dont on représente le comportement
     */
    Locomotive& loco;

    /**
     * @brief sharedSection Pointeur sur la section partagée
     */
    std::shared_ptr<SharedSectionInterface> sharedSection;

    void countContact(int borne);

    /*
     * Vous êtes libres d'ajouter des méthodes ou attributs
     *
     * Par exemple la priorité ou le parcours
     */

    SharedSectionInterface::LocoId locoId;
    BornesInfo bornesDebut;
    BornesInfo bornesFin;
    int borneDepart;
    int nbTours = 0;
    PcoSemaphore mutexBorne;
    WayController* way;
};

#endif // LOCOMOTIVEBEHAVIOR_H
