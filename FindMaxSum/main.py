
# Author: CJ Kim
# Date: 3/21/2020
# Title: Find the Sum of SubArray with Consecutive Numbers
# Explain: Input: [-2, 2, 5, -11, 6]
#          Output: 7
# Note: The size of SubArray is not determined. It must be at least 1.
#		The SubArray could be the entire Array if necessary.
#

# The hint is that the elements must be consecutive.
# Everytime we iterate thru the array, we find if the Sum has became greater
# or smaller. Smaller means just start over the whole "summing up" process.
def FindSumSubArray(Array):
	MaxSum = Array[0]
	CurrentSum = MaxSum

	for element in Array:
		# Find whichever current sum gives higher value, if "element" itself
		# is bigger than the "CurrentSum + element", then we choose "element"
		# and practically "start over".
		CurrentSum = max(CurrentSum + element, element)

		# Once the CurrentSum is determined, check if that became greater than
		# the current MaxSum. If so, update.
		MaxSum = max(MaxSum, CurrentSum)

	return MaxSum



def Test(TestNum, Memo, Array, output):
    if(FindSumSubArray(Array) == output):
        print("#" + str(TestNum) + " " + Memo + "\tPassed")
    else:
        print("#" + str(TestNum) + " " + Memo + "\tFailed")



def main():
    Test(1, "Size of 2",[-2,2,5,-11,6], 7)
    Test(1, "Size of 4",[-2,2,1,-1,6], 8)
    Test(1, "Size of 1",[-2,2,-5,-1,6], 6)



if __name__ == "__main__":
	main()