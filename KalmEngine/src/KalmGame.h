#ifndef KGAME_H_
#define KGAME_H_

#include "CommonIncludes.h"
#include "KalmShared.h"
#include "KalmTypes.h"


class KalmGame : public kGame {
    public:
        static gameExport_t     gameExport;

        b32         Initialize();
        i32         Loop ();
        void        Terminate();
    private:
        void        HandleInput( const f32 deltaTime );

        kScene_t *  currentScene = nullptr;
        void        SetCurrentScene( kScene_t *scene);

        void        LoadScene( kScene_t* scene );

        void        RunCurrentScene( const f32 deltaTime);
        void        RenderCurrentScene( const f32 deltaTime);

        /** Dev method, normally we'd load one, not create it.
         *  Some other class will do the creating */
        kScene_t*   CreateTestScene();
        void        LoadTestScene( kScene_t* scene );
};


#endif /* end of include guard: KGAME_H_ */
