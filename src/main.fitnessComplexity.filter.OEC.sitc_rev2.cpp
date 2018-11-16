#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_FILTER

#include "common.h"
#include "networks.h"
using namespace std;
// *****************************************************
int main_fitness_complexity_filter(int argc, char** argv)
{
  const string DIR0 = "data/complexity/OEC.sitc_rev2/",
               DIR_DATA0 = DIR0 + "data0/", DIR_DATA = DIR0 + "data/",
               DIR_INFO = DIR0 + "info/", DIR_COMMON = DIR0 + "dataCommon/";
  const NodeType YEAR1 = 2001, YEAR2 = 2014; // YEAR_FILTER = 2008;

  // 筛选进出口数据的国家和产品名
  // get countries' and products' names
  _ERR(
      filter_trade_name_OEC((DIR_DATA0 + "year_origin_sitc_rev2.txt").c_str(),
          (DIR_INFO + "0.country.iso3166-1.code.txt").c_str(),
          (DIR_INFO + "0.country.iso3166-1.code3cU.txt").c_str(),
          (DIR_INFO + "1.export.country." + to_string(YEAR1) + "-"
              + to_string(YEAR2) + ".code.txt")
              .c_str(),
          (DIR_INFO + "1.export.country." + to_string(YEAR1) + "-"
              + to_string(YEAR2) + ".code3c.txt")
              .c_str(),
          (DIR_INFO + "1.export.product." + to_string(YEAR1) + "-"
              + to_string(YEAR2) + ".code4d.txt")
              .c_str(),
          YEAR1, YEAR2 + 1));

  //_ERR(filter_trade_name_OEC(
  //(DIR_DATA0 + "year_origin_sitc_rev2.txt").c_str(),
  //(DIR_INFO + "0.country.iso3166-1.code.txt").c_str(),
  //(DIR_INFO + "0.country.iso3166-1.code3cU.txt").c_str(),
  //(DIR_INFO + "1.export.country." + to_string(YEAR_FILTER)
  //+ ".code.txt")
  //.c_str(),
  //(DIR_INFO + "1.export.country." + to_string(YEAR_FILTER)
  //+ ".code3c.txt")
  //.c_str(),
  //(DIR_INFO + "1.export.product." + to_string(YEAR_FILTER)
  //+ ".code4d.txt")
  //.c_str(),
  // YEAR_FILTER, YEAR_FILTER + 1));

  // sum export data
  _ERR(filter_sum_trade_OEC((DIR_DATA0 + "year_origin_sitc_rev2.txt").c_str(),
      (DIR_INFO + "1.export.country." + to_string(YEAR1) + "-"
          + to_string(YEAR2) + ".code3c.txt")
          .c_str(),
      (DIR_INFO + "1.export.product." + to_string(YEAR1) + "-"
          + to_string(YEAR2) + ".code4d.txt")
          .c_str(),
      (DIR_DATA0 + "1.export." + to_string(YEAR1) + "-" + to_string(YEAR2)
          + ".")
          .c_str(),
      YEAR1, YEAR2 + 1));

  // 筛选进出口和 gdp 的共同国家
  _ERR(filter_trade_gdp_country_code_OEC(
      (DIR_INFO + "1.export.country." + to_string(YEAR1) + "-"
          + to_string(YEAR2) + ".code.txt")
          .c_str(),
      (DIR_INFO + "0.country.gdp.1970-2016.code.txt").c_str(),
      (DIR_INFO + "1.country.trade.gdp." + to_string(YEAR1) + "-"
          + to_string(YEAR2) + ".code.txt")
          .c_str()));
  // 剔除 export 和 gdp 0 值国家和产品
  _ERR(filter_export_gdp_0_OEC((DIR_DATA0 + "1.export." + to_string(YEAR1)
                                   + "-" + to_string(YEAR2) + ".")
                                   .c_str(),
      YEAR1, YEAR2 + 1,
      (DIR_INFO + "1.export.product." + to_string(YEAR1) + "-"
          + to_string(YEAR2) + ".code4d.txt")
          .c_str(),
      (DIR_INFO + "1.export.country." + to_string(YEAR1) + "-"
          + to_string(YEAR2) + ".code.txt")
          .c_str(),
      (DIR_INFO + "1.export.country." + to_string(YEAR1) + "-"
          + to_string(YEAR2) + ".code3c.txt")
          .c_str(),

      (DIR_DATA0 + "0.gdp.country.1970-2016.txt").c_str(), 1970,
      (DIR_INFO + "0.country.gdp.1970-2016.code.txt").c_str(),

      (DIR_INFO + "1.country.trade.gdp." + to_string(YEAR1) + "-"
          + to_string(YEAR2) + ".code.txt")
          .c_str(),
      (DIR_INFO + "2.country.trade.gdp.not0.code.txt").c_str(),
      (DIR_INFO + "2.product.trade.gdp.not0.code4d.txt").c_str()));

  _ERR(filter_code2name((DIR_INFO + "0.country.iso3166-1.name.txt").c_str(),
      (DIR_INFO + "0.country.iso3166-1.code.txt").c_str(),
      (DIR_INFO + "2.country.trade.gdp.not0.code.txt").c_str(),
      (DIR_INFO + "2.country.trade.gdp.not0.name.txt").c_str()));

  _ERR(filter_code2name(
      (DIR_INFO + "0.product.trade.1962-2014.name.txt").c_str(),
      (DIR_INFO + "0.product.trade.1962-2014.code4d.txt").c_str(),
      (DIR_INFO + "2.product.trade.gdp.not0.code4d.txt").c_str(),
      (DIR_INFO + "2.product.trade.gdp.not0.name.txt").c_str()));

  /*
    // 剔除人口小于 1200E3 的国家 510
    _ERR(filter_population_OEC(
        (DIR_DATA0 + "0.population.1950-2015.txt").c_str(),
        YEAR_FILTER - 1950,
        (DIR_INFO + "0.country.population.code.txt").c_str(),
        (DIR_INFO + "2.country.trade.gdp.not0.code.txt").c_str(), 1200,
        (DIR_INFO + "3.country.population.code.txt").c_str()));

    // 剔除进出口小于 1E6 的国家 & Iraq(368),Chad(148),Macau(446)
    _ERR(filter_trade_OEC((DIR_DATA0 + "1.export.all.").c_str(), 2006, 2008,
        (DIR_INFO + "0.country.trade.code.iso3166-1.txt").c_str(),
        (DIR_INFO + "2.country.population.code.iso3166-1.txt").c_str(), 1E6,
        (DIR_INFO + "3.country.trade.code.iso3166-1.txt").c_str()));
  */

  // 输出可用进出口，用于进一步分析
  _ERR(filter_data_export_OEC((DIR_DATA0 + "1.export." + to_string(YEAR1)
                                  + "-" + to_string(YEAR2) + ".")
                                  .c_str(),
      (DIR_INFO + "1.export.country.2001-2014.code.txt").c_str(),
      (DIR_INFO + "1.export.product.2001-2014.code4d.txt").c_str(),
      (DIR_INFO + "2.country.trade.gdp.not0.code.txt").c_str(),
      (DIR_INFO + "2.product.trade.gdp.not0.code4d.txt").c_str(), YEAR1,
      YEAR2 + 1, (DIR_DATA).c_str(), ".export.txt"

      ));

  return 0;
}

// ******************************************************
#endif
