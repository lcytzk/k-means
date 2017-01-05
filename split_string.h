#ifndef __SPLIT_STRING_H__
#define __SPLIT_STRING_H__

#include<string>
#include<vector>
#include<unordered_map>
#include<unordered_set>

void splitString(std::string &s, std::vector<std::string> &output, const char delimiter) {
    size_t start;
    size_t index = 0;

    while(index != std::string::npos) {
        index = s.find_first_not_of(delimiter, index);
        if(index == std::string::npos) break;
        start = index;
        index = s.find_first_of(delimiter, index);
        if(index == std::string::npos) {
            output.push_back(s.substr(start, s.size() - start));
            break;
        }
        output.push_back(s.substr(start, index - start));
    }
}

void splitStringAndHashWithCombo(std::string s, const char delimiter, std::vector<int> &x, float &y, std::vector<std::pair<std::string, std::string>> &combos, std::unordered_set<std::string> &ignores) {
    const char* c = s.c_str();
    uint64_t hash = 17;
    uint64_t hash2 = 17;
    bool first = true;
    bool group = false;
    std::unordered_map<std::string, std::vector<uint64_t>> groupMap;
    std::string groupname;
    char g[20];
    bool ignore = false;
    
    y = (atoi(s.substr(0, 2).c_str()) == 1) ? 1 : 0;

    while(*c) {
        while(*c && *c == delimiter) { ++c; }
        if(!*c) break;
        if(*c == '|') {
            ++c;
            hash = 17;
            char *t = g;
            ignore = false;
            while(*c && *c != delimiter) { 
                hash = hash * 31 + *c;
                *t = *c;
                ++c; ++t;
            }
            *t = 0;
            groupname = std::string(g);
            if(groupMap.find(groupname) == groupMap.end()) groupMap[groupname] = std::vector<uint64_t>();
            if(ignores.find(groupname) != ignores.end()) ignore = true;
            continue;
        }
        hash2 = hash;
        while(*c && *c != delimiter) { 
            hash2 = hash2 * 31 + *c;
            ++c;
        }
        if(first) {
            first = false;
        } else {
            groupMap[groupname].push_back(hash2);
            if(!ignore) x.push_back(hash2);
        }
    }
    for(auto &p : combos) {
        if(groupMap.find(p.first) == groupMap.end() || groupMap.find(p.second) == groupMap.end()) continue;
        std::vector<uint64_t> &fs1 = groupMap[p.first];
        std::vector<uint64_t> &fs2 = groupMap[p.second];
        for(uint64_t f1 : fs1) {
            uint64_t k = f1;
            for(uint64_t f2 : fs2) {
                x.push_back(k * 31 + f2);
            }
        }
    }
} 

void splitStringAndHash(std::string s, const char delimiter, std::vector<int>& x, float& y) {
    const char* c = s.c_str();
    uint64_t hash = 17;
    uint64_t hash2 = 17;
    bool first = true;
    bool group = false;
    
    y = (atoi(s.substr(0, 2).c_str()) == 1) ? 1 : 0;

    while(*c) {
        while(*c && *c == delimiter) { ++c; }
        if(!*c) break;
        if(*c == '|') {
            group = true;
            hash = 17;
        }
        hash2 = hash;
        while(*c && *c != delimiter) { 
            hash2 = hash2 * 31 + *c;
            ++c;
        }
        if(group) { 
            hash = hash2; 
            group = false; 
        } else {
            if(first) {
                first = false;
                continue;
            }
            x.push_back(hash2);
        }
    }
} 

void splitStringAndHashWithComboNoLabel(std::string s, const char delimiter, std::vector<int> &x, std::vector<std::pair<std::string, std::string>> &combos, std::unordered_set<std::string> &ignores) {
    const char* c = s.c_str();
    uint64_t hash = 17;
    uint64_t hash2 = 17;
    bool group = false;
    std::unordered_map<std::string, std::vector<uint64_t>> groupMap;
    std::string groupname;
    char g[20];
    bool ignore = false;
    
    while(*c) {
        while(*c && *c == delimiter) { ++c; }
        if(!*c) break;
        if(*c == '|') {
            ++c;
            hash = 17;
            char *t = g;
            ignore = false;
            while(*c && *c != delimiter) { 
                hash = hash * 31 + *c;
                *t = *c;
                ++c; ++t;
            }
            *t = 0;
            groupname = std::string(g);
            groupMap[groupname] = std::vector<uint64_t>();
            if(ignores.find(groupname) != ignores.end()) ignore = true;
            continue;
        }
        hash2 = hash;
        while(*c && *c != delimiter) { 
            hash2 = hash2 * 31 + *c;
            ++c;
        }
        groupMap[groupname].push_back(hash2);
        if(!ignore) x.push_back(hash2);
    }
    for(auto &p : combos) {
        if(groupMap.find(p.first) == groupMap.end() || groupMap.find(p.second) == groupMap.end()) continue;
        std::vector<uint64_t> &fs1 = groupMap[p.first];
        std::vector<uint64_t> &fs2 = groupMap[p.second];
        for(uint64_t f1 : fs1) {
            uint64_t k = f1;
            for(uint64_t f2 : fs2) {
                x.push_back(k * 31 + f2);
            }
        }
    }
} 

void splitStringAndHashNoLabel(std::string s, const char delimiter, std::vector<int>& x) {
    const char* c = s.c_str();
    uint64_t hash = 17;
    uint64_t hash2 = 17;
    bool group = false;

    while(*c) {
        while(*c && *c == delimiter) { ++c; }
        if(!*c) break;
        if(*c == '|') {
            group = true;
            hash = 17;
        }
        hash2 = hash;
        while(*c && *c != delimiter) { 
            hash2 = hash2 * 31 + *c;
            ++c;
        }
        if(group) { 
            hash = hash2; 
            group = false; 
        } else {
            x.push_back(hash2);
        }
    }
} 
#endif
