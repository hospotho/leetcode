#include <string>
#include <unordered_map>
#include <vector>

class Solution {
public:
  std::vector<std::vector<std::string>>
  groupAnagrams(std::vector<std::string> &strs) {
    unsigned long long count[26] = {};
    unsigned long long gp1Id = 0;
    unsigned long long gp2Id = 0;
    unsigned long long gp3Id = 0;
    unsigned long long hashId = 0;
    unsigned int current = 0;
    unsigned int index = 0;
    std::unordered_map<unsigned long long, unsigned int> indexMap(512);
    std::vector<std::vector<std::string>> stringGroup;
    stringGroup.reserve(strs.size());

    for (std::string str : strs) {
      // update char count
      std::fill(std::begin(count), std::end(count), 0);
      for (char ch : str) {
        count[ch - 'a']++;
      }

      // get group id
      gp1Id = count[0] | (count[1] << 7) | (count[2] << 14) | (count[3] << 21) |
              (count[4] << 28) | (count[5] << 35) | (count[6] << 42) |
              (count[7] << 49) | (count[8] << 56);
      gp2Id = count[9] | (count[10] << 7) | (count[11] << 14) |
              (count[12] << 21) | (count[13] << 28) | (count[14] << 35) |
              (count[15] << 42) | (count[16] << 49) | (count[17] << 56);
      gp3Id = count[18] | (count[19] << 7) | (count[20] << 14) |
              (count[21] << 21) | (count[22] << 28) | (count[23] << 35) |
              (count[24] << 42) | (count[25] << 49);

      // hash
      hashId = 0xA974B1335FC44A6A;
      hashId ^= gp1Id + 0x9E3779B97F4A7C13 + (hashId << 6) + (hashId >> 2);
      hashId ^= gp2Id + 0x9E3779B97F4A7C13 + (hashId << 6) + (hashId >> 2);
      hashId ^= gp3Id + 0x9E3779B97F4A7C13 + (hashId << 6) + (hashId >> 2);

      // get global index
      if (indexMap.find(hashId) == indexMap.end()) {
        indexMap[hashId] = current;
        index = current++;
        stringGroup.push_back(std::vector<std::string>());
      } else {
        index = indexMap[hashId];
      }

      // add to group
      stringGroup[index].push_back(std::move(str));
    }

    return stringGroup;
  }
};
