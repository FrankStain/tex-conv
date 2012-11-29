#pragma once

#include <windows.h>
#include "plugin_logger.h"
#include "plugin_desc.h"
#include "plugin_operator.h"
#include "plugin_image.h"
#include "plugin_option.h"

namespace plugin {
	typedef desc_t* (*desc_proc_t)();
};
