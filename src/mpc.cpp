#include <casadi/casadi.hpp>
using namespace casadi;

 
int main(){

    int pred_horz = 5;
    double dt = 0.1;
    std::vector<double> x_ref_value = {2.0, 2.0, 3.0, 0.5};

    std::vector<MX> x_ref;
    std::vector<MX> x_prd;
    std::vector<MX> veloc;
    DM x_init = DM({1.0, 2.0, 3.0, 4.0}); // x, y, z, yaw
    DM x_constr = DM({10, 10, 10, 99999}); 
    DM v_constr = DM({0.5, 0.5, 0.5, 0.5}); // v_x, v_y, v_z, v_yaw

    MX Q = MX::eye(4);
    //MX Q = 1.0;
    MX R = MX::eye(4);
    //MX R = 1.0;

    MX opti_func;
    MX stage_cost;
    MX traj_error;
    Opti opti;

    // Loop to define the variables and constraints over the horizon
    for (int k = 0; k < pred_horz; ++k) {
        x_prd.push_back(opti.variable(4, 1));  
        veloc.push_back(opti.variable(4, 1));  
        x_ref.push_back(opti.parameter(4, 1)); 

        if (k == 0) {
            x_prd.push_back(opti.variable(4, 1));  
            opti.set_initial(x_prd.at(k), x_init);
        }
        if (k < pred_horz - 1) { // Define the dynamics: x_{k+1} = x_k + dt * v_k
            opti.subject_to(x_prd.at(k+1) == x_prd.at(k) + dt * veloc.at(k));
        }

        for(int i = 0; i < 4; i++){
            opti.set_value(x_ref.at(k)(i), x_ref_value.at(i)); // input traejctory pose reference
        }

        traj_error = x_prd.at(k) - x_ref.at(k);
        // calculating the quadratic sum of the errors or somthing like this
        // J(x) = Sum((x(k).T)*Q*x(k)+v(k)*R*v(k))
        stage_cost = mtimes(traj_error.T(), mtimes(Q, traj_error)) + mtimes(veloc.at(k).T(), mtimes(R, veloc.at(k)));
        opti_func += stage_cost;

        // constraints
        opti.subject_to(opti.bounded(-x_constr, x_prd.at(k), x_constr));  
        opti.subject_to(opti.bounded(-v_constr, veloc.at(k), v_constr));   
    }

    opti.minimize(opti_func);

    opti.solver("ipopt");
        
    //OptiSol sol = opti.solve();


return 0;

}



