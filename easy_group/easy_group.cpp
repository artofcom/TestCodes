// easy_group.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <map>
#include <queue>

using namespace std;

struct ListNode 
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}	
};

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool isBadVersion(int version)
{
	if (version >= 1702766719)
		return true;
	return false;
}

class Solution {
public:
	bool isPalindrome(string s) {

		if (s.length() <= 0)
			return true;

		int head = 0;
		int tail = s.length() - 1;

		while (head<tail)
		{
			char head0 = 0;
			for (; head<tail; ++head)
			{
				head0 = s.at(head);
				if ((head0 >= 'A' && head0 <= 'Z') || (head0 >= 'a' && head0 <= 'z'))
				{
					head0 = tolower(head0);
					break;
				}
			}
			if (head == tail)  break;

			char tail0 = 0; // s.at(tail);
			for (; head<tail; --tail)
			{
				tail0 = s.at(tail);
				if ((tail0 >= 'A' && tail0 <= 'Z') || (tail0 >= 'a' && tail0 <= 'z'))
				{
					tail0 = tolower(tail0);
					break;
				}
			}
			if (head == tail)  break;

			if (head0 != tail0)
				return false;

			++head;
			--tail;
		};

		return true;
	}

	string countAndSay(int n) {

		vector<string> v;
		v.push_back("1");

		for (int q = 1; q < n; ++q)
		{
			string target = v.at(q - 1);
			string newOne = "";
			for (int len = 0; len < target.size(); )
			{
				int count = 1;
				char chTarget = target.at(len);
				for (int r = len + 1; r < target.size(); ++r)
				{
					if (chTarget == target.at(r))
						++count;
					else break;
				}

				len += count;
				char buff[2];
				//itoa(count, buff, 10);
				sprintf_s(buff, "%d", count);
				newOne += buff;
				newOne += chTarget;

			}

			v.push_back(newOne);
		}

		return v[n - 1];
	}


	bool isPalindrome(ListNode* head)
	{
		if (!head)   return true;

		ListNode* fast = head;
		ListNode* slow = head;
		while (NULL!=fast && NULL!=fast->next)
		{
			slow = slow->next;
			fast = fast->next->next;
		}

		// slow comes middle of list.
		ListNode* center = slow;
		center = reverseList(slow);

		fast = head;

		for (;;)
		{
			if (NULL==center) break;

			if (fast->val != center->val)
				return false;

			fast = fast->next;
			center = center->next;
		}

		return true;
	}

	ListNode* reverseList(ListNode* head)
	{
		ListNode* prev = NULL;
		ListNode* pCur = head;
		for (; pCur != NULL; )
		{
			ListNode* temp = pCur->next;
			pCur->next = prev;
			prev = pCur;
			if (temp == NULL)
				return pCur;

			pCur = temp;
		}
		return NULL;
	}

	int firstBadVersion(int n) {

		if (isBadVersion(1))     return 1;

		return this->getBadVersion(0, n - 1);
	}

	int getBadVersion(int s, int e)
	{
		if (s + 1 == e && false == isBadVersion(s + 1) && true == isBadVersion(e + 1))
			return e + 1;


		int idxMid = s + (e - s) / 2;

		if (true == isBadVersion(idxMid - 1 + 1))
		{
			if (true == isBadVersion(idxMid - 1))
				return idxMid;
			return getBadVersion(s, idxMid - 1);
		}

		if (true == isBadVersion(idxMid + 1))
			return idxMid + 1;

		return getBadVersion(idxMid, e);
	}

	int lengthOfLongestSubstring(string s) 
	{
		map<char, int> mRet;
		int max = 0;

		for (int i = 0; i < s.length(); ++i)
		{
			pair< map<char, int>::iterator, bool> ret = mRet.insert(pair<char, int>(s[i], i));
			if (ret.second == false)
			{				
				i = mRet[s[i]];
				mRet.clear();
			}

			max = max < mRet.size() ? mRet.size() : max;
			//++i;
		}

		return max;

	}

	vector<vector<int>> zigzagLevelOrder(TreeNode* root)
	{
		vector< vector<int> > vRet;
		if (NULL == root)  return vRet;

		queue<TreeNode*> q;
		q.push(root);


		bool left_right = true;
		do
		{
			int size = q.size();

			vector<int> vTest;

			for (int t = 0; t < size; ++t)
			{
				TreeNode* cur = q.front();
				q.pop();

				if (NULL != cur->left)
					q.push(cur->left);
				if (NULL != cur->right)
					q.push(cur->right);

				vTest.push_back(cur->val);
			}

			if (false == left_right)
				reverse(vTest.begin(), vTest.end());

			vRet.push_back(vTest);
			left_right = !left_right;

			if (true == q.empty())
				break;

		} while (true);

		return vRet;
	}

	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		if (preorder.empty() || inorder.empty())
			return NULL;

		return this->_build(preorder, inorder);
	}

	TreeNode* _build(vector<int>& preorder, vector<int>& inorder)
	{
		if (preorder.empty() || inorder.empty())
			return NULL;

		int val = preorder[0];

		int idxFound = -1;
		for (int k = 0; k < inorder.size(); ++k)
		{
			if (inorder[k] == val)
			{
				idxFound = k;
				break;
			}
		}

		if (-1 == idxFound)
			return NULL;

		TreeNode* node = new TreeNode(val);


		vector<int> preLeft = preorder;
		preLeft.erase(preLeft.begin());
		preLeft.erase(preLeft.begin() + idxFound, preLeft.end());

		vector<int> preRight = preorder;
		preRight.erase(preRight.begin(), preRight.begin() + idxFound + 1);


		vector<int> inLeft = inorder;
		inLeft.erase(inLeft.begin() + idxFound, inLeft.end());

		vector<int> inRight = inorder;
		inRight.erase(inRight.begin(), inRight.begin() + idxFound+1);

		node->left = this->_build(preLeft, inLeft);
		node->right = this->_build(preRight, inRight);

		return node;
	}


	int kthSmallest(TreeNode* root, int k) {

		// pre-order로 k 번째 위치하는 녀석.
		int kth = 0;  int ret = 0;
		this->preAdd(root, k, kth, ret);

		return ret;

	}

	void preAdd(TreeNode* root, int k, int& kth, int& ret)
	{
		if (NULL == root)  return;
		if (ret > 0)     return;

		if (root->left)
		{
			//++kth;
			this->preAdd(root->left, k, kth, ret);
		}

		++kth;
		if (k == kth && 0==ret )
		{
			ret = root->val;
			return;
		}

		if (root->right)
		{
			//++kth;
			this->preAdd(root->right, k, kth, ret);
		}
	}


	vector<string> letterCombinations(string digits) {

		vector<string> ret;
		if (digits.empty())
			return ret;

		string str;
		this->_push_data(ret, str, 0, digits);
		return ret;
	}

	bool _push_data(vector<string>& ret, string str, int idx, string digits)
	{
		if (idx >= digits.size())
		{
			ret.push_back(str);
			return true;
		}


		const int MAX = 4;
		for (int z = 0; z < MAX; ++z)
		{
			char data = this->_getData(digits[idx], z);
			
			if (0 != data)			str += data;
			else if (z == MAX - 1)	break;

			//if (true == 
			_push_data(ret, str, idx + 1, digits);	
			if (0 != data)
				str.assign(str, 0, str.size() - 1);
		}
		return false;
	}

	char _getData(char digit, int idx)
	{
		vector<string> vec;
		switch (digit)
		{
		case '9':
			if (3 == idx) return 'z';
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
			if (0 == idx) return ('a' + digit - '2');
			if (1 == idx) return ('b' + digit - '2');
			if (2 == idx) return ('c' + digit - '2');
			break;
		case '0':
		case '1':
		default:
			break;

		}

		return 0;
	}
};

int main()
{
	Solution s;

	//s.isPalindrome("0P");

	//s.countAndSay(5);

	//ListNode* head = new ListNode(0);
	//head->next = (new ListNode(0));
	//s.isPalindrome(head);

	//s.firstBadVersion(21267533390);

	//s.lengthOfLongestSubstring("dvdf");

	//[3,9,20,null,null,15,7]

	/*
	TreeNode* a = new TreeNode(3);
	TreeNode* b0 = new TreeNode(9);
	TreeNode* b1 = new TreeNode(20);
	a->left = b0;
	a->right = b1;
	TreeNode* c0 = new TreeNode(15);
	TreeNode* c1 = new TreeNode(7);
	b1->left = c0;
	b1->right = c1;

	s.zigzagLevelOrder(a);
	*/

	/*
	vector<int> preorder;
	preorder.push_back(3);
	preorder.push_back(9);
	preorder.push_back(20);
	preorder.push_back(15);
	preorder.push_back(7);
	
	vector<int> inorder;
	inorder.push_back(9);
	inorder.push_back(3);
	inorder.push_back(15);
	inorder.push_back(20);
	inorder.push_back(7);

	s.buildTree(preorder, inorder);*/

	/*
	TreeNode* a = new TreeNode(3);
	TreeNode* b0 = new TreeNode(1);
	TreeNode* b1 = new TreeNode(4);
	TreeNode* c0 = new TreeNode(2);

	a->left = b0;
	a->right = b1;
	b0->right = c0;

	s.kthSmallest(a, 1);
	*/

	s.letterCombinations("23");
    return 0;
}

