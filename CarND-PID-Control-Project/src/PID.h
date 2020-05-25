#ifndef PID_H
#define PID_H

#include <vector>
using namespace std;


class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;
  double best_error;

  /*
  * Coefficients
  */ 
  // Represents [P,I,D]
  vector<double> P;
  vector<double> dP;

  /*
  * cte related variables
  */ 
  double current_cte;
  double previous_cte;
  vector<double> ctes;

  /*
  * Counts, etc
  */
  unsigned int count;
  unsigned int min_cycles;
  int reset_interval;
  int current_P_index;
  int phase;
  double current_steer;


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

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
   * Performs the twiddle algorithm
   */ 
  void Twiddle();

private:
   /*
   * Computes and returns the steering angle
   */ 
  double CalculateSteer(double kp, double ki, double kd);



};

#endif /* PID_H */