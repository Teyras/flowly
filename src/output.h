#ifndef _OUTPUT_H_
#define _OUTPUT_H_

#include <sys/types.h>
#include <time.h>

#include "common.h"
#include "config.h"
#include "flowstat.h"

/**
 * The header of flowly's output
 */
typedef struct {
	u_int32_t version;
	u_int32_t time;
	u_int32_t nanotime;
	u_int32_t network_count;
	u_int32_t stat_count;
} output_header_t;

/**
 * The header of a statistic
 */
typedef struct {
	char name[STAT_NAME_LENGTH];
} output_stat_header_t;

/**
 * The header of a statistic for a particular network
 */
typedef struct {
	char network[NET_NAME_LENGTH];
	u_int32_t time_in;
	u_int32_t nanotime_in;
	u_int32_t time_out;
	u_int32_t nanotime_out;
} output_network_header_t;

/**
 * The value of a statistic for a single network
 */
typedef struct {
	stat_number_t value_in;
	stat_number_t value_out;
} output_item_t;

/**
 * Send output to flowly's clients
 * @param config The configuration
 * @param stats The statistic data to be sent
 * @param threshold Determines data that is too old to be sent
 */
void
output (flowly_config_t *config, stat_container_t *stats, struct timespec *threshold);

#endif
