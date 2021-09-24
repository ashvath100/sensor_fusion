#include <tf/tf.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Pose2D.h>
#include "iostream"
#include "sensor_msgs/Imu.h"

ros::Publisher pub_pose_1;
ros::Publisher pub_pose_2;

void imuCallback_(const sensor_msgs::Imu::ConstPtr& msg)
{
    geometry_msgs::Pose2D pose2d;
    tf::Quaternion q(
    msg->orientation.x,
    msg->orientation.y,
    msg->orientation.z,
    msg->orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    pose2d.theta = yaw;
    pub_pose_2.publish(pose2d);
}



void odometryCallback_(const nav_msgs::Odometry::ConstPtr msg) {
    geometry_msgs::Pose2D pose2d;
    pose2d.x = msg->pose.pose.position.x;
    pose2d.y = msg->pose.pose.position.y;
    
    tf::Quaternion q(
        msg->pose.pose.orientation.x,
        msg->pose.pose.orientation.y,
        msg->pose.pose.orientation.z,
        msg->pose.pose.orientation.w);
    tf::Matrix3x3 m(q);
    double roll, pitch, yaw;
    m.getRPY(roll, pitch, yaw);
    
    pose2d.theta = yaw;
    pub_pose_1.publish(pose2d);
    std::cout<<yaw * (180/3.14)<<std::endl;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "conversion_node");
    
    ros::NodeHandle nh_;
    
    ros::Subscriber sub_odom_ = nh_.subscribe("odom", 1000, odometryCallback_);
    ros::Subscriber sub_imu_ = nh_.subscribe("imu/filtered", 1000, imuCallback_);

    pub_pose_1 = nh_.advertise<geometry_msgs::Pose2D>("odom_yaw", 1000);
    pub_pose_2 = nh_.advertise<geometry_msgs::Pose2D>("imu_yaw", 1000); 
    ros::spin();
    
    return 0;
}