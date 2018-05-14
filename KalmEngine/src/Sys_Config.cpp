/**
 *
 * kConfig
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 10/05/2018
 */

#include "Sys_Config.h"
#include "Sys_Shared.h"

void kConfig::Initialize() {
}

void kConfig::Input() {

    gameInput_t * newInput = g_Common->GetNewState();
    mouseInput_t * newMouse = &newInput->mouseInput;
    gameInput_t * oldInput = g_Common->GetOldState();
    mouseInput_t * oldMouse = &oldInput->mouseInput;

    if( newInput->actionF5.endedDown && newInput->actionF5.toggleCount > 0) {
        this->values.drawWireframe = !this->values.drawWireframe;
        printf("drawWireframe: %u\n", this->values.drawWireframe);
    }

    if( newMouse->scrollOffsetY != oldMouse->scrollOffsetY ) {
        f32 newFoV = this->values.field_of_view - newMouse->scrollOffsetY - oldMouse->scrollOffsetY;

        /** constrictions here */
        this->values.field_of_view = newFoV;

        printf("field of view: %f\n", this->values.field_of_view);
        g_Render->UpdateFieldOfView( this->values.field_of_view);
    }

}
preferences_t * kConfig::GetPreferences() {
    return &this->values;
}

kConfig * kConfig::Get() {
    return this;
};
