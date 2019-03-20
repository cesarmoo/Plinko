#include <iostream>
#include <cassert>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <vector>
using namespace std;

// asks user for experiment variables
// crashes if user enters invalid input
void userinput(int &numColumns, int &numRows, int &startColumn, int &numTrials) {
  cout << "Number of columns/boxes: ";
  cin >> numColumns;
  cout << "Number of peg rows: ";
  cin >> numRows;
  cout << "Column to start at [1-" << numColumns << "]: ";
  cin >> startColumn;
  cout << "Number of trials: ";
  cin >> numTrials;

  // checking against invalid input
  assert(numColumns > 0);
  assert(numRows > 0);
  assert(1 <= startColumn && startColumn <= numColumns);
  assert(numTrials > 0);
}

// runs the experiment
void run_experiment(int numColumns, int numRows, 
                  int startColumn, int numTrials, vector<int> &buckets) {
  srand(time(0));

  for (int trial = 0; trial < numTrials; ++trial) {
    int currColumn = startColumn;
    for (int row = 0; row < numRows; ++row) {
      // if at left wall, go right
      if (currColumn == 1) {
        ++currColumn;
      }

      // if at right wall, go left
      else if (currColumn == numColumns) {
        --currColumn;
      }

      // else, randomly go left or right
      else {
        int choice = rand() % 2;
        if (choice == 0) {
          --currColumn;
        }
        else {
          ++currColumn;
        }
      }
    }

    ++(buckets[currColumn - 1]);
  }
}

void print_bucket_contents(const vector<int> &buckets, int numTrials) {
  cout << "Bucket contents:\n";
  for (int b = 0; b < (int)buckets.size(); ++b) {
    cout << buckets[b] << " ";
  }

  cout << "\n\nBucket probabilities:\n";
  for (int b = 0; b < (int)buckets.size(); ++b) {
    cout << (buckets[b] / numTrials) << " ";
  }
  cout << endl;
}

int main() {
  // prompting user for experiment variables
  int numColumns; // 1-indexed
  int numRows; // 1-indexed; number of rows of pegs
  int startColumn;
  int numTrials;
  userinput(numColumns, numRows, startColumn, numTrials);

  // running the experiment
  vector<int> buckets(numColumns, 0);
  run_experiment(numColumns, numRows, startColumn, numTrials, buckets);

  // printing out bucket contents and probabilities
  print_bucket_contents(buckets, numTrials);

  return 0;
}