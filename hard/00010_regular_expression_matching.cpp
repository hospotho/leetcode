/*
Pattern type: CDAS

0. if str and pattern is empty return true
1. remove last A S
2. handle absorb case: C D
3. handle process case: AC
   AC => A (process C if A is C)
         C (process A)
4. handle remove case: AS SA SS AA0 AA1
   AS => S (remove A)
   SA => S (remove A)
   SS => S (remove S)
   AA => A (remove A if A is A)
   AA => A (handle A update absorb)
5. handle recursive case: AD
   AD => A (handle D update absorb)
6. handle recursive case: SC SD
strIndex++ until next C
check remove curr char and SC/SD
else strIndex++
*/

#include <algorithm>
#include <string>

class Solution {
 public:
  bool isMatch(std::string s, std::string p) {
    // check min char
    int minChar = p.length() - std::count(p.begin(), p.end(), '*') * 2;
    if (minChar > s.length()) return false;

    int strIndex = 0;
    int patternIndex = 0;
    int lastAbsorbCount = 0;
    char lastAbsorbChar = '\0';
    while ((strIndex < s.length() || lastAbsorbCount > 0) && patternIndex < p.length()) {
      // handle last A S
      if (patternIndex + 2 == p.length() && p[patternIndex + 1] == '*') {
        while (strIndex < s.length() && (s[strIndex] == p[patternIndex] || p[patternIndex] == '.')) {
          strIndex++;
        }
        return strIndex == s.length();
      }

      // handle absorb case: C D
      if (patternIndex + 1 == p.length() || (patternIndex + 1 < p.length() && p[patternIndex + 1] != '*')) {
        // handle absorb
        if (lastAbsorbCount > 0) {
          // remove absorb C
          if (s[strIndex - 1] == p[patternIndex] && p[patternIndex] == lastAbsorbChar) {
            patternIndex++;
            lastAbsorbCount--;
            minChar--;
            continue;
          }
          // try split and remove absorb D
          if (p[patternIndex] == '.') {
            std::string newStr = s.substr(strIndex + 1);
            std::string newPattern = p.substr(patternIndex + 1);
            if (isMatch(newStr, newPattern)) return true;
            patternIndex++;
            lastAbsorbCount--;
            minChar--;
            continue;
          }
          // reset absorb
          lastAbsorbCount = 0;
          lastAbsorbChar = '\0';
        }
        // normal case
        if ((s[strIndex] == p[patternIndex] || p[patternIndex] == '.')) {
          strIndex++;
          patternIndex++;
          minChar--;
          continue;
        }
        return false;
      }

      bool continueAsterisk = p[patternIndex + 1] == '*' && patternIndex + 3 < p.length() && p[patternIndex + 3] == '*';
      bool matchAll = p[patternIndex] == '.' || p[patternIndex + 2] == '.';
      bool samePatternChar = p[patternIndex] == p[patternIndex + 2];
      // handle process case: AC
      if (!continueAsterisk && !matchAll) {
        // remove C case
        if (samePatternChar) {
          if (s[strIndex] != p[patternIndex]) return false;
          strIndex++;
          p[patternIndex + 1] = p[patternIndex];
          p[patternIndex + 2] = '*';
          patternIndex++;
          minChar--;
          continue;
        } else {
          // remove A case
          while (strIndex < s.length() && (s[strIndex] == p[patternIndex])) {
            strIndex++;
            minChar--;
          }
          patternIndex += 2;
          continue;
        }
      }

      // handle remove case: AS SA SS AA0 AA1
      if (continueAsterisk) {
        // handle AS SA SS
        if (matchAll) {
          patternIndex += 2;
          p[patternIndex] = '.';
          continue;
        }
        // handle same AA
        if (samePatternChar) {
          patternIndex += 2;
          continue;
        }
        // handle diff AA
        while (strIndex < s.length() && (s[strIndex] == p[patternIndex])) {
          lastAbsorbChar = p[patternIndex];
          lastAbsorbCount++;
          strIndex++;
        }
        patternIndex += 2;
        continue;
      }

      // handle recursive case: AD
      if (p[patternIndex] != '.' && p[patternIndex + 2] == '.') {
        // check can remove AD (absorb 0)
        std::string newStr = s.substr(strIndex + 1);
        std::string newPattern = p.substr(patternIndex + 3);
        if (isMatch(newStr, newPattern)) return true;
        for (int i = 0; i < lastAbsorbCount; i++) {
          newStr = s.substr(strIndex - i);
          if (isMatch(newStr, newPattern)) return true;
        }
        // handle A and remove AD (absorb >1)
        while (strIndex < s.length() && (s[strIndex] == p[patternIndex])) {
          minChar--;
          strIndex++;
          if (s.length() == strIndex || minChar + strIndex > s.length()) return false;
          // check can remove AD
          newStr = s.substr(strIndex + 1);
          if (isMatch(newStr, newPattern)) return true;
        }
        // not match
        return false;
      }

      // handle recursive case: SC SD
      while (true) {
        // handle SD
        if (p[patternIndex + 2] == '.') {
          // check can remove SD (absorb 0)
          std::string newStr = s.substr(strIndex + 1);
          std::string newPattern = p.substr(patternIndex + 3);
          if (isMatch(newStr, newPattern)) return true;
          for (int i = 0; i < lastAbsorbCount; i++) {
            newStr = s.substr(strIndex - i);
            if (isMatch(newStr, newPattern)) return true;
          }
          // handle S and remove AD (absorb >1)
          while (strIndex < s.length()) {
            minChar--;
            strIndex++;
            if (s.length() == strIndex || minChar + strIndex > s.length()) return false;
            // check can remove SD
            newStr = s.substr(strIndex + 1);
            if (isMatch(newStr, newPattern)) return true;
          }
          // not match
          return false;
        }
        // find next C
        while (strIndex < s.length() && (s[strIndex] != p[patternIndex + 2])) {
          strIndex++;
        }
        // next C not found
        if (strIndex == s.length()) return false;
        // check can remove SC (absorb 0)
        std::string newStr = s.substr(strIndex + 1);
        std::string newPattern = p.substr(patternIndex + 3);
        if (isMatch(newStr, newPattern)) return true;
        // handle S and remove SC (absorb >1)
        while (strIndex < s.length()) {
          // find next C
          if (s[strIndex] != p[patternIndex + 2]) {
            minChar--;
            strIndex++;
            continue;
          }
          if (s.length() == strIndex || minChar + strIndex > s.length()) return false;
          // check can remove SD
          newStr = s.substr(strIndex + 1);
          if (isMatch(newStr, newPattern)) return true;
          strIndex++;
        }
        // not match
        return false;
      }
    }

    // handle remaining A S
    while (patternIndex + 1 < p.length() && p[patternIndex + 1] == '*') {
      patternIndex += 2;
    }

    return strIndex == s.length() && patternIndex == p.length();
  }
};
