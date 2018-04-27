/**
 *
 * kGame Interface
 *
 * Copyright (C) 2018 Kasper Sauramo
 * Created: 27/04/2018
 */

#include "kalm_shared.h"

class kGame {
    public:
    virtual b32 Initialize( gameImport_t* import) = 0;
    virtual i32 Loop () = 0;
    virtual void Terminate() = 0;
};

struct engineAPI_t {
    kGame *engine;
};

