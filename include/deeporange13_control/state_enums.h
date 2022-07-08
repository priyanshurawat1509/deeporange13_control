/*********************************************************************
 Refer to FORT SRC Manual for description
 Refer to Deep Orange used CAN messages for description
 *********************************************************************/

#ifndef _DO_STATE_ENUM_H
#define _DO_STATE_ENUM_H
#include <stdint.h>

namespace deeporange_dbw_ros
{

#undef BUILD_ASSERT

enum {
  // ROS States
  ROS_NOT_OK                = 0,
  ROS_OK                    = 1,

  // Raptor States
  RAPTOR_NOT_OK                       = 0,

};

} //deeporange_dbw_ros

#endif // _DO_STATE_ENUM_H
