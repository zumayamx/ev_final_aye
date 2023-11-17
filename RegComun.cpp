#include "RegComun.hpp"
  
 bool RegComun::compareDateAsc(RegComun a, RegComun b){
    return a.date < b.date;
  }
  bool RegComun::compareNameAsc(RegComun a, RegComun b){
    return a.nameOrigin < b.nameOrigin;
  }
  std::string RegComun::getDate() const{
    return date;
  }
  std::string RegComun::getNameOrigin() const{
    return nameOrigin;
  }
  std::string RegComun::getIpDestiny() const{
    return ipDestiny;
  }
  std::string RegComun::getPortOrigin() const{
    return originPort;
  }
  std::string RegComun::getNameDestiny() const{
    return nameDestiny;
  }
  std::string RegComun::getDestinyPort() const{
    return destinyPort;
  }
  
  std::string RegComun::getipOrigin() const{
    return ipOrigin;
  }
  std::ostream & operator<<(std::ostream & os, const RegComun & registro)
  {
      //os << registro.nameOrigin<<std::endl;
      //os << registro.nameDestiny<<std::endl;
      //os << registro.destinyPort<<std::endl;
      os << registro.ipOrigin<<std::endl;
      //os << registro.ipDestiny<<std::endl;
      os << std::endl;
      
      return os;
  }
  
  
  bool RegComun::operator!=(const RegComun& other){
    return this->ipOrigin != other.ipOrigin || this->ipDestiny != other.ipDestiny;
  }
  
  
  bool RegComun::operator==(const RegComun& other){
    return this->ipOrigin == other.ipOrigin || this->ipDestiny == other.ipDestiny;
  }
  
  
  