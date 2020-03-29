
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

class Matrix:
    #array of arrays
    Values = []

    def __init__(self, arrays):
        self.Values = arrays
    
    def PrintMatrix(self):
        print(np.array(self.Values))

    def RotateOutside(self):
        # 1 1 1 1 2
        # 4 - - - 2
        # 4 - - - 2
        # 4 - - - 2
        # 4 3 3 3 3
        #
        # Save Row #1.
        # Move Row #2 to #1.
        # Move Row #3 to #2.
        # Move Row #4 to #3.
        # Move Saved Row #1 to #4.
        #
        # Each corner is starting of each Row.

        Array1 = self.Values[0][:-1]
        Array2 = [row[-1] for row in self.Values][:-1]
        Array3 = list(reversed(self.Values[-1][1:])) # Corner is starting point of array.
        Array4 = list(reversed([row[0] for row in self.Values][1:]))

        for i in range(0, len(self.Values) - 1):
            # Move #2 to #1
            self.Values[0][i] = Array2[i]
            # Move #3 to #2
            self.Values[i][-1] = Array3[i]
            # Move #4 to #3
            self.Values[-1][len(self.Values) - 1 - i] = Array4[i]
            # Move #1 to #4
            self.Values[len(self.Values) - 1 - i][0] = Array1[i]

    # Outer is marked as "O"
    # Inner is marked as "I"
    #
    # O O O O O
    # O I I I O
    # O I I I O
    # O I I I O
    # O O O O O
    def GetInnerMatrix(self):
        Arrays = []

        for i in range(1, len(self.Values[0]) - 1):
            Array = self.Values[i][1:-1]
            Arrays.append(Array)

        return Matrix(Arrays)

    def MergeInnerMatrix(self, Inner):
        # The inner matrix is always be index 1 ~ N - 2
        # Skip the first and last arrays.

        for i in range(1, len(self.Values[0]) - 1):
            for j in range(1, len(self.Values[0]) - 1):
                self.Values[i][j] = Inner.Values[i - 1][j - 1]

    # We are guaranteed the Width and Height are the same.
    # Recursive through the Matrix, change the cores one at a time.
    # We still look throught the element in linear time.
    def RotateCCW(self):
        if len(self.Values) < 2:
            return self

        self.RotateOutside()
        NewInnerMatrix = self.GetInnerMatrix().RotateCCW()
        self.MergeInnerMatrix(NewInnerMatrix)

        return self



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
