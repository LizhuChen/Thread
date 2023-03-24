#include <iostream> // cout, endl
#include <fstream> // open, is_open, close, ignore
#include <string> // string, find_last_of, substr
#include <string.h> // string, find_last_of, substr
#include <vector> // vector, push_back
#include <cstdlib> // system, atoi
#include <sstream>
#include <stdio.h>
#include <ctime>
#include <algorithm>
#include <stdlib.h>
#include <thread>
#include <mutex> 
#include<Windows.h>

#include <sys/fcntl.h> 
#include <unistd.h> 
#include <sys/types.h>


using namespace std;

string input ;
string command ;
mutex mtx;


void BubbleSort ( vector<int> &cSet) {
    
    for( int i = 0 ; i < cSet.size() ; i++) {
        
        for( int j = 0; j < cSet.size() ; j++) {
        	
            if( cSet[j] > cSet[i] ) {
			                
                int temp = cSet[j] ;
                cSet[j] = cSet[i] ;
                cSet[i] = temp ;
                
            }
        }
    }
}

void BubbleSort2( vector< vector<int> > &cSet) {
	for(int k = 0 ; k < cSet.size() ; k ++ ) {
    	for( int i = 0 ; i < cSet[k].size() ; i++) {
        
        	for( int j = 0; j < cSet[k].size() ; j++) {
        	
            	if( cSet[k][j] > cSet[k][i] ) {
			                
                	int temp = cSet[k][j] ;
                	cSet[k][j] = cSet[k][i] ;
                	cSet[k][i] = temp ;
                
            	}
        	}
    	}
 	}
}

void Merge(vector<int> &c1Set, vector<int> &c2Set) { 
    int left = 0 ;
    int right = 0 ;
	vector<int> cSet ;
  	mtx.lock();
    while ( left < c1Set.size() && right < c2Set.size())  { 
        if ( c1Set[left] <= c2Set[right] ) { 
            cSet.push_back(c1Set[left]); 
            left = left + 1 ; 
        } 
        else { 
        	cSet.push_back(c2Set[right]); 
            right = right + 1 ; 
        } 
    } 
  
    while ( left < c1Set.size()) { 
        cSet.push_back(c1Set[left]); 
        left = left + 1 ; 
    } 
  
    while ( right < c2Set.size()) { 
        cSet.push_back(c2Set[right]); 
        right = right + 1 ; 
    } 
    
    c1Set = cSet ;
    mtx.unlock();
} 

void Merge2(vector< vector<int> > &cSet) { 

	for(int k = 1 ; k < cSet.size(); k++) {
	
    	int left = 0 ;
    	int right = 0 ;
		vector<int> temp_cSet ;

    	while ( left < cSet[0].size() && right < cSet[k].size())  { 
    	    if ( cSet[0][left] <= cSet[k][right] ) { 
        	    temp_cSet.push_back(cSet[0][left]); 
        	    left = left + 1 ; 
       	 	} 
      	  	else { 
        		temp_cSet.push_back(cSet[k][right]); 
           	 	right = right + 1 ; 
        	} 
    	} 
  
    	while ( left < cSet[0].size()) { 
        	temp_cSet.push_back(cSet[0][left]); 
        	left = left + 1 ; 
    	} 
  
    	while ( right < cSet[k].size()) { 
        	temp_cSet.push_back(cSet[k][right]); 
        	right = right + 1 ; 
    	} 
    
    	cSet[0] = temp_cSet ;
    	
	} 
} 

bool readFile( vector<int> &process) {

	cout << endl << "Input file name : " ;
	cin >> input ;

	fstream file ;
	string tempname = input + ".txt" ;
	file.open( tempname.c_str(), ios::in);	
	
	if (!file.is_open()){
		cout << "檔案無法開啟\n" ;
		return false ;		
	}
	else {
		getline(file,command) ;
	    char tempchar = '\0' ;
	    string temp = "" ;
	    file.get(tempchar) ;
		while( !file.eof()) { 

			if(tempchar != ' '){
				temp = temp + tempchar ;
			}
			else{
				int number ;
            	stringstream ss(temp.c_str()); 
            	ss >> number ;
				process.push_back(number) ;
				temp = "" ;
			}
			file.get(tempchar) ;
		}
		
		file.close() ;
	}
	
	return true ;
} 	

void CreatprocessB(vector<int> &cSet){
	    
    for( int i = 0 ; i < cSet.size() ; i++) {
        
        for( int j = 0; j < cSet.size() ; j++) {
        	
            if( cSet[j] > cSet[i] ) {
			                
                int temp = cSet[j] ;
                cSet[j] = cSet[i] ;
                cSet[i] = temp ;
                
            }
        }
    }
}

void CreatprocessM(vector<int> &c1Set, vector<int> &c2Set){
    int left = 0 ;
    int right = 0 ;
	vector<int> cSet ;
  	
    while ( left < c1Set.size() && right < c2Set.size())  { 
        if ( c1Set[left] <= c2Set[right] ) { 
            cSet.push_back(c1Set[left]); 
            left = left + 1 ; 
        } 
        else { 
        	cSet.push_back(c2Set[right]); 
            right = right + 1 ; 
        } 
    } 
  
    while ( left < c1Set.size()) { 
        cSet.push_back(c1Set[left]); 
        left = left + 1 ; 
    } 
  
    while ( right < c2Set.size()) { 
        cSet.push_back(c2Set[right]); 
        right = right + 1 ; 
    } 
    
    c1Set = cSet ;
    
}

void saveFile( vector<int> &cSet , float time  ) { //逐一輸出檔案內容 
	string tempname = "output.txt" ;
	fstream file ;
	file.open( tempname.c_str(), ios::out) ; //開啟寫入模式 
	
	file << "排序: " << endl ;
	
	for(int i = 0; i < cSet.size() ; i++)  {  
		file << cSet[i] << " " ;

	}
	file << endl << "執行時間: " << time ;
	file.close() ; 
}
/*
void k_processB( vector <int> &data ) {
	pid_t pid = fork() ;
	if(pid == 0){
		BubbleSort(data) ;
		exit(0) ;
	}
	exit(0) ;
	
}


void k_processM( vector <int> &data1 ,vector <int> &data2 ) {
	pid_t pid = fork() ;
	if(pid == 0){
		Merge(data1,data2) ;
		exit(0) ;
	}
	exit(0) ;
	
}
*/

void Mission( vector <int> &process ){
	int number ;
    stringstream ss(command.c_str());
    ss >> number ;

	switch (number)  { 
		case 0: break;
 		case 1: {
 			float bT = clock() ;
			BubbleSort (process) ;
			bT = clock() - bT ;
			saveFile( process , bT/1000 ) ; 
 			break;
 		} 
 		case 2: {	
		 	int k = 0 ;	
			cout << "切成幾份: " ;
			cin >> k ; 
			int datasize = process.size() / k ;
			
			vector< vector<int> > k_process ;
			for(int i = 1 ; i <= k ; i ++ ) {
				vector<int> temp ;
				if( i < k ) {
					for(int j = (i-1)*datasize ; j < i*datasize ; j ++ ) {
						temp.push_back(process[j]) ;
					}
				}
				else {
					for(int j = (i-1)*datasize ; j < process.size() ; j ++ ) {
						temp.push_back(process[j]) ;
					}
				}

				k_process.push_back(temp) ;
			}
			
			float b_mT = clock() ;
			
    		vector<thread> threads;
    		for (int i = 0; i < k_process.size(); ++i){
         		threads.push_back( thread( BubbleSort , ref(k_process[i]) ) );   			
			}	
   			for(int i = 0; i < threads.size(); i++){
        		threads[i].join();
    		}
    		
    		vector<thread> threads2;
    		for (int i = 1; i < k_process.size(); ++i){
         		threads2.push_back( thread( Merge , ref(k_process[0]), ref(k_process[i]) ) );   			
			}	
   			for(int i = 0; i < threads2.size(); i++){
        		threads2[i].join();
    		}    		


			b_mT = clock() - b_mT ;	
			saveFile( k_process[0] , b_mT/1000 ) ; 	
			
 			break;
 		} 	
 		case 3: {
		 	int k = 0 ;	
			cout << "切成幾份: " ;
			cin >> k ; 
			int datasize = process.size() / k ;
			
			vector< vector<int> > k_process ;
			for(int i = 1 ; i <= k ; i ++ ) {
				vector<int> temp ;
				if( i < k ) {
					for(int j = (i-1)*datasize ; j < i*datasize ; j ++ ) {
						temp.push_back(process[j]) ;
					}
				}
				else {
					for(int j = (i-1)*datasize ; j < process.size() ; j ++ ) {
						temp.push_back(process[j]) ;
					}					
				}

				k_process.push_back(temp) ;
			}
			
 			float b_mT = clock() ;
		
			/*for(int h = 0 ; h < k_process.size() ; h ++ ){
				k_processB(k_process[h]) ;
			} 	
					
			for(int h = 1 ; h < k_process.size() ; h ++ ){
				k_processM(k_process[0],k_process[h]) ;
			} 		*/
			
			for(int h = 0 ; h < k_process.size() ; h ++ ){
				CreatprocessB(k_process[h]) ;
			} 	
			for(int h = 1 ; h < k_process.size() ; h ++ ){
				CreatprocessM(k_process[0],k_process[h]) ;
			} 				
			
			b_mT = clock() - b_mT ;	
			saveFile( k_process[0] , b_mT/1000 ) ; 			
 			break;
 		}
 		case 4: {
 		 	int k = 0 ;	
			cout << "切成幾份: " ;
			cin >> k ; 
			int datasize = process.size() / k ;
			
			vector< vector<int> > k_process ;
			for(int i = 1 ; i <= k ; i ++ ) {
				vector<int> temp ;
				if( i < k ) {
					for(int j = (i-1)*datasize ; j < i*datasize ; j ++ ) {
						temp.push_back(process[j]) ;
					}
				}
				else {
					for(int j = (i-1)*datasize ; j < process.size() ; j ++ ) {
						temp.push_back(process[j]) ;
					}					
				}

				k_process.push_back(temp) ;
			}
			
 			float b_mT = clock() ;
			BubbleSort2(k_process) ;					
			Merge2(k_process) ;		
			b_mT = clock() - b_mT ;	
			saveFile( k_process[0] , b_mT/1000 ) ; 			
 			break;
 		}
 	}
}

int main(void) { 


	vector<int> process ;
	readFile(process) ;
	cout << "process size : " << process.size() << endl ;
	Mission( process ) ;
	
	return 0;
} // end main


