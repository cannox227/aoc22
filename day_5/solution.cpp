#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <queue>

using namespace std;

void print_stack(stack<char> s)
{
  stack<char> temp;
  while(!s.empty()){
    cout << s.top();
    temp.push(s.top());
    s.pop();
  }
  while (!temp.empty())
  {
    char t = temp.top();
    //cout << t << ",";
    temp.pop();
    s.push(t); 
  }
}
void print_stacks(vector<stack<char>> vec){
  for(auto i : vec){
    print_stack(i);
    cout << endl;
  }
}

int get_last_space_position(string* s){
  bool found = false;
  int index = -1;
  for(int i = s->length()-1; i >= 0 && !found; i--){
    if(s->at(i) == ' '){
      found = true;
      index = i;
    }
  }
  return index;
}

stack<char>* reverse_stack(stack<char> st){
  stack<char>* temp = new stack<char>();
  while(!st.empty()){
    temp->push(st.top());
    st.pop();
  }
  return temp;
}

stack<char>* reverse_stack(stack<char>* st, int amount_of_lements){
  stack<char>* temp = new stack<char>();
  int counter = 0;
  while(!st->empty() && counter < amount_of_lements){
    temp->push(st->top());
    st->pop();
    counter++;
  }
  return temp;
}

void execute_movement_9000(vector<stack<char>> *vec, int amount, int from, int to){
  from -= 1;
  to -= 1;
  for(int i = 0; i < amount && !vec->at(from).empty(); i++){
    vec->at(to).push(vec->at(from).top());
    vec->at(from).pop();
  }
}

void execute_movement_9001(vector<stack<char>> *vec, int amount, int from, int to){
  from -= 1;
  to -= 1;
  int counter = 0;
  if(amount > 1){
    stack<char> rev = *reverse_stack(&vec->at(from), amount);
    while(!rev.empty()){
      vec->at(to).push(rev.top());
      rev.pop();
    }
  }else{
    execute_movement_9000(vec,amount, ++from, ++to);
  }
}

string get_tops(vector<stack<char>> *vec){
  string tops;
  for(auto i : *vec){
    tops.push_back(i.top());
  }
  return tops;
}

int main (int argc, char *argv[])
{

  ifstream input_file("input.txt");
  string raw_line;
  int crates_number = 0;
  bool parse_instructions = false;
  bool acquire_stacks = true;
  int instruction[3];
  size_t ticker_move_pos = 5;
  size_t  ticker_from_pos;
  size_t ticker_to_pos;
  int line_len;
  vector<stack<char>> crates; 
  vector<stack<char>> reversed_9000;
  vector<stack<char>> reversed_9001;
  int stacks_amount;
  while(getline(input_file, raw_line)){
    if(raw_line[1] == '1' && raw_line.length()>0){
      stacks_amount = stoi(raw_line.substr(get_last_space_position(&raw_line)-1));
      acquire_stacks = false;
    } 
    if(parse_instructions){
      ticker_from_pos = raw_line.find("from");
      ticker_to_pos = raw_line.find("to");
      line_len = raw_line.length();
      instruction[0] = stoi(raw_line.substr(ticker_move_pos, ticker_from_pos-ticker_move_pos-1));
      instruction[1] = stoi(raw_line.substr(ticker_from_pos+ticker_move_pos, ticker_to_pos-ticker_move_pos-ticker_from_pos - 1));
      instruction[2] = stoi(raw_line.substr(ticker_to_pos+3));
      execute_movement_9000(&reversed_9000, instruction[0], instruction[1], instruction[2]);
      execute_movement_9001(&reversed_9001, instruction[0], instruction[1], instruction[2]);
    }else if(acquire_stacks){
      //cout << raw_line << endl; 
      for(int i = 1; i < raw_line.length(); i=i+4){
        char c = raw_line[i];
        if(i/4 >= crates.size()){
          crates.push_back(stack<char>());
        }if(c != ' '){
          crates.at(i/4).push(c);
        }
      }
    }
    if(raw_line.compare("") == 0){
      parse_instructions = true;
      for(auto i : crates){
        reversed_9000.push_back(stack<char>(*reverse_stack(i)));
        reversed_9001.push_back(stack<char>(*reverse_stack(i)));
      }
      //print_stacks(reversed_9000);
      //print_stacks(reversed_9001);
    }
  }
  input_file.seekg(0);
  cout << "PART 1: combination: "<<get_tops(&reversed_9000)<<endl;
  cout << "PART 2: combination: "<<get_tops(&reversed_9001)<<endl;
  return 0;
}
