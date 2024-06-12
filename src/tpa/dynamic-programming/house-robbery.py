class Solution(object):
    def rob(self, nums):
        n = len(nums)
        robberies = [0] * n
        for i in range(0, n):
            if (i == 0):
                robberies[0] = nums[0]
            elif (i == 1):
                robberies[1] = max(nums[1], nums[0])
            else:
                robberies[i] = max(robberies[i-1], robberies[i-2] + nums[i])
        return robberies[n - 1]
