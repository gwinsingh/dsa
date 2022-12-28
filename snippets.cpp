#include <bits/stdc++.h>


// STRING

string st = "Hello World!";
to_string(121);
st.starts_with("Hell"); // True
st.ends_with("d!"); // True
st.substr(0,5); // "Hello"
st.substr(5); // " World!"


// VECTOR

// Inserting in Vector -- O(n)
vector<int> vectorA{1,4,9};
vectorA.insert(solution.begin(), 0); // [0, 1, 4, 9]
vectorA.insert(solution.begin() + 2, 3); // [0, 1, 3, 4, 9]


vector<vector<int>> solution;
for (auto person : people){
    solution.insert(solution.begin() + person[1], person);
}


// LOWER BOUND / UPPER BOUND

vector<int> v{ 5, 6, 7, 7, 6, 5, 5, 6 };
sort(v.begin(), v.end()); // 5 5 5 6 6 6 7 7
vector<int>::iterator lower, upper;

lower = lower_bound(v.begin(), v.end(), 6); // the first element in the range [first,last) which has a value not less than ‘val’. 
upper = upper_bound(v.begin(), v.end(), 6); // the first element in the range [first,last) which has a value greater than ‘val’. 

cout << "lower_bound for 6 at position " << (lower - v.begin()) << '\n'; // 3 i.e index of first 6
cout << "upper_bound for 6 at position "<< (upper - v.begin()) << '\n'; // 6 i.e first index after 6

// BINARY SEARCH

// Template -- To find leftmost value that satisfies some specific condition.

int left = 0;
int right = n-1;
int mid;

while (left < right) {
	int mid = (left+right)/2; 	// -- Note that due to way right and left are changed, this will always be less than right, hence never be equal to 'n-1' i.e no need to handle the case for index out of bounds.

	if (right-bound-condition) {
		right = mid;
	} else {
		left = mid + 1;
	}
}

return left; // left points to the leftmost value that satisfies the 'condition'.



// TRIE

class Trie {
	class TrieNode {
	public:
	  int val;
	  vector<TrieNode*> next;
	  
	  TrieNode() : val(-1), next(27, nullptr) {}
	};


private:
	TrieNode* trieNode;

public:
	Trie() {
		trieNode = new TrieNode();
	}

	void insert(string& word, int val) {
		TrieNode* currNode = trieNode;

		for (char ch : word) {
		  if (currNode->next[ch - 'a'] == nullptr) 
		    currNode->next[ch - 'a'] = new TrieNode();
		  
		  currNode = currNode->next[ch - 'a'];
		  currNode->val = val;
		}
	}

	TrieNode* find(string& searchString) {
		TrieNode* currNode = trieNode;

		for (char ch : searchString) {
			if (currNode->next[ch-'a'] == nullptr) return nullptr;

			currNode = currNode->next[ch-'a'];
		}

		return currNode;
	}
};
  
void insertToTrie(string& word, int idx) {
	TrieNode* currNode = trieNode;

	for (char ch : word) {
	  if (currNode->next[ch - 'a'] == nullptr) 
	    currNode->next[ch - 'a'] = new TrieNode();
	  
	  currNode = currNode->next[ch - 'a'];
	  currNode->val = idx;
	}
}



// PRIOIRITY QUEUE 

// Usage

// PQ of integers
priority_queue<int> maxPq;
priority_queue<int, vector<int>, greater<vector<int>>> minPq;

// PQ of integer pairs.
priority_queue< pair<int, int>> maxPq;
priority_queue< pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>> > minPq;

maxPq.push(5);
maxPq.top(); // Probably
maxPq.pop();


// Comparator for PQ: EXAMPLE
priority_queue<vector<int>, vector<vector<int>>, compare> maxPq;

struct compare {
    bool operator()(vector<int>& p, vector<int>& q) {
        return p[0] * p[0] + p[1] * p[1] > q[0] * q[0] + q[1] * q[1];
    }
};



// COMPARATORs


// NOTE: True value in return implies that the first argument should fall in order before the second element.
bool compareInterval(vector<int>& V1, vector<int>& V2)
{
	if (V1[0] == V2[0]) return V2[1] >= V1[1];

	return V1[0] <= V2[0];
}


// Custom Comparator for CLASS, e.g to be used in Priority Queue.
class Person {
 
public:
    int age;
 
    float height;
 
    // this is used to initialize the variables of the class
    Person(int age, float height)
        : age(age), height(height)
    {
    }
};
 
// we are doing operator overloading through this
bool operator<(const Person& p1, const Person& p2)
{
 
    // this will return true when second person
    // has greater height. Suppose we have p1.height=5
    // and p2.height=5.5 then the object which
    // have max height will be at the top(or
    // max priority)
    return p1.height < p2.height;
}

priority_queue<Person> Q; // This will now be a max heap of Person objects.


// SEGMENT TREE

class SegmentTree {
public:
  vector<int> treeVec;
  int size;

  SegmentTree(vector<int>& nums) : treeVec (nums.size() * 4) {
    size = nums.size();
    buildSegmentTree(1, 0, size-1, nums);
  }
  
  void buildSegmentTree(int node, int left, int right, vector<int>& nums) {
    if (left == right) {
      treeVec[node] = nums[left];
      return;
    }
    
    int mid = (left+right)/2;
    buildSegmentTree(2*node, left, mid, nums);
    buildSegmentTree(2*node+1, mid+1, right, nums);
    
    treeVec[node] = treeVec[2*node] + treeVec[2*node+1];
  }
  
  int query(int node, int currLeft, int currRight, int left, int right) {
    if (currLeft > right || currRight < left) return 0;
    if (left <= currLeft && currRight <= right) return treeVec[node];
    
    int mid = (currLeft + currRight)/2;
    int lQuery = query(node*2, currLeft, mid, left, right);
    int rQuery = query(node*2+1, mid+1, currRight, left, right);
    
    return (lQuery + rQuery);
  }
  
  int querySum(int x, int y) {
    return query(1, 0, size-1, x, y);
  }
  
  void update(int currNode, int currLeft, int currRight, int index, int val) {
    if (currLeft == currRight) {
      treeVec[currNode] = val;
      return;
    }
    
    int mid = (currLeft + currRight)/2;
    if (index > mid) update(2*currNode+1, mid+1, currRight, index, val);
    else update(2*currNode, currLeft, mid, index, val);
    
    treeVec[currNode] = treeVec[2*currNode] + treeVec[2*currNode + 1];
  }
  
  void update(int index, int val) {
    update(1, 0, size-1, index, val);
  }
  
};



// SEGMENT TREE (Practice)

class SegmentTree {
private:
	vector<int> treeVec;
	int size;

public:
	SegmentTree(vector<int>& arr) : treeVec(4 * arr.size()), size(arr.size()) {
		buildSegmentTree(0, size-1, 0, arr);
	}

	void buildSegmentTree(int left, int right, int treeIdx, vector<int>& arr) {
		if (left == right) {
			treeVec[treeIdx] = arr[left];
			return;
		}

		int mid = (left + right)/2;

		buildSegmentTree(left, mid, 2*treeIdx+1, arr);
		buildSegmentTree(mid+1, right, 2*treeIdx+2, arr);

		treeVec[treeIdx] = treeVec[2*treeIdx+1] + treeVec[2*treeIdx+2];
	}

	int query(int treeIdx, int currLeft, int currRight, int left, int right) {
		if (currLeft > right || currRight < left) return 0;
		if (left <= currLeft && currRight <= right) return treeVec[treeIdx];

		int mid = (currLeft + currRight)/2;

		return (query(2*treeIdx+1, currLeft, mid, left, right) + query(2*treeIdx+2, mid+1, currRight, left, right));
	}

	void update(int node, int currL, int currR, int idx, int target) {
		if (currL == idx && currR == idx) {
			treeVec[node] = target;
			return;
		}

		int mid = (currL + currR)/2;
		if (idx <= mid) {
			update(2*node+1, currL, mid, idx, target);
		} else {
			update(2*node+2, mid+1, currR, idx, target);
		}

		treeVec[node] = treeVec[2*node+1] + treeVec[2*node+2];
	}
};







// UNION FIND

// Implementation 

class UnionFind {
	int components;
	vector<int> root;
	vector<int> rank;

	UnionFind(int size) {
		for (int i = 0; i < size; i++) {
			root.push_back(i);
			rank.push_back(1);
		}

		components = size;
	}

	int find(int x) {
		if (root[x] == x) return x;

		return root[x] = find(root[x]);
	}

	void unionSet(int x, int y) {
		int rootX = find(x);
		int rootY = find(y);

		if (rootX != rootY) {
			if (rank[rootX] > rank[rootY]) {
				root[rootY] = root[rootX];
			} else if (rank[rootX] < rank[rootY]) {
				root[rootX] = root[rootY];
			} else {
				root[rootX] = root[rootY];
				rank[rootY]++;
			}
			components--;
		}
	}

	int numComponents() {
		return components;
	}
};







class UnionFindPractice {
private:
	vector<int> root;
	vector<int> rank;

	int numComponents;

public:
	UnionFindPractice(int n) : root(n), rank(n) {
		for (int i = 0; i < n; i++) {
			root[i] = i;
			rank[i] = 0;
		}

		numComponents = n;
	}

	int find(int n) {
		if (root[n] == n) return n;

		return root[n] = find(root[n]);
	}

	void UnionSet(int n1, int n2) {
		int root1 = find(n1);
		int root2 = find(n2);

		if (root1 != root2) {
			if (rank[root1] > rank[root2]) {
				root[root2] = root1;
			} else if (rank[root1] < rank[root2]) {
				root[root1] = root2;
			} else {
				root[root1] = root2;
				rank[root2]++;
			}
			numComponents--;
		}
	}

	bool connected(int n1, int n2) {
		return find(n1) == find(n2);
	}

	int GetNumComponents() {
		return numComponents;
	}
}










// MERGE SORT

  void mergeSubArrays(vector<int>& nums, int i1, int j1, int i2, int j2) {
    int x = i1;
    int y = i2;
    vector<int> mergedArr;
    
    while (x <= j1 || y <= j2) {
      if (x > j1) {mergedArr.push_back(nums[y++]);}
      else if (y > j2) {mergedArr.push_back(nums[x++]);}
      else {
        if (nums[x] < nums[y]) mergedArr.push_back(nums[x++]);
        else mergedArr.push_back(nums[y++]);
      }
    }
    
    int idx = 0;
    for (int i = i1; i <= j1; i++) nums[i] = mergedArr[idx++];
    for (int i = i2; i <= j2; i++) nums[i] = mergedArr[idx++];
  }
  
  void mergeSort(vector<int>& nums, int i, int j) {
    if (i >= j) return;
    
    int mid = (i+j)/2;
    mergeSort(nums, i, mid);
    mergeSort(nums, mid+1, j);
    mergeSubArrays(nums, i, mid, mid+1, j);
  }
  
  vector<int> sortArray(vector<int>& nums) {
    mergeSort(nums, 0, nums.size() - 1);
    
    return nums;
  }

// QUICK SORT

int pivotPartition(vector<int>& nums, int x, int y) {
  int pivotNum = nums[y];
  int pivotIdx = x;
  for (int i = x; i < y; i++) {
    if (nums[i] < pivotNum) swap(nums[i], nums[pivotIdx++]);
  }
  swap(nums[y], nums[pivotIdx]);
  
  return pivotIdx;
}
  
void quickSort(vector<int>& nums, int i, int j) {
  if (i >= j) return;
  
  int pivotIndex = pivotPartition(nums, i, j);
  quickSort(nums, i, pivotIndex-1);
  quickSort(nums, pivotIndex+1, j);
}

vector<int> sortArray(vector<int>& nums) {
  quickSort(nums, 0, nums.size() - 1);
  
  return nums;
}






























