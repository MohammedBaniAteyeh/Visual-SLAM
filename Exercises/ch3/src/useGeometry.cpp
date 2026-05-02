#include <iostream>
#include <cmath>

#include </usr/include/eigen3/Eigen/Core>
#include </usr/include/eigen3/Eigen/Geometry>

// This program demonstrates how to use the Eigen geometry module

int main(){

    Eigen::Matrix3d rotation_matrix = Eigen::Matrix3d::Identity();  
  
    Eigen::AngleAxisd rotation_vector(M_PI / 4, Eigen::Vector3d(0, 0, 1)); // Rotate 45 degrees along z axis

    std::cout.precision(3);
    std::cout << "rotation matrix = \n " << rotation_vector.matrix() << std::endl; // convert to matrix with matrix()

    // can also be assigned directly
    rotation_matrix = rotation_vector.toRotationMatrix();

    // coordinate transformation with AngleAxis
    Eigen::Vector3d v(1, 0, 0);
    Eigen::Vector3d v_rotated = rotation_vector * v; // this only works due to operator overloading as the rotation vector here is not a matrix
    std::cout << "(1,0,0) after rotation (by angle axis) = " << v_rotated.transpose() << std::endl;

    // Or use the rotation matrix directly
    Eigen::Vector3d v_rotated_matrix = rotation_matrix * v;
    

    // Euler angle
    Eigen::Vector3d euler_angles = rotation_matrix.eulerAngles(2, 1, 0); // ZYX order (321)
    std::cout << "yaw pitch roll = " << euler_angles.transpose() << std::endl;

    // Euclidean transformation matrix using Eigen::Isometry (Homogenous Transformation Matrix)
    Eigen::Isometry3d T = Eigen::Isometry3d::Identity(); 
    T.rotate(rotation_vector); 
    T.pretranslate(Eigen::Vector3d(1, 3, 4)); // Set the translation vector to (1,3,4)
    std::cout << "Transform matrix = \n" << T.matrix() << std::endl;
    // Use the transformation matrix for coordinate transformation
    Eigen::Vector3d v_transformed = T * v; // Equivalent to R∗v+t
    std::cout << "v tranformed = " << v_transformed.transpose() << std::endl;

    // For affine and projective transformations, use Eigen::Affine3d and Eigen::Projective3d.

    // Quaternion
    // You can assign AngleAxis directly to quaternions, and vice versa
    Eigen::Quaterniond q = Eigen::Quaterniond(rotation_vector);
    std::cout << "quaternion from rotation vector = " << q.coeffs().transpose() << std::endl;
    // Order of coeffs is (x, y, z, w)
    // can also assign a rotation matrix to it
    q = Eigen::Quaterniond(rotation_matrix);
    std::cout << "quaternion from rotation matrix = " << q.coeffs().transpose() << std::endl;
    // Rotate a vector with a quaternion and use overloaded multiplication
    v_rotated = q * v; // Note that the math is qvq^{−1}
    std::cout << "(1,0,0) after rotation = " << v_rotated.transpose() << std::endl;
    // expressed by regular vector multiplication, it should be calculated as follows
    std::cout << "should be equal to " << (q * Eigen::Quaterniond(0, 1, 0, 0) * q.inverse()).coeffs().transpose() << std::endl;

    return 0;
}