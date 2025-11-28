# 3381. Maximum Subarray Sum With Length Divisible by K

**Difficulty:** 🟡 MEDIUM

**Topics/Tags:** `Array`, `Dynamic Programming`, `Prefix Sum`

---

## 📝 Problem Statement

You are given an array of integers `nums` and an integer `k`.

Return the maximum sum of a subarray of `nums`, such that the size of the subarray is divisible by `k`.

### Example 1:

**Input:** `nums = [1,2], k = 1`

**Output:** `3`

**Explanation:**

The subarray `[1, 2]` with sum `3` has length equal to `2` which is divisible by `1`.

### Example 2:

**Input:** `nums = [-1,-2,-3,-4,-5], k = 4`

**Output:** `-10`

**Explanation:**

The maximum sum subarray is `[-1, -2, -3, -4]` which has length equal to `4` which is divisible by `4`.

### Example 3:

**Input:** `nums = [-5,1,2,-3,4], k = 2`

**Output:** `4`

**Explanation:**

The maximum sum subarray is `[1, 2, -3, 4]` which has length equal to `4` which is divisible by `2`.

### Constraints:

*   `1 <= k <= nums.length <= 2 * 10^5`
*   `-10^9 <= nums[i] <= 10^9`

### Input
An array of integers `nums` and an integer `k`.

### Output
The maximum sum of a subarray whose length is divisible by `k`.

---


## 💡 Explanation

The solution utilizes a **prefix sum** array to efficiently calculate subarray sums. It then iterates through possible starting remainders modulo k, and for each remainder, it finds the maximum sum subarray whose length is a multiple of k by considering subarrays that start at indices with the same remainder modulo k. This is achieved by maintaining a running minimum prefix sum for each remainder.

---

## 🔑 Key Insights

1. The sum of a subarray `nums[i...j]` can be calculated as `prefixSum[j+1] - prefixSum[i]`. This is a fundamental technique for optimizing subarray sum queries.
2. The length of a subarray `nums[i...j]` is `j - i + 1`. For the length to be divisible by `k`, we need `(j - i + 1) % k == 0`, which implies `(j + 1) % k == i % k`.
3. By iterating through possible remainders `r` from `0` to `k-1`, we can group indices `i` and `j+1` such that `i % k == r` and `(j+1) % k == r`. This ensures that the subarray length `(j+1) - i` is a multiple of `k`.
4. To maximize `prefixSum[j+1] - prefixSum[i]` for a fixed `j+1` and a fixed remainder `r`, we need to find the minimum `prefixSum[i]` where `i % k == r` and `i <= j+1`. This is where the `min_prefix_sum` array comes into play.

---

## 🎯 Hints

1. Use a **prefix sum array** to quickly calculate the sum of any subarray.
2. Consider the **remainders of indices modulo k** to identify subarrays with lengths divisible by k.
3. Maintain the **minimum prefix sum encountered so far for each remainder modulo k**.
4. The problem can be rephrased as finding `max(prefixSum[j] - prefixSum[i])` such that `(j - i) % k == 0`.
5. Initialize the result to a very small number (e.g., `LLONG_MIN`) to handle cases with all negative numbers.
6. Handle the case where the subarray starts from the beginning of the array (i.e., `i = 0`). This can be done by initializing `min_prefix_sum[0]` to 0.

---

## 🔍 Algorithm

```
function maxSubarraySum(nums, k):
  n = nums.length
  prefixSum = array of size (n + 1) initialized to 0

  // Calculate prefix sums
  for i from 0 to n-1:
    prefixSum[i+1] = prefixSum[i] + nums[i]

  maxSum = negative infinity (e.g., LLONG_MIN)
  minPrefixSum = array of size k, initialized to positive infinity (e.g., LLONG_MAX)

  // Initialize for the case where the subarray starts from index 0
  minPrefixSum[0] = 0

  // Iterate through the prefix sums
  for j from 1 to n:
    currentRemainder = j % k

    // If we have seen a prefix sum with the same remainder before
    if minPrefixSum[currentRemainder] is not positive infinity:
      // Calculate the sum of a subarray ending at j-1 with length divisible by k
      // The subarray starts at an index i such that i % k == currentRemainder
      // The length is j - i, which is divisible by k if j % k == i % k
      currentSubarraySum = prefixSum[j] - minPrefixSum[currentRemainder]
      maxSum = max(maxSum, currentSubarraySum)

    // Update the minimum prefix sum for the current remainder
    // We are looking for prefixSum[i] where i % k == currentRemainder
    // The current prefixSum[j] is a candidate for future calculations
    minPrefixSum[currentRemainder] = min(minPrefixSum[currentRemainder], prefixSum[j])

  // If maxSum is still negative infinity, it means no valid subarray was found.
  // This can happen if k > n and no single element subarray is valid, or if all possible sums are negative.
  // However, the problem guarantees 1 <= k <= nums.length, so at least one subarray of length k exists.
  // If all numbers are negative, the result will be the largest negative sum.
  // If no subarray of length divisible by k can be formed (e.g., k > n, which is not allowed by constraints), we might return LLONG_MIN.
  // But given constraints, a valid subarray always exists.

  return maxSum

```

---

## 📋 Approach

1. **Calculate Prefix Sums**: Create a `prefixSum` array where `prefixSum[i]` stores the sum of elements from `nums[0]` to `nums[i-1]`. This allows for O(1) calculation of any subarray sum.
2. **Initialize Minimum Prefix Sums**: Create an array `minPrefixSum` of size `k`. `minPrefixSum[r]` will store the minimum prefix sum encountered so far for indices `i` such that `i % k == r`.
3. **Handle Base Case**: Initialize `minPrefixSum[0]` to 0. This accounts for subarrays that start from the beginning of the `nums` array (index 0).
4. **Iterate and Update**: Iterate through the `prefixSum` array from index `j = 1` to `n`.
5. **Calculate Current Remainder**: For each `j`, determine `currentRemainder = j % k`.
6. **Find Potential Maximum Sum**: If `minPrefixSum[currentRemainder]` is not its initial large value (meaning we've encountered a previous prefix sum with the same remainder), calculate `currentSubarraySum = prefixSum[j] - minPrefixSum[currentRemainder]`. This `currentSubarraySum` represents the sum of a subarray ending at `nums[j-1]` whose length is divisible by `k`.
7. **Update Maximum Sum**: Update `maxSum = max(maxSum, currentSubarraySum)`.
8. **Update Minimum Prefix Sum**: Update `minPrefixSum[currentRemainder] = min(minPrefixSum[currentRemainder], prefixSum[j])`. This ensures that for future iterations, we have the smallest possible starting prefix sum for a given remainder.
9. **Return Result**: After iterating through all `j`, `maxSum` will hold the maximum subarray sum with a length divisible by `k`.

---

## 🚶 Step-by-Step Walkthrough

Let's walk through `nums = [-5, 1, 2, -3, 4], k = 2`.

**Initialization:**
`n = 5`, `k = 2`
`prefixSum = [0, 0, 0, 0, 0, 0]` (size n+1)
`maxSum = -Infinity`
`minPrefixSum = [Infinity, Infinity]` (size k)
`minPrefixSum[0] = 0`

**Step 1: Calculate Prefix Sums**

| i | nums[i] | prefixSum[i+1] |
|---|---------|----------------|
| 0 | -5      | -5             |
| 1 | 1       | -4             |
| 2 | 2       | -2             |
| 3 | -3      | -5             |
| 4 | 4       | -1             |

`prefixSum = [0, -5, -4, -2, -5, -1]`

--- 

**Step 2: Iterate and Update**

**j = 1:**
`prefixSum[1] = -5`
`currentRemainder = 1 % 2 = 1`
`minPrefixSum[1]` is `Infinity`. No update to `maxSum`.
`minPrefixSum[1] = min(Infinity, prefixSum[1]) = min(Infinity, -5) = -5`
`minPrefixSum = [0, -5]`

**j = 2:**
`prefixSum[2] = -4`
`currentRemainder = 2 % 2 = 0`
`minPrefixSum[0]` is `0`.
`currentSubarraySum = prefixSum[2] - minPrefixSum[0] = -4 - 0 = -4` (This corresponds to subarray `[-5, 1]`, length 2)
`maxSum = max(-Infinity, -4) = -4`
`minPrefixSum[0] = min(0, prefixSum[2]) = min(0, -4) = -4`
`minPrefixSum = [-4, -5]`

**j = 3:**
`prefixSum[3] = -2`
`currentRemainder = 3 % 2 = 1`
`minPrefixSum[1]` is `-5`.
`currentSubarraySum = prefixSum[3] - minPrefixSum[1] = -2 - (-5) = 3` (This corresponds to subarray `[1, 2]`, length 2)
`maxSum = max(-4, 3) = 3`
`minPrefixSum[1] = min(-5, prefixSum[3]) = min(-5, -2) = -5`
`minPrefixSum = [-4, -5]`

**j = 4:**
`prefixSum[4] = -5`
`currentRemainder = 4 % 2 = 0`
`minPrefixSum[0]` is `-4`.
`currentSubarraySum = prefixSum[4] - minPrefixSum[0] = -5 - (-4) = -1` (This corresponds to subarray `[1, 2, -3]`, length 3 - wait, this is not right. The logic is `prefixSum[j] - minPrefixSum[i]` where `j % k == i % k`. Here `j=4`, `i` could be `0` or `2`. If `i=0`, length is `4-0=4`. If `i=2`, length is `4-2=2`. The `minPrefixSum[0]` is `-4` which corresponds to `prefixSum[2]`. So the subarray is `nums[2...3] = [2, -3]`, sum is `-1`. Length is `4-2=2`.)
`maxSum = max(3, -1) = 3`
`minPrefixSum[0] = min(-4, prefixSum[4]) = min(-4, -5) = -5`
`minPrefixSum = [-5, -5]`

**j = 5:**
`prefixSum[5] = -1`
`currentRemainder = 5 % 2 = 1`
`minPrefixSum[1]` is `-5`.
`currentSubarraySum = prefixSum[5] - minPrefixSum[1] = -1 - (-5) = 4` (This corresponds to subarray `[1, 2, -3, 4]`, length 4. `j=5`, `i` could be `1` or `3`. `minPrefixSum[1]` is `-5` which corresponds to `prefixSum[1]`. So the subarray is `nums[1...4] = [1, 2, -3, 4]`, sum is `4`. Length is `5-1=4`.)
`maxSum = max(3, 4) = 4`
`minPrefixSum[1] = min(-5, prefixSum[5]) = min(-5, -1) = -5`
`minPrefixSum = [-5, -5]`

**Final Result:** `maxSum = 4`


---

## 📊 Complexity Analysis

### Time Complexity
**O(n)** - We iterate through the `nums` array once to calculate prefix sums, and then we iterate through the prefix sums array once (which has `n+1` elements). The operations inside the loop are constant time. Therefore, the overall time complexity is linear with respect to the size of the input array `n`.

### Space Complexity
**O(n)** - We use a `prefixSum` array of size `n+1` to store prefix sums. We also use a `minPrefixSum` array of size `k`. Since `k <= n`, the dominant space complexity comes from the `prefixSum` array, resulting in O(n) space complexity.

---

## ⚠️ Edge Cases

- **All negative numbers**: The algorithm correctly handles cases where all numbers in `nums` are negative. The `maxSum` will be updated with the largest (least negative) sum of a subarray whose length is divisible by `k`. For example, `nums = [-1, -2, -3, -4, -5], k = 4` should return `-10` (from `[-1, -2, -3, -4]`).
- **k = 1**: If `k` is 1, any subarray length is divisible by `k`. The problem reduces to finding the maximum subarray sum (Kadane's algorithm). This solution will correctly find it because `j % 1` is always 0, and `minPrefixSum[0]` will track the minimum prefix sum, effectively implementing Kadane's logic.
- **k = nums.length**: If `k` is equal to the length of the array, the only subarray with a length divisible by `k` is the entire array itself. The algorithm will correctly calculate its sum.
- **Large positive and negative numbers**: The use of `long long` for sums and prefix sums prevents integer overflow, which is crucial given the constraint `-10^9 <= nums[i] <= 10^9` and `n <= 2 * 10^5`.

---

## 📥 Examples

### Example 1
**Input:** `nums = [1,2], k = 1`
**Output:** `3`

### Example 2
**Input:** `nums = [-1,-2,-3,-4,-5], k = 4`
**Output:** `-10`

### Example 3
**Input:** `nums = [-5,1,2,-3,4], k = 2`
**Output:** `4`

---
*Generated on 2025-11-28 07:07:47*
