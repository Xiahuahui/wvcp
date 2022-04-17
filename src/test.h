#ifndef TEST_H
#define TEST_H
#ifdef __cplusplus
extern std::vector<int> result_colors;
extern "C"
{
#endif

void test(int** info,int** edges_list,int** weight_list,int** colors,int** para_list);
#ifdef __cplusplus
}
#endif
#endif