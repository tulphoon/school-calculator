/**
 * calculator.cpp
 * Purpose: Calculates the result of an arithmetic expression.
 *
 * @author Dawid Osuchowski
 */
#include <algorithm>
#include <cmath>
#include <iostream>
#include <iterator>
#include <stack>
#include <sstream>
#include <vector>

int eval(std::string op, int a, int b) {
  int result;

  if (op == "^") {
    result = std::pow(a, b);
  } else if (op == "*") {
    result = a * b;
  } else if (op == "/") {
    if (b == 0) {
      std::cout << "Cannot divide by zero" << '\n';
      std::exit(EXIT_FAILURE);
    }
    result = a / b;
  } else if (op == "+") {
    result = a + b;
  } else if (op == "-") {
    result = a - b;
  }

  return result;
}

int calculate_result(std::vector<std::string> expression) {
  std::string operators = "^*/+-";
  std::stack<std::string> stack;
  std::vector<std::string> output;
  int operand_1, operand_2, result;

  for (std::string token : expression ) {
    if (token == "^" || token == "*" || token == "/" || token == "+" || token == "-") {
      int operand_2 = std::stoi(stack.top()); stack.pop();
      int operand_1 = std::stoi(stack.top()); stack.pop();
      result = eval(token, operand_1, operand_2);
      stack.push(std::to_string(result));

    } else if (std::all_of(token.begin(), token.end(), ::isdigit)) {
      stack.push(token);
    }
  }

  result = std::stoi(stack.top()); stack.pop();

  return result;
}

std::vector<std::string> convertToRPN(std::vector<std::string> expression) {
  std::string operators = "^*/+-";
  std::stack<std::string> stack;
  std::vector<std::string> output;

  for (std::string token : expression ) {
    if (std::all_of(token.begin(), token.end(), ::isdigit)) {
      output.push_back(token);
    }
    if (token == "^" || token == "*" || token == "/" || token == "+" || token == "-") {
      if (!stack.empty()) {
          while (operators.find(stack.top()) < operators.find(token)) {
              output.push_back(std::move(stack.top()));
              stack.pop();
              if (stack.empty()) {
                break;
              }
          }
      }
      stack.push(token);
    }
    if (token == "(") {
      stack.push(token);
    }
    if (token == ")") {
      while (stack.top() != "(") {
        output.push_back(std::move(stack.top()));
        stack.pop();
      }
      stack.pop();
    }
  }

  while (!stack.empty()) {
    output.push_back(std::move(stack.top()));
    stack.pop();
  }

  return output;
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
}

std::vector<std::string> split(std::string str) {

  replaceAll(str, "(", " ( ");
  replaceAll(str, ")", " ) ");

  std::stringstream ss(str);
  std::istream_iterator<std::string> begin(ss);
  std::istream_iterator<std::string> end;
  std::vector<std::string> vstrings(begin, end);

  return vstrings;
}

std::string createExpression() {

  std::string expression;
  std::cout << "Enter an expression to evaluate: ";
  std::getline(std::cin, expression);

  return expression;
}

int main(int argc, char const *argv[]) {
  std::string expression = createExpression();

  std::vector<std::string> vexpression = split(expression);

  int result;

  result = calculate_result(convertToRPN(vexpression));

  std::cout << "Result: " << result << '\n';

  return 0;
}
