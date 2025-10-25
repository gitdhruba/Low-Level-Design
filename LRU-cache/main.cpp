#include <iostream>
#include "./Cache.hpp"
#include "./Exception.hpp"
#include "./LRUCache.hpp"

using namespace std;

int main() {
    int cachesize;
    cout << "Enter cache size: ";
    cin >> cachesize;

    try {
        LRUCache<int, int> cache(cachesize);
        for (int i = 0; i <= cachesize; i++) {
            cache.put(i, i);
            cout << "put: " << i << endl;
        }

        int k = 0;
        cout << cache.get(k) << endl;
    }
    catch (const CacheException &e) {
        cout << e.what() << endl;
        return 1;
    }

    return 0;
}