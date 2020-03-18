
# Author: CJ Kim
# Date: 3/18/2020
# Title: Find the Area of Overlapping Rectangles
# Explain: Input: [(0,5), (5,0)], [(4,8), (8,4)]
#          Output: 1
# Note: The coordinates are written in normal XY plane grid.
#       The order is [(TopLeftX, TopLeftY), (BottomRightX, BottomRightY)]
#

class Rect:
    TopLeftX = None
    TopLeftY = None
    BotRightX = None
    BotRightY = None

    def __init__(self, topX = 0, topY = 0, botX = 0, botY = 0):
        self.TopLeftX = topX
        self.TopLeftY = topY
        self.BotRightX = botX
        self.BotRightY = botY


def FindOverlappingArea(Rect1, Rect2):
    # Compare 2 leftmost x coords, find the biggest of those two.
    LeftX = max(Rect1.TopLeftX, Rect2.TopLeftX)

    # Find the smallest of rightmost x coords.
    RightX = min(Rect1.BotRightX, Rect2.BotRightX)

    # Do the same for Y coords. Compare topmost and find smallest,
    # compare bottom-most and find the biggest.
    TopY = min(Rect1.TopLeftY, Rect2.TopLeftY)
    BottomY = max(Rect1.BotRightY, Rect2.BotRightY)
    
    Width = RightX - LeftX
    Height = TopY - BottomY

    # If either Width or Height is negative, we know there was no overlapping.
    if Width <= 0 or Height <= 0:
        return 0
    else:
        return Width * Height

def Test(TestNum, Memo, Rect1, Rect2, output):
    if(FindOverlappingArea(Rect1, Rect2) == output):
        print("#" + str(TestNum) + " " + Memo + "\tPassed")
    else:
        print("#" + str(TestNum) + " " + Memo + "\tFailed")

def main():
    Test(1, "Simple Overlap",Rect(0,5,5,0), Rect(4,8,8,4), 1)
    Test(2, "No Overlap", Rect(0,5,5,0), Rect(5,8,8,5), 0)
    Test(3, "Identical Rects", Rect(0,5,5,0), Rect(0,5,5,0), 25)


if __name__ == "__main__":
    main()