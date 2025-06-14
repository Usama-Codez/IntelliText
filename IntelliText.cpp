#include<iostream>
#include<string>
#include<windows.h>
#include<fstream>
#include <limits>
#include<conio.h>
#include<stdlib.h>
#include <queue>
#include <unordered_map>
using namespace std;

//-----------------------------* Huff-Man Encoding*----------------------------//
struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};

// Function to allocate a new tree node
Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}

// object to be used to order the heap
struct comp
{
	bool operator()(Node* l, Node* r)
	{
		// highest priority item has lowest frequency
		return l->freq > r->freq;
	}
};

// traverse the Huffman Tree and store Huffman Codes
void encode(Node* root, string str,
	unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}
// traverse the Huffman Tree and decode the encoded string
void decode(Node* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}

	// found a leaf node
	if (!root->left && !root->right)
	{
		cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}
// Builds Huffman Tree and decode given input text
void buildHuffmanTree(string text)
{
	// count frequency of appearance of each character
	// and store it in a map
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}

	// Create a priority queue to store live nodes of
	// Huffman tree;
	priority_queue<Node*, vector<Node*>, comp> pq;

	// Create a leaf node for each character and add it
	// to the priority queue.
	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	// do till there is more than one node in the queue
	while (pq.size() != 1)
	{
		// Remove the two nodes from start
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();
		// Create a new internal node with these two nodes
				// as children and with frequency equal to the sum
				// of the two nodes' frequencies. Add the new node
				// to the priority queue.
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	// root stores root of Huffman Tree
	Node* root = pq.top();

	// traverse the Huffman Tree and store Huffman Codes
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	cout << "Huffman Codes are :\n" << '\n';
	for (auto pair : huffmanCode) {
		cout << pair.first << " " << pair.second << '\n';
	}

	cout << "\nOriginal string was :\n" << text << '\n';

	// print encoded string
	string str = "";
	for (char ch : text) {
		str += huffmanCode[ch];
	}

	cout << "\nEncoded string is :\n" << str << '\n';

	// decode the encoded string
	int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)str.size() - 2) {
		decode(root, index, str);
	}
}


//-----------------------*Trie-Tree *-----------------------------//
struct node // node structure 
{
	char Letter;
	bool IswordComplete = false;
	node* children[97];
	string Meaning;
};

class trieTree
{
public:
	node* root = createNode();
public:
	node* createNode() // function to create a new node
	{
		node* newnode = new node();
		newnode->IswordComplete = false;
		for (int x = 0; x < 97; x++)
		{
			newnode->children[x] = NULL;
		}
		return newnode;
	}
	void large(string& w) // function to enlarge the letters of a word
	{
		for (int i = 0; i < w.length(); i++)
		{
			if (w[i] > 96 && w[i] < 123)
			{
				w[i] -= 32; // to go on to upper case letters
			}
		}
		string temp;
		for (int i = 0; i < w.length(); i++)
		{
			if (w[i] != ' ')
			{
				temp += w[i];
			}
		}
		w = temp;
	}
	void LoadTxt() // function = to load the dictionary into the trie tree
	{
		int pos = 0;
		ifstream read;
		read.open("data/dictionary.txt", ios::in);
		string word;

		if (!read.is_open())
		{
			cout << "Error! File is not open" << endl;
		}
		else
		{
			while (!read.eof())
			{
				read >> word;

				large(word);

				node* temp = root; // used for traversing the string

				for (int x = 0; x < word.length(); x++)
				{
					pos = word[x]; // determining the position of each letter in the array
					if (temp->children[pos] == NULL) // checking if position is occupied already or not 
						temp->children[pos] = createNode(); // if not create a node on that position
					temp = temp->children[pos]; // pointing at the new node
				}
				temp->IswordComplete = true;

			}
		}
		read.close();
	}
	void AddWord(string word) // function to add new words
	{
		large(word);

		node* temp = root; // used for traversing the string
		int length = word.length(); // storing length of the string

		for (int x = 0; x < length; x++)
		{
			int pos = word[x]; // determining the position of each letter in the array
			if (temp->children[pos] == NULL) // checking if position is occupied already or not 
				temp->children[pos] = createNode(); // if not create a node on that position

			temp = temp->children[pos]; // pointing at the new node
		}
		temp->IswordComplete = true;

		ofstream write;
		write.open("Dictionary.txt", ios::app);
		write << word << endl;
		cout << "\n\n<--------Word added successfully---------->\n" << endl;
		write.close();
	}
	bool find(string word, node*& current)  // function to perfrom the actual searching
	{
		int index;
		//this for loop check word index by index etc a,l,i.
		for (int i = 0; i < word.length(); i++)
		{
			index = word[i];
			//As we know at word last end_word = false
			//so this loop run when word not find means end_word = true.
			if (!current->children[index])
			{
				return false;
			}
			//moves to the next index.
			current = current->children[index];
		}
		//if word exist function return value.
		if (current->IswordComplete == true)
		{
			return true;
		}
		//if word not exist.
		return false;
	}
	void search(string word) // function to search word and display it 
	{
		node* current = root;
		//large the string
		//if ali =ALI.
		large(word);

		ifstream in("Dictionary.txt");
		string s;
		bool check = false, checkword = true;
		while (!in.eof())
		{
			in >> s;
			checkword = true;
			if (!in.eof())
			{
				if (s.length() == word.length())
					for (int i = 0; i < s.length(); ++i)
					{
						if (s[i] != word[i])
						{
							checkword = false;
						}
					}
				if (checkword)
				{
					check = true;
					break;
				}
			}
		}


		if (check)
		{
			cout << "\t\t" << word << endl;
		}
		else
		{
			cout << "\t<-----------Word Not Found------------>" << endl;
		}

	}

	bool isEmpty() // function to check for empty tree
	{
		for (int i = 0; i < 97; i++)
			if (root->children[i])
				return false;
		return true;
	}

	void delete_word(string word) // Search function for deletion
	{
		node* current = root;
		//word = arge(word);
		if (!find(word, current))
		{
			cout << "\t\t\tWord is Not Available" << endl;
			return;
		}
		current->IswordComplete = false;
		return;
	}

	void DeleteWord(string w) // function to delete words from the tree
	{

		delete_word(w);
		string word;
		ifstream read;
		ofstream write;
		write.open("Dictionary.txt", ios::app);
		read.open("Dictionary.txt");
		while (!read.eof())
		{
			read >> word;
			if (word != w) {
				write << word << endl;
			}
		}
		read.close();
		write.close();
		remove("Dictionary.txt");
		write.open("Dictionary.txt");
		read.open("Dictionary.txt");

		while (!read.eof())
		{
			read >> word;
			write << word << endl;
		}
		read.close();
		write.close();
		cout << "\t\t\tWord is deleted Sucessfully from file" << endl;
		remove("Dictionary.txt");
	}

	void deleteAll(node* ptr) // function to delete the entire tree
	{
		if (ptr == NULL)
			return;
		else
		{
			for (int i = 0; i < 97; i++)
			{
				if (ptr->children[i])
					deleteAll(ptr->children[i]);
			}
			delete ptr;
		}
		root = NULL;
	}

	int choic()
	{
		int a;
		cout << "\nTo Skip sugesstions, Press 0.\n";
		cout << "\nEnter your choice (1-10) for suggestion: ";
		cin >> a;
		if (a == 15)
		{
			return -1;
		}
		while (a > 10)
		{
			cout << "\nSorry wrong chioce. Please enter a choice between 1-10: ";
			cin >> a;
		}
		return a - 1;
	}

	string findSugg(string str)
	{
		ifstream wordsDec;
		string wordFromFile;
		wordsDec.open("Dictionary.txt");
		string strRet;
		bool flag = false, mainFlag = false;
		int count = 1, j = 0, i = 0, l = 0;
		string arr[10];
		int index = 0, iter = 1;
		while (!wordsDec.eof() && !mainFlag)
		{
			do
			{
				wordsDec >> wordFromFile;

			} while (str.length() > wordFromFile.length());

			while (j < wordFromFile.length())
			{
				if (i > str.length())
				{
					j = wordFromFile.length();
				}
				else if (count == str.length() && flag)
				{
					flag == true;
					cout << "\n" << iter << "- " << wordFromFile << endl;
					arr[index] = wordFromFile;
					j = wordFromFile.length();
					index++;
					if (index == 10)
					{
						mainFlag = true;
						break;
					}
					iter++;
				}
				else if (count == str.length())
				{
					cout << "\n" << iter << "- " << wordFromFile << endl;
					arr[index] = wordFromFile;
					j = wordFromFile.length();
					index++;
					if (index == 10)
					{
						mainFlag = true;
						break;
					}
					iter++;
				}
				else if (str[i] == wordFromFile[j])
				{
					if (l != 0)
						count++;
					l++;
					i++;
					j++;
				}
				else if (str[i] != wordFromFile[j])
				{
					break;
				}
			}
			count = 1;
			i = 0;
			j = 0;
			l = 0;
		}
		wordsDec.close();
		if (index == 0)
		{
			cout << "\n\nSorry No Suggestion found.\n\n";
			system("pause>0");
		}
		else
		{
			index = choic();
			if (index == -1)
				return strRet;
			strRet = arr[index];
		}
		return strRet;
	}

	~trieTree() // destructor
	{
		deleteAll(root);
	}
};
//-------------------------* Main *--------------------------------//
int main()
{
	string loading = "Loading.......\n";
	bool found, flag = true;
	trieTree obj;
	int options = 0;
	for (int i = 0; i < loading.length(); i++)
	{
		cout << loading[i];
		Sleep(150);
	}
	string str = "-------------IntelliText Text Editor---------------\n";
	for (int i = 0; i < str.length(); i++)
	{
		cout << str[i];
		Sleep(50);
	}
	obj.LoadTxt(); // loading words from a text file

	do
	{
		cout << "/________* Please select from the folowing options *________/ " << endl;
		cout << "1) Insert Text" << endl;
		cout << "2) Search any word" << endl;
		cout << "3) Enter -1 to exit" << endl;
		cout << "\nEnter your choice: ";
		cin >> options;
		if (options == 1)
		{
			char choi = NULL;
			cout << "\nDo you want to continue your editing or want to clear previous data?\n";
			cout << "Press \"c\" to Continue editing or Press \"n\" to start from begining: ";
			cin >> choi;
			int choice, i = 0;
			bool fg = false;
			string str1 = "";
			string str2 = "";
			string str3 = "";
			char ch;
			cout << "\n\n Here are some instructions for you:\n";
			cout << "->> Press \" ` \" to exit editing mode.\n";
			cout << "->> Press \"\ \ \" to get suggestions while insertion.\n";
			cout << "Enter the data you want to insert in the text file:\n";
			do
			{
				ch = getchar();
				if (ch != 92)
				{
					str2.push_back(ch);
				}
				if (ch == 92)     // If '\' pressed, (for suggestion)
				{
					str3 = obj.findSugg(str2);
					str2.clear();
					system("cls");

					for (int i = 0; i < str3.length(); i++)
					{
						str1.push_back(str3[i]);
					}
					cout << "Here are some instructions for you:\n";
					cout << "->> Press \" ` \" to exit editing mode.\n";
					cout << "->> Press \"\ \ \" to get suggestions while insertion.\n\n";
					cout << str1;
				}

				if (ch == ' ')
				{
					for (int i = 0; i < str2.length(); i++)
					{
						str1.push_back(str2[i]);
					}
					str2.clear();
					fg = true;
				}
				if (!fg)
				{
					str1.push_back(ch);
				}
			} while (ch != '`');
			cout << "\nEditing exited sucessfully.\n\n";
			obj.AddWord(str1);
			cout << "\n\nCompressing your data.\n";
			buildHuffmanTree(str1);
			flag = true;
		}
		else if (options == 2)
		{
			string word;
			cout << "Enter The word to search : " << endl;
			cin.ignore();
			getline(cin, word);
			obj.search(word);
			flag = true;
		}
		else if (options == 3)
		{
			string word;
			cout << "Enter the word to delete : " << endl;
			cin.ignore();
			getline(cin, word);
			obj.DeleteWord(word);
			if (obj.root == NULL)
				cout << "<------------Deletion Successful-------->" << endl;
			flag = true;
		}
		if (options == 0)
		{
			cout << "<-------Exiting the Text Editor------->" << endl;
			flag = false;
		}
		cout << endl;
		cin.clear();

		system("pause");
		system("cls");
	} while (options != 0);
	return 0;
}
