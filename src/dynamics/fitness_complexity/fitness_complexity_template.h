#ifndef DYNAMICS__FITNESS_COMPLEXITY__FITNESS_COMPLEXITY_TEMPLATE_H_
#define DYNAMICS__FITNESS_COMPLEXITY__FITNESS_COMPLEXITY_TEMPLATE_H_
#include "fitness_complexity.h"
#ifdef ACT_FITNESS_COMPLEXITY

#include <cstdlib>
#include <cstring>

#include "../../common/common.h"

// *******************************************************
template <typename T, typename T2>
int network::fitness_complexity::export_2_Mcp(
    const std::vector<std::vector<T>>& e, std::vector<std::vector<T2>>& mcp)
{
  // cal Qp Qc Qsum
  const size_t NC = e.size(), NP = e[0].size();
  std::vector<T> Qc(NC, 0), Qp(NP, 0);
  T Qsum = 0;
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++) {
      Qp[p] += e[c][p];
      Qc[c] += e[c][p];
    }
    Qsum += Qc[c];
  }

  // cal Mcp
  mcp.assign(NC, std::vector<T2>(NP, (T2)0));
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < NP; p++) {
      mcp[c][p] = (T2)(e[c][p] > 0
                  && (double)e[c][p] * Qsum >= (double)Qc[c] * Qp[p]
              ? 1
              : 0);
    }
  }

  return 0;
}

template <typename T>
int network::fitness_complexity::Mcp_2_C_P(
    const std::vector<std::vector<T>>& mcp, VVNodeType& pc, VVNodeType& pp)
{
  const size_t NC = mcp.size(), NP = mcp[0].size();
  pc.clear();
  pc.resize(NC);
  pp.clear();
  pp.resize(NP);
  for (size_t c = 0; c < NC; c++) {
    for (size_t p = 0; p < mcp[c].size(); p++) {
      if (mcp[c][p] != 0) {
        pc[c].push_back(p);
        if (p >= NP) {
          ERROR();
          return -1;
        }
        pp[p].push_back(c);
      }
    }
  }
  return 0;
}

template <typename T>
int network::fitness_complexity::Mcp_2_FC(
    VDouble& Fc, VDouble& Cp, const std::vector<std::vector<T>>& Mcp)
{
  int flag = 0;
  const double delta = 1.0e-8;
  const size_t NC = Mcp.size(), NP = Mcp[0].size();
  Fc.assign(NC, 1);
  Cp.assign(NP, 1);
  VDouble iFc = Fc, iCp = Cp;
  double fMean = 1, cMean = 1, ifMean, icMean;
  for (int count = 1; 1; count++) {
    iFc.assign(NC, -1);
    ifMean = 0;
    size_t n = 0;
    for (size_t c = 0; c < NC; c++) {
      for (size_t p = 0; p < NP; p++)
        if (Mcp[c][p]) {
          if (iFc[c] < 0)
            iFc[c] = 0;
          iFc[c] += Cp[p];
        }
      if (iFc[c] >= 0) {
        ifMean += iFc[c];
        ++n;
      }
    }
    if (n <= 0 || ifMean <= 0) {
      flag = -1;
      ERROR("ifMean = ", ifMean, "\t", count);
      break;
    }
    ifMean /= n;
    // ifMean /= NC;

    iCp.assign(NP, -1);
    icMean = 0;
    n = 0;
    for (size_t p = 0; p < NP; p++) {
      for (size_t c = 0; c < NC; c++) {
        if (Mcp[c][p]) {
          if (iCp[p] < 0)
            iCp[p] = 0;
          iCp[p] += 1 / Fc[c];
        }
      }
      if (iCp[p] >= 0) {
        iCp[p] = 1 / iCp[p];
        icMean += iCp[p];
        ++n;
      }
    }
    if (n <= 0 || icMean <= 0) {
      flag = -1;
      ERROR("icMean = ", icMean, "\t", count);
      break;
    }
    icMean /= n;
    // icMean /= NP;

    // INFORM(count, "\t", ifMean, "\t", icMean);
    for (size_t c = 0; c < NC; c++)
      Fc[c] = iFc[c] < 0 ? -1 : iFc[c] / ifMean;
    for (size_t p = 0; p < NP; p++)
      Cp[p] = iCp[p] < 0 ? -1 : iCp[p] / icMean;

    if ((1.0 - delta) * cMean <= icMean && icMean <= (1.0 + delta) * cMean
        && (1.0 - delta) * fMean <= ifMean
        && ifMean <= (1.0 + delta) * fMean) {
      // DBG(count);
      break;
    }
    fMean = ifMean;
    cMean = icMean;
    // if (count % 1000 == 0)
    // DBG(count, "\tfm ", fMean, "\tcm ", cMean);
  }
  for (size_t c = 0; c < NC; c++)
    if (iFc[c] < 0)
      Fc[c] = 0;
  for (size_t p = 0; p < NP; p++)
    if (iCp[p] < 0)
      Cp[p] = 0;

  return flag;
}

template <typename T>
int network::fitness_complexity::Mcp_2_FC_p2p(VDouble& Fc, VDouble& Cp,
    const std::vector<std::vector<T>>& c2p,
    const std::vector<std::vector<T>>& p2c)
{
  int flag = 0;
  const double delta = 1.0e-8;
  const size_t NC = c2p.size(), NP = p2c.size();
  Fc.assign(NC, 1);
  Cp.assign(NP, 1);
  VDouble iFc = Fc, iCp = Cp;
  double fMean = 1, cMean = 1, ifMean, icMean;
  for (int count = 1; 1; count++) {
    iFc.assign(NC, -1);
    ifMean = 0;
    size_t n = 0;
    for (size_t c = 0; c < NC; c++) {
      // for (size_t p = 0; p < NP; p++){
      for (auto p : c2p[c]) {
        if (iFc[c] < 0)
          iFc[c] = 0;
        iFc[c] += Cp[p];
      }
      if (iFc[c] >= 0) {
        ifMean += iFc[c];
        ++n;
      }
    }
    if (n <= 0 || ifMean <= 0) {
      flag = -1;
      ERROR("ifMean = ", ifMean, "\t", count);
      break;
    }
    ifMean /= n;
    // ifMean /= NC;

    iCp.assign(NP, -1);
    icMean = 0;
    n = 0;
    for (size_t p = 0; p < NP; p++) {
      // for (size_t c = 0; c < NC; c++) {
      for (auto c : p2c[p]) {
        if (iCp[p] < 0)
          iCp[p] = 0;
        iCp[p] += 1 / Fc[c];
      }
      if (iCp[p] >= 0) {
        iCp[p] = 1 / iCp[p];
        icMean += iCp[p];
        ++n;
      }
    }
    if (n <= 0 || icMean <= 0) {
      flag = -1;
      ERROR("icMean = ", icMean, "\t", count);
      break;
    }
    icMean /= n;
    // icMean /= NP;

    // INFORM(count, "\t", ifMean, "\t", icMean);
    for (size_t c = 0; c < NC; c++)
      Fc[c] = iFc[c] < 0 ? -1 : iFc[c] / ifMean;
    for (size_t p = 0; p < NP; p++)
      Cp[p] = iCp[p] < 0 ? -1 : iCp[p] / icMean;

    if ((1.0 - delta) * cMean <= icMean && icMean <= (1.0 + delta) * cMean
        && (1.0 - delta) * fMean <= ifMean
        && ifMean <= (1.0 + delta) * fMean) {
      // DBG(count);
      break;
    }
    fMean = ifMean;
    cMean = icMean;
    // if (count % 1000 == 0)
    // DBG(count, "\tfm ", fMean, "\tcm ", cMean);
  }
  for (size_t c = 0; c < NC; c++)
    if (iFc[c] < 0)
      Fc[c] = 0;
  for (size_t p = 0; p < NP; p++)
    if (iCp[p] < 0)
      Cp[p] = 0;

  return flag;
}

template <typename T, typename T2>
int network::fitness_complexity::filter_data1_code1(const char* d0File,
    const char* code0File, const char* codeFile, const char* dFile)
{
  std::vector<T> d0, d;
  std::vector<T2> code0, code;
  _ERR(common::read1_0(d0File, d0));
  _ERR(common::read1_0(code0File, code0));
  _ERR(common::read1_0(codeFile, code));
  d.resize(code.size());
  for (size_t i = 0; i < code.size(); ++i)
    for (size_t j = 0; j < code0.size(); ++j) {
      if (code[i] == code0[j]) {
        d[i] = d0[j];
        break;
      }
    }
  _ERR(common::save1(dFile, d, '\n'));
  return 0;
}

template <typename T, typename T2>
int filter_data2_code1(const char* d0File, const char* code0File,
    const char* codeFile, const char* dFile, const size_t n1, const size_t n2)
{
  std::vector<std::vector<T>> d0, d;
  std::vector<T2> code0, code;
  _ERR(common::read2_0(d0File, d0));
  _ERR(common::read1_0(code0File, code0));
  _ERR(common::read1_0(codeFile, code));
  d.resize(code.size());
  for (size_t i = 0; i < code.size(); ++i)
    for (size_t j = 0; j < code0.size(); ++j) {
      if (code[i] == code0[j]) {
        d[i].assign(d0[j].begin() + n1, d0[j].beign() + n2);
        break;
      }
    }
  _ERR(common::save2(dFile, d, '\n'));
  return 0;
}

template <typename T, typename T2>
int network::fitness_complexity::filter_data2_code2(const char* d0File,
    const char* code0File, const char* codeFile, const char* dFile_dir,
    const char* dFile_dir2, const size_t y1, const size_t y2, const size_t y0)
{
  std::vector<std::vector<T>> d0, d;
  std::vector<T> d2;
  std::vector<T2> code0, code;
  std::string name = dFile_dir;
  _ERR(common::read2_0(d0File, d0));
  _ERR(common::read1_0(code0File, code0));
  _ERR(common::read1_0(codeFile, code));
  d.resize(code.size());
  for (size_t i = 0; i < code.size(); ++i) {
    d[i].resize(y2 - y1);
    bool flag = false;
    for (size_t j = 0; j < code0.size(); ++j) {
      if (code[i] == code0[j]) {
        flag = true;
        d[i].assign(&d0[j][y1 - y0], &d0[j][y2 - y0]);
        // for (size_t y = y1; y < y2; ++y)
        // d[i][y - y1] = d0[j][y - y0];
        break;
      }
    }
    if (!flag) {
      INFORM(code[i], " not found!");
    }
  }
  d2.resize(code.size());
  for (size_t y = y1; y < y2; ++y) {
    for (size_t i = 0; i < code.size(); ++i)
      d2[i] = d[i][y - y1];
    _ERR(common::save1(
        (name + std::to_string(y) + dFile_dir2).c_str(), d2, '\n'));
  }
  return 0;
}

// ********************************************************
#endif // ACT_FITNESS_COMPLEXITY
#endif // _H
