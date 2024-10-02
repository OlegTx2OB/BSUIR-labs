#include "PowerManager.h"
#include <windows.h>
#include <powrprof.h>


void PowerManager::goIntoSleepMode() {
    SetSuspendState(FALSE, FALSE, FALSE);
}
void PowerManager::goIntoHibernationMode() {
    SetSuspendState(TRUE, FALSE, FALSE);
}
