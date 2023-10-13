#include "Event.h"

void Meeting::printEventInfo()
{
    printf("|Event id: %d\n|Event type: %s\n|Duration in hours: %d\n|Is completed: %d\n|",
           this->getId(), this->getEventName().c_str(), this->getDurationInHours(), this->getIsCompleted());
    this->printTime();
}

void Reminder::printEventInfo()
{
    printf("|Event id: %d\n|Event type: %s\n|",
           this->getId(), this->getEventName().c_str());
    this->printTime();
}
