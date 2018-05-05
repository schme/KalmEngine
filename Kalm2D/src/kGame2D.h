#ifndef KALM2D_H_
#define KALM2D_H_

#include "kalm_shared.h"
#include "kGame.h"
#include "Scene.h"

class Kalm2D : public kGame {
    public:
        static gameImport_t * system;
        static gameExport_t gameExport;

        static void *GetMemory( u32 bytes );

        b32 Initialize();
        i32 Loop ();
        void Terminate();
    private:
        kScene_t *currentScene = nullptr;

        void SetCurrentScene( kScene_t *scene);

        void RunCurrentScene();
        void RenderCurrentScene();
        /** Dev method, normally we'd load one, not create it.
         *  Some other class will do the creating */
        kScene_t* CreateTestScene();
};


#endif /* end of include guard: KALM2D_H_ */
