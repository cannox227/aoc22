#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
using namespace std;

typedef enum
{
  ROCK = 0,
  PAPER,
  SCISSORS,
  ERROR
} move;

typedef enum
{
  LOST = 0,
  DRAW = 3,
  WIN = 6
} match_result;

int match_results_matrix[3][3] =
    // cols (opponent):  rock, paper, scissors
    // rows (your_move): rock, paper, scissors
    {{DRAW, LOST, WIN},
     {WIN, DRAW, LOST},
     {LOST, WIN, DRAW}};

const int ROCK_POINTS = 1;
const int PAPER_POINTS = 2;
const int SCISSORS_POINTS = 3;

int get_player_move(const char player_encrypted_move)
{
  if (player_encrypted_move == 'A' || player_encrypted_move == 'X')
  {
    return ROCK;
  }
  else if (player_encrypted_move == 'B' || player_encrypted_move == 'Y')
  {
    return PAPER;
  }
  else if (player_encrypted_move == 'C' || player_encrypted_move == 'Z')
  {
    return SCISSORS;
  }
  else
  {
    return ERROR;
  }
}

int get_your_single_round_points(int elf_move, int your_move)
{
  int points = 0;
  switch (your_move)
  {
  case ROCK:
    points += ROCK_POINTS;
    break;
  case PAPER:
    points += PAPER_POINTS;
    break;
  case SCISSORS:
    points += SCISSORS_POINTS;
    break;
  }
  points += match_results_matrix[your_move][elf_move];

  return points;
}

int get_move_with_second_strategy(int elf_move, const char your_move)
{
  int expected_result = ERROR;
  switch (your_move)
  {
  case 'X':
    expected_result = LOST;
    break;
  case 'Y':
    expected_result = DRAW;
    break;
  case 'Z':
    expected_result = WIN;
    break;
  }
  int chosen_move = ERROR;
  for (int i = 0; i < 3; i++)
  {
    if (match_results_matrix[i][elf_move] == expected_result)
    {
      chosen_move = i;
    }
  }
  return chosen_move;
}

int main()
{
  string raw_line;
  int points = 0;
  int elf_move = ERROR;
  int player_move = ERROR;

  ifstream input_file("input.txt");
  while (getline(input_file, raw_line))
  {
    elf_move = get_player_move(raw_line[0]);
    player_move = get_player_move(raw_line[2]);
    points += get_your_single_round_points(elf_move, player_move);
    cout << raw_line << ":" << get_your_single_round_points(elf_move, player_move) << endl;
  }
  input_file.close();

  cout << "With strategy 1, you have scored " << points << " points in total" << endl;

  points = 0;
  input_file.open("input.txt");
  while (getline(input_file, raw_line))
  {
    elf_move = get_player_move(raw_line[0]);
    player_move = get_move_with_second_strategy(elf_move, raw_line[2]);
    points += get_your_single_round_points(elf_move, player_move);
    cout << raw_line << ":" << get_your_single_round_points(elf_move, player_move) << endl;
  }
  input_file.close();

  cout << "With strategy 2, you have scored " << points << " points in total" << endl;

  return 0;
}
