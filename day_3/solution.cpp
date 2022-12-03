#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <vector>
#include <set>
using namespace std;

int get_points(const char letter){
  int points = 0;
  if(int(letter)<=int('z') && int(letter)>=int('a')){
    points = int(letter)-int('a')+1;
  }else if(int(letter)<=int('Z') && int(letter)>=int('A')){
    points = int(letter)-int('A')+27;
  }else{
    points = -1;
  }
  return points;
}

char find_common_char(vector<string>* elves){
  set <char> common_chars;
  for(int i = 0; i < elves->at(0).length(); i++){
    size_t pos = elves->at(1).find(elves->at(0)[i]);
    if(pos != string::npos){
      common_chars.insert(elves->at(0)[i]);
    }
  }
  char found_char;
  for(auto i : common_chars){
    size_t pos = elves->at(2).find(i);
    if(pos != string::npos){
      found_char = i;
    }
  }
  common_chars.clear();
  return found_char;
}

int main()
{
  string raw_line;
  string sub_string_A;
  string sub_string_B;
  int index = 0;
  int total_points = 0;
  ifstream input_file("short_input.txt");
  while (getline(input_file, raw_line))
  {
    index = raw_line.length()/2;
    sub_string_A = raw_line.substr(0, index);
    sub_string_B = raw_line.substr(index);
    char common_char;
    bool found = false;
    for(int i = 0; i < sub_string_B.length() && !found; i++){
      size_t pos = sub_string_A.find(sub_string_B[i]);
      if(pos != string::npos){
        found = true;
        common_char=sub_string_A[pos];
        total_points+=get_points(common_char);
      }
    }  
  }
  cout << "Part 1 - Total points: "<<total_points<<endl;
  input_file.close();

  //PART TWO
  input_file.open("input.txt");
  int row_index = 0;
  char common_char;
  int total_points_2 = 0; 
  vector<string> group_of_elves[3];
  vector<char> common_chars_between_two_strings;
  while(getline(input_file, raw_line)){    
    group_of_elves->push_back(raw_line);
    row_index++;
    if(row_index % 3 == 0 && row_index != 0){
      char common_char = find_common_char(group_of_elves);
      total_points_2 += get_points(common_char);
      common_chars_between_two_strings.clear();//cout<<endl; 
      row_index = 0;
      group_of_elves->clear();
    } 
  }
  cout << "Part 2 - Total points: "<<total_points_2<<endl;
  input_file.close();
  return 0;
}
