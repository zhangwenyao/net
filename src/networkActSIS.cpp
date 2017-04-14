#include "networkActSIS.h"
#ifdef ACT_SIS

#include "ActSIS.h"
#include "common.h"
using namespace std;

//**//****************************************************//*
Act_SIS::Act_SIS(void)
    : M(0),
      rho(0),
      p(0),
      lambda(0),
      tau(0),
      t_av(0),
      ksi(0),
      lambda_c(0),
      nSum(0),
      n2Sum(0) {}

std::ostream& operator<<(std::ostream& os, const Act_SIS& sis) {
  if (!os) {
    ERROR();
    return os;
  }
  os << "--sis.lambda_c\t" << sis.lambda_c << "\n--sis.tau\t" << sis.tau
     << "\n--sis.ksi\t" << sis.ksi << "\n--sis.lambda\t" << sis.lambda
     << "\n--sis.rho\t" << sis.rho << "\n--sis.p\t" << sis.p << "\n";
  return os;
}

int Act_SIS::save_params(std::ostream& os)const {
  os << *this;
  return 0;
}

int Act_SIS::save_params(const char* name)const { return 0; }
int Act_SIS::save_data(const char* name) { return 0; }
int Act_SIS::save(const char* name) { return 0; }

int Act_SIS::read_params_1(string& s, istream& is) { return 0; }

//**//****************************************************//*
Act_SIS& Act_SIS::clear(void) { return *this; }

//**//****************************************************//*
int Networks::cal_SIS_tau() {
  ::act_SIS_init(sis.statusSN, sis.SN, sis.N_i, sis.NDeg_i, sis.t, p2p, sis.rho,
                 sis.M);
  sis.nSum = 0;
  sis.n2Sum = 0;
  sis.nNum = 0;
  ::act_SIS_tau(sis.tau, sis.statusSN, sis.SN, sis.N_i, sis.NDeg_i, sis.t,
                sis.nSum, sis.n2Sum, sis.nNum, sis.p, sis.lambda, p2p, kMax);
  return 0;
}

int Networks::act_SIS() {
  ::act_SIS_init(sis.statusSN, sis.SN, sis.N_i, sis.NDeg_i, sis.t, p2p, sis.rho,
                 sis.M);
  sis.nSum = 0;
  sis.n2Sum = 0;
  sis.nNum = 0;
  ::act_SIS(sis.statusSN, sis.SN, sis.N_i, sis.NDeg_i, sis.t, sis.nSum,
            sis.n2Sum, sis.nNum, sis.p, sis.lambda, sis.tau, sis.t_av, p2p,
            kMax);
  ::act_SIS_cal_params(sis.ksi, sis.lambda_c, p2p, sis.nSum, sis.n2Sum,
                       sis.nNum);
  return 0;
}

//**//****************************************************//*
#endif  // ACT_SIS
