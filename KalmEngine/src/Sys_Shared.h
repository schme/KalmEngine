#ifndef SYSTEMSLOCAL_H_
#define SYSTEMSLOCAL_H_

#include "KalmShared.h"
#include "Systems.h"
#include "Sys_Memory.h"
#include "Sys_Assets.h"
#include "Sys_Common.h"
#include "Sys_Filesystem.h"
#include "Sys_Render.h"

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
