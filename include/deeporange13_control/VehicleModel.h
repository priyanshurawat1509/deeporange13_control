/* A class that has definition of the vehicle model (tracked) and 
functions to split velocity to left and right track velocities
*/

#ifndef _VEHICLE_MODEL_H_
#define _VEHICLE_MODEL_H_

#include <string.h>
#include <ros/ros.h>
#include <can_msgs/Frame.h>
#include <geometry_msgs/TwistStamped.h>

namespace deeporange_dbw_ros
{
    class VehicleModel
    {
        public:
        VehicleModel(ros::NodeHandle &node, ros::NodeHandle &priv_nh);
        ~VehicleModel();

        private:
        void recvTwist(const geometry_msgs::TwistStamped::ConstPtr& msg);

        ros::Timer timer_;

        ros::Subscriber sub_cmdVel_;
        ros::Publisher pub_trackVel_;
    };
}

#endif // _VEHICLE_MODEL_H_