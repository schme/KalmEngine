#ifndef SYS_SHARED_H_
#define SYS_SHARED_H_

#include "Sys_Memory.h"
#include "Sys_Assets.h"
#include "Sys_Common.h"
#include "Sys_Filesystem.h"
#include "Sys_Render.h"
#include "Sys_Config.h"

/**
 * Global pointers for use inside the platform side.
 * Rethink this for awhile
 */
static kMemory * g_Memory           = nullptr;
static kCommonSystem * g_Common     = nullptr;
static kAssets * g_Assets           = nullptr;
static kFilesystem * g_Filesystem   = nullptr;
static kRender * g_Render           = nullptr;
static kConfig * g_Config           = nullptr;

#endif /* end of include guard: SYS_SHARED_H_ */
