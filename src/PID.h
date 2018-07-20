#ifndef PID_H
#define PID_H

#include <fstream>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;

  /*
  * steering should be ranged in [-1, 1], so limit number also set for adjusting error 
  */

  double min_limit;
  double max_limit;


  // Output filestreams for radar and laser NIS
  std::ofstream ostream_steer;

  int step;
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  void setMinMaxLimit(double mi, double mx);
    //

  void setFilename(std::string fname);  

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
  double TotalError_throttle(double throttle);
};

#endif /* PID_H */
