# Solution - CPP

class Solution {
public:
    long long maxSubarraySum(vector<int>& nums, int k) {
        int n = nums.size();
        vector<long long int> presum(n+1,0);

        for(int i=0;i<n;i++){
            presum[i+1] = presum[i] + nums[i];
        }

        long long res = LLONG_MIN;

        for(int i=0;i<k;i++){
            long long currsum = 0;
            int s = i;
            int e = i + k -1;

            while(s<n && e<n){
                long long subsum = presum[e+1] - presum[s];

                currsum = max(subsum , currsum+subsum);

                res = max(res,currsum);

                s += k;
                e = s + k - 1;
            }
        }

        return res;
    }
};
