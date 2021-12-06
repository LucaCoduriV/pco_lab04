#ifndef WAYCONTROLLER_H
#define WAYCONTROLLER_H

#include "ctrain_handler.h"
#include "vector"

class EventDetail{
private:
    int noPlaquePression;
    int noAiguillage;
    int direction;
public:
    EventDetail(int noPlaquePression, int noAiguillage, int direction):noPlaquePression(noPlaquePression), noAiguillage(noAiguillage), direction(direction){};

    int getNoPlaquePression(){
        return noPlaquePression;
    }
    int getNoAiguillage(){
        return noAiguillage;
    }
    int getDirection(){
        return direction;
    }
};

class WayController
{
private:
    std::vector<EventDetail>* events;

public:
    WayController(std::vector<EventDetail>* events):events(events){};

    void changeWay(int noPlaquePression){
        for(size_t i = 0; i < events->size(); i++){
            if(events->at(i).getNoPlaquePression() == noPlaquePression){
                EventDetail* event = &events->at(i);
                diriger_aiguillage(event->getNoAiguillage(), event->getDirection(), 0);
            }
        }
    }

};

#endif // WAYCONTROLLER_H
