#include <cmath>
#include "def_usrmod.hpp"

#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>
#include <fstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "rbdl/rbdl.h"
#include <rbdl/addons/luamodel/luamodel.h>
#include <rbdl/addons/luamodel/luatables.h>

#include<random>
#include <sys/stat.h>
#include<string>
#include<sstream>
#include<iomanip>

using namespace RigidBodyDynamics;
using namespace RigidBodyDynamics::Math;
using namespace std;

// Forward declare.
int counter();
bool fileExists(const std::string& file);
string meshup_naming_file();

// datfileutils.h needs VectorNd and therefore RigidBodyDynamics::Math
#include "datfileutils.h"

// Global Definitions
int NMOS   =  1;  /* Number of phases (Model Stages) */
int NP     =  0;  /* Number of parameters */
int NRC    =  0;  /* Number of coupled constraints */
int NRCE   =  0;  /* Number of coupled equality constraints */

int NXD    =  4;  /* Number of differential states */
int NXA    =  0;  /* Number of algebraic states */
int NU     =  1;  /* Number of controls */
int NPR    =  0;  /* Number of local parameters */

// Variables
Model *model = NULL;
string model_file_name  ="model.lua"; // path/model.lua
string meshup_file_name= meshup_naming_file();
std::string log_fileName = "log.txt";


VectorNd Q, QDOT, QDDOT, TAU;

unsigned int nDof;
unsigned int nActuatedDof;

// ********************************o
// *
// * Random Number Generation
// *
// ********************************o

//seed
std::random_device rd1;
std::random_device rd2;
std::random_device rd3;
std::random_device rd4;
std::mt19937 gen1(rd1());
std::mt19937 gen2(rd2());
std::mt19937 gen3(rd3());
std::mt19937 gen4(rd4());

std::uniform_real_distribution<float> dis1(0.,2*M_PI);
//std::uniform_real_distribution<float> dis2(0.,2*M_PI);
//std::uniform_real_distribution<float> dis3(-10.,10);
//std::uniform_real_distribution<float> dis4(-10,.10);

float r1=dis1(gen1);
//float r2=dis2(gen2);;
float r3=0;
//float r4=dis4(gen4);

// ********************************o
// *
// * stringstream
// * 
// ********************************o


string meshup_naming_file()
{
  string name;
  stringstream meshup_file_name_o("");
  meshup_file_name_o << "meshup_cart_pendulum_count_" << setfill('0') << setw(4) << to_string(counter()) << ".csv"; 
  
  name=meshup_file_name_o.str();
  return name;
}

// ********************************o
// *
// * Counter
// * 
// ********************************o

int counter()
{
    int returnedCount = 0;
    int possibleMax = 5000; //some number you can expect.

    for (int starter = 0; starter < possibleMax; starter++){
        stringstream fileName_s("");
        fileName_s << "/home/patrick/Downloads/MUSCOD-Intro/cartPenudlum_template/build/RES/meshup_cart_pendulum_count_" 
         << setfill('0') << setw(4) << to_string(starter) << ".csv";
         string fileName= fileName_s.str();
      
        bool status = fileExists(fileName);

        returnedCount = starter;

        if (!status)
            break;
        }

    return returnedCount;
}

bool fileExists(const std::string& file) {
    struct stat buf;
    return (stat(file.c_str(), &buf) == 0);
}



// ********************************o
// *
// * Utilities
// *
// ********************************o
// update RBDL vectors
static void updateState (const double *sd, const double *u=NULL)
{
  Q   [0] = sd[0]; //sd[0]
  Q   [1] = sd[1];
  QDOT[0] = sd[2]; //sd[2]
  QDOT[1] = sd[3];
  
  TAU[0]  = 0.0;
  TAU[1]  = 0.0;
  
  if (u)
  {
    TAU[0] = u[0];//u[0]
  }
}

// ********************************o
// *
// * Objective Funtions
// *
// ********************************o
/** \brief Objective function (Lagrangian type) */
static void lfcn_energy(double *t, double *xd, double *xa, double *u,
  double *p, double *lval, double *rwh, long *iwh, InfoPtr *info) 
{

  *lval = u[0]*u[0];

}

/** \brief Objective function (Mayer type) */
static void mfcn_end_time(double *ts, double *sd, double *sa, double *p, 
  double *pr, double *mval,  long *dpnd, InfoPtr *info) 
{

  if (*dpnd) {
    *dpnd = MFCN_DPND(*ts, 0, 0, 0, 0);
    return;
  }
  
  *mval = ts[0];

}

// ********************************o
// *
// * Right Hand Sides
// *
// ********************************o
static void ffcn (double *t, double *xd, double *xa, double *u,
  double *p, double *rhs, double *rwh, long *iwh, InfoPtr *info)
{
  updateState (xd, u);
  
  // Compute Forward Dynamics with RBDL (see documentation)
  ForwardDynamics(*model,Q,QDOT,TAU,QDDOT);// ForwardDynamics(Q, QDOT, TAU)

  for (unsigned int i = 0; i < nDof; i++) {
    rhs[i]        = QDOT[i];//QDOT[i]
    rhs[i + nDof] = QDDOT[i];//QDDOT[i]
  }
  
}

// ********************************o
// *
// * Decoupled Constraints
// *
// ********************************o
/// \brief Constraints at start point */
// # of all constraints   # of equality constraints
static int RDFCN_S_N = 4, RDFCN_S_NE = 4;
static void rdfcn_s(double *ts, double *sd, double *sa, double *u,
  double *p, double *pr, double *res, long *dpnd, InfoPtr *info)
{
  if (*dpnd) {
    *dpnd = RFCN_DPND(NULL, *sd, 0, 0, 0, 0);
    return;
  }
  
  updateState (sd, NULL);
  
  res[0] = ( Q[1]-r1 ) * 100; // = 0 (* 100 just for scaling reasons)
  res[1] = ( Q[0]-r3 ) * 100; // = 0
  res[2] = ( QDOT[0]-0 ) * 100; // = 0
  res[3] = ( QDOT[1]-0 ) * 100; // = 0
  
}

/// \brief Constraints at end point */
// # of all constraints   # of equality constraints
static int RDFCN_E_N = 4, RDFCN_E_NE = 4;
static void rdfcn_e(double *ts, double *sd, double *sa, double *u,
  double *p, double *pr, double *res, long *dpnd, InfoPtr *info)
{
  if (*dpnd) {
    *dpnd = RFCN_DPND(NULL, *sd, 0, 0, 0, 0);
    return;
  }
  
  updateState (sd, NULL);
  
  res[0] = ( Q[1]-0 ) * 100; // = 0 (* 100 just for scaling reasons)
  res[1] = ( Q[0]-0 ) * 100; // = 0
  res[2] = ( QDOT[0]-0 ) * 100; // = 0
  res[3] = ( QDOT[1]-0 ) * 100; // = 0

}

// ********************************o
// *
// * Data Output
// *
// ********************************o
static void data_output( double *t, double *sd, double *sa, double *u, 
  double *p, double *rwh, long *iwh, InfoPtr* info ) 
{
  FILE *fp;
  
  stringstream output_filename ("");
  
 // const char* meshup_header = "COLUMNS: \n\
                               time,\n\
                               cart:T:X,\n\
                               pendulum:R:Y:rad";
  
  // define output path
  output_filename << "./RES/" << meshup_file_name;
  
  // if in first MS node then create file, else append data
  // get imsn and imos from InfoPtr
  if ((info->cnode == 0) && (info->cimos == 0)) {
    fp = fopen (output_filename.str().c_str(), "w");
    if (!fp) {
      fprintf (stderr, "Error: Could not open file '%s'!\n", output_filename.str().c_str());
      return;
    }
    
    // write the header of the meshup file
  //  fprintf (fp, "%s\n", meshup_header);
  //  fprintf (fp, "DATA:\n");
  }
  else {
    fp = fopen (output_filename.str().c_str(), "a");

    if (!fp) {
      fprintf (stderr, "Error: Could not open file '%s'!\n", output_filename.str().c_str());
      return;
    }
  }

  // write data
  int i;
  
  // print time
  fprintf (fp, "%e,\t", *t);

  // print degrees of freedom
  for (i = 0; i < nDof; i ++) {
    fprintf (fp, "%e,\t", sd[i]);
  }
  
  fprintf (fp, "\n");

  // close file
  fclose (fp);  


}

void meshup_output
(
  long   *imos,      ///< index of model stage (I)
  long   *imsn,      ///< index of m.s. node on current model stage (I)
  double *ts,        ///< time at m.s. node (I)
  double *te,        ///< time at end of m.s. interval (I)
  double *sd,        ///< differential states at m.s. node (I)
  double *sa,        ///< algebraic states at m.s. node (I)
  double *u,         ///< controls at m.s. node (I)
  double *udot,      ///< control slopes at m.s. node (I)
  double *ue,        ///< controls at end of m.s. interval (I)
  double *uedot,     ///< control slopes at end of m.s. interval (I)
  double *p,         ///< global model parameters (I)
  double *pr,        ///< local i.p.c. parameters (I)
  double *ccxd,
  double *mul_ccxd,  ///< multipliers of continuity conditions (I)
#if defined(PRSQP) || defined(EXTPRSQP)
  double *ares,
  double *mul_ares,
#endif
  double *rd,
  double *mul_rd,    ///< multipliers of decoupled i.p.c. (I)
  double *rc,
  double *mul_rc,    ///< multipliers of coupled i.p.c. (I)
  double *obj,
  double *rwh,       ///< real work array (I)
  long   *iwh        ///< integer work array (I)
)
{
  InfoPtr info(0, *imos, *imsn);
  data_output( ts, sd, sa, u, p, rwh, iwh, &info);
}


/// \brief Entry point for the muscod application
extern "C" void def_model(void);
void def_model(void)
{
  std::cout<<"r1="<<r1<<endl;
  std::cout<<"count="<<counter()<<endl;
 

  // load LUA model
  model = new Model;

  if (!Addons::LuaModelReadFromFile (model_file_name.c_str(), model, false)) {
    cerr << "Error loading RBDL model '" << model_file_name << "'!" << endl;
    abort();
  }
  
  assert (model->dof_count == 2);
  
  nDof = model->dof_count;
  nActuatedDof = 2;

  Q     = VectorNd::Zero(model->dof_count);
  QDOT  = VectorNd::Zero(model->dof_count);
  QDDOT = VectorNd::Zero(model->dof_count);
  TAU   = VectorNd::Zero(model->dof_count);    
  
  def_mdims(NMOS, NP, NRC, NRCE);

  def_mstage( 0,
              NXD, NXA, NU,
              mfcn_end_time, NULL,   // mayer term, lagrange term
              0, 0, 0, 
              NULL, ffcn, NULL,
              NULL, NULL
            );

  def_mpc(0, "s", NPR, RDFCN_S_N, RDFCN_S_NE, rdfcn_s, NULL);
  def_mpc(0, "e", NPR, RDFCN_E_N, RDFCN_E_NE, rdfcn_e, NULL);

// ********************************o
// *
// * Logfile
// *
// ********************************o

//saving logfile
FILE *lp;
    std::string log_fileName = "log.txt";
    //open
    lp=fopen(log_fileName.c_str(),"a+");

    //create text
    string txt=meshup_file_name+","+ to_string(r1)+","+ to_string(r3);

  //print
    fprintf(lp,"%s\n",txt.c_str());

  //close
   fclose(lp);

  def_mio (NULL, meshup_output, data_output);

#ifdef HAVE_USERPLOT
  def_userplot (plot_start, plot_data, plot_end);
#endif
}
