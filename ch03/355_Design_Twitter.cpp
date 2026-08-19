#include "../common/Doubly_Linked_List.hpp"
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Twitter {
public:
    int globalCounter;
    struct tweetData {
        int globalId;
        int userId;
        int tweetId;
    };
    DLinkedList<tweetData> tweetsGlobalDLL;
    unordered_map<int, unordered_map<int, int>> usersAndFollowersMap;

    Twitter()
        : globalCounter(0)
        , tweetsGlobalDLL()
        , usersAndFollowersMap()
    {
    }

    void postTweet(int userId, int tweetId)
    {
        // we increment the GID before registering the tweet with it
        globalCounter++;
        // we add the tweet to the global tweets DLL
        tweetsGlobalDLL.addFront(tweetData {
            globalCounter, userId, tweetId });
        // in case the user isn't a registered user in the map
        // we must register the user and also follow the user themselves
        if (!usersAndFollowersMap.count({ userId })) {
            usersAndFollowersMap.insert({ userId, { { userId, 1 } } });
        }
        return;
    }

    vector<int> getNewsFeed(int userId)
    {
        vector<int> tweetsInFeed {};
        // first we ensure that the user themselves exist in the map.
        if (!usersAndFollowersMap.count(userId)) {
            return tweetsInFeed;
        }
        // next we need to traverse the DLL with the tweets from most to least recent, i.e.,
        // make a pointer to the header.next, lets call out pointer the iterator and with each new
        // node until iterator.next = trailer, we check if its userId lies within the internal map of
        // that user and we use count for that.
        DNode<tweetData>* iterator = tweetsGlobalDLL.header->next;
        int tweetCount = 0;
        while ((!(iterator == tweetsGlobalDLL.trailer)) && (tweetCount < 10)) {
            if (usersAndFollowersMap[userId].count(iterator->elem.userId)) {
                tweetsInFeed.push_back(iterator->elem.tweetId);
                tweetCount++;
            }
            iterator = iterator->next;
        }
        return tweetsInFeed;
    }

    void follow(int followerId, int followeeId)
    {
        // first we guard against that the user cannot follow themselves.
        if (followeeId == followerId) {
            return;
        }
        // first we need to ensure that the user is registered, if its not registered,
        // we register the user and the user itself as the follower.
        if (!usersAndFollowersMap.count(followerId)) {
            usersAndFollowersMap.insert({ followerId, { { followerId, 1 } } });
        }
        usersAndFollowersMap[followerId].insert({ followeeId, 1 });
        return;
    }

    void unfollow(int followerId, int followeeId)
    {
        // first guard against the equal condition.
        if (followeeId == followerId) {
            return;
        }

        // then ensure that the followee and follower are in the inner and outer maps respectively
        // that is, first we ensure the user is there and then we check if followee is in the internal map.
        if (!usersAndFollowersMap.count(followerId) || !usersAndFollowersMap[followerId].count(followeeId)) {
            return;
        }
        // finally we remove the followeeId from the inner map.
        usersAndFollowersMap[followerId].erase(followeeId);
        return;
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */

void printIntVector(vector<int>& v)
{
    cout << "[ ";
    for (const auto& x : v) {
        cout << x << " ";
    }
    cout << "]";
    cout << endl;
}

int main()
{

    Twitter* twitter = new Twitter();
    // User 1 posts a new tweet (id = 5).
    twitter->postTweet(1, 5);
    // User 1's news feed should return a list with 1 tweet id -> [5]. return [5]
    vector<int> resVec1 = twitter->getNewsFeed(1);
    printIntVector(resVec1);
    // User 1 follows user 2.
    twitter->follow(1, 2);
    // User 2 posts a new tweet (id = 6).
    twitter->postTweet(2, 6);
    // User 1's news feed should return a list with 2 tweet ids -> [6, 5].
    //  Tweet id 6 should precede tweet id 5 because it is posted after tweet id 5.
    vector<int> resVec2 = twitter->getNewsFeed(1);
    printIntVector(resVec2);
    // User 1 unfollows user 2.
    twitter->unfollow(1, 2);
    // User 1's news feed should return a list with 1 tweet id -> [5],
    // since user 1 is no longer following user 2.
    vector<int> resVec3 = twitter->getNewsFeed(1);
    printIntVector(resVec3);
    return 0;
}