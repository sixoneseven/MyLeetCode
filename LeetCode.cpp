// LeetCode.cpp : �������̨Ӧ�ó������ڵ㡣
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
			for (int j = i; j<numsSize - 1; j++){ //˳���ƶ�
				*(nums + j) = *(nums + j + 1);
			}
			*(nums + numsSize - 1) = val;
			i--; //�ƶ�������Ҫ�ӵ�ǰλ�����¿�ʼ����
			numsSize--;
		}
	}
	return numsSize;
}
#endif



#if 1
int removeElement(int* nums, int numsSize, int val) {
	int j = 0; //��ָ��
	for (int  i = 0; i <numsSize; i++)
	{
		if (val!=nums[i])
		{
			nums[j] = nums[i];  //��ָ��������Ѱ��val��������ָ������ָ��Ӧ������λ��
			j++;
		}
	}
	return j;
}
#endif

#if 0
int removeDuplicates(int* nums, int numsSize) {
	int i=0; //��ָ��
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
//�ظ�����ֻ����1��
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

//�ظ����ֱ������2��

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
/*���Ӷ�ΪO(kn)*/
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
	reverse(nums, 0, numsSize - 1); //���巭ת
	reverse(nums, 0, k%numsSize - 1); //ǰ��k%numssize�����ַ�ת
	reverse(nums, k%numsSize, numsSize - 1); //ʣ�����ַ�ת
}


/*Ѱ����С������*/
int firstMissingPositive(int* nums, int numsSize) {
	/*
	����˼�룺�����鱾ʡ����keyֵΪ0-numsSize��map����
	Ͱ����ͬ���ǣ�keyΪi,һ��Ҫ��ӦΪi������������ǣ���ô
	Ҫô����nums[i]Ϊλ�����������ֽ�����������С�򲻶���
	���nums[nums[i]]=nums[i]����Ҫ����),��������±���
	����һ�����ͻ�ĵط����Ķ�
	*/

	if (0 == numsSize) return 1;
	if (1 == numsSize){
		if (nums[0] != 1) return 1; //�ӿ������ٶȣ����ҷ�����ѡ����ֹ��������[2147483647]�����(int���ܱ�ʾ���������)ȱ�³�����
		else return 2;
	}
	unsigned int ret=0;
	int buff; //����������λ����Ҫʹ��;
	for (int i = 0; i < numsSize; i++)
	{
		if (i!=nums[i])
		{
			if (nums[i]>numsSize - 1 || nums[i]<0||nums[nums[i]] == nums[i]) // Ϊ��������ָ�볬����Χ���߽���ǰ�����������
			{
				continue;
			}
			else
			{
				buff = nums[i];
				nums[i] = nums[buff];
				nums[buff] = buff;
				i--; //����֮����Ҫ��������
			}
		}
	}

	//��ѡ��Ҳ���ѵ�
	for (int  i = 1; i < numsSize; i++) //��2��ʼ����һ���������ж�
	{
		if (i!=nums[i])
		{
			ret = i;
			break;
		}
	}
	if (ret==0) //��index=1��Index=numsSize-1��û����:��index��1��ʼ����1,2�Ľṹ
	{
		if (nums[0]<=0) //[0,1,2]����[-1,1,2]
		{
			ret = nums[numsSize - 1] + 1; //����3
		}
		else  //[3,1,2] ����[4,1,2]
		{
			if (nums[0]-nums[numsSize-1]>1) //[4,1,2]�����
			{
				ret = nums[numsSize - 1]+1;
			}
			else{ //[2,1,2]����[3,1,2]
				ret = nums[0] + 1;
			}
		}
	}
	return ret;
}

/*�������*/
/**
* Return an array of arrays.
* The sizes of the arrays are returned as *columnSizes array.
* Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
*/
int** generate(int numRows, int** columnSizes) {
	if (0 == numRows) return columnSizes;
	//��i�У���n=i+1��������0����1������1����2��������
	//���У�j=0���±��j=n-1=i�ĵ��±��ʾ������ÿһ�е���β�����������п����غϣ���1
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
/*�����������*/
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
/*�������ȡN��*/
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


/*������*/
/*
����ͶƱ�㷨:
�����뿼���������Ħ��ͶƱ���⣬�ҳ�һ�����������г��ִ�����������1/2�����֣����Ҽ����������һ�����ڣ���
��Ȼ�������ֻ������һ����Ħ��ͶƱ�㷨�ǻ��������ʵ��ÿ�δ�������ѡ����������ͬ������ɾ���������Ϊ������������
���ʣ��һ�����ֻ򼸸���ͬ�����֣����ǳ��ִ�����������һ����Ǹ�����������ͬ�����ʵ�����ﲻ֤����~
���ߣ�����ϲ
���ӣ�https://www.zhihu.com/question/49973163/answer/235921864
��Դ��֪��
����Ȩ���������С���ҵת������ϵ���߻����Ȩ������ҵת����ע��������
*/

#if 0
int majorityElement(int* nums, int numsSize) {
	if (0 == numsSize) return 0;
	int TmpDate = nums[0]; //��ʼ��,��һ�����ӷŽ�ȥ
	int TmpDateCunt = 1; //���޷���������������������
	int j = 0;
	while (j<numsSize)
	{
		if (TmpDate==nums[j])
		{
			if (j!=0) TmpDateCunt++; //�׸����ü���;                                                       
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
		j++; //���ڲ��ȵ�������ô�j�������ƶ�һ�Σ�ָ��TmpDate�ĺ�һ��
	}
	return TmpDateCunt ? TmpDate : 0;
}
#endif

#if 0

int majorityElement(int* nums, int numsSize) {
	if (0 == numsSize) return 0;
	int Data=nums[0];
	int j = 0; //˫ָ�룬ָ��Data���ڵ�����:����Ŀû��Ҫ��λ�ã�������ʵj�ǿ���ʡ�Եģ���Ϊ���Ĵ�����Կ�����8�д����ʾ��
	int DataCunt = 1;
	for (int  i = 0; i < numsSize-1; i++)
	{
		if (Data == nums[i]){
			if (j!=i) DataCunt++;
			else{
				continue;
			}
		}else if (!--DataCunt){
				j = i + 1; //1 2 1 2 �����
				Data = nums[j];
				DataCunt = 1; //���¿�ʼ����
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


���������������ִ�������n/3�������������޶���ʱ��Ϳռ临�Ӷȣ�
��ô�Ͳ�������Ҳ����ʹ�ù�ϣ����ô���̵���������ֻ��һ�ַ����ܽ��ˣ�
�Ǿ���Ħ��ͶƱ�� Moore Voting�����ַ�����֮ǰ�ǵ���Majority Element ��������Ҳʹ���ˡ�
��Ŀ�и���һ������Ҫ����ʾ���������ȿ��ǿ��ܻ��ж��ٸ��������������˺ܶ����ӷ����ó���
����һ��������ִ�������n/3����������������������֤���ҾͲ����ˣ���Ҳ������ѧרҵ�ġ�
��ô���������Ϣ������ʹ��ͶƱ���ĺ������ҳ�������ѡ��������ͶƱ����Ҫ���������
��һ�����ҳ�������ѡ�������ڶ����������ͶƱ��֤��������ѡ�����Ƿ�Ϊ�������ɣ�
ѡ��ѡ����������ǰ����ƪMajority Element ������һ��������֮ǰ������Ŀ���޶���һ�������������ڣ�
�ʶ�ʡ������֤��ѡ�����Ĳ��裬�����ȴû�������޶���������Ҫ����������ܲ����ڣ�����Ҫ����֤����������*/
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
			else --cm, --cn; //ע����ǣ�����һ������Ӧ�ܹ���ȥ������
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
Hָ����

*/
#if 0
/*������������û����������*/
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
/*���������������е����*/
int hIndex(int* citations, int citationsSize) {
	if (0 == citationsSize) return 0;
	int numH = 0; //����Hƪ������
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
/*���������������е����*/
//���ֲ��ҵ����
int hIndex(int* citations, int citationsSize){
	if (0 == citationsSize) return 0;
	int numH = 0; //����Hƪ������
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
NO213:�����ظ�Ԫ��
*/
//����
//ps:�鲢�����У�mid=(left+right)/2;left<=x<=mid��mid+1<=x<=right����������
void merge(int *nums, int left, int mid, int right){
	int i = left, j = mid+1, k = 0;
	int *tmpArr = (int *)malloc(sizeof(int)*(right - left + 1)); //��������
	while (i<=mid&&j<=right) nums[i] < nums[j] ? tmpArr[k++] = nums[i++] : tmpArr[k++] = nums[j++];
	while (i<=mid)	tmpArr[k++] = nums[i++]; //��ʱ������ұߵ���������
	while (j <=right)	tmpArr[k++] = nums[j++];//��ʱ�������ߵ���������
	for (int i = 0; i < right-left+1; i++) nums[left + i] = tmpArr[i]; //�����������е����ַŻ�nums������Ϊleft��right��λ��
	free(tmpArr);
}

void MergeSort(int * nums, int left, int mid, int right){
	if (left >= right) return; //ֻ��һ�����ֵ�ʱ�����ţ�ֱ�ӷ���
	MergeSort(nums, left, (left + mid) / 2, mid);
	MergeSort(nums, mid + 1, (mid + 1 + right - 1) / 2, right);
	merge(nums, left, mid, right);
}

bool containsDuplicate(int* nums, int numsSize) {
	if (0 == numsSize) return false;
	bool ret=false;
	MergeSort(nums, 0, (0 + numsSize - 1) / 2, numsSize-1); //������
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
N0219:�����ظ�Ԫ��2
*/
#if 0
class Solution {
public:
	bool containsNearbyDuplicate(vector<int>& nums, int k) {
		int index;
		for (int i = 0; i < nums.size(); i++)
		{
			if (IndexMap[nums[i]]) { //�����Ԫ����map����
				index = IndexMap[nums[i]]-1; //�鿴��Ԫ�ص��±�
				if (abs(index - i)<= k) return true; //�����򷵻�ok
			}
			IndexMap[nums[i]] = i + 1; //map��δ��ֵ������£�Ĭ�Ϸ��ص���0���˴�Ϊ�˺����ȽϷ��㣬����ֵ��1��nums.size();
		}
		return false;
	}
};

#endif

 /* NO121: ������Ʊ */ #if 0 /*�������������͵İ취����*/ int maxProfit(int* prices, int pricesSize) {
	if (0 == pricesSize) return 0;//���Ϊ0�Ļ�����0
	int *subArr = (int *)malloc((pricesSize - 1)*sizeof(int));//����ת��Ϊ�����������ͣ����ö�̬�滮DP��˼������
	for (int i = 0; i < pricesSize - 1; i++)	subArr[i] = prices[i + 1] - prices[i];//���������е�ֵ
	int tmp = 0;
	int maxPro = 0; //�������
	for (int i = 0; i < pricesSize - 1; i++){
		if (tmp + subArr[i] > 0) tmp += subArr[i];
		else tmp = 0;
		maxPro = tmp> maxPro?tmp:maxPro; //���ؽϴ����һ��ֵ
	}
	return maxPro;
}
#else
/*����Ѱ�ҹɼ������Сֵ�İ취����*/
int maxProfit(int* prices, int pricesSize) {
	if (0 == pricesSize) return 0;//���Ϊ0�Ļ�����0
	int minPrice = prices[0];
	int maxPro = 0; //��Ʊ��ʼ���ֵĬ��Ϊ��һ��
	for (int i = 0; i < pricesSize - 1; i++)
	{
		if (prices[i] < minPrice){
			minPrice = prices[i];//���ò���
		}
		if (maxPro<prices[i + 1] - minPrice){
			maxPro = prices[i + 1] - minPrice; //Ѱ��ÿ���ڵ��Ĳ�����Ѿ���Ĳ��ȵ�������
		}
	}
	return maxPro;
}
#endif

#if 0
/*
NO122:������Ʊ2
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