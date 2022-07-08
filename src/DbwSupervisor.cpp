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
        sub_raptor_ = node.subscribe("raptor_state", 10, &DbwSupervisor::getRaptorMsg, this, ros::TransportHints().tcpNoDelay(true));
        sub_cmdVel_ = node.subscribe("cmd_vel", 10, &DbwSupervisor::getTrackVelocity, this, ros::TransportHints().tcpNoDelay(true));

        pub_trackVel_ = node.advertise<can_msgs::Frame>("can_tx", 10);
        pub_estop_ = node.advertise<std_msgs::Bool>("fort_estop", 10);
        pub_rosState_ = node.advertise<deeporange13_msgs::RosState>("ros_state", 10);

        // Set up Timer - with calback to publish ROS state all the time that the node is running
        timer_ = node.createTimer(ros::Duration(1 / 20.0), &DbwSupervisor::publishROSState, this);

        // Initiate ROS State with a NOT OK state to be safe. This state will be published till the 
        // ROs supervisor intentionally changes it.
        rosSupMsg_.ros_state = ROS_NOT_OK;

    }

    DbwSupervisor::~DbwSupervisor(){}

    void DbwSupervisor::getTrackVelocity(const geometry_msgs::TwistStamped::ConstPtr& msg)
    {
        // trackVelMsg_ = VehicleModel.cmdVel2trackVel(const geometry_msgs::TwistStamped::ConstPtr& msg);
        // pub_trackVel_.publish(trackVelMsg_);
    }

    void DbwSupervisor::getRaptorMsg(const deeporange13_msgs::RaptorState& msg)
    {
        // check if the msg is old.
        if (msg.header.stamp < ros::Time::now())
        {
            ROS_WARN("Time stamp received from Raptor way too old. Not safe. Sending Zero cmd_vels now.");
            is_raptorMsg_old_ = true;
        }

        raptorMsg_.system_state = msg.system_state;

    }

    void DbwSupervisor::updateROSStateMsg()
    {

    }

    void DbwSupervisor::publishROSState(const ros::TimerEvent& event)
    {
        raptorMsg_.header.stamp = ros::Time::now();
        pub_rosState_.publish(rosSupMsg_);
    }

} // end namespace namespace deeporange_dbw_ros
