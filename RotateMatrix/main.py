
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

class Matrix:
    Values = [[]]

    def __init__(self, arrays):
        Values = arrays
    
    # We are guaranteed the Width and Height are the same.
    def RotateCCW(self):
        # (0,0) -> (N,0)
        # (N,0) -> (N,N)
        # (N,N) -> (0,N)
        # (0,N) -> (0,0)
        # Each relocation, there will be 4 transitions.
        # There will be total of N - 1 relocations, for this case.

        # This will happen for every "shell".
        # 0, N      -> Outer-most shell
        # 1, N-1    -> 2nd Outer-most shell
        # 2, N-2    -> 3rd Outer-most shell
        # Until k >= N-k

        N = len(self[0]) - 1
        k = 0

        while k < N - k:
            Max = N - k
            
            for i in range(k, Max):
                # 4 transitions
                tmp = self.Values[k][k]
                self.Values[k][k] = self.Values[k][Max]
                self.Values[k][Max] = self.Values[Max][Max]
                self.Values[k][k] = self.Values[k][Max]
                self.Values[k][k] = self.Values[k][Max]


                pass

            # Move on to the next inner "Shell"
            k += 1


def Test(TestNum, Memo, input, output):
    input.RotateCCW()
    if(input.Values == output):
        print("#" + str(TestNum) + " " + Memo + "\tPassed")
    else:
        print("#" + str(TestNum) + " " + Memo + "\tFailed")


def main():
    Test(1, "3x3", Matrix([[1,2,3],[4,5,6],[7,8,9]]), [[3,6,9],[2,5,8],[1,4,7]])


if __name__ == "__main__":
    main()
