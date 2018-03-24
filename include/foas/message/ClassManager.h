#ifndef __FOAS_MESSAGE_CLASSMANAGER_H__
#define __FOAS_MESSAGE_CLASSMANAGER_H__


#include <map>
#include <mutex>
#include <string>
#include <memory>

#include <foas/message/Class.h>


namespace foas {
  namespace message {
    class ClassManager {
    private:
      std::mutex mClassesAccess;
      std::map<std::string, std::shared_ptr<Class>> mClasses;
      
    public:
      ClassManager();
      ~ClassManager();
      
      std::shared_ptr<Class> CreateClass(std::string name);
      std::shared_ptr<Class> GetClass(std::string name);

      bool IsSubClassOf(std::string subClass, std::string superClass);
    };
  }
}


#endif /* __FOAS_MESSAGE_CLASSMANAGER_H__ */
