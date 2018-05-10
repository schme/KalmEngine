/**
 *
 * Config.h
 *
 * A file to load and set different configurations.
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 10/05/2018
 */

#ifndef CONFIG_H_UIEUBWKJ
#define CONFIG_H_UIEUBWKJ

#include "Types.h"
#include "KalmShared.h"

struct gameInput_t;

class kConfig : public ConfigSystem {
    public:
    preferences_t values;

    void Initialize();

    void Input( gameInput_t *input) {

        if( input->actionF5.endedDown && input->actionF5.toggleCount > 0) {
            this->values.drawWireframe = !this->values.drawWireframe;
            printf("drawWireframe: %u\n", this->values.drawWireframe);
        }
    };

    preferences_t * GetPreferences() {
        return &this->values;
    }

    kConfig *Get() {
        return this;
    };
};


#endif /* end of include guard: CONFIG_H_UIEUBWKJ */
