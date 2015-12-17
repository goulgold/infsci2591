//MirrorTree.cc

//#include"Tree.h"
#include"Tree.h"

//if two trees are mirror
bool IsMirrorTree(TreeNode* tree1, TreeNode* tree2);
//return mirrored tree
TreeNode* MirrorTree(TreeNode* root);



TreeNode* MirrorTree(TreeNode* root)
{
	TreeNode* mirror;
	if(root==NULL)return NULL;
	mirror = new TreeNode(root->val);
	mirror->left = MirrorTree(root->right);
	mirror->right = MirrorTree(root->left);
	return mirror;
}

bool IsMirrorTree(TreeNode* tree1, TreeNode* tree2)
{
	if((tree1==NULL)&&(tree2==NULL))return true;
	if((tree1==NULL)^(tree2==NULL))return false;
	if(tree1->val != tree2->val)return false;
	if(IsMirrorTree(tree1->left,tree2->right) && IsMirrorTree(tree2->left,tree1->right))return true;
	else return false;

}

TreeNode* CreateTree(int size){
	vector<int>nums;
	int i=size;
	while(i--){
		nums.push_back(i);
	}
	sort(nums.begin(),nums.end());
	//PrintVector(nums);
	TreeNode* root= MiniBinaryTree(nums);

	return root;
}

int main(int argc, char *argv[])
{
	int size = stoi(argv[1]);
	TreeNode* tree1 = CreateTree(size);
	TreeNode* tree2 = CreateTree(size);
	cout << "Original tree:\n";
	//PrintTree(tree1);
	cout << "Its mirror:\n";
	TreeNode* mirror = MirrorTree(tree1);
	//PrintTree(mirror);

	cout <<"The trees are"<< (IsMirrorTree(tree1, tree2)?" ":" not ")<<"mirrored!\n"<< endl;

	return 0;
}
