#ifndef SYSTEMSLOCAL_H_
#define SYSTEMSLOCAL_H_

#include "kalm_shared.h"
#include "kGame.h"

#include "Memory.h"
#include "Assets.h"
#include "CommonSystem.h"
#include "Filesystem.h"
#include "Render.h"

/**
 * Global pointers for use inside the platform side.
 * Rethink this for awhile
 */
static kMemory * g_Memory           = nullptr;
static kCommonSystem * g_Common     = nullptr;
static kAssets * g_Assets           = nullptr;
static kFilesystem * g_Filesystem   = nullptr;
static kRender * g_Render           = nullptr;

#endif /* end of include guard: SYSTEMSLOCAL_H_ */
