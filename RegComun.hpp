  #ifndef RegComun_hpp
  #define RegComun_hpp
  #include <iostream>
  
  
  class RegComun{
  private:
  std::string date, hour, ipOrigin, originPort, nameOrigin, ipDestiny, destinyPort, nameDestiny;
  
  public:
  RegComun()=default;
  RegComun(std::string _date, std::string _hour, std::string _ipOrigin, std::string _originPort, std::string _nameOrigin, std::string _ipDestiny, std::string _destinyPort, std::string _nameDestiny): date(_date), hour(_hour), ipOrigin(_ipOrigin), originPort(_originPort), nameOrigin(_nameOrigin), ipDestiny(_ipDestiny), destinyPort(_destinyPort), nameDestiny(_nameDestiny){}
  
  static bool compareDateAsc(RegComun, RegComun);
  static bool compareNameAsc(RegComun, RegComun);
  std::string getDate() const;
  std::string getNameOrigin() const;
  std::string getipOrigin() const;
  std::string getIpDestiny() const;
  std::string getNameDestiny() const;
  std::string getDestinyPort() const;
  
  
  bool operator==(const RegComun& other);
  bool operator!=(const RegComun& other);
  
  friend std::ostream & operator<<(std::ostream & os, const RegComun & registro);
  
  };
  
  
  #endif /*RegComun*/