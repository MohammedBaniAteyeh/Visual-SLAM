#include <iostream>
#include </usr/include/eigen3/Eigen/Dense>
#include <ctime>

#define MATRIX_SIZE 50

int main(){
    // Examples of how to declare matrices with Eigen

    Eigen::Matrix<double,3,3> matrix_33;
    Eigen::Matrix3d matrix_3d; // 3x3 matrix
    Eigen::Vector3d v_3d; // Vector3d is like a typedef for Matrix<double, 3, 1>
    Eigen::MatrixXd matrix_dynamic; // Dynamic size

    // Matrices Initialization

    matrix_3d << 1.0, 0, 0,
                 0, 2.0, 0,    
                 0, 0, 3.0;

    v_3d << 1.0, 2.0, 3.0;

    std::cout << "The 3x3 Matrix :\n"<<matrix_3d << std::endl; // This works due to operator over loading
    std::cout << "The 3x1 Vector :\n"<<v_3d << std::endl;

    // Some matrix operations

    Eigen::MatrixXd matrix_multiply = matrix_3d * v_3d;

    std::cout << "Matrix Multiplication Results Transposed :\n" << matrix_multiply.transpose() << std::endl;

    matrix_33 = Eigen::Matrix3d::Random(); // Random Number Matrix

    std::cout << "trace: " << matrix_33.trace() << std::endl;
    std::cout << "inverse: \n" << matrix_33.inverse() << std::endl;
    std::cout << "det: " << matrix_33.determinant() << std::endl;

    // Eigenvalues

    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver(matrix_33.transpose() * matrix_33); // Real symmetric matrix can guarantee successful diagonalization

    std::cout << "Eigen values = \n" << eigen_solver.eigenvalues() << std::endl;
    std::cout << "Eigen vectors = \n" << eigen_solver.eigenvectors() << std::endl;

    // Solving equations
    // Solve the equation of matrix_NN ∗ x = v_Nd
    Eigen::Matrix<double, MATRIX_SIZE, MATRIX_SIZE> matrix_NN = Eigen::MatrixXd::Random(MATRIX_SIZE, MATRIX_SIZE);
    matrix_NN = matrix_NN * matrix_NN.transpose(); // Guarantee semi−positive definite (enforce symmetry and inversion stability)
    Eigen::Matrix<double, MATRIX_SIZE, 1> v_Nd = Eigen::MatrixXd::Random(MATRIX_SIZE, 1);

    clock_t time_stt = clock(); // Testing executing time between different methods
    Eigen::Matrix<double, MATRIX_SIZE, 1> x = matrix_NN.inverse() * v_Nd;
    std::cout << "time of normal inverse is " << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << std::endl;
    // std::cout << "x = " << x.transpose() << std::endl;

    // Solving with matrix decomposition, such as QR decomposition, will give a faster solutions
    time_stt = clock();
    x = matrix_NN.colPivHouseholderQr().solve(v_Nd);
    std::cout << "time of Qr decomposition is " << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << std::endl;
    // std::cout << "x = " << x.transpose() << std::endl;

    // For positive definite matrices, you can also use cholesky decomposition to solve equations
    time_stt = clock();
    x = matrix_NN.ldlt().solve(v_Nd);
    std::cout << "time of ldlt decomposition is " << 1000 * (clock() - time_stt) / (double) CLOCKS_PER_SEC << "ms" << std::endl;
    // std::cout << "x = " << x.transpose() << std::endl;


    return 0;
}
