/*
 * thd_engine_dts.h: thermal engine dts class interface
 *
 * Copyright (C) 2012 Intel Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 *
 *
 * Author Name <Srinivas.Pandruvada@linux.intel.com>
 *
 */

#ifndef THD_ENGINE_DTS_H_
#define THD_ENGINE_DTS_H_


#include "thd_engine.h"
#include <time.h>

class cthd_engine_dts: public cthd_engine
{
private:
	csys_fs			thd_sysfs;
	unsigned int	cpu_mask_remaining;

public:
	static const unsigned int def_cpu_mask = 0xffff;
	unsigned int 			sensor_mask;

	cthd_engine_dts() :
		thd_sysfs("/sys/devices/platform/coretemp.0/"),
		cpu_mask_remaining(def_cpu_mask),
		sensor_mask(0),
		power_clamp_index(-1)
		{}
	int read_thermal_zones();
	int read_cooling_devices();
	bool apply_cpu_operation(int cpu);
	void remove_cpu_mask_from_default_processing(unsigned int mask);
	unsigned int get_cpu_mask();
	int find_cdev_power_clamp();

	static const int msr_turbo_states_index = soft_cdev_start_index;
	static const int msr_p_states_index = soft_cdev_start_index+1;
	static const int turbo_on_off_index = soft_cdev_start_index+2;
	static const int cpufreq_index = soft_cdev_start_index+3;
	static const int t_state_index = soft_cdev_start_index+4;
	int power_clamp_index; // dynamic based on thermal cdev
};


#endif /* THD_ENGINE_DTS_H_ */