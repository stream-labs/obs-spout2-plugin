/**
 * Copyright Off World Live Ltd (https://offworld.live), 2019-2021
 *
 * and licenced under the GPL v2 (https://www.gnu.org/licenses/old-licenses/gpl-2.0.en.html)
 *
 * Many thanks to authors of https://github.com/baffler/OBS-OpenVR-Input-Plugin which
 * was used as guidance to working with the OBS Studio APIs
 */

#include <obs-module.h>
#include <sys/stat.h>

#include "win-spout.h"

OBS_DECLARE_MODULE()
OBS_MODULE_AUTHOR("Off World Live")
OBS_MODULE_USE_DEFAULT_LOCALE("win-spout", "en-US")

extern struct obs_source_info create_spout_source_info();
struct obs_source_info spout_source_info;

bool obs_module_load(void)
{
	// load spout - source
	spout_source_info = create_spout_source_info();
	obs_register_source(&spout_source_info);

	blog(LOG_INFO, "win-spout loaded!");

	return true;
}

void obs_module_unload()
{
	blog(LOG_INFO, "win-spout unloaded!");
}

const char *obs_module_name()
{
	return "win-spout";
}

const char *obs_module_description()
{
	return "Spout input/output for OBS Studio";
}
