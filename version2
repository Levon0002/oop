#include <iostream>
#include <string>
#include <vector>
#include <stack>

class Node {
		private:
		char operand;
		public:
		Node* left;
		Node* right;
		Node(char _operand) {
			left = nullptr;
			right = nullptr;
			operand = _operand;
		}
		char getOperand() {
				return operand;
		}
};


int getPriority(char operand) {
		switch(operand)	{
				case('+'): return 1;
				case('-'): return 1;
				case('*'): return 2;
				case('/'): return 2;
				default: return 0;
		}
	
}


void postfix_eval(std::string &math_exp, std::vector<Node> &nodes) {
	
	std::stack<char> st;
	for(int i = 0; i < math_exp.size(); ++i) {
		if(isdigit(math_exp[i])) {
				Node obj(math_exp[i]);
				nodes.push_back(obj);
		}
		else if (math_exp[i] == '(') {
					st.push(math_exp[i]);		
		}

		else if (math_exp[i] == ')') {
					while(!st.empty() && st.top() != '(') {
								char cur_operator = st.top();
								Node obj(cur_operator);
								nodes.push_back(obj);
								st.pop();
					}
				st.pop();			
		}

		else {
			int cur_priority = getPriority(math_exp[i]);
			while(!st.empty() && st.top() != '(' &&
					cur_priority <= getPriority(st.top()) ) {
					Node obj(st.top());
					nodes.push_back(obj);
					st.pop();
				}
			
				st.push(math_exp[i]);

		}


	}

	while(!st.empty()) {
			Node obj(st.top());
			nodes.push_back(obj);
			st.pop();	
	}

}

Node* built_tree(std::vector<Node> &nodes) {
	std::stack<Node*> st;
	for(int i = 0; i < nodes.size(); ++i) {
					if(isdigit(nodes[i].getOperand())) {
							st.push(&nodes[i]);
					}
					else {
							Node* obj1 = st.top();
							st.pop();
							Node* obj2 = st.top();
							st.pop();
							nodes[i].left = obj2;
							nodes[i].right = obj1;
							st.push(&nodes[i]);
					}
	}
	std::cout << "tree was built\n";

	return st.top();
	

}


int main()
{
	std::string math_exp = "";
	std::cout << "input the expresion: ";
	std::cin >> math_exp;
	std::vector<Node> nodes;
	postfix_eval(math_exp, nodes);
	Node* res = built_tree(nodes);
	std::cout << res->right->getOperand() << "\n";
	std::cout << res->right->left->getOperand() << "\n";
	std::cout << res->right->left->left->getOperand() << "\n";

	
}
