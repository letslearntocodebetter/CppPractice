
void DutchNationFlag(std::vector<int> & nums) {
    if (nums.empty()) return;
    int low = 0;
    int high = nums.size() - 1;
    int mid = low + (high - low)/2;
    
    while (mid < high) {
       switch (nums[mid]) {
        case 0 :
            std::swap(nums[low], nums[mid]);
            mid++;
            low++;
            break;
        case 2 :
            std::swap(nums[mid], nums[high]);
            high--;
            break;
        case 1: 
            mid++;
            break;
        }
    }

}