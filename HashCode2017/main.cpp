//
//  main.cpp
//  HashCode2017
//
//  Created by Giorgi Ghughunishvili on 2/23/17.
//  Copyright © 2017 Giorgi Ghughunishvili. All rights reserved.
//

/*
 
/ rd_statistics [ ENDPOINT_ID ]    [ VIDEO_ID ] = REQUEST_NUMBER;
 
 caches_latencies [ ENDPOINT_ID ]    [ CACHE_ID ] = LATENCY;
 
 video_sizes [ VIDEO_ID ] = SIZE;
 
 datacenter_latencies [ ENDPOINT_ID ] = LATENCY
 
 
 */

#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <set>

using namespace std;


int main() {
    int VIDEOS, ENDPOINTS, REQUESTS, CACHES, CACHE_CAPACITY;
    
    int tmp_dc_latency, num_of_caches,
        tmp_cache_id, tmp_cache_latency,
        tmp_video_id, tmp_endpoint_id, tmp_request_number;
    
    ifstream fin("kittens.in");
    //ifstream fin("input.in");
    ofstream fout("kittens.out");
    fin>>VIDEOS>>ENDPOINTS>>REQUESTS>>CACHES>>CACHE_CAPACITY;
    ////////////// Answer Vars \\\\\\\\\\\\\\\\\
    
    vector<vector<int>> video_caches;
    video_caches.resize(CACHES);
    
    vector<int> left_sizes(CACHES, CACHE_CAPACITY);
    
    set <int> seen_videos;
    
    //////////////// Input Vars \\\\\\\\\\\\\\\\\\\\\\\\\
    
    // Statistics with sets
    
    
    
    
    
    
    //Video Sizes
    vector<int> video_sizes;
    video_sizes.resize(VIDEOS);
    
    // Each Cache Latencies depending on endpoint
//    vector<vector<int>> caches_latencies;
//    caches_latencies.resize(CACHES);
    
    vector<set<pair<int,int>>> caches_latencies;
    caches_latencies.resize(CACHES);
    
    // Datacenter Latencies depending on endpoint
    vector<int> datacenter_latencies;
    datacenter_latencies.resize(ENDPOINTS);
    
    // Request Details statistics depending on endpoint with caches
//    vector< vector<int> > rd_statistics;
//    rd_statistics.resize(ENDPOINTS);
//    for (int i=0; i<CACHES; i++) {
//        vector<int> tmp_caches;
//        tmp_caches.resize(CACHES);
//        rd_statistics[i] = tmp_caches;
//    }
    vector< set<pair<int,int>> > rd_statistics;
    rd_statistics.resize(ENDPOINTS);
    
    
    // Enter Videos
    for (int i=0; i<VIDEOS; i++) {
        fin>>video_sizes[i];
    }
    
    // Enter Caches
    for (int i=0; i<ENDPOINTS; i++) {
        
        fin>>tmp_dc_latency>>num_of_caches;
        
        // DC Latancy
        datacenter_latencies[i] = tmp_dc_latency;
        
        set<pair<int, int>> tmp_set;
        for (int j=0; j<num_of_caches; j++) {
            fin>>tmp_cache_id>>tmp_cache_latency;
            tmp_set.insert(make_pair(tmp_cache_latency, tmp_cache_id));
        }
        caches_latencies[i] = tmp_set;
    }
    
    // Enter statistics Request descriptions
    for (int i=0; i<REQUESTS; i++) {
        fin>>tmp_video_id>>tmp_endpoint_id>>tmp_request_number;
        rd_statistics[tmp_endpoint_id].insert(make_pair(tmp_request_number, tmp_video_id));
    }
    
    ///////////////////// Main Part \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
    
    //for (set<pair<int,int>>::reverse_iterator it=caches_latencies.rbegin(); it!=caches_latencies.rend(); ++it){
    
    for (int i=0; i<ENDPOINTS; i++) {
        set<pair<int,int>> tmp_set = rd_statistics[i];
        if (tmp_set.size() == 0) {
            continue;
        }
        for (set<pair<int,int>>::reverse_iterator it=tmp_set.rbegin(); it!=tmp_set.rend(); ++it) {
            pair<int, int> p = *it;
            cout<<i<<"  "<<p.first<<"   "<<p.second<<endl;
            if (video_sizes[p.second] > CACHE_CAPACITY){
                continue;
            }
            
            if (caches_latencies[i].size() < 1) {
                continue;
            }
            /// lets loop in the caches
            for (set<pair<int,int>>::iterator itt=caches_latencies[i].begin(); itt!=caches_latencies[i].end(); ++itt){
                tmp_cache_id = (*itt).second;
                
                vector<int>::iterator it;
                it = find(video_caches[tmp_cache_id].begin(), video_caches[tmp_cache_id].end(), p.second);
                if (left_sizes[tmp_cache_id] >= video_sizes[p.second] && it == video_caches[tmp_cache_id].end()) {
                    left_sizes[tmp_cache_id]-=video_sizes[p.second];
                    video_caches[tmp_cache_id].push_back(p.second);
                }
                
            }
        }
    }
    
    
    
    ///////////////// Algorithm \\\\\\\\\\\\\\\\
    
    int c_count = 0;
    for (int i=0; i<CACHES; i++) {
        if ( video_caches.size() >0 ) {
            c_count++;
        }
    }
    
    fout<<c_count<<endl;
    for (int i=0; i<CACHES; i++) {
        if ( video_caches.size() >0 ) {
            fout<<i;
            for (int j=0; j<video_caches[i].size(); j++) {
                fout<<" "<<video_caches[i][j];
            }
            fout<<endl;
        }
    }
    
    
    
    
    return 0;
}
