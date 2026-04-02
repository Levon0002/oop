#include <iostream>
#include <stack>
#include <string>


int evaluate(std::string &text) {
	std::stack<int> st;
	int size = text.size();

	std::cout << "\n";
	for(int i = 0; i < text.size(); ++i) {
			std::cout << text[i] << "\n";
	}

	//std::cout << "process of evaluate\n";
	for(int i = 0; i < size; ++i) {
					if (isdigit(text[i])) {
							//std::cout << "if is done\n";
							st.push(text[i] - '0');
					}		
					else {
						int elem1 = st.top();
						st.pop();
						int elem2 = st.top();
						st.pop();
						switch(text[i]) {
								case('+'):
									st.push(elem1 + elem2);
									break;
								case('-'):
									st.push(elem1 - elem2);
									break;
								case('*'):
									st.push(elem1 * elem2);
									break;
								case('/'):
									st.push(elem1 / elem2);	
									break;
						}
					}

	}	
		return st.top();


}
int check_priority(char operand) {

	switch(operand) {
		case('+') : return 1;
		case('-'): return 1;
		case('/'): return 2;
		case('*'): return 2;

	}
	return 0;

}
void postfix_eval(std::string &math_exp, std::string &text)
{
	std::stack<char> st;
	int size = math_exp.size();
	for(int i = 0; i < size; ++i) {
		if(math_exp[i] == '(') {
				st.push(math_exp[i]);
		}
		
		else if (isdigit(math_exp[i])) {
					std::cout << "is digit\n"; 
					text.push_back(math_exp[i]);		
		}
		else if (math_exp[i] == ')') {
			while(!st.empty() && st.top() != '(') {
				char top_element = st.top();
				st.pop();
				text.push_back(top_element);				
			}
			st.pop();
		}				
		else {
				if (st.empty()) 
						st.push(math_exp[i]);
				
				int current_prior = check_priority(math_exp[i]);		
				while(!st.empty() && st.top() != '(' &&
			      current_prior <= check_priority(st.top())) {
				text.push_back(st.top());
				st.pop();
			}
				st.push(math_exp[i]);
		}

	}
	while(!st.empty()) {
			text.push_back(st.top());
			st.pop();
	}


}

int main() {

std::string math_exp;
std::string text = "";
std::cout << "input the expresion  ";
std::cin >> math_exp;
postfix_eval(math_exp, text);	
std::cout << "the result is  " << evaluate(text) << "\n";


}
