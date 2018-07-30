#include "networkActSis.h"
#ifdef ACT_SIS

#include "common.h"
#include "networks.h"
using namespace std;

// ******************************************************
Act_sis::Act_sis(void)
    : M(0)
    , rho(0)
    , p(0)
    , lambda(0)
    , tau(0)
    , t_av(0)
    , ksi(0)
    , lambda_c(0)
    , nSum(0)
    , n2Sum(0)
{
}

ostream& operator<<(ostream& os, const Act_sis& sis)
{
  if (!os) {
    ERROR();
    return os;
  }
  os << "--sis.lambda_c\t" << sis.lambda_c << "\n--sis.tau\t" << sis.tau
     << "\n--sis.ksi\t" << sis.ksi << "\n--sis.lambda\t" << sis.lambda
     << "\n--sis.rho\t" << sis.rho << "\n--sis.p\t" << sis.p << "\n";
  return os;
}

int Act_sis::save_params(std::ostream& os) const
{
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int Act_sis::save_params(const char* name) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  ofstream os(name);
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  os.close();
  return 0;
}

int Act_sis::save_data(
    const char* name, const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  return 0;
}

int Act_sis::save(
    const char* name, const char priChar, const char priChar2) const
{
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".sis.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".sis").c_str(), priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int Act_sis::read_params_1(string& s, istream& is)
{
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--sis.M") {
      is >> M;
      cout << s << '\t' << M << endl;
      break;
    }
    if (s == "--sis.rho") {
      is >> rho;
      cout << s << '\t' << rho << endl;
      break;
    }
    if (s == "--sis.p") {
      is >> p;
      cout << s << '\t' << p << endl;
      break;
    }
    if (s == "--sis.lambda") {
      is >> lambda;
      cout << s << '\t' << lambda << endl;
      break;
    }
    if (s == "--sis.tau") {
      is >> tau;
      cout << s << '\t' << tau << endl;
      break;
    }
    if (s == "--sis.t_av") {
      is >> t_av;
      cout << s << '\t' << t_av << endl;
      break;
    }
    if (s == "--sis.ksi") {
      is >> ksi;
      cout << s << '\t' << ksi << endl;
      break;
    }
    if (s == "--sis.lambda_c") {
      is >> lambda_c;
      cout << s << '\t' << lambda_c << endl;
      break;
    }
    if (s == "--sis.nSum") {
      is >> nSum;
      cout << s << '\t' << nSum << endl;
      break;
    }
    if (s == "--sis.n2Sum") {
      is >> n2Sum;
      cout << s << '\t' << n2Sum << endl;
      break;
    }
    if (s == "--sis.nNum") {
      is >> nNum;
      cout << s << '\t' << nNum << endl;
      break;
    }
    flag = 0;
  } while (0);
  if (flag)
    s.clear();
  return 0;
}

Act_sis& Act_sis::clear(void) { return *this; }

// ******************************************************
Networks& Networks::act_sis_tau(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  ::act_SIS_init(
      sis.statusSN, sis.SN, sis.N_i, sis.NDeg_i, sis.t, p2p, sis.rho, sis.M);
  sis.nSum = 0;
  sis.n2Sum = 0;
  sis.nNum = 0;
  ::act_SIS_tau(sis.tau, sis.statusSN, sis.SN, sis.N_i, sis.NDeg_i, sis.t,
      sis.nSum, sis.n2Sum, sis.nNum, sis.p, sis.lambda, p2p, kMax);
  return *this;
}

Networks& Networks::act_sis(void)
{
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  ::act_SIS_init(
      sis.statusSN, sis.SN, sis.N_i, sis.NDeg_i, sis.t, p2p, sis.rho, sis.M);
  sis.nSum = 0;
  sis.n2Sum = 0;
  sis.nNum = 0;
  ::act_sis(sis.statusSN, sis.SN, sis.N_i, sis.NDeg_i, sis.t, sis.nSum,
      sis.n2Sum, sis.nNum, sis.p, sis.lambda, sis.tau, sis.t_av, p2p, kMax);
  ::act_SIS_cal_params(
      sis.ksi, sis.lambda_c, p2p, sis.nSum, sis.n2Sum, sis.nNum);
  return *this;
}

// ******************************************************
#endif // ACT_SIS
