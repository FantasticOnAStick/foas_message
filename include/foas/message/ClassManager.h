#ifndef __FOAS_MESSAGE_CLASSMANAGER_H__
#define __FOAS_MESSAGE_CLASSMANAGER_H__


#include <map>
#include <mutex>
#include <string>
#include <memory>
#include <iostream>

#include <foas/message/Class.h>
#include <foas/common/Property.h>


namespace foas {
  namespace message {
    class ClassManager {
    private:
      static std::shared_ptr<ClassManager> sSingleton;
      
      std::mutex mClassesAccess;
      std::map<std::string, std::shared_ptr<Class>> mClasses;
      
    public:
      ClassManager();
      ~ClassManager();
      
      std::shared_ptr<Class> CreateClass(std::string name);
      std::shared_ptr<Class> GetClass(std::string name);

      bool IsSubClassOf(std::string subClass, std::string superClass);
      
      std::shared_ptr<common::Property> InstantiateClass(std::string name);

      static std::shared_ptr<ClassManager> GetSingleton();
    };
  }
}


#endif /* __FOAS_MESSAGE_CLASSMANAGER_H__ */
