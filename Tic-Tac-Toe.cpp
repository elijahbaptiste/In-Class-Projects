// NxN tic-tac-toes
#include <iostream>
#include <cstdlib>

using namespace std;

// The following 3 functions are helper functions to convert
// between 1D and 2D array indices.  The grid itself is stored
// as a 1D array.  However, for printing, checking who won,
// etc. it may be easier to write loops that generate separate
// row/column indices (i.e. treating the array like a 2D array).
// The functions below should be written using the hints in the
// writeup for performing the appropriate arithmetic conversion
// between 1D- and 2D-indices, and can then be called in any
// of the other functions when you find yourself wanting to
// convert one to the other.

/**
 * Helper function - Given the grid array and its dimension
 *    as well as a particular row (r) and column (c), this
 *    function performs the arithmetic to convert r and c
 *    to a 1D index and returns that character in the grid.
 *    For example, for dim = 3 and r = 2, c = 1, this function
 *    should compute the corresponding index: 7 and return
 *    grid[7].
 *
 * Use this function wherever you generate, row/column
 *    indices and want to access that element in the grid.
 *    Pass the row/column indices as r and c, respectively.
 *
 */
char getEntryAtRC(char grid[], int dim, int r, int c);

/**
 * Helper function - Given a 1D index returns the row
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToCol() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToRow(int idx, int dim);

/**
 * Helper function - Given a 1D index returns the column
 * that corresponds to this 1D index.  Use this in
 * conjunction with idxToRow() anytime you have a 1D index
 * and want to convert to 2D indices.
 */
int idxToCol(int idx, int dim);

/** Should print the tic-tac-toe board in a nice grid
 *  format as shown below:
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O'
 *         (the letter oh), or '?'.
 */
void printTTT(char grid[], int dim);

/**
 * Should check if any player has won the game yet.
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'

 
 *
 * Return value:
 *   Should return 1 if 'X' has won, 2 if 'O' has won, or 0 (zero)
 *   if the game is still undecided.
 *
 */

//modify from dim to size of data array with spaces and lines included

int checkForWinner(char grid[], int dim);

/**
 * Should check if there is no possible way any player can win.
 * More specifically, if there does not exist a row, column,
 * or diagonal that can still have 3 of a kind, then the game
 * will be a draw.
 *
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *
 * Return value:
 *   Return true if no player can win given the current
 *   game state, false otherwise.
 */
bool checkForDraw(char grid[], int dim);

/**
 * @brief Get the Ai Choice for the current player and update grid object
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If an error occurred or a choice was unable to be made
 * @return false If a play was successfully made
 */
bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player);

/**
 * @brief Picks a random location for the current player and update grid
 *
 * Parameters:
 *   grid: Array of dim^2 characters representing the state
 *         of each square.  Each entry contains 'X', 'O', or '?'
 *   dim: the dim(-ension) of the tic-tac-toe board
 *   player: current player => 'X' or 'O'
 * @return true If no viable location to be played
 * @return false If a play was successfully made
 */
bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player);

/**********************************************************
 *  Write your implementations for each function prototyped
 *  above in the space below
 **********************************************************/

char getEntryAtRC(char grid[], int dim, int r, int c) {
  return grid[(dim * r) + c];
}

int idxToRow(int idx, int dim) {
  return idx / dim; /* Add Expression here to convert idx to appropriate row */ ;
}

int idxToCol(int idx, int dim) {
  return idx % dim; /* Add Expression here to convert idx to appropriate column */ ;
}

void printTTT(char grid[], int dim) {

  int count = 0;
  for (int i = 0; i < dim; i++) {
    for (int j = 0; j < dim; j++) {
      if (j != (dim - 1)) {
        cout << " " << grid[count] << " |";
        count++;
      } else {
        cout << " " << grid[count];
        count++;

      }
      //Should work for all values of tttgriddata
    }
    cout << endl;
    if (i != dim - 1) {
      for (int x = 0; x < 4 * dim; x++) {
        if (x != ((4 * dim) - 1)) {

          cout << "-";

        }
      }
      cout << endl;
    }
  }
}

int checkForWinner(char grid[], int dim) {
  int win = 0;
  int match = 0;

  // Code to check the horizontal columns for wins
  for (int m = 0; m < dim; m++) {
    match = 0;
    for (int n = 0; n < dim; n++) {
      if (grid[m * dim] == grid[(m * dim) + n]) {
        match++;

        if ((grid[m * dim] == 'X') && (match == dim)) {
          win = 1;
          return win;
        }
        if ((grid[m * dim] == 'O') && (match == dim)) {
          win = 2;
          return win;
        }
      }
    }
  }

  // Code to check the vertical columns for wins
  for (int q = 0; q < dim; q++) {
    match = 0;
    for (int r = 0; r < dim; r++) {
      //grid[q + (dim*r)]
      //getEntryAtRC(grid, dim, r, q)
      if (grid[q] == grid[q + (dim * r)]) {
        match++;

        if ((grid[q] == 'X') && (match == dim)) {
          win = 1;
          return win;
        }
        if ((grid[q] == 'O') && (match == dim)) {
          win = 2;
          return win;
        }
      }
    }
  }

  //Code to check  diagonal cases for win
  match = 0;
  for (int w = 0; w < dim; w++) {
    char l = grid[0];
    if (grid[(w * dim) + w] == l) {
      match++;
    }
    if ((grid[0] == 'X') && (match == dim)) {
      win = 1;
      return win;
    }
    if ((grid[0] == 'O') && (match == dim)) {
      win = 2;
      return win;
    }
  }

  match = 0;

  for (int s = 0; s < dim; s++) {
    int c = grid[dim - 1];
    if (grid[(dim - 1) * (s + 1)] == c) {
      match++;
    }
    if ((grid[dim - 1] == 'X') && (match == dim)) {
      win = 1;
      return win;
    }
    if ((grid[dim - 1] == 'O') && (match == dim)) {
      win = 2;
      return win;
    }

  }
  return win;
}

bool checkForDraw(char grid[], int dim) {
  int moves = 0;
  bool draw = true;
  int xfound = 0;
  int ofound = 0;

  // Code to check the horizontal columns for wins
  for (int m = 0; m < dim; m++) {
    for (int n = 0; n < dim; n++) {
    
      //grid[m * dim] != grid[(m*dim) + n] && ((grid[m*dim] != '?')&&(grid[(m*dim)+n] != '?'))
      if (grid[(m * dim) + n] == 'X') {
        xfound++;
      }
      if (grid[(m * dim) + n] == 'O') {
        ofound++;
      }
    }
    if ((xfound >= 1) && (ofound >= 1)) {
      moves++;
    }
  }
  xfound = 0;
  ofound = 0;

  // Code to check the vertical columns for wins
  for (int q = 0; q < dim; q++) {
    for (int r = 0; r < dim; r++) {
      if (grid[(r * dim) + q] == 'X') {
        xfound++;
      }
      if (grid[(r * dim) + q] == 'O') {
        ofound++;
      }
    }
    if ((xfound >= 1) && (ofound >= 1)) {
      moves++;
    }
    xfound = 0;
    ofound = 0;
  }

  xfound = 0;
  ofound = 0;

  //Code to check  diagonal cases for win
  for (int w = 0; w < dim; w++) {
    char l = grid[0];
    if (grid[(w * dim) + w] == 'X') {
      xfound++;
    }
    if (grid[(w * dim) + w] == 'O') {
      ofound++;
    }

  }
  if ((xfound >= 1) && (ofound >= 1)) {
    moves++;
  }

  xfound = 0;
  ofound = 0;
  for (int s = 0; s < dim; s++) {
    char c = grid[dim - 1];
    if (grid[(dim - 1) * (s + 1)] == 'X') {
      xfound++;
    }
    if (grid[(dim - 1) * (s + 1)] == 'O') {
      ofound++;
    }

  }
  if ((xfound >= 1) && (ofound >= 1)) {
    moves++;
  }

  //cout << moves;
  if (moves == ((2 * dim) + 2)) {
    draw = true;
  } else {
    draw = false;
  }
  return draw;
}

bool getAiChoiceAndUpdateGrid(char grid[], int dim, char player) {
  int moves = 0;
  bool draw = true;
  int xfound = 0;
  int ofound = 0;
  int free = 0;

  // Code to check the horizontal columns for wins
  for (int m = 0; m < dim; m++) {
    for (int n = 0; n < dim; n++) {

      //grid[m * dim] != grid[(m*dim) + n] && ((grid[m*dim] != '?')&&(grid[(m*dim)+n] != '?'))
      if (grid[(m * dim) + n] == 'X') {
        xfound++;
      }
      if (grid[(m * dim) + n] == 'O') {
        ofound++;
      }
      if (grid[(m * dim) + n] == '?') {
        free = (m * dim) + n;
      }
    }
    if (((xfound == (dim - 1) && (ofound == 0)))) {
      grid[free] = player;
      return false;
    } else if (((ofound == (dim - 1)) && (xfound == 0))) {
      grid[free] = player;
      return false;
    }
    xfound = 0;
    ofound = 0;
  }
  xfound = 0;
  ofound = 0;

  // Code to check the vertical columns for wins
  for (int q = 0; q < dim; q++) {
    for (int r = 0; r < dim; r++) {
      if (grid[(r * dim) + q] == 'X') {
        xfound++;
      }
      if (grid[(r * dim) + q] == 'O') {
        ofound++;
      }
      if (grid[(r * dim) + q] == '?') {
        free = (r * dim) + q;
      }

    }
    if (((xfound == (dim - 1) && (ofound == 0)))) {
      grid[free] = player;
      return false;
    } else if (((ofound == (dim - 1)) && (xfound == 0))) {
      grid[free] = player;
      return false;
    }
    xfound = 0;
    ofound = 0;

  }

  xfound = 0;
  ofound = 0;

  //Code to check  diagonal cases for win
  for (int w = 0; w < dim; w++) {
    if (grid[(w * dim) + w] == 'X') {
      xfound++;
    }
    if (grid[(w * dim) + w] == 'O') {
      ofound++;
    }
    if (grid[(w * dim) + w] == '?') {
      free = (w * dim) + w;
    }
  }

  if (((xfound == (dim - 1) && (ofound == 0)))) {
    grid[free] = player;
    return false;
  } else if (((ofound == (dim - 1)) && (xfound == 0))) {
    grid[free] = player;
    return false;
  }

  xfound = 0;
  ofound = 0;
  for (int s = 0; s < dim; s++) {
    char c = grid[dim - 1];
    if (grid[(dim - 1) * (s + 1)] == 'X') {
      xfound++;
    }
    if (grid[(dim - 1) * (s + 1)] == 'O') {
      ofound++;
    }
    if (grid[(dim - 1) * (s + 1)] == '?') {
      free = (dim - 1) * (s + 1);
    }

  }
  if (((xfound == (dim - 1) && (ofound == 0)))) {
    grid[free] = player;
    return false;
  } else if (((ofound == (dim - 1)) && (xfound == 0))) {
    grid[free] = player;
    return false;
  }

  return true;
}


bool getRandChoiceAndUpdateGrid(char grid[], int dim, char player) {
  int start = rand() % (dim * dim);
  // look for an open location to play based on random starting location.
  // If that location is occupied, move on sequentially until wrapping and
  // trying all locations
  for (int i = 0; i < dim * dim; i++) {
    int loc = (start + i) % (dim * dim);
    if (grid[loc] == '?') {
      grid[loc] = player;
      return false;
    }
  }
  // No viable location
  return true;
}

int main() {
  // This array holds the actual board/grid of X and Os. It is sized
  // for the biggest possible case (11x11)
  char tttdata[121];

  // dim stands for dimension and is the side length of the
  // tic-tac-toe board i.e. dim x dim (3x3 or 5x5).
  int dim;
  int seed;

  // Get the dimension from the user
  cin >> dim >> seed;
  srand(seed);

  int dim_sq = dim * dim;

  for (int i = 0; i < dim_sq; i++) {
    tttdata[i] = '?';
  }

  // Print one of these messages when the game is over and before you quit
  const char xwins_msg[] = "X player wins!";
  const char owins_msg[] = "O player wins!";
  const char draw_msg[] = "Draw...game over!";

  bool done = false;
  char player = 'X';
  char player2 = 'O';

  // Show the initial starting board
  printTTT(tttdata, dim);

  int cnt = 0;

  while (!done) {

    int z = 0;
    cnt++;

    cout << "Player " << player << " enter your square choice [0-24], -1 (AI), or -2 (RANDOM): " << endl;
    cin >> z;

    if (z == -1) {
      getAiChoiceAndUpdateGrid(tttdata, dim, player);

    } else if (z == -2) {
      getRandChoiceAndUpdateGrid(tttdata, dim, player);
    } else {
      while ((z < -2 || z > dim_sq - 1) || tttdata[z] != '?') {
        if (z < -2 || z > (dim_sq - 1)) {
          exit(0);
        }
        cout << "Player " << player << " enter your square choice [0-24], -1 (AI), or -2 (RANDOM): " << endl;;
        cin >> z;
      }
      tttdata[z] = player;
    }

    printTTT(tttdata, dim);
    if (checkForWinner(tttdata, dim) == 1) {
      cout << xwins_msg;
      done = true;
      break;
    }
    if (checkForWinner(tttdata, dim) == 2) {
      cout << owins_msg;
      done = true;
      break;
    }
    if (checkForDraw(tttdata, dim)) {
      cout << draw_msg;
      done = true;
      break;
    }

    cout << "Player " << player2 << " enter your square choice [0-24], -1 (AI), or -2 (RANDOM): " << endl;
    cin >> z;

    if (z == -1) {
      getAiChoiceAndUpdateGrid(tttdata, dim, player2);

    } else if (z == -2) {
      getRandChoiceAndUpdateGrid(tttdata, dim, player2);
    } else {
      while ((z < -2 || z > dim_sq - 1) || tttdata[z] != '?') {
        if (z < -2 || z > (dim_sq - 1)) {
          exit(0);
        }
        cout << "Player " << player2 << " enter your square choice [0-24], -1 (AI), or -2 (RANDOM): " << endl;
        cin >> z;
      }
      tttdata[z] = player2;
    }

    printTTT(tttdata, dim);

    if (checkForWinner(tttdata, dim) == 1) {
      cout << xwins_msg;
      done = true;
      break;
    }
    if (checkForWinner(tttdata, dim) == 2) {
      cout << owins_msg;
      done = true;
      break;
    }
    if (checkForDraw(tttdata, dim)) {
      cout << draw_msg;
      done = true;
      break;
    }

  } // end while
  return 0;
}