/* This file was generated by upbc (the upb compiler) from the input
 * file:
 *
 *     envoy/config/trace/v3/skywalking.proto
 *
 * Do not edit -- your changes will be discarded when the file is
 * regenerated. */

#ifndef ENVOY_CONFIG_TRACE_V3_SKYWALKING_PROTO_UPBDEFS_H_
#define ENVOY_CONFIG_TRACE_V3_SKYWALKING_PROTO_UPBDEFS_H_

#include "upb/def.h"
#include "upb/port_def.inc"
#ifdef __cplusplus
extern "C" {
#endif

#include "upb/def.h"

#include "upb/port_def.inc"

extern _upb_DefPool_Init envoy_config_trace_v3_skywalking_proto_upbdefinit;

UPB_INLINE const upb_MessageDef *envoy_config_trace_v3_SkyWalkingConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_trace_v3_skywalking_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.trace.v3.SkyWalkingConfig");
}

UPB_INLINE const upb_MessageDef *envoy_config_trace_v3_ClientConfig_getmsgdef(upb_DefPool *s) {
  _upb_DefPool_LoadDefInit(s, &envoy_config_trace_v3_skywalking_proto_upbdefinit);
  return upb_DefPool_FindMessageByName(s, "envoy.config.trace.v3.ClientConfig");
}

#ifdef __cplusplus
}  /* extern "C" */
#endif

#include "upb/port_undef.inc"

#endif  /* ENVOY_CONFIG_TRACE_V3_SKYWALKING_PROTO_UPBDEFS_H_ */