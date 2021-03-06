#include "filter_OEC_sitc_rev2.h"
#ifdef MAIN_FITNESS_COMPLEXITY_FILTER

#include "../../common/common.h"
#include "../../network/networks.h"
using namespace std;
using namespace common;
using namespace network;

// *****************************************************
int main_func::fitness_complexity::filter(int argc, char** argv)
{
  const string iso_cCodeFile
      = DIR_INFO + "0.country.iso3166-1.code.txt",
      iso_cCode3cFile = DIR_INFO + "0.country.iso3166-1.code3cU.txt",
      iso_cNameFile = DIR_INFO + "0.country.iso3166-1.name.txt",
      epAll_File0 = DIR_DATA0 + "year_origin_sitc_rev2.txt",
      epAll_cCodeFile0 = DIR_INFO + "0.country.trade.1962-2014.code.txt",
      epAll_cNameFile0 = DIR_INFO + "0.country.trade.1962-2014.name.txt",
      epAll_pCodeFile0 = DIR_INFO + "0.product.trade.1962-2014.code4d.txt",
      epAll_pNameFile0 = DIR_INFO + "0.product.trade.1962-2014.name.txt",
      epAll_cCodeFile = DIR_INFO + "1.export.country." + to_string(YEAR1)
      + "-" + to_string(YEAR2) + ".code.txt",
      epAll_cCode3cFile = DIR_INFO + "1.export.country." + to_string(YEAR1)
      + "-" + to_string(YEAR2) + ".code3c.txt",
      epAll_pCodeFile = DIR_INFO + "1.export.product." + to_string(YEAR1)
      + "-" + to_string(YEAR2) + ".code4d.txt",
      epAll_pnameFile = DIR_INFO + "1.export.product." + to_string(YEAR1)
      + "-" + to_string(YEAR2) + ".name.txt",
      epAll_dir = DIR_DATA0 + "1.export." + to_string(YEAR1) + "-"
      + to_string(YEAR2) + ".",
      gdp_File0 = DIR_DATA0 + "0.gdp.country.1970-2016.txt",
      gdp_cCodeFile0 = DIR_INFO + "0.country.gdp.1970-2016.code.txt",
      gdp_cNameFile0 = DIR_INFO + "0.country.gdp.1970-2016.name.txt",
      gdpPpc_File0 = DIR_DATA0 + "0.gdpPpc.country.1970-2016.txt",
      gdpPpc_cCodeFile0 = DIR_INFO + "0.country.gdpPpc.1970-2016.code.txt",
      gdpPpc_cNameFile0 = DIR_INFO + "0.country.gdpPpc.1970-2016.name.txt",
      epGdp_cCodeFile0 = DIR_INFO + "1.country.trade.gdp." + to_string(YEAR1)
      + "-" + to_string(YEAR2) + ".code.txt",
      continent_File0 = DIR_INFO + "0.country.continent.val.txt",
      continent_nameFile0 = DIR_INFO + "0.country.continent.name.txt",
      continent_codeFile0 = DIR_INFO + "0.country.continent.code.txt",
      cCodeFile
      = DIR_INFO + "2.country.trade.gdp." TOSTRING(MAIN_FILTER) ".code.txt",
      cNameFile
      = DIR_INFO + "2.country.trade.gdp." TOSTRING(MAIN_FILTER) ".name.txt",
      pCodeFile
      = DIR_INFO + "2.product.trade.gdp." TOSTRING(MAIN_FILTER) ".code4d.txt",
      pNameFile
      = DIR_INFO + "2.product.trade.gdp." TOSTRING(MAIN_FILTER) ".name.txt",
      continentFile
      = DIR_INFO + "2.country.continent." TOSTRING(MAIN_FILTER) ".val.txt",
      cSum_dir2 = ".export.sum.country.txt",
      pSum_dir2 = ".export.sum.product.txt", gdp_dir2 = ".country.gdp.txt",
      gdpPpc_dir2 = ".country.gdpPpc.txt";
  const NodeType YEAR0 = 1970;

  // 筛选进出口数据的国家和产品名
  if (1) {
    // get countries' and products' names
    _ERR(trade_name_OEC(epAll_File0.c_str(), iso_cCodeFile.c_str(),
        iso_cCode3cFile.c_str(), epAll_cCodeFile.c_str(),
        epAll_cCode3cFile.c_str(), epAll_pCodeFile.c_str(), YEAR1,
        YEAR2 + 1));

    // sum export data
    _ERR(sum_trade_OEC(epAll_File0.c_str(), epAll_cCode3cFile.c_str(),
        epAll_pCodeFile.c_str(), epAll_dir.c_str(), YEAR1, YEAR2 + 1));

    // 筛选进出口和 gdp 的共同国家
    _ERR(trade_gdp_country_code_OEC(epAll_cCodeFile.c_str(),
        gdp_cCodeFile0.c_str(), epGdp_cCodeFile0.c_str()));

    // 剔除 export 和 gdp 0 值国家和产品
    _ERR(export_gdp_0_OEC(epAll_dir.c_str(), YEAR1, YEAR2 + 1,
        epAll_pCodeFile.c_str(), epAll_cCodeFile.c_str(),
        epAll_cCode3cFile.c_str(), gdp_File0.c_str(), 1970,
        gdp_cCodeFile0.c_str(), epGdp_cCodeFile0.c_str(), cCodeFile.c_str(),
        pCodeFile.c_str(), MAIN_FILTER));

    _ERR(code2name(iso_cNameFile.c_str(), iso_cCodeFile.c_str(),
        cCodeFile.c_str(), cNameFile.c_str()));

    _ERR(code2name(epAll_pNameFile0.c_str(), epAll_pCodeFile0.c_str(),
        pCodeFile.c_str(), pNameFile.c_str()));

    // 输出可用进出口，用于进一步分析
    _ERR(data_export_OEC(epAll_dir.c_str(), epAll_cCodeFile.c_str(),
        epAll_pCodeFile.c_str(), cCodeFile.c_str(), pCodeFile.c_str(), YEAR1,
        YEAR2 + 1, DIR_DATA.c_str(), ep_dir2.c_str()));

    /*
      // 剔除人口小于 1200E3 的国家 510
      _ERR(population_OEC(
          (DIR_DATA0 + "0.population.1950-2015.txt").c_str(),
          YEAR_FILTER - 1950,
          (DIR_INFO + "0.country.population.code.txt").c_str(),
          (DIR_INFO + "2.country.trade.gdp.not0.code.txt").c_str(), 1200,
          (DIR_INFO + "3.country.population.code.txt").c_str()));

      // 剔除进出口小于 1E6 的国家 & Iraq(368),Chad(148),Macau(446)
      _ERR(trade_OEC((DIR_DATA0 + "1.export.all.").c_str(), 2006, 2008,
          (DIR_INFO + "0.country.trade.code.iso3166-1.txt").c_str(),
          (DIR_INFO + "2.country.population.code.iso3166-1.txt").c_str(), 1E6,
          (DIR_INFO + "3.country.trade.code.iso3166-1.txt").c_str()));
    */

    _ERR(sum_export(DIR_DATA.c_str(), ep_dir2.c_str(), YEAR1, YEAR2 + 1,
        DIR_DATA.c_str(), cSum_dir2.c_str(), DIR_DATA.c_str(),
        pSum_dir2.c_str()));
  }
  {
    _ERR((filter_data2_code2<string, NodeType>(gdp_File0.c_str(),
        gdp_cCodeFile0.c_str(), cCodeFile.c_str(), DIR_DATA.c_str(),
        gdp_dir2.c_str(), YEAR1, YEAR2 + 1, YEAR0)));
    _ERR((filter_data2_code2<string, NodeType>(gdpPpc_File0.c_str(),
        gdpPpc_cCodeFile0.c_str(), cCodeFile.c_str(), DIR_DATA.c_str(),
        gdpPpc_dir2.c_str(), YEAR1, YEAR2 + 1, YEAR0)));
    filter_data1_code1<NodeType, NodeType>(continent_File0.c_str(),
        continent_codeFile0.c_str(), cCodeFile.c_str(),
        continentFile.c_str());
  }

  return 0;
}

// ******************************************************
#endif
