#ifndef _SFLOW_H_
#define _SFLOW_H_

#include <sys/types.h>
#include <sys/socket.h>

#define IPV4_SIZE 4
#define IPV6_SIZE 16
#define ETH_HEADER_SIZE 14

/**
 * sFlow datagram header (followed either by an ipv4 or ipv6 address)
 */
typedef struct {
	u_int32_t version;
	u_int32_t ip_version;
} sflow_data_header_t;

/**
 * sFlow datagram body (followed by @a sample_count samples)
 */
typedef struct {
	u_int32_t subagent_id;
	u_int32_t sequence_number;
	u_int32_t switch_uptime;
	u_int32_t sample_count;
} sflow_data_body_t;

/**
 * Information about flow data
 */
typedef struct {
	u_int32_t format; // Enterprise (5B) and format (3B) number
	u_int32_t length;
} sflow_sample_data_t;

/**
 * Enterprise 0 format 1
 * Flow sample (followed by @a record_count records)
 */
typedef struct {
	u_int32_t sequence_number;
	u_int32_t source_id;
	u_int32_t sample_rate;
	u_int32_t sample_pool;
	u_int32_t drops;
	u_int32_t input;
	u_int32_t output;
	u_int32_t record_count;
} sflow_flow_sample_t;

/**
 * sFlow flow record header
 */
typedef struct {
	u_int32_t format; // Enterprise (5B) and format (3B) number
	u_int32_t length;
} sflow_flow_record_t;

/**
 * Raw packet header record (followed by sampled packet header)
 */
typedef struct {
	u_int32_t protocol;
	u_int32_t frame_length;
	u_int32_t stripped;
	u_int32_t header_size;
} sflow_raw_header_t;

typedef enum {
	FLOW_SAMPLE = 1,
	SWITCH_DATA = 1001
} sflow_sample_format_t;

typedef enum {
	RAW_HEADER = 1
} sflow_record_format_t;

typedef enum {
	ETHERNET = 1,
	ISO88024 = 2,
	ISO88025 = 3,
	FDDI = 4,
	FRAME = 5,
	X25 = 6,
	PPP = 7,
	SMDS = 8,                
	AAL5 = 9,
	AAL5IP = 10,
	IPV4 = 11,
	IPV6 = 12,
	MPLS = 13,
	POS = 14
} sflow_header_protocol_t;

int
next_sample (void *packet, size_t packet_size, sflow_sample_data_t **sample);

int
next_record (sflow_sample_data_t *sample, sflow_flow_record_t **record);

int
is_sample_format (sflow_sample_data_t *sample, sflow_sample_format_t format);

int 
is_record_format (sflow_flow_record_t *record, sflow_record_format_t format);

int 
get_source (sflow_raw_header_t *header, struct sockaddr_storage *dst);

int
get_destination (sflow_raw_header_t *header, struct sockaddr_storage *dst);

#endif