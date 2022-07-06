/*
 A class deifinition to allow the supervising of dbw control and communication ...
between multiple functional objects like VehicleModel and DeepOrangeDbwCan
*/

#include <deeporange13_control/DbwSupervisor.h>

namespace deeporange_dbw_ros
{
    DbwSupervisor::DbwSupervisor(ros::NodeHandle &node, ros::NodeHandle &priv_nh)
    {
        // Instantiate sub/pubs
        // sub_raptor_ = node.subscribe("raptor_state", 10, &DbwSupervisor::?, this, ros::TransportHints().tcpNoDelay(true));
        // sub_cmdVel_ = node.subscribe("cmd_vel", 10, &DbwSupervisor::?, this, ros::TransportHints().tcpNoDelay(true));

        pub_trackVel_ = node.advertise<can_msgs::Frame>("can_tx", 10);
        pub_estop_ = node.advertise<std_msgs::Bool>("fort_estop", 10);
        pub_rosState_ = node.advertise<deeporange13_msgs::RosState>("ros_state", 10);

        // Set up Timer
        // timer_ = node.createTimer(ros::Duration(1 / 20.0), &DbwSupervisor::publish_estop, this);        

    }

} // end namespace namespace deeporange_dbw_ros
