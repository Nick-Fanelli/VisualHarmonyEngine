//
// Created by Nick Fanelli on 3/7/21.
//

#pragma once

#include "harmonypch.h"

// For release: COMMENT-OUT THIS LINE
#define HARMONY_DEBUG_ENABLED

#ifdef HARMONY_DEBUG_ENABLED

    #define HARMONY_ASSERT(msg) { Log::Error(msg); exit(-1); }

#else

    #define HARMONY_ASSERT(msg) { Log::Error(msg); }

#endif
