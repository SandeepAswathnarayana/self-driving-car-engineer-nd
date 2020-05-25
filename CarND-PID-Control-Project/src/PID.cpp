#include "PID.h"
#include <vector>
#include <iostream>
#include <limits>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

// TODO take into account time?

void PID::Init(double Kp, double Ki, double Kd) {    
    P = vector<double>(3);
    P[0] = Kp;
    P[1] = Ki;
    P[2] = Kd;
    
    dP = vector<double>(3);
    dP[0] = 0.001;
    dP[1] = 0.0001;
    dP[2] = 0.1;


    // Getting the max double to bootstrap our best error
	numeric_limits<double> nl;
    best_error = nl.max();

    ctes = vector<double>(0);
    previous_cte = 0.0;
    current_cte = 0.0;    
    current_P_index = 0;
    phase = 0;
    count = 0;
    min_cycles = 5;
    
}

void PID::UpdateError(double cte) {    
    cout << "UPDATE ERROR!! (" << count << ")" << endl;
    double dP_sum = dP[0] + dP[1] + dP[2];
    if(count >= min_cycles){
        cout << "[UpdateError] [dP-sum=" << dP_sum 
             << ", dP=(" << dP[0] << "," << dP[1] << "," << dP[2] 
             << ")]" << endl;        
        if(dP_sum >= 0.00001){
            Twiddle();
        }
        
    }
    
    previous_cte = current_cte;
    current_cte = cte;
    ctes.push_back(current_cte);
    ++count;

    current_steer = CalculateSteer(P[0], P[1], P[2]);
}

double PID::TotalError() {
    double sum_cte = 0.0;
    for(auto cte: ctes){
        sum_cte += cte * cte;
    }

    return sum_cte / ctes.size();
}

void PID::Twiddle(){
    cout << "[TWIDDLE] [ctes-size=" << ctes.size() 
         << ", phase=" << phase 
         << ", current-index=" << current_P_index
         << "]" << endl;

    if(ctes.size() == 0){
        cout << "[TWIDDLE] ctes reset" << endl;
        if(phase == 0){
            P[current_P_index] += dP[current_P_index];
        }else if(phase == 1){
            P[current_P_index] -= 2 * dP[current_P_index];
        }
    }
    
    if(ctes.size() == min_cycles){        
        double err = TotalError();
        cout << "[TWIDDLE] COMPUTED ERROR: " << err << endl;
        if(err < best_error){
            best_error = err;
            dP[current_P_index] *= 1.1;
            // Move on to the next component of PID
            current_P_index = (current_P_index + 1) % P.size();
        }else{
            if(phase == 0){
                phase = 1;
            }else{
                P[current_P_index] += dP[current_P_index];
                dP[current_P_index] *= 0.9;
                // Move on to the next component of PID
                current_P_index = (current_P_index + 1) % P.size();
                phase = 0;
            }
        }
        // make sure to clear (and thus resize) our cte vector
        ctes.clear();
    }
}

double PID::CalculateSteer(double kp, double ki, double kd){
    double p_comp = kp * current_cte;
    double d_comp = 0.0;
    if(count > 0){
        d_comp = kd * (current_cte - previous_cte);
    }

    double sum_cte = 0.0;
    for(auto cte: ctes){
        sum_cte += cte;
    }

    double i_comp = ki * sum_cte;

    double steer = -p_comp - d_comp - i_comp;

    if(steer < -1){
        return -1;
    }
    if(steer > 1){
        return 1;        
    }
    return steer;    
}