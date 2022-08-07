# Deep Orange DBW Controls Interface Package

### Functionality:

- Enable passing the `robot_ns/cmd_vel` topic to the Raptor DBW controller, which executes the commands for the platform to move.
- Use the vehicle dynamics model to convert vehicle velocity to left and right track velocity/torques.
- Run a ROS state machine in sync with the Raptor controller state machine.
- Monitor health of sensors hardware and ROS connections to the on-board computer
- Allow remote access? - TBD if this is inside the package.
