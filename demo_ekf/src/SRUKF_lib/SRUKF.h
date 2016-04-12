/**
  ***************************************************************************************
  * @file    SRUKF.h
  * @author  YANG Shuo
  * @version V1.0.0
  * @date    02-April-2014
  * @brief   This file is a implementation of square-root UKF, depends on linear algebra
  *          C++ library Eigen3  
  ***************************************************************************************
  */
#ifndef _SRUKF_H
#define _SRUKF_H
#include <iostream>
#include <cmath>
#include <Eigen/Dense>
#include </usr/local/include/eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

class SRUKF
{
    public:

        SRUKF(int _n, int _m, 
              float _q, float  _r,
              void (*_f_func)(VectorXf&, const VectorXf&, const VectorXf&, const float dt),
              void (*_h_func)(VectorXf&, const VectorXf&), 
              float _w_m0 = 0.5, float _w_c0 = 0.5);
        ~SRUKF();

		void setR(MatrixXf _R);
		void setQ(MatrixXf _Q);

        void predict(const VectorXf &a, const float dt);
        void correct(const VectorXf& z_t);
		void setMeasurementFunc(void (*_h_func)(VectorXf&, const VectorXf&));

        VectorXf state_pre, state_post;
        MatrixXf S_pre, S_post;
        
    private:
        int n;              //state dimension
        int m;              //measurement dimension

        float w_m0, w_mi;
        float w_c0, w_ci;   //ukf weights
        float gamma;        // ukf parameter

        MatrixXf R; // measurement errorCov
		MatrixXf Q; // processs errorCov

        MatrixXf K_t;

        // function pointer to process function
        void (*f_func)(VectorXf&, const VectorXf&, const VectorXf&, const float dt);
        // function pointer to measurement function
        void (*h_func)(VectorXf&, const VectorXf&);               

        MatrixXf sigmaPoints;
        MatrixXf sigmaZ;

        // Eigen function for QR decomposition
        HouseholderQR<MatrixXf> qrSolver;
        FullPivHouseholderQR<MatrixXf> colPiv_qrSolver;
        MatrixXf m_q, m_r;
        // tmp variables for computation
        VectorXf x_tmp, z_tmp, z_t_bar;
        MatrixXf OS;
        MatrixXf S_y_bar, P_t_xz_bar;
        MatrixXf K_tmp;
        MatrixXf U;

};
#endif
