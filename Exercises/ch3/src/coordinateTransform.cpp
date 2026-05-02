#include <iostream>
#include <cmath>

#include </usr/include/eigen3/Eigen/Core>
#include </usr/include/eigen3/Eigen/Geometry>

// This programs solves the Coordinate Transform Example
/*
The Problem : 

The robot No.1 and the robot No.2 are located in the world coordinate
system. We use the world coordinate system as W, robot coordinate system as R1
and R2. 

The pose of the robot 1 is q1 = [0.35, 0.2, 0.3, 0.1]T ,t1 = [0.3, 0.1, 0.1]T.
The pose of the robot 2 is q2 = [−0.5, 0.4, −0.1, 0.2]T ,t2 = [−0.1, 0.5, 0.3]T

Here q and t express TRk,W , k = 1, 2, which is the world to the robot transform matrix. Now,
assume that robot 1 sees a point in its own coordinate system with coordinates of
pR1 = [0.5, 0, 0.2]T
We want to find the coordinates of the vector in the robot 2’s
coordinate system.

The solution should basically be : P(R2) = T2w * Tw1 * P(R1), where T is homogeneous transformation

*/
int main(){

    Eigen::Quaterniond q1w(0.35, 0.2, 0.3, 0.1), q2w(-0.5, 0.4, -0.1, 0.2);

    q1w.normalize();
    q2w.normalize();

    Eigen::Vector3d t1w(0.3, 0.1, 0.1), t2w(-0.1, 0.5, 0.3); // t1w reads as : the vector from worlds origin to robot 1 origin
                                                             // This does not match book convetion, the author did it differently here..
    Eigen::Vector3d p11(0.5, 0, 0.2); // point 1 with respect to frame 1 (Robot 1)
    Eigen::Isometry3d T1w(q1w), T2w(q2w); // Homogeneous transformation from world to robot

    T1w.pretranslate(t1w);
    T2w.pretranslate(t2w);

    Eigen::Vector3d p21 = T2w * T1w.inverse() * p11;
    std::cout << std::endl << p21.transpose() << std::endl;


    return 0;
}