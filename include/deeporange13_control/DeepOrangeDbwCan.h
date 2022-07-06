// A class to manage can msgs (parse and publish to can_tx/rx) using dbc file provided

#ifndef _DEEPORANGE_DBW_CAN_H_
#define _DEEPORANGE_DBW_CAN_H_

#include <string.h>
#include <ros/ros.h>
// ROS messages
#include <can_msgs/Frame.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/JointState.h>
#include <sensor_msgs/Joy.h>
#include <geometry_msgs/TwistStamped.h>
#include <std_msgs/Empty.h>
#include <std_msgs/Bool.h>
#include <std_msgs/String.h>
#include <deeporange13_msgs/RaptorState.h>
#include <deeporange13_msgs/RosState.h>
#include <nav_msgs/Odometry.h>
// Can dbc parser mackage
#include <can_dbc_parser/DbcMessage.h>
#include <can_dbc_parser/DbcSignal.h>
#include <can_dbc_parser/Dbc.h>
#include <can_dbc_parser/DbcBuilder.h>

namespace deeporange_dbw_ros

{
    class DeepOrangeDbwCan
    {
        public:
        DeepOrangeDbwCan(ros::NodeHandle &node, ros::NodeHandle &priv_nh);
        ~DeepOrangeDbwCan();

        private:
        void recvCAN(const can_msgs::Frame::ConstPtr& msg);
        void tester(const std_msgs::String msg);
        void publishCAN(const ros::TimerEvent& event);
        void publishTrackVeltoCAN(const geometry_msgs::TwistStamped& msg);

        ros::Timer timer_;

        // Publishers
        ros::Publisher pub_can_;
        ros::Publisher pub_estop_;
        // Subscribers
        ros::Subscriber sub_can_;
        ros::Subscriber sub_trackVel_;

        // Published msgs
        deeporange13_msgs::RaptorState raptorMsg_;
        nav_msgs::Odometry odometryMsg_;
        // Subscribed msgs
        deeporange13_msgs::RosState rosSupMsg_;
        

        // Frame ID
        std::string frameId_;

        // E-stop indicator variables
        long int estop_;
        std_msgs::Bool estopMsg_;


        // dbc file variables
        NewEagle::Dbc dbwDbc_;
        std::string dbcFile_;

        // Raptor Comms Variables
        int sysState_;

    };
} // deeporange_dbw_ros

#endif // _DEEPORANGE_DBW_CAN_H_
