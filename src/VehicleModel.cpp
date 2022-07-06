/* A class that has definition of the vehicle model (tracked) and 
functions to split velocity to left and right track velocities
*/

#include <deeporange13_control/VehicleModel.h>

namespace  deeporange_dbw_ros
{
    VehicleModel::VehicleModel(ros::NodeHandle &node, ros::NodeHandle &priv_nh)
    {
        sub_cmdVel_ = node.subscribe("cmd_vel", 10, &VehicleModel::recvTwist, this);
    }

    VehicleModel::~VehicleModel(){}

    void VehicleModel::recvTwist(const geometry_msgs::TwistStamped::ConstPtr& msg)
    {
        bool what = true;
    }
}