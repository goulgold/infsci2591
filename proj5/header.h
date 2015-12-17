#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<map>
#include<stack>
#include<vector>
#include<utility>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<math.h>  
using namespace std;

struct TreeNode
{
    int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void FindDeleteString(string &str1, string str2);
vector<int> windowsum(vector<int>nums, int ws);
void PrintVector(vector<int>nums);


//convert string in the format of [1,2,3]

vector<int> string2vector(string s){
    vector<int>res;
    FindDeleteString(s,"[");
    FindDeleteString(s,"]");
    //cout << "string="<<s << endl;

    string delimiter = ",";
    size_t pos = 0;
    std::string token;
    while ((pos = s.find_first_of(delimiter)) != std::string::npos) {
            token = s.substr(0, pos);
            res.push_back(stoi(token));
            //std::cout << token << std::endl;
            s.erase(0, pos + delimiter.length());
    }
    res.push_back(stoi(s));
	//PrintVector(res);
    return res;
}


//delete substring 
void FindDeleteString(string &str1, string str2){

    size_t found = str1.find(str2);
    if(found!=string::npos){
        str1.erase(found, str2.size());
    }

    return;
}

//print vector element by element
void PrintVector(vector<int>nums){
    for(int i=0;i<nums.size();i++){
        cout << nums[i];
        if(i<nums.size()-1)cout << ',';
        else cout <<endl;
    }
    //cout <<endl;
}
//true if two vectors are equal
bool CmpVector(vector<int>v1, vector<int>v2){
    int n1 = v1.size(), n2=v2.size();
    if(n1!=n2)return false;
    if(n1==0 && n2==0)return true;
    for(int i=0;i<n1;i++){
        if(v1[i]!=v2[i])return false;
    }
    return true;


}
