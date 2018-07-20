#include "PID.h"
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {

    ostream_steer.close();

}

void PID::Init(double Kp, double Ki, double Kd) {
    //
    
    std::cout << "Initial process to set kp ki kd." << std::endl;

    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;

    p_error = 0.0;
    i_error = 0.0;
    d_error = 0.0;


    step = 0;

}

void PID::setMinMaxLimit(double mi, double mx) {

    this->min_limit = mi;
    this->max_limit = mx;

}

void PID::setFilename(std::string fname) {
    // Output filestreams for radar and laser NIS
    ostream_steer.open( fname, ios::out );

}

void PID::UpdateError(double cte) {
    //

    d_error = cte - p_error;  // p_error is previsou error
 
    p_error = cte; // set new cte as p_error
    
    i_error += cte;

    /*if (i_error > max_limit) {
        i_error = max_limit;
    }
    if (i_error < min_limit) {
        i_error = min_limit;
    }*/

    
}
double PID::TotalError() {
    // double total_error = -Kp * p_error - Ki * i_error - Kd * d_error;
    double total_error = -Kp * p_error - Ki * i_error - Kd * d_error;

    if (total_error > max_limit) {
        total_error = max_limit;
    }
    if (total_error < min_limit) {
        total_error = min_limit;
    }
    
    ostream_steer << "Step," << step << ",error," << total_error << std::endl;

    step++;

    return total_error;
}

double PID::TotalError_throttle(double throttle) {
    // double total_error = -Kp * p_error - Ki * i_error - Kd * d_error;
    double total_error = throttle -Kp * p_error - Ki * i_error - Kd * d_error;

    if (total_error > max_limit) {
        total_error = max_limit;
    }
    if (total_error < min_limit) {
        total_error = min_limit;
    }
    
    ostream_steer << "Step," << step << ",error," << total_error << std::endl;

    step++;

    return total_error;
}

