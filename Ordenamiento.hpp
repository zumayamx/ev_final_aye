#ifndef Ordenamiento_hpp
#define Ordenamiento_hpp
#include <iostream>
#include <vector>

template <class T>
class Ordenamiento{

public:
  static std::vector<T> insercion(std::vector<T>, bool(*)(T, T));

};

  template <class T>
  std::vector<T> Ordenamiento<T>::insercion(std::vector<T> vtos, bool tsort(T, T)){
    T index;
    int n=(int) vtos.size();
     for (int i = 1; i < n; ++i)
    {
        index = vtos[i];
        
        int j = i-1;
        
        while ( j >= 0 && tsort(index, vtos[j]))
        {
            vtos[j + 1] = vtos[j];
            j--;
        }
        
        vtos[j+1] = index;
    }
    
    return vtos;
}

 

#endif /*Ordenamiento*/