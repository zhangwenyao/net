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
  const NodeType YEAR1 = 2001, YEAR2 = 2014 + 1;

  // 筛选进出口数据的国家和产品名
  if (1) {
    ERROR_TEST(filter_trade_name_OEC(
        (DIR_DATA0 + "year_origin_sitc_rev2.txt").c_str(),
        (DIR_INFO + "country.names3c.export.txt").c_str(),
        (DIR_INFO + "product.names4d.export.txt").c_str(), YEAR1, YEAR2));

    // sum export data
    ERROR_TEST(filter_sum_trade_OEC(
        (DIR_DATA0 + "year_origin_sitc_rev2.txt").c_str(),
        (DIR_INFO + "country.names3c.export.txt").c_str(),
        (DIR_INFO + "product.names4d.export.txt").c_str(), DIR_DATA0.c_str(),
        YEAR1, YEAR2));

    // 剔除 0 值国家和产品
    ERROR_TEST(filter_index_export_0_OEC((DIR_DATA0).c_str(),
        (DIR_INFO + "country.index.export.not0.txt").c_str(),
        (DIR_INFO + "product.index.export.not0.txt").c_str(),
        (DIR_INFO + "country.names3c.export.txt").c_str(),
        (DIR_INFO + "product.names4d.export.txt").c_str(), YEAR1, YEAR2));

    // 输出可用进出口，用于进一步分析
    ERROR_TEST(filter_data_export((DIR_DATA0).c_str(),
        (DIR_INFO + "country.index.export.not0.txt").c_str(),
        (DIR_INFO + "product.index.export.not0.txt").c_str(),
        DIR_DATA.c_str(), YEAR1, YEAR2));

    // 筛选进出口和 gdp 的共同国家名
    ERROR_TEST(filter_export_gdp_country_name(
        (DIR_INFO + "country.namesFull.trade.txt").c_str(),
        (DIR_INFO + "country.namesFull.gdp.txt").c_str(),
        (DIR_INFO + "country.namesFull.common").c_str()));

    // 手动查找相同国家，得到 same.trade.txt 和 same.gdp.txt，再执行
    // 合并国家名，得到下标 trade.index 和 gdp.index
    ERROR_TEST(
        filter_index_same_all_OEC((DIR_INFO + "country.namesFull").c_str()));
    // 剔除 0 值国家
    ERROR_TEST(filter_index_same_not0_OEC(
        (DIR_INFO + "country.namesFull.common").c_str(),
        (DIR_INFO + "country.index.export.not0.txt").c_str()));

  }

  return 0;
}

// ******************************************************
#endif
