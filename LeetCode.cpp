// LeetCode.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>
#include<vector>
#include<map>
using namespace std;
#if 0
int removeElement(int* nums, int numsSize, int val) {
	int tmp;
	int j;
	for (int i = 0; i<numsSize; i++){
		if (val == *(nums + i)){
			tmp = val;
			for (int j = i; j<numsSize - 1; j++){ //顺序移动
				*(nums + j) = *(nums + j + 1);
			}
			*(nums + numsSize - 1) = val;
			i--; //移动后还是需要从当前位置重新开始检索
			numsSize--;
		}
	}
	return numsSize;
}
#endif



#if 1
int removeElement(int* nums, int numsSize, int val) {
	int j = 0; //慢指针
	for (int  i = 0; i <numsSize; i++)
	{
		if (val!=nums[i])
		{
			nums[j] = nums[i];  //快指针用来搜寻非val的数，慢指针用来指明应该填充的位置
			j++;
		}
	}
	return j;
}
#endif

#if 0
int removeDuplicates(int* nums, int numsSize) {
	int i=0; //慢指针
	for (int j = 0; j < numsSize; j++)
	{
		if (nums[i] < nums[j]){
			nums[i + 1] = nums[j];
			i++;
			j = i;
		}
	}
	return i+1;
}
#endif

#if 0
//重复数字只保留1个
int removeDuplicates(int* nums, int numsSize) {
	int i = 0, j = 0;
	if (0 == numsSize) return 0;
	for (i = 0; i < numsSize-1; i++)
	{
		if (nums[i] != nums[i + 1]){
			nums[j++] = nums[i];
		}
	}
	nums[j] = nums[numsSize - 1];
	return j + 1;
}
#endif

//重复数字保留最多2个

int removeDuplicates(int* nums, int numsSize) {
	if (0 == numsSize || 1 == numsSize || 2 == numsSize)
	{
		return numsSize;
	}
	int i = 1;
	int j = 1;

	for (int j = 2; j < numsSize; j++)
	{
		if (nums[i]==nums[j])
		{
			if (nums[i] != nums[i - 1]){
				nums[++i] = nums[j];
			}
			else
			{
				nums[i] = nums[j];
			}
		}
		else
		{
			nums[++i] = nums[j];
		}
	}

	return i + 1;
}

#if 0
/*复杂度为O(kn)*/
void rotate(int* nums, int numsSize, int k) {
	if (0==numsSize)
	{
		return;
	}

	int buff;
	for (int  i = 0; i < k%numsSize; i++)
	{
		buff = nums[numsSize - 1];
		for (int j = numsSize - 2; j >= 0; j--)
		{
			nums[j + 1] = nums[j];
		}
		nums[0] = buff;
	}
}
#endif


void reverse(int *nums, int begin, int end){
	int buff;
	while (begin<end)
	{
		buff = nums[begin];
		nums[begin++] = nums[end];
		nums[end--] = buff;
	}
}

void rotate(int* nums, int numsSize, int k) {
	if (0==numsSize||0==k)
	{
		return;
	}
	reverse(nums, 0, numsSize - 1); //整体翻转
	reverse(nums, 0, k%numsSize - 1); //前面k%numssize个数字翻转
	reverse(nums, k%numsSize, numsSize - 1); //剩余数字翻转
}


/*寻找最小的数字*/
int firstMissingPositive(int* nums, int numsSize) {
	/*
	核心思想：将数组本省当作key值为0-numsSize的map表，和
	桶排序不同的是，key为i,一定要对应为i的数，如果不是，那么
	要么和以nums[i]为位置索引的数字交换（超出大小则不动，
	如果nums[nums[i]]=nums[i]则需要跳过),最后再重新遍历
	看第一个起冲突的地方是哪儿
	*/

	if (0 == numsSize) return 1;
	if (1 == numsSize){
		if (nums[0] != 1) return 1; //加快运行速度，并且方便挑选，防止出现输入[2147483647]的情况(int所能表示的最大数据)缺德出题人
		else return 2;
	}
	unsigned int ret=0;
	int buff; //交换两个数位置需要使用;
	for (int i = 0; i < numsSize; i++)
	{
		if (i!=nums[i])
		{
			if (nums[i]>numsSize - 1 || nums[i]<0||nums[nums[i]] == nums[i]) // 为负数或者指针超出范围或者交换前后两个数相等
			{
				continue;
			}
			else
			{
				buff = nums[i];
				nums[i] = nums[buff];
				nums[buff] = buff;
				i--; //交换之后需要重新来看
			}
		}
	}

	//挑选：也是难点
	for (int  i = 1; i < numsSize; i++) //从2开始，第一个供后续判断
	{
		if (i!=nums[i])
		{
			ret = i;
			break;
		}
	}
	if (ret==0) //从index=1到Index=numsSize-1都没问题:如index从1开始后面1,2的结构
	{
		if (nums[0]<=0) //[0,1,2]或者[-1,1,2]
		{
			ret = nums[numsSize - 1] + 1; //返回3
		}
		else  //[3,1,2] 或者[4,1,2]
		{
			if (nums[0]-nums[numsSize-1]>1) //[4,1,2]的情况
			{
				ret = nums[numsSize - 1]+1;
			}
			else{ //[2,1,2]或者[3,1,2]
				ret = nums[0] + 1;
			}
		}
	}
	return ret;
}

/*杨辉三角*/
/**
* Return an array of arrays.
* The sizes of the arrays are returned as *columnSizes array.
* Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
*/
int** generate(int numRows, int** columnSizes) {
	if (0 == numRows) return columnSizes;
	//第i行，有n=i+1个数，如0行有1个数，1行有2个数。。
	//其中，j=0的下标和j=n-1=i的的下标表示的数是每一行的首尾，这两个数有可能重合，是1
	for (int  i = 0; i < numRows; i++)
	{
		for (int  j = 0; j < i+1; j++)
		{
			if (0==j||i==j){
				columnSizes[i][j] = 1;
				continue;
			}
			else
			{
				columnSizes[i][j] = columnSizes[i - 1][j - 1] + columnSizes[i - 1][j];
			}
		}
	}
	return columnSizes;
}

#if 0
/*生成杨辉三角*/
class Solution {
public:
	vector<vector<int>> generate(int numRows) {
		vector<int> rows;
		vector<vector<int>> RetArr;
		if (0 == numRows) return RetArr;
		for (int i = 0; i < numRows; i++){
			rows.assign(i + 1, 0);
			RetArr.push_back(rows); 
			for (int j = 0; j < i + 1; j++){
				if (0 == j || i == j){
					RetArr[i][j] = 1;
					continue;
				}else{
					RetArr[i][j] = RetArr[i - 1][j - 1] + RetArr[i - 1][j];
				}
			}
			rows.clear();
		}
		return RetArr;
	}
};
#endif

#if 0
/*杨辉三角取N行*/
class Solution {
private:
	int Index;
public:
	vector<int> getRow(int rowIndex) {
		Index = rowIndex;
		vector<int> rowsA(rowIndex + 1, 0); 
		vector<int>	rowsB(rowIndex + 1, 0);
		return rowsFunc(rowsA, rowsB, 0);
	}
	vector<int> rowsFunc(vector<int> rows_UP, vector<int> rows_DOWN,int rows){
		if (Index + 1 == rows)return rows_UP;
		for (int j = 0; j <= rows; j++){
			if (0 == j || rows == j){
				rows_DOWN[j] = 1;
				continue;
			}
			else{
				rows_DOWN[j] = rows_UP[j - 1] + rows_UP[j];
			}
		}
		return rowsFunc(rows_DOWN, rows_UP, rows + 1);
	}
};

#endif


/*求众数*/
/*
采用投票算法:
首先请考虑最基本的摩尔投票问题，找出一组数字序列中出现次数大于总数1/2的数字（并且假设这个数字一定存在）。
显然这个数字只可能有一个。摩尔投票算法是基于这个事实：每次从序列里选择两个不相同的数字删除掉（或称为“抵消”），
最后剩下一个数字或几个相同的数字，就是出现次数大于总数一半的那个。请首先认同这个事实，这里不证明了~
作者：喝七喜
链接：https://www.zhihu.com/question/49973163/answer/235921864
来源：知乎
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。
*/

#if 0
int majorityElement(int* nums, int numsSize) {
	if (0 == numsSize) return 0;
	int TmpDate = nums[0]; //初始化,第一个数子放进去
	int TmpDateCunt = 1; //对无法抵消的数字做计数处理
	int j = 0;
	while (j<numsSize)
	{
		if (TmpDate==nums[j])
		{
			if (j!=0) TmpDateCunt++; //首个不用计数;                                                       
		}
		else
		{
			if (j<numsSize-1)
			{
				TmpDate = nums[++j];
				TmpDateCunt--;
			}
			else
			{
				TmpDateCunt--;
			}
		}
		j++; //对于不等的情况，该处j又往后移动一次，指向TmpDate的后一个
	}
	return TmpDateCunt ? TmpDate : 0;
}
#endif

#if 0

int majorityElement(int* nums, int numsSize) {
	if (0 == numsSize) return 0;
	int Data=nums[0];
	int j = 0; //双指针，指向Data所在的数据:但题目没有要求位置，所以其实j是可以省略的，更为简介的代码可以看下面8行代码的示范
	int DataCunt = 1;
	for (int  i = 0; i < numsSize-1; i++)
	{
		if (Data == nums[i]){
			if (j!=i) DataCunt++;
			else{
				continue;
			}
		}else if (!--DataCunt){
				j = i + 1; //1 2 1 2 的情况
				Data = nums[j];
				DataCunt = 1; //重新开始计数
		}
	}
	return DataCunt ? Data : 0;
}
#else
int majorityElement(int* nums, int numsSize) {
	int data = 0,cunt = 0;
	for (int  i = 0; i < numsSize; i++){
		if (0 == cunt) data = nums[i];
		else data == nums[i] ? ++cunt : --cunt;
	}
	return data;
}
#endif 

#if 0
/*


这道题让我们求出现次数大于n/3的众数，而且限定了时间和空间复杂度，
那么就不能排序，也不能使用哈希表，这么苛刻的限制条件只有一种方法能解了，
那就是摩尔投票法 Moore Voting，这种方法在之前那道题Majority Element 求众数中也使用了。
题目中给了一条很重要的提示，让我们先考虑可能会有多少个众数，经过举了很多例子分析得出，
任意一个数组出现次数大于n/3的众数最多有两个，具体的证明我就不会了，我也不是数学专业的。
那么有了这个信息，我们使用投票法的核心是找出两个候选众数进行投票，需要两遍遍历，
第一遍历找出两个候选众数，第二遍遍历重新投票验证这两个候选众数是否为众数即可，
选候选众数方法和前面那篇Majority Element 求众数一样，由于之前那题题目中限定了一定会有众数存在，
故而省略了验证候选众数的步骤，这道题却没有这种限定，即满足要求的众数可能不存在，所以要有验证。代码如下*/
class Solution {
public:
	vector<int> majorityElement(vector<int>& nums) {
		vector<int> res;
		int m = 0, n = 0, cm = 0, cn = 0;
		for (auto &a : nums) {
			if (a == m) ++cm;
			else if (a == n) ++cn;
			else if (cm == 0) m = a, cm = 1;
			else if (cn == 0) n = a, cn = 1;
			else --cm, --cn; //注意的是，这里一个数对应能够消去两个数
		}
		cm = cn = 0;
		for (auto &a : nums) {
			if (a == m) ++cm;
			else if (a == n) ++cn;
		}
		if (cm > nums.size() / 3) res.push_back(m);
		if (cn > nums.size() / 3) res.push_back(n);
		return res;
	}
};

#endif 
#if 0
class Solution {
public:
	vector<int> majorityElement(vector<int>& nums) {
		vector<int> ret;
		int m = 0, n = 0, cm = 0, cn = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == m) cm++;
			else if (nums[i] == n) cn++;
			else if (0 == cm)	m = nums[i],cm=1;
			else if (0 == cn) n = nums[i], cn = 1;
			else	--cm,--cn;
		}

		cm = cn = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] == m) ++cm;
			else if (nums[i] == n) ++cn;
		}
		if (cm>nums.size() / 3) ret.push_back(m);
		if (cn>nums.size() / 3) ret.push_back(n);
		return ret;
	}
};
#endif 


/*
H指数：

*/
#if 0
/*论文引用数组没有排序的情况*/
int hIndex(int* citations, int citationsSize) {
	int H = 0;
	int cntPaper = 0;  //b
	if (0 == citationsSize) return 0;
	for (H = citationsSize; H > 0; H--)
	{
		for (int j = 0; j < citationsSize; j++)
		{
			if (citations[j] >= H) cntPaper++;
		}
		if (H <= cntPaper) break;
		cntPaper = 0;
	}
	return H;
}
#endif 
#if 0
/*论文数组升序排列的情况*/
int hIndex(int* citations, int citationsSize) {
	if (0 == citationsSize) return 0;
	int numH = 0; //大于H篇的论文
	int H = citationsSize;
	while (H >= 0)
	{
		for (int i = citationsSize-1; i >= 0; i--)
		{
			if (citations[i] >= H) numH++;
			else break;
		}
		if (numH >= H) break;
		H--, numH = 0;
	}
	return H;
}
#endif
/*论文数组升序排列的情况*/
//二分查找的情况
int hIndex(int* citations, int citationsSize){
	if (0 == citationsSize) return 0;
	int numH = 0; //大于H篇的论文
	int beginH = 0, endH = citationsSize, midH; 
	int H;
	while (beginH <= endH)
	{
		numH = 0;
		midH = (beginH + endH) / 2;
		for (int i = citationsSize-1; i >=0 ; i--)
		{
			if (citations[i] >= midH) numH++;
			else break;
		}
		if (numH >= midH) {
			H = midH;
			beginH = midH + 1;
		}else endH = midH - 1;
	}
	return H;
}


/*
NO213:存在重复元素
*/
//排序
//ps:归并排序中，mid=(left+right)/2;left<=x<=mid和mid+1<=x<=right构成两部分
void merge(int *nums, int left, int mid, int right){
	int i = left, j = mid+1, k = 0;
	int *tmpArr = (int *)malloc(sizeof(int)*(right - left + 1)); //缓存数组
	while (i<=mid&&j<=right) nums[i] < nums[j] ? tmpArr[k++] = nums[i++] : tmpArr[k++] = nums[j++];
	while (i<=mid)	tmpArr[k++] = nums[i++]; //有时候可能右边的数先排完
	while (j <=right)	tmpArr[k++] = nums[j++];//有时候可能左边的数先排完
	for (int i = 0; i < right-left+1; i++) nums[left + i] = tmpArr[i]; //将缓存数组中的数字放回nums中索引为left到right的位置
	free(tmpArr);
}

void MergeSort(int * nums, int left, int mid, int right){
	if (left >= right) return; //只有一个数字的时候不用排，直接返回
	MergeSort(nums, left, (left + mid) / 2, mid);
	MergeSort(nums, mid + 1, (mid + 1 + right - 1) / 2, right);
	merge(nums, left, mid, right);
}

bool containsDuplicate(int* nums, int numsSize) {
	if (0 == numsSize) return false;
	bool ret=false;
	MergeSort(nums, 0, (0 + numsSize - 1) / 2, numsSize-1); //先排序
	for (int i = 0; i < numsSize-1; i++)
	{
		if (nums[i] == nums[i + 1]) {
			ret = true;
			break;
		}
	}
	return ret;
}

/*
N0219:存在重复元素2
*/
#if 0
class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		int index;
		for (int i = 0; i < nums.size(); i++)
		{
			if (IndexMap[nums[i]]) { //如果该元素在map表中
				index = IndexMap[nums[i]]-1; //查看该元素的下标
				if (abs(index - i)<= k) return true; //满足则返回ok
			}
			IndexMap[nums[i]] = i + 1; //map在未赋值的情况下，默认返回的是0，此处为了后续比较方便，索引值从1到nums.size();
		}
		return false;
	}
};

#endif

 /* NO121: 买卖股票 */ #if 0 /*采用子数组最大和的办法来做*/ int maxProfit(int* prices, int pricesSize) {
	if (0 == pricesSize) return 0;//如果为0的话返回0
	int *subArr = (int *)malloc((pricesSize - 1)*sizeof(int));//问题转化为最大子序列求和，采用动态规划DP的思想来做
	for (int i = 0; i < pricesSize - 1; i++)	subArr[i] = prices[i + 1] - prices[i];//计算子序列的值
	int tmp = 0;
	int maxPro = 0; //最大利润
	for (int i = 0; i < pricesSize - 1; i++){
		if (tmp + subArr[i] > 0) tmp += subArr[i];
		else tmp = 0;
		maxPro = tmp> maxPro?tmp:maxPro; //返回较大的那一个值
	}
	return maxPro;
}
#else
/*采用寻找股价最大最小值的办法来做*/
int maxProfit(int* prices, int pricesSize) {
	if (0 == pricesSize) return 0;//如果为0的话返回0
	int minPrice = prices[0];
	int maxPro = 0; //股票初始最大值默认为第一个
	for (int i = 0; i < pricesSize - 1; i++)
	{
		if (prices[i] < minPrice){
			minPrice = prices[i];//设置波峰
		}
		if (maxPro<prices[i + 1] - minPrice){
			maxPro = prices[i + 1] - minPrice; //寻找每个节点后的波峰和已经存的波谷的最大距离
		}
	}
	return maxPro;
}
#endif

#if 0
/*
NO122:买卖股票2
*/
int maxProfit(int* prices, int pricesSize){
		
}
#endif




int _tmain(int argc, _TCHAR* argv[]){ 
	int Arr[] = { 1, 2, 3, 4, 5 };
	int size = sizeof(Arr) / sizeof(int);
	int Profit = maxProfit(Arr, size);
	printf("Profit:%d", Profit);
	getchar();
} 