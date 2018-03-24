#ifndef __FOAS_MESSAGE_CLASS_H__
#define __FOAS_MESSAGE_CLASS_H__


#include <string>
#include <list>
#include <algorithm>
#include <mutex>


namespace foas {
  namespace message {
    class Class {
    private:
      std::string mName;

      std::mutex mSuperClassesAccess;
      std::list<std::string> mSuperClasses;
      
    public:
      Class(std::string name);
      ~Class();
      
      std::string GetName();
      void AddSuperClass(std::string name);
      bool HasDirectSuperClass(std::string name);

      std::list<std::string> GetSuperClasses();
    };
  }
}


#endif /* __FOAS_MESSAGE_CLASS_H__ */
