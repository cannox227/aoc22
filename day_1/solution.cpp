#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdio.h>
using namespace std;

bool max(int a, int b){
  return a >= b;
}

void add_elf_and_update_values(vector<int>& v, int& sum, int& max_val, int& max_index, int& current_index){
  v.push_back(sum);
  if(max(sum, max_val)){
    max_val = sum;
    max_index = current_index; 
  }
  //cout << "=" << sum << endl;
  current_index++;
  sum = 0;
}
int main() {
  vector<int> elf_calories;
  string raw_line;
  ifstream input_file("input.txt");
  int sum_of_single_elf_calories = 0;
  int max_value = 0;
  int max_index = 0;
  int current_index = 0;

  while (getline (input_file,  raw_line)) {
    if(raw_line.compare("")==0){
      add_elf_and_update_values(elf_calories, sum_of_single_elf_calories, max_value, max_index, current_index); 
    }else{
      sum_of_single_elf_calories += stoi(raw_line);
      //cout << ">>" << raw_line << endl;
    }
  }
  input_file.close();

  cout << "Max value found at " << max_index+1 << "=" << max_value << endl;
  cout << "calories["<<max_index<<"]="<<elf_calories[max_index]<<endl;

  // PART 2
  sort(elf_calories.begin(), elf_calories.end(), greater<int>());
  const int TOP_CARRIERS = 3;
  int sum_of_carriers_calories = 0;
  for(int i = 0; i < TOP_CARRIERS; i++){
    cout << "Carrier "<<i<<" has "<< elf_calories[i] << endl;
    sum_of_carriers_calories += elf_calories[i];
  }
  cout << "Total amount of the first "<<TOP_CARRIERS<<"carriers is: "<<sum_of_carriers_calories<<endl;

  return 0;
}



