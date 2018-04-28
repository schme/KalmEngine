#ifndef KALM2D_H_
#define KALM2D_H_

#include "kalm_shared.h"
#include "kGame.h"

class Kalm2D : public kGame {
    public:
        static gameImport_t * system;
        static gameExport_t gameExport;

        b32 Initialize();
        i32 Loop ();
        void Terminate();
    private:
};

#endif /* end of include guard: KALM2D_H_ */
