// A class to manage can msgs (parse and publish to can_tx/rx) using dbc file provided

#include <deeporange13_control/DeepOrangeDbwCan.h>
#include <deeporange13_control/dispatch_can_msgs.h>

namespace deeporange_dbw_ros
{
    DeepOrangeDbwCan::DeepOrangeDbwCan(ros::NodeHandle &node, ros::NodeHandle &priv_nh)
    {
        
        // Initialise variables
        estopMsg_.data = 0;

        // Instantiate sub/pubs
        sub_can_ = node.subscribe("can_rx", 10, &DeepOrangeDbwCan::recvCAN, this, ros::TransportHints().tcpNoDelay(true));
        sub_trackVel_ = node.subscribe("cmd_vel", 10, &DeepOrangeDbwCan::publishTrackVeltoCAN, this, ros::TransportHints().tcpNoDelay(true));

        pub_can_ = node.advertise<can_msgs::Frame>("can_tx", 10);
        pub_estop_ = node.advertise<std_msgs::Bool>("fort_estop", 10);

        // Instantiate the dbs class
        dbwDbc_ = NewEagle::DbcBuilder().NewDbc(dbcFile_);

        // get params
        priv_nh.getParam("dbw_dbc_file", dbcFile_);

        // Set up Timer
        // timer_ = node.createTimer(ros::Duration(1 / 20.0), &DeepOrangeDbwCan::publish_estop, this);

    }

    DeepOrangeDbwCan::~DeepOrangeDbwCan()
    { 
    }

    void DeepOrangeDbwCan::recvCAN(const can_msgs::Frame::ConstPtr& msg)
    {
        if (!msg->is_rtr && !msg->is_error)
        {
            switch (msg->id)
            {
                case ID_VSS_MSG:
                {
                    NewEagle::DbcMessage* message = dbwDbc_.GetMessageById(ID_VSS_MSG);
                    if (msg->dlc >= message->GetDlc())
                    {
                        message->SetFrame(msg);
                        raptorMsg_.header.stamp = msg->header.stamp;
                        raptorMsg_.system_state = message->GetSignal("Sys_State")->GetResult();                       
                    }
                }
                break;

                case ID_MOTOR1_POSITION:
                {
                    NewEagle::DbcMessage* message = dbwDbc_.GetMessageById(ID_VSS_MSG);
                    if (msg->dlc >= message->GetDlc())
                    {
                        odometryMsg_.header.stamp = msg->header.stamp;
                    }
                }
                break;

            }
        }
    }

    void DeepOrangeDbwCan::publishTrackVeltoCAN(const geometry_msgs::TwistStamped& msg)
    {
        pub_can_.publish(estopMsg_);
    }


} // end namespace deeporange_dbw_ros