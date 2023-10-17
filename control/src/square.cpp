//#include <moveit/move_group_interface/move_group.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <std_msgs/Float64.h>
//#include <moveit_visual_tools/moveit_visual_tools.h>

// Main moveit libraries are included
int main(int argc, char **argv)
{
  ros::init(argc, argv, "move_group_interface_tutorial");
  ros::NodeHandle node_handle;
ros::NodeHandle nhp;
ros::NodeHandle nhp2;
  ros::AsyncSpinner spinner(0);
  spinner.start(); // For moveit implementation we need AsyncSpinner, we cant use ros::spinOnce()
  static const std::string PLANNING_GROUP = "arm"; /* Now we specify with what group we want work,
  here group1 is the name of my group controller*/
ros::Publisher pos_publisherx = nhp.advertise<std_msgs::Float64>("cartezian_posx", 1000);
ros::Publisher pos_publishery = nhp2.advertise<std_msgs::Float64>("cartezian_posy", 1000);
  moveit::planning_interface::MoveGroupInterface move_group(PLANNING_GROUP); // loading move_group
  const robot_state::JointModelGroup *joint_model_group =
      move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP); //For joint control
  geometry_msgs::PoseStamped current_pose;
  geometry_msgs::PoseStamped target_pose; // Pose in ROS is implemented using geometry_msgs::PoseStamped, google what is the type of this msg
  current_pose = move_group.getCurrentPose(); /* Retrieving the information about the
  current position and orientation of the end effector*/
  target_pose = current_pose;
  target_pose.pose.position.x = target_pose.pose.position.x - 0.25; /* Basically our target pose is the same as current,
  except that we want to move it a little bit along x-axis*/

std_msgs::Float64 cartx;
std_msgs::Float64 carty;

  ros::Rate loop_rate(50); //Frequency
  while (ros::ok()){
    move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
    move_group.move(); // Move the robot
    current_pose = move_group.getCurrentPose();
    if (abs(current_pose.pose.position.x - target_pose.pose.position.x) < 0.05){
		target_pose.pose.position.y = target_pose.pose.position.y - 0.25;
		move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
		move_group.move(); // Move the robot
		current_pose = move_group.getCurrentPose();
		if (abs(current_pose.pose.position.y - target_pose.pose.position.y) < 0.05){
			target_pose.pose.position.x = target_pose.pose.position.x - 0.25;
			move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
			move_group.move(); // Move the robot
			current_pose = move_group.getCurrentPose();
			if (abs(current_pose.pose.position.x - target_pose.pose.position.x) < 0.05){
				target_pose.pose.position.y = target_pose.pose.position.y + 0.25;
				move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
				move_group.move(); // Move the robot
				current_pose = move_group.getCurrentPose();
				if (abs(current_pose.pose.position.y - target_pose.pose.position.y) < 0.05){
					target_pose.pose.position.y = target_pose.pose.position.y + 0.25;
					move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
					move_group.move(); // Move the robot
					current_pose = move_group.getCurrentPose();
          if (abs(current_pose.pose.position.y - target_pose.pose.position.y) < 0.05){
					target_pose.pose.position.x = target_pose.pose.position.x + 0.25;
					move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
					move_group.move(); // Move the robot
					current_pose = move_group.getCurrentPose();
          if (abs(current_pose.pose.position.x - target_pose.pose.position.x) < 0.05){
					target_pose.pose.position.y = target_pose.pose.position.y - 0.25;
					move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
					move_group.move(); // Move the robot
					current_pose = move_group.getCurrentPose();
          if (abs(current_pose.pose.position.y - target_pose.pose.position.y) < 0.05){
					target_pose.pose.position.x = target_pose.pose.position.x + 0.25;
					move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
					move_group.move(); // Move the robot
					current_pose = move_group.getCurrentPose();
					if (abs(current_pose.pose.position.x - target_pose.pose.position.x) < 0.05){
						break; // Basically, check if we reached the desired position
					}
          }
          }
          }
				}
			}
		}
    }

    loop_rate.sleep();
  }
while(ros::ok()){
current_pose = move_group.getCurrentPose();
cartx.data=current_pose.pose.position.x;
carty.data=current_pose.pose.position.y;
pos_publisherx.publish(cartx);
pos_publishery.publish(carty);
ROS_INFO("%f", cartx.data);
ros::spinOnce();

    loop_rate.sleep();
}

  ROS_INFO("Done");
  ros::shutdown();
  return 0;
}
