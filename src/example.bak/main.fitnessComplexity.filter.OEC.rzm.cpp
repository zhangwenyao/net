#include "main.h"
#ifdef MAIN_FITNESS_COMPLEXITY_FILTER

#include "common.h"
#include "networks.h"
using namespace std;
// *****************************************************
int main_fitness_complexity_filter(int argc, char** argv)
{
  const string DIR0 = "data/complexity/OEC.rzm/",
               DIR_DATA0 = DIR0 + "data0/", DIR_DATA = DIR0 + "data/",
               DIR_INFO = DIR0 + "info/";
  const NodeType YEAR1 = 2001, YEAR2 = 2014 + 1;

  if(0){}
  // 筛选进出口数据的国家和产品名
  for (unsigned year = 1995; year <= 2014; ++year) {
    cout << year << endl;
    ERROR_TEST(filter_trade_name_OEC(
        (string("data/DataSet/NBER-UN - WORLD TRADE FLOWS/NBER-UN/wtf")
            + (year % 100 == 0 ? "0" : "") + to_string(year % 100) + ".txt")
            .c_str(),
        (DIR_INFO + "country.namesCode.export2.all.txt").c_str(),
        (DIR_INFO + "product.names4c.export2.all.txt").c_str(),
        (DIR_INFO + "country.namesCode.export2.all.txt").c_str(),
        (DIR_INFO + "product.names4c.export2.all.txt").c_str()));
  }

  /*
  // sum export data
  for (unsigned year = 1962; year <= 2000; ++year) {
    cout << year << endl;
    ERROR_TEST(filter_sum_trade_NBER_wtf(
        (string("data/DataSet/NBER-UN - WORLD TRADE FLOWS/NBER-UN/wtf")
            + (year % 100 == 0 ? "0" : "") + to_string(year % 100) + ".txt")
            .c_str(),
        (DIR_INFO + "country.namesCode.export2.all.txt").c_str(),
        (DIR_INFO + "product.names4c.export2.all.txt").c_str(),
        (DIR_DATA0 + to_string(year) + ".export.txt").c_str()));
  }
  */

  // 剔除 0 值国家和产品
  ERROR_TEST(filter_index_export_0_NBER_wtf((DIR_DATA0).c_str(),
          (DIR_INFO + "country.index.export2.not0.txt").c_str(),
          (DIR_INFO + "product.index.export2.not0.txt").c_str()));

  /*
  // 筛选进出口和 gdp 的共同国家名
  filter_sum_trade_OEC((DIR_DATA0 + "year_origin_sitc_rev2.txt").c_str(),
      (DIR_INFO + "country.nameCcode.export.txt").c_str(),
      (DIR_INFO + "product.names4c.export.txt").c_str(), (DIR_DATA).c_str(),
      1995, 1996);

  // 剔除 0 值国家和产品
  filter_index_export_0((DIR_DATA0).c_str(),
      (DIR_INFO + "country.index.export.not0.txt").c_str(),
      (DIR_INFO + "product.index.export.not0.txt").c_str(), 2000, 2014);

  // 输出可用进出口，用于进一步分析
  filter_data_export((DIR_DATA0).c_str(), (DIR_INFO + "country.index.export.not0.txt").c_str(),
      (DIR_INFO + "product.index.export.not0.txt").c_str(), DIR_DATA.c_str(),
      2000, 2010);
  */

  /*
  // 筛选进出口和 gdp 的共同国家名
  filter_export_gdp_country_name((DIR_DATA0 +
  "country_names.txt").c_str(),
      (DIR_DATA0 + "country.names3c.export.txt").c_str(),
      (DIR_DATA0 + "country.namesFull.gdp.txt").c_str(),
      (DIR_DATA0 + "country.namesFull").c_str());
  // 手动查找相同国家，得到 same.export.txt 和
  same.gdp.txt，再执行下面步骤
  filter_index_same_all((DIR_DATA0 + "country.namesFull").c_str(),
      (DIR_DATA0 + "country.index.same.all").c_str());

  // 剔除 gdp=0 国家
  filter_index_gdp_0((DIR_DATA0 + "gdp.1995-2014.txt").c_str(),
      (DIR_DATA0 + "country.index.gdp.not0.txt").c_str());

  // 输出可用进出口和 gdp 下标
  filter_index_export_gdp(
      (DIR_DATA0 + "country.index.same.all.gdp.txt").c_str(),
      (DIR_DATA0 + "country.index.gdp.not0.txt").c_str(),
      (DIR_DATA0 + "country.index.gdp.data.txt").c_str(),
      (DIR_DATA0 + "country.index.same.all.export.txt").c_str(),
      (DIR_DATA0 + "country.index.export.not0.txt").c_str(),
      (DIR_DATA0 + "country.index.export.data.txt").c_str());

  // 输出可用进出口和 gdp 数据，用于进一步分析
  filter_data((DIR_DATA0 + "gdp.1995-2014.txt").c_str(),
      (DIR_DATA0 + "country.index.gdp.data.txt").c_str(),
      (DIR_DATA0 + "hs92.export/").c_str(),
      (DIR_DATA0 + "country.index.export.data.txt").c_str(),
      (DIR_DATA0 + "product.index.export.not0.txt").c_str(),
      DIR_DATA.c_str());
  */

  SHOW_TIME(cout); // 显示系统时间
  return 0;
}

// ******************************************************
#endif
