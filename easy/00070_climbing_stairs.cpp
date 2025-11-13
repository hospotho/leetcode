/*
// level i = (n-i)Ci
function climbStairs(n) {
  let ans = 1
  let current = n - 1
  for (let i = 1; i <= Math.floor(n / 2); i++) {
    ans += current
    current = (((current * (n - i * 2)) / (i + 1)) * (n - i * 2 - 1)) / (n - i)
  }
  return ans
}
// from observation => fibonacci sequence
function climbStairsV2(n) {
  let a = 1, b = 2
  for (let i = 3; i <= n; i++) {
    let c = a + b
    a = b
    b = c
  }
  return n === 1 ? 1 : b
}
*/

class Solution {
 public:
  constexpr int climbStairs(int n) {
    constexpr int ans[45] = {1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025, 121393, 196418, 317811, 514229, 832040, 1346269, 2178309, 3524578, 5702887, 9227465, 14930352, 24157817, 39088169, 63245986, 102334155, 165580141, 267914296, 433494437, 701408733, 1134903170, 1836311903};
    if (n >= 1 && n <= 45) return ans[n - 1];
    return 0;
  }
};
