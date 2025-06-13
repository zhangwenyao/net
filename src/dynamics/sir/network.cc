#include "network.h"
#ifdef ACT_SIR

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// ******************************************************
network::sir::Sir::Sir(void) : beta(0), gamma(0), ksi(0), lambda_c(0), id0(0) {}

ostream& operator<<(ostream& os, const network::sir::Sir& sir) {
  if (!os) {
    ERROR();
    return os;
  }
  os << "--sir.beta\t" << sir.beta << "\n--sir.gamma\t"
     << sir.gamma
     //  << "\n--sir.ksi\t" << sir.ksi
     << "\n--sir.lambda_c\t"
     << sir.lambda_c
     //  << "\n--sir.id0\t" << sir.id0
     << "\n";
  return os;
}

int network::sir::Sir::save_params(std::ostream& os) const {
  if (!os) {
    ERROR();
    return -1;
  }
  os << *this;
  return 0;
}

int network::sir::Sir::save_params(const char* name) const {
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

int network::sir::Sir::save_data(const char* name, const long seed,
                                 const char priChar,
                                 const char priChar2) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (save1((fn + ".modularity.txt").c_str(), modularity_nums, priChar) != 0)
    return -1;
  if (save1((fn + ".modularity2.txt").c_str(), modularity_nums2, priChar) != 0)
    return -1;
  if (save1((fn + ".R_nums_" + to_string(seed) + ".txt").c_str(), Rs,
            priChar) != 0)
    return -1;
  return 0;
}

int network::sir::Sir::save(const char* name, const char priChar,
                            const char priChar2) const {
  if (name == NULL || name[0] == '\0') {
    ERROR();
    return -1;
  }
  string fn = name;
  if (0 != save_params((fn + ".sir.params.txt").c_str())) {
    ERROR();
    return -1;
  }
  if (0 != save_data((fn + ".sir").c_str(), priChar, priChar2)) {
    ERROR();
    return -1;
  }
  return 0;
}

int network::sir::Sir::read_params_1(string& s, istream& is) {
  if (!is) {
    ERROR();
    return -1;
  }
  int flag = 1;
  do {
    if (s == "--sir.beta") {
      is >> beta;
      cout << s << '\t' << beta << endl;
      break;
    }
    if (s == "--sir.gamma") {
      is >> gamma;
      cout << s << '\t' << gamma << endl;
      break;
    }
    // if (s == "--sir.ksi") {
    //   is >> ksi;
    //   cout << s << '\t' << ksi << endl;
    //   break;
    // }
    if (s == "--sir.lambda_c") {
      is >> lambda_c;
      cout << s << '\t' << lambda_c << endl;
      break;
    }
    if (s == "--sir.id0") {
      is >> id0;
      cout << s << '\t' << id0 << endl;
      break;
    }
    // if (s == "--sir.nSum") {
    //   is >> nSum;
    //   cout << s << '\t' << nSum << endl;
    //   break;
    // }
    // if (s == "--sir.n2Sum") {
    //   is >> n2Sum;
    //   cout << s << '\t' << n2Sum << endl;
    //   break;
    // }
    // if (s == "--sir.nNum") {
    //   is >> nNum;
    //   cout << s << '\t' << nNum << endl;
    //   break;
    // }
    flag = 0;
  } while (0);
  if (flag) s.clear();
  return 0;
}

network::sir::Sir& network::sir::Sir::clear(void) { return *this; }

// ******************************************************

Networks& Networks::act_sir(void) {
  if (0 != runStatus) {
    ERROR();
    return *this;
  }
  network::sir::act_sir_lambda(sir.Rs, sir.beta, p2p, nodeSize);
  return *this;
}

// ******************************************************
#endif  // ACT_SIR
