class Solution:
    def minDistance(self, word1, word2):
        m = len(word1)
        n = len(word2)
        # dp[i][j] := min number of operations to convert word1[0..i) to word2[0..j)
        dp = [[0] * (n + 1) for _ in range(m + 1)]

        # to convert a word of length "i" into a word of length 0 it takes "i" deletions
        for i in range(1, m + 1):
            dp[i][0] = i

        # to convert a word of length "i" into a word of length "i" it takes "i" additions
        for j in range(1, n + 1):
            dp[0][j] = j

        for i in range(1, m + 1):
            for j in range(1, n + 1):
                if word1[i - 1] == word2[j - 1]:
                    # no operation needs to be done for this letter
                    dp[i][j] = dp[i - 1][j - 1]
                else:
                    # the letters are different so we will try the minimum between:
                    # replace the character in word1 with a character in word2: dp[i-1][j-1] + 1
                    # delete a character from word1: dp[i-1][j] + 1
                    # insert a character (word2[j-1]) in word1 (word1[i]): dp[i][j-1] + 1
                    dp[i][j] = min(dp[i - 1][j - 1] + 1, dp[i - 1]
                                   [j] + 1, dp[i][j - 1] + 1)

        return dp[m][n]
