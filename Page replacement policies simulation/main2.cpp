#include <bits/stdc++.h>
#include <sys/time.h>
using namespace std;
#define ll long long
int pf = 0, s = 0;
struct pages
{
    int counter = 0, page_num, frame_num;
};
int total = 0;

int enter_time()
{
    struct timeval ob;
    gettimeofday(&ob, NULL);
    return ob.tv_usec;
}

struct frames
{
    int ref;
    int flag;
};

vector<int> splitAndConvertInput(string data)
{
    // split the string based on  separated values
    stringstream ss(data);
    string word;
    vector<int> sequence;
    while (ss >> word)
    {
        if (word[0] != '#')
        {
            sequence.push_back(stoi(word));
        }
        else
        {
            word = word.substr(1);
            sequence.push_back(-1 * stoi(word));
        }
        // cout << word << endl;
    }
    return sequence;
}

class LRUNode
{
public:
    int key;
    int value;
    LRUNode *next;
    LRUNode *prev;
    LRUNode(int k, int v)
    {
        key = k;
        value = v;
    }
};

class NFU
{
public:
    class node
    {
    public:
        int key;
        int val;
        int freq;
        node *next;
        node *prev;
        node(int k, int v, int f)
        {
            key = k;
            val = v;
            freq = f;
            node *next = NULL;
            node *prev = NULL;
        }
    };
    class listOfNodes
    {
    public:
        node *head;
        node *tail;
        listOfNodes()
        {
            head = new node(0, 0, 0);
            tail = new node(0, 0, 0);
            head->next = tail;
            tail->prev = head;
        }
    };
    int cap;
    int min_freq = INT_MAX;
    unordered_map<int, node *> hash;
    unordered_map<int, listOfNodes *> freq;
    void addNode(node *newNode, int frequency)
    {

        if (freq.find(frequency) == freq.end())
        {
            freq[frequency] = new listOfNodes();
        }
        listOfNodes *list = freq[frequency];
        node *prevNode = list->head;
        node *nextNode = list->head->next;
        prevNode->next = newNode;
        newNode->prev = prevNode;
        newNode->next = nextNode;
        nextNode->prev = newNode;
        min_freq = min(frequency, min_freq);
        int key = newNode->key;
        hash[key] = newNode;
        // cap+=1;
    }
    // bool flag=false;
    void deleteFunc(node *deleteNode)
    {
        // flag=false;
        node *nextNode = deleteNode->next;
        node *prevNode = deleteNode->prev;
        prevNode->next = nextNode;
        nextNode->prev = prevNode;
        deleteNode->next = NULL;
        deleteNode->prev = NULL;
        int key = deleteNode->key;
        // cout<<key<<endl;
        delete deleteNode;
        hash.erase(key);
    }
    bool checkListIsEmpty(int node_freq)
    {
        listOfNodes *list = freq[node_freq];
        node *head = list->head;
        node *tail = list->tail;
        if (head->next == tail and tail->prev == head)
            return true;
        else
            return false;
    }
    void updatePositionOfNode(node *upNode, int key, int value)
    {
        int node_freq = upNode->freq;
        deleteFunc(upNode);
        node *newNode = new node(key, value, node_freq + 1);
        addNode(newNode, node_freq + 1);
        if (checkListIsEmpty(node_freq) and min_freq == node_freq)
        {
            // cout<<"hello"<<" "<<key<<endl;
            min_freq = node_freq + 1;
        }
    }
    NFU(int capacity)
    {
        cap = capacity;
    }

    int get(int key)
    {
        if (hash.find(key) == hash.end())
        {
            return -1;
        }
        // return -1;
        else
        {

            node *upNode = hash[key];
            int val = upNode->val;
            updatePositionOfNode(upNode, key, val);
            return val;
        }
        return -1;
    }

    bool put(int key, int value)
    {

        if (cap == 0)
            return false;
        if (hash.find(key) == hash.end())
        {
            node *newNode = new node(key, value, 1);
            if (cap != hash.size())
            {
                addNode(newNode, 1);
            }
            else if (cap == hash.size())
            {

                listOfNodes *list = freq[min_freq];
                node *deleteNode = list->tail->prev;
                deleteFunc(deleteNode);
                addNode(newNode, 1);
                min_freq = 1;
            }
            return false;
        }
        else if (hash.find(key) != hash.end())
        {
            node *upNode = hash[key];
            updatePositionOfNode(upNode, key, value);
            return true;
        }
        return false;
    }
    void display()
    {
        for (auto each : hash)
        {
            cout << each.first << " ";
        }
        cout << endl;
    }
};

unordered_map<int, LRUNode *> LRUHash;

void addLRUNode(LRUNode *cur, LRUNode *head)
{
    cur->next = head->next;
    head->next->prev = cur;
    cur->prev = head;
    head->next = cur;
}

void removeLRUNode(LRUNode *cur)
{
    LRUNode *delprev = cur->prev;
    LRUNode *delnext = cur->next;
    delprev->next = delnext;
    delnext->prev = delprev;
}

void display(queue<int> q)
{
    while (!q.empty())
    {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

void display(vector<int> v)
{
    for (auto x : v)
        cout << x << " ";
    cout << endl;
}

void display(set<int> s)
{
    for (auto it = s.begin(); it != s.end(); it++)
        cout << *it << " ";
    cout << endl;
}

void display(LRUNode *head, LRUNode *tail)
{
    LRUNode *temp = head->next;
    while (temp != tail)
    {
        cout << temp->value << " ";
        temp = temp->next;
    }
    cout << endl;
}

set<int> fun(deque<int> dq)
{
    set<int> s;
    for (auto it = dq.begin(); it != dq.end(); it++)
        s.insert(*it);
    return s;
}

void makePos(vector<int> &v)
{
    for (int i = 0; i < v.size(); i++)
        v[i] = abs(v[i]);
}

void calculate(int frames, int hit, int miss, string fname)
{
    int total = hit + miss;
    cout << fname << endl;
    cout << "hits are " << hit << " "
         << "misses are " << miss << endl;
    cout << "hit ratio is " << float(hit) / total << endl;
    cout << "miss ratio is " << float(miss) / total << endl;
    FILE *fp;
    float hit_ratio = float(hit) / total;
    float miss_ratio = float(miss) / total;
    fp = fopen(fname.c_str(), "a");
    string content = "";
    content += to_string(frames) + " " + to_string(hit_ratio) + " " + to_string(miss_ratio) + "\n";
    fputs(content.c_str(), fp);
    fclose(fp);
}

void optimalPageReplacementAlgorithm(int noOfFrames, vector<int> pageSequence)
{
    unordered_set<int> sequence;
    int n = pageSequence.size();
    int hitCount = 0;
    int missCount = 0;
    for (int i = 0; i < n; i++)
    {
        int pageNo = abs(pageSequence[i]);
        // cout << pageNo << " ";
        if (sequence.find(pageNo) != sequence.end())
        {
            hitCount += 1;
            // cout << "hit" << endl;
        }
        else
        {
            if (sequence.size() < noOfFrames)
            {
                sequence.insert(pageNo);
                missCount += 1;
                // cout << "miss" << endl;
            }
            else if (sequence.size() == noOfFrames)
            {
                unordered_set<int> seq(sequence.begin(), sequence.end());
                for (int j = i + 1; j < n; j++)
                {
                    if (seq.find(pageSequence[j]) != seq.end())
                    {
                        seq.erase(pageSequence[j]);
                    }
                    if (seq.size() == 1)
                    {
                        break;
                    }
                }
                for (auto each : seq)
                {
                    sequence.erase(each);
                    break;
                }
                sequence.insert(pageNo);
                missCount += 1;
                // cout << "miss" << endl;
            }
        }
        // for (auto each : sequence)
        //     cout << each << " ";
        // cout << endl;
    }
    calculate(noOfFrames, hitCount, missCount, "optimal.txt");
    // cout << hitCount << " " << missCount << " " << noOfFrames << endl;
}

void LRUPageReplacementAlgorithms(int noOfFrames, vector<int> pageSequence)
{
    makePos(pageSequence);
    int cap = noOfFrames;
    LRUNode *head = NULL;
    LRUNode *tail = NULL;
    head = new LRUNode(-1, -1);
    tail = new LRUNode(-1, -1);
    LRUHash.clear();
    head->next = tail;
    tail->prev = head;
    int hitCount = 0;
    int missCount = 0;
    int itr = 1;
    for (auto each : pageSequence)
    {
        // key is a frame number
        int key = abs(each);
        // cout << key << " ";
        // insert a frame
        if (LRUHash.find(key) == LRUHash.end())
        {
            // cout << "miss" << endl;
            missCount += 1;
            LRUNode *newNode = new LRUNode(key, key);
            LRUHash[key] = newNode;
            addLRUNode(newNode, head);
            if (LRUHash.size() > cap)
            {
                LRUHash.erase(tail->prev->key);
                removeLRUNode(tail->prev);
            }
        }
        else
        {
            // cout << "hit" << endl;
            hitCount += 1;
            LRUNode *temp = LRUHash[key];
            removeLRUNode(temp);
            LRUNode *newNode = new LRUNode(key, key);
            addLRUNode(newNode, head);
            LRUHash[key] = newNode;
        }
        // cout << "iteration " << itr << "miss = " << missCount << endl;
        // display(head, tail);
        // itr++;
    }
    calculate(noOfFrames, hitCount, missCount, "lru.txt");
    // cout << hitCount << " " << missCount << " " << noOfFrames << endl;
}

void NFUPageReplacementAlgorithms(int noOfFrames, vector<int> pageSequence)
{
    // makePos(pageSequence);
    NFU obj = NFU(noOfFrames);
    int hitCount = 0;
    int missCount = 0;
    int itr = 1;
    for (auto each : pageSequence)
    {
        int key = abs(each);
        bool pageHit = obj.put(key, key);
        if (pageHit == true)
        {
            hitCount += 1;
        }
        else
        {
            missCount += 1;
        }
        // cout << "iteration " << itr << " miss = " << missCount << endl;
        // obj.display();
        // itr++;
    }
    calculate(noOfFrames, hitCount, missCount, "nfu.txt");
    // cout << hitCount << " " << missCount << " " << noOfFrames << endl;
}

void clock(int frameSize, int noOfPages, vector<int> referenceString)
{
    makePos(referenceString);
    int presentFrameSize = 0;
    int hitCount = 0, missCount = 0;
    unordered_map<int, int> umap;
    vector<int> frameArray;
    int indexPointer = 0;
    for (int i = 0; i < noOfPages; i++)
    {
        // cout << "frameArray ended" << endl;
        if (umap.find(referenceString[i]) != umap.end())
        {
            umap[referenceString[i]] = 1;
        }
        else
        {
            missCount += 1;
            if (presentFrameSize < frameSize)
            {
                umap[referenceString[i]] = 0;
                frameArray.push_back(referenceString[i]);
                presentFrameSize += 1;
                // cout ?<< missCount << endl;
            }
            else
            {
                while (umap[frameArray[indexPointer]] == 1)
                {
                    umap[frameArray[indexPointer]] = 0;
                    indexPointer = indexPointer + 1;
                    indexPointer = indexPointer % frameSize;
                }
                // cout << indexPointer << endl;
                // cout << frameArray[indexPointer] << endl;
                umap.erase(frameArray[indexPointer]);
                frameArray[indexPointer] = referenceString[i];
                umap.insert({referenceString[i], 0});
                indexPointer += 1;
                indexPointer = indexPointer % frameSize;
            }
        }
    }
    hitCount = noOfPages - missCount;
    calculate(frameSize, hitCount, missCount, "clock.txt");
    // cout << "No of Page Faults: " << missCount << endl;
    // cout << "No of Hits: " << noOfPages - missCount << endl;
    // for (int i = 0; i < frameSize; i++)
    // {
    //     cout << frameArray[i] << endl;
    // }
    // cout<<frameSize<<endl;
}

void secondChance(int frameSize, int noOfPages, vector<int> referenceString)
{
    cout << frameSize << " "
         << " " << noOfPages << endl;
    makePos(referenceString);
    deque<int> dq;
    unordered_map<int, int> pageMap;
    int presentFrameSize = 0;
    int hitCount = 0, missCount = 0;
    int itr = 1;
    for (auto it : referenceString)
    {
        if (pageMap.find(it) != pageMap.end())
        {
            pageMap[it] = 1;
        }
        else
        {
            missCount += 1;
            if (presentFrameSize < frameSize)
            {
                pageMap[it] = 0;
                dq.push_back(it);
                presentFrameSize += 1;
            }
            else
            {
                vector<int> tempVector;
                while (!dq.empty() && pageMap[dq.front()] != 0)
                {
                    int tempFront = dq.front();
                    dq.pop_front();
                    tempVector.push_back(tempFront);
                }
                if (dq.empty())
                {
                    pageMap.erase(tempVector[0]);
                    for (int i = tempVector.size() - 1; i >= 0; i--)
                    {
                        dq.push_front(tempVector[i]);
                    }
                }
                else
                {
                    pageMap.erase(dq.front());
                    dq.pop_front();
                    for (int i = tempVector.size() - 1; i >= 0; i--)
                    {
                        dq.push_front(tempVector[i]);
                        pageMap[tempVector[i]] = 0;
                    }
                }
                pageMap[it] = 0;
                dq.push_back(it);
            }
        }
        hitCount = noOfPages - missCount;
        // cout << "iteration " << itr << " miss = " << missCount << endl;
        // itr++;
        // display(temp)
    }
    calculate(frameSize, hitCount, missCount, "fisc.txt");
    // cout << missCount << endl;
}

void working_set(vector<int> pages, int frames)
{
    makePos(pages);
    int max_set_size = frames;
    set<int> s;
    deque<int> dq;
    int hit_count = 0;
    int miss_count = 0;
    for (int i = 0; i < max_set_size; i++)
    {
        if (s.count(pages[i]) == 0)
        {
            miss_count++;

            dq.push_back(pages[i]);
            s = fun(dq);
        }
        else
            hit_count++;
        // cout << "iteration " << i + 1 << "miss = " << miss_count << endl;
        // display(s);
    }
    for (int i = max_set_size; i < pages.size(); i++)
    {
        // int val_to_remove = pages[i - max_set_size];
        dq.pop_front();
        s = fun(dq);
        if (s.count(pages[i]) == 1)
            hit_count++;
        else
            miss_count++;
        dq.push_back(pages[i]);
        s = fun(dq);
        // cout << "iteration " << i + 1 << "miss = " << miss_count << endl;
        // display(s);
    }
    calculate(frames, hit_count, miss_count, "working_set.txt");
}

void random(vector<int> pages, int frames)
{
    makePos(pages);
    vector<int> v;
    map<int, int> mp;
    int hit = 0, miss = 0;
    srand(time(0));
    for (int i = 0; i < pages.size(); i++)
    {
        if (mp.find(pages[i]) == mp.end())
        {
            mp[pages[i]]++;
            miss++;
            // cout << "miss ";
            if (v.size() < frames)
                v.push_back(pages[i]);
            else
            {
                int ind = rand() % frames;
                int page_to_remove = v[ind];
                mp.erase(page_to_remove);
                v.erase(v.begin() + ind);
                v.push_back(pages[i]);
            }
        }
        else
        {
            // cout << "hit ";
            hit++;
        }
        // cout << i + 1 << " iteration "
        //      << "miss = " << miss << " ";
        // display(v);
    }
    calculate(frames, hit, miss, "random.txt");
}

void fifo(vector<int> pages, int frames)
{
    makePos(pages);
    queue<int> q;
    map<int, int> mp;
    int hit = 0, miss = 0;
    for (int i = 0; i < pages.size(); i++)
    {
        if (mp.find(pages[i]) == mp.end())
        {
            mp[pages[i]]++;
            miss++;
            if (q.size() < frames)
                q.push(pages[i]);
            else
            {
                int page_to_remove = q.front();
                q.pop();
                q.push(pages[i]);
                mp.erase(page_to_remove);
            }
        }
        else
        {
            hit++;
        }
        // cout << i + 1 << " ";
        // display(q);
    }
    calculate(frames, hit, miss, "fifo.txt");
}

void NRUPageReplacementAlgorithms(int noOfFrames, vector<int> pageSequence)
{

    // class_0 not modified and not referenced
    // class_1 not modified and referenced
    // class_2 referenced and not modified
    // class_3 referenced and modified
    unordered_map<int, vector<int>> nruTable;
    int hitCount = 0;
    int missCount = 0;
    int capacity = noOfFrames;
    unordered_map<int, int> hash; // page number and class number;
    int current_cap = 0;
    int clock_counter = 4;
    int counter = 0;
    for (auto each : pageSequence)
    {
        // cout << "as " << each << endl;
        if (counter % clock_counter == 0)
        {
            for (auto pageNo : nruTable[2])
            {
                nruTable[0].push_back(pageNo);
                hash[pageNo] = 0;
            }
            nruTable[2].clear();
            for (auto pageNo : nruTable[3])
            {
                nruTable[1].push_back(pageNo);
                hash[pageNo] = 1;
            }
            nruTable[3].clear();
        }
        int pageNo = abs(each);
        bool modified_bit = false;
        if (each < 0)
        {
            modified_bit = true;
            // hitCount-=1;
        }

        if (hash.find(pageNo) == hash.end())
        {
            missCount += 1;
            if (hash.size() < capacity)
            {
                nruTable[2].push_back(pageNo);
                hash[pageNo] = 2;
            }
            else if (hash.size() == capacity)
            {
                int classFromPageIsRemoved;
                for (int i = 0; i < 4; i++)
                {
                    if (nruTable[i].size() != 0)
                    {
                        classFromPageIsRemoved = i;
                        break;
                    }
                }
                int classSize = nruTable[classFromPageIsRemoved].size();
                srand(time(0));
                int randomIndex = rand() % classSize;
                int pageNumberToRemove = nruTable[classFromPageIsRemoved][randomIndex];
                auto it = find(nruTable[classFromPageIsRemoved].begin(), nruTable[classFromPageIsRemoved].end(), pageNumberToRemove);
                nruTable[classFromPageIsRemoved].erase(it);
                hash.erase(pageNumberToRemove);
                nruTable[2].push_back(pageNo);
                hash[pageNo] = 2;
            }
        }
        else
        {
            hitCount += 1;
            int pageClassNo = hash[pageNo];
            if (modified_bit == true)
            {
                if (pageClassNo == 3 or pageClassNo == 1)
                {
                    continue;
                }
                auto it = find(nruTable[pageClassNo].begin(), nruTable[pageClassNo].end(), pageNo);
                nruTable[pageClassNo].erase(it);
                int newClassNo = pageClassNo | 1;
                nruTable[newClassNo].push_back(pageNo);
                hash[pageNo] = newClassNo;
            }
            else if (modified_bit == false)
            {
                if (pageClassNo == 2 or pageClassNo == 3)
                {
                    // continue;
                }
                else
                {
                    auto it = find(nruTable[pageClassNo].begin(), nruTable[pageClassNo].end(), pageNo);
                    nruTable[pageClassNo].erase(it);
                    int newClassNo = pageClassNo | 2;
                    nruTable[newClassNo].push_back(pageNo);
                    hash[pageNo] = newClassNo;
                }
            }
        }
        // cout << each << endl;
        // counter += 1;
        // for (int i = 0; i < 4; i++)
        // {
        //     cout << "class no " << i << " ---";
        //     for (auto each : nruTable[i])
        //         cout << each << " ";
        //     cout << endl;
        // }
        // cout << "************************" << endl;
    }
    calculate(noOfFrames, hitCount, missCount, "nru.txt");
    // cout << hitCount << " " << missCount << " " << noOfFrames << endl;
}

bool compare(struct pages &a1, struct pages &a2)
{
    return a1.counter < a2.counter;
}

vector<pages> update(vector<pages> &vec)
{
    for (auto &i : vec)
    {
        i.counter >>= 1;
    }
    return vec;
}

bool add_page(vector<int> &free, int current, vector<pages> &cache)
{
    bool isFrameReplaced = false;
    for (int f = 0; f < free.size(); f++)
    {

        if (free[f] == -1) // found one free frame
        {
            pf++;
            s++;
            // cout << pf << " " << current << endl;
            free[f] = current;
            struct pages item;
            item.page_num = current;
            item.frame_num = f;
            item.counter = item.counter | 256;

            cache.push_back(item);

            isFrameReplaced = true;

            break;
        }
        else if (free[f] == current)
        {
            s++;

            for (auto &v : cache)
            {
                if (v.frame_num == f)
                {
                    v.page_num = current;
                    v.counter = v.counter | 256;
                }
            }

            isFrameReplaced = true;
            break;
        }
    }
    return isFrameReplaced;
}

void aging_algo(vector<int> page, int num_frames)
{
    pf = 0, s = 0;
    makePos(page);
    int n = page.size();
    vector<int> free;
    for (int i = 0; i < num_frames; i++)
    {
        free.push_back(-1);
    }
    vector<pages> cache;
    for (int p = 0; p < n; p++)
    {
        int current = page[p];
        if (!add_page(free, current, cache))
        {
            s++;
            pf++;
            sort(cache.begin(), cache.end(), compare);
            // cout << pf << " " << current << " " << cache[0].counter << endl;
            cache[0].page_num = current;
            cache[0].counter = 256;
            int frame_number = cache[0].frame_num;
            free[frame_number] = current;
        }
        if (s == num_frames)
        {
            s = 0;
            update(cache);
        }
    }
    int hits = n - pf;
    calculate(num_frames, hits, pf, "aging.txt");
}

void ws_clock(vector<int> &prf, int n)
{
    total = 0;
    makePos(prf);
    vector<frames> f;
    unordered_map<int, int> f_no;
    unordered_map<int, pair<frames, int>> info;
    int cf = 0, threshold = 80;
    int missCount = 0;
    for (int i = 0; i < prf.size(); i++)
    {
        // cout<<prf[i]<<endl;
        if (f_no.find(prf[i]) == f_no.end())
        {
            // cout<<i<<" "<<prf[i]<<endl;
            missCount++;
            if (total < n)
            {
                struct frames fr;
                fr.ref = enter_time();
                fr.flag = 0;
                f_no[prf[i]] = cf;
                info[cf] = {fr, prf[i]};
                total++;
                cf = (cf + 1) % n;
            }
            else
            {
                while (1)
                {
                    if (info[cf].first.flag == 0)
                    {
                        if (enter_time() - info[cf].first.ref > threshold)
                        {
                            f_no.erase(info[cf].second);
                            f_no[prf[i]] = cf;
                            info[cf].first.flag = 0;
                            info[cf].first.ref = enter_time();
                            info[cf].second = prf[i];
                            cf = (cf + 1) % n;
                            break;
                        }
                    }
                    else
                    {
                        info[cf].first.flag = 0;
                    }
                    cf = (cf + 1) % n;
                }
            }
        }
        else
        {
            info[f_no[prf[i]]].first.flag = 1;
            info[f_no[prf[i]]].first.ref = enter_time();
        }
    }
    int hits = prf.size() - missCount;
    calculate(n, hits, missCount, "wsclock.txt");
}

int main()
{
    ifstream in("input.txt");
    int i = 0;
    vector<int> pageSequence;
    string data;
    getline(in, data);
    pageSequence = splitAndConvertInput(data);
    // while (!in.eof())
    // {

    //     if (!in.eof())
    //     {
    //         getline(in, data);
    //     }
    //     else
    //     {
    //         cout << "invalid data" << endl;
    //     }

    //     pageSequence = splitAndConvertInput(data);
    // }
    for (auto each : pageSequence)
        cout << each << " ";
    cout << endl;
    cout << "---------PAGE REPLACEMENT ALGORITHM SIMULATION--------------------" << endl;
    while (true)
    {
        cout << "*********************************************************" << endl;
        cout << "enter 1 for single page replacement algorithm" << endl;
        cout << "enter 2 for all page replacement algorithms simulation" << endl;
        cout << "enter 3 for quit" << endl;
        cout << "*********************************************************" << endl;
        int c;

        cin >> c;
        if (c == 1)
        {
            system("/usr/bin/python3 remove.py");
            cout << "enter the number of frames" << endl;
            int noOfFrames;
            cin >> noOfFrames;
            cout << "select the type of algorithm" << endl;
            cout << "1. RANDOM" << endl;
            cout << "2. OPTIMAL" << endl;
            cout << "3. NRU" << endl;
            cout << "4. FIFO" << endl;
            cout << "5. FIFO WITH SECOND CHANCE" << endl;
            cout << "6. CLOCK" << endl;
            cout << "7. LRU" << endl;
            cout << "8. NFU" << endl;
            cout << "9. WORKING SET" << endl;
            cout << "10. AGING" << endl;
            cout << "11. WSCLOCK" << endl;
            int ch;
            cin >> ch;
            switch (ch)
            {
            case 1:
                random(pageSequence, noOfFrames);
                break;
            case 2:
                optimalPageReplacementAlgorithm(noOfFrames, pageSequence);
                break;
            case 3:
                NRUPageReplacementAlgorithms(noOfFrames, pageSequence);
                break;
            case 4:
                fifo(pageSequence, noOfFrames);
                break;
            case 5:
                secondChance(noOfFrames, pageSequence.size(), pageSequence);
                break;
            case 6:
                clock(noOfFrames, pageSequence.size(), pageSequence);
                break;
            case 7:
                LRUPageReplacementAlgorithms(noOfFrames, pageSequence);
                break;
            case 8:
                NFUPageReplacementAlgorithms(noOfFrames, pageSequence);
                break;
            case 9:
                working_set(pageSequence, noOfFrames);
                break;
            case 10:
                aging_algo(pageSequence, noOfFrames);
                break;
            case 11:
                ws_clock(pageSequence, noOfFrames);
                break;
            default:
                cout << "invalid input" << endl;
                break;
            }
            // system("/usr/bin/python3 hit.py");
        }
        if (c == 2)
        {
            system("/usr/bin/python3 remove.py");
            cout << "enter starting frame size: ";
            int start_frameSize, ending_frameSize;
            cin >> start_frameSize;
            cout << "enter ending frame size: ";
            cin >> ending_frameSize;
            for (int i = start_frameSize; i <= ending_frameSize; i++)
            {
                int noOfFrames = i;
                random(pageSequence, noOfFrames);
                optimalPageReplacementAlgorithm(noOfFrames, pageSequence);
                NRUPageReplacementAlgorithms(noOfFrames, pageSequence);
                fifo(pageSequence, noOfFrames);
                secondChance(noOfFrames, pageSequence.size(), pageSequence);
                clock(noOfFrames, pageSequence.size(), pageSequence);
                LRUPageReplacementAlgorithms(noOfFrames, pageSequence);
                NFUPageReplacementAlgorithms(noOfFrames, pageSequence);
                working_set(pageSequence, noOfFrames);
                aging_algo(pageSequence, noOfFrames);
                ws_clock(pageSequence, noOfFrames);
            }
            system("/usr/bin/python3 hit1.py");
            system("/usr/bin/python3 miss1.py");
            system("/usr/bin/python3 hit2.py");
        }
        if (c == 3)
        {
            break;
        }
    }
    return 0;
}