
# Author: CJ Kim
# Date: 3/18/2020
# Title: Rotate Matrix by 90 degrees CCW
# Explain: Input: [1 2 3]
#                 [4 5 6]
#                 [7 8 9]
#          Output: [3 6 9]
#                  [2 5 8]
#                  [1 4 7]
#
# Note: Do not use extra memory space.
#

import numpy as np
import copy

class Matrix:
    #array of arrays
    Values = []

    def __init__(self, arrays):
        self.Values = arrays
    
    def PrintMatrix(self):
        print(np.array(self.Values))

    # We are guaranteed the Width and Height are the same.
    # Recursive through the Matrix, change the cores one at a time.
    # We still look throught the element in linear time.
    def RotateCCW(self):
        Arrays = []

        # Just loop through the right most columns and store them into arrays
        # Then hardcopy that array into Matrix.
        for i in range(len(self.Values) - 1, -1, -1):
            Arrays.append([row[i] for row in self.Values])

        self.Values = copy.deepcopy(Arrays)


def Test(TestNum, Memo, input, output):
    input.RotateCCW()
    if(input.Values == output):
        print("#" + str(TestNum) + " " + Memo + "\tPassed")
    else:
        print("#" + str(TestNum) + " " + Memo + "\tFailed")


def main():
    Test(1, "3x3", Matrix([[1,2,3],[4,5,6],[7,8,9]]), [[3,6,9],[2,5,8],[1,4,7]])
    Test(2, "4x4", Matrix([[1,2,3,4],[5,6,7,8],[9,10,11,12],[13,14,15,16]]), [[4,8,12,16],[3,7,11,15],[2,6,10,14],[1,5,9,13]])

if __name__ == "__main__":
    main()
