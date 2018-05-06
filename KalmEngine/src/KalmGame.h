#ifndef KGAME_H_
#define KGAME_H_

#include "CommonIncludes.h"
#include "KalmShared.h"
#include "KalmTypes.h"
#include "Scene.h"

class KalmGame : public kGame {
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


#endif /* end of include guard: KGAME_H_ */
