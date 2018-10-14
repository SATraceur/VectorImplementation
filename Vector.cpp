/* 
 * File:   main.cpp
 * Author: Gamma
 *
 * Created on 8 May 2016, 2:58 PM
 */

#include <cstdlib>
#include <unistd.h>
#include <iostream>
#include <string>

using namespace std;

template <class T> 
class Vector { 
public: 
  typedef T* iterator; 
  
  Vector ()
  {
      used = 0;
  }
  
  iterator begin ()
  {
     return(&items[0]);
  }
  
  iterator end ()
  {
      return(&items[used]);
  }
  
  int size ()
  {
      return(used);
  }
  
  iterator insert (iterator position, const T& item)
  {
      for(iterator i = end(); i > position; i--)
      {
          *i = *(i-1);
      }
      
      *position = item;
      used++;
      
      return(position);
  }
  
private: 
  T items[1000]; 
  int used; 
}; 

int main(int argc, char** argv)
{ 
  enum { total, unique, alphabetical } mode = total; 
  
  for(int c; (c = getopt(argc, argv, "tui")) != -1;)
  { 
    switch(c)
    {
        case 't':
            mode = total;
            break; 
            
        case 'u':
            mode = unique;
            break; 
            
        case 'i':
            mode = alphabetical;
            break;
    } 
  } 
  
  argc -= optind; 
  argv += optind; 
  string word; 
  Vector<string> v;
  Vector<string> u;
  mode = alphabetical;
  switch(mode)
    {
        case total:
            while(cin>>word)
            {
                v.insert(v.end(), word);
            }
            break;
            
        case unique:
            while(cin>>word)
            {
                bool match = false;
                
                for(Vector<string>::iterator i = v.begin(); i <= v.end(); i++)
                {
                    if(*i == word)
                    {
                        match = true;
                    }
                }
                
                if(match != true)
                {
                    v.insert(v.end(), word);
                }
            }
            break;
            
        case alphabetical:
            while(cin>>word)
            {
                v.insert(v.end(), word);
            }
            word = "*USED*";
            for(int i = 0; i < v.size(); i++)
            {
                string *p = v.begin();
                for(Vector<string>::iterator i = v.begin(); i < v.end(); i++)
                {
                    if(*p < *i && *p != "*USED*")
                    {
                        *p = *i;
                    }
                }
                int counter = 0;
                u.insert(u.end(), *p);
                *p = *(u.end() - 1);
                for(Vector<string>::iterator i = v.begin(); i < v.end(); i++)
                {
                    if(*i == *p)
                    {
                        counter++;
                        v.insert(*i, word);
                    }
                }
                
            }
            break;
    }
   
  
  switch(mode)
  { 
    case total:
        cout << "Total: " << v.size() << endl;
        break; 
      
    case unique:
        cout << "Unique: " << v.size() << endl;
        break; 
      
    case alphabetical:
        for(Vector<string>::iterator i = u.begin(); i < u.end(); i++)
        {
            cout<<*i<<endl;
        }
        break;
  } 
} 