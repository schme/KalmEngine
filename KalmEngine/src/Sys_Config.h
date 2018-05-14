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

#include "KalmShared.h"

struct gameInput_t;

class kConfig : public ConfigSystem {
    public:
    preferences_t values;

    void Initialize();
    void Input();
    preferences_t * GetPreferences();

    kConfig *Get();
};


#endif /* end of include guard: CONFIG_H_UIEUBWKJ */
