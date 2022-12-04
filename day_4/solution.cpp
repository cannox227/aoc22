#include <fstream>
#include <string>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

bool is_fully_overlapped(string elf_a, string elf_b){
  bool found = false; 
  size_t separator_pos_a = elf_a.find('-');
  int start_a = stoi(elf_a.substr(0, separator_pos_a));
  int stop_a = stoi(elf_a.substr(separator_pos_a+1));
  int size_a = stop_a - start_a;
  size_t separator_pos_b = elf_b.find('-');
  int start_b = stoi(elf_b.substr(0, separator_pos_b));
  int stop_b = stoi(elf_b.substr(separator_pos_b+1));
  int size_b = stop_b - start_b; 
  if(size_a >= size_b){
    if(start_b >= start_a && stop_b <= stop_a){
      found =  true;
    }
  }else{
    if(start_b <= start_a && stop_b >= stop_a){
      found = true;
    }
  }
  return found;
}

bool is_overlapped(string elf_a, string elf_b){
  bool found = false; 
  size_t separator_pos_a = elf_a.find('-');
  int start_a = stoi(elf_a.substr(0, separator_pos_a));
  int stop_a = stoi(elf_a.substr(separator_pos_a+1));
  size_t separator_pos_b = elf_b.find('-');
  int start_b = stoi(elf_b.substr(0, separator_pos_b));
  int stop_b = stoi(elf_b.substr(separator_pos_b+1));
 
  if(start_a <= start_b && stop_a >= start_b){
      found=true;
  }else if(start_a >= start_b && start_a <= stop_b) {
    found = true;
  }
 return found;
}



int main (int argc, char *argv[])
{
  ifstream input_file("input.txt");
  vector<string> elves_ids;
  string raw_line;
  string first_elf;
  string second_elf;
  size_t separator_pos;
  int fully_overlap_counter = 0;
  int overlap_counter = 0;
  while (getline(input_file, raw_line)) {
    separator_pos = raw_line.find(',');
    first_elf = raw_line.substr(0, separator_pos);
    second_elf = raw_line.substr(separator_pos+1);
    cout << first_elf << " "<<second_elf; 
    if(is_fully_overlapped(first_elf, second_elf)){fully_overlap_counter++;}
    if(is_overlapped(first_elf,second_elf)){overlap_counter++;}
  }
  cout << "Fully Overlaps: "<<fully_overlap_counter<<endl;
  cout << "Overlaps: "<<overlap_counter<<endl;
  return 0;
}
