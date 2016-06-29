#include <iostream>
using namespace std; 

// Eigen 部分
#include <Eigen/Core>
// 稠密矩阵的代数运算（逆，特征值等）
#include <Eigen/Dense>

int main( int argc, char** argv )
{
    // Eigen 中所有向量和矩阵都是Eigen::Matrix，它是一个模板类。它的前三个参数为：数据类型，行，列
    // 声明一个2*3的float矩阵
    Eigen::Matrix<float, 2, 3> matrix_23;
    // 同时，Eigen 通过 typedef 提供了许多内置类型，不过底层仍是Eigen::Matrix
    // 例如 Vector3d 实质上是 Eigen::Matrix<double, 3, 1>
    Eigen::Vector3d v_3d;
    // 还有 Matrix3d 实质上是 Eigen::Matrix<double, 3, 3>
    Eigen::Matrix3d matrix_33 = Eigen::Matrix3d::Zero(); //初始化为零
    // 如果您不确定矩阵大小，可以使用动态大小的矩阵
    Eigen::Matrix< double, Eigen::Dynamic, Eigen::Dynamic > matrix_dynamic;
    // 更简单的
    Eigen::MatrixXd matrix_x; 
    // 这种类型还有很多，我们不一一列举
    
    // 下面是对Eigen阵的操作
    // 输入数据
    matrix_23 << 1, 2, 3, 4, 5, 6;
    // 输出
    cout << matrix_23 << endl;
    
    // 用()访问矩阵中的元素
    for (int i=0; i<1; i++)
        for (int j=0; j<2; j++)
            cout<<matrix_23(i,j)<<endl;
    
    // 矩阵和向量相乘（实际上仍是矩阵和矩阵）
    v_3d << 3, 2, 1;
    // 但是在Eigen里你不能混合两种不同类型的矩阵，像这样是错的
    // Eigen::Matrix<double, 2, 1> result_wrong_type = matrix_23 * v_3d;
    
    // 应该显式转换
    Eigen::Matrix<double, 2, 1> result = matrix_23.cast<double>() * v_3d;
    cout << result << endl;
    
    // 同样你不能搞错矩阵的维度
    // 试着取消下面的注释，看看Eigen会报什么错
    // Eigen::Matrix<double, 2, 3> result_wrong_dimension = matrix_23.cast<double>() * v_3d;
    
    // 一些矩阵运算
    // 四则运算就不演示了，直接用+-*/即可。
    matrix_33 = Eigen::Matrix3d::Random(); 
    cout << matrix_33 << endl << endl;
    
    cout << matrix_33.transpose() << endl;      //转置
    cout << matrix_33.sum() << endl;            //各元素和
    cout << matrix_33.trace() << endl;          //迹
    cout << 10*matrix_33 << endl;               //数乘
    cout << matrix_33.inverse() << endl;        //逆
    cout << matrix_33.determinant() << endl;    //行列式 
    
    // 特征值
    Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d> eigen_solver ( matrix_33 );
    cout << "Eigen values = " << eigen_solver.eigenvalues() << endl; 
    cout << "Eigen vectors = " << eigen_solver.eigenvectors() << endl; 
    
    // 解方程 
    // 我们求解 matrix_33 * x = v_3d 这个方程
    // 直接求逆自然是最直接的，但是求逆运算量大
    Eigen::Vector3d x = matrix_33.inverse()*v_3d;
    cout << "x=" << x << endl; 
    // 通常用矩阵分解来求，例如QR分解
    x = matrix_33.colPivHouseholderQr().solve(v_3d);
    cout << "x=" << x << endl; 
    
    return 0;
}