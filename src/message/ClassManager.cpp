#include <foas/message/ClassManager.h>


namespace foas {
  namespace message {
    ClassManager::ClassManager() {
    }
    
    ClassManager::~ClassManager() {
    }
    
    std::shared_ptr<Class> ClassManager::CreateClass(std::string name) {
      std::shared_ptr<Class> newClass = this->GetClass(name);
      
      if(!newClass) {
	std::lock_guard<std::mutex> lock(mClassesAccess);
	
	newClass = std::make_shared<Class>(name);
	mClasses[name] = newClass;
      }
      
      return newClass;
    }
    
    std::shared_ptr<Class> ClassManager::GetClass(std::string name) {
      std::lock_guard<std::mutex> lock(mClassesAccess);
      
      if(mClasses.find(name) != mClasses.end()) {
	return mClasses[name];
      }
      
      return nullptr;
    }
    
    bool ClassManager::IsSubClassOf(std::string subClass, std::string superClass) {
      std::shared_ptr<Class> theClass = this->GetClass(subClass);
      
      if(theClass) {
	if(subClass == superClass) {
	  return true;
	} else {
	  if(theClass->HasDirectSuperClass(superClass)) {
	    return true;
	  } else {
	    for(std::string theSuperClass : theClass->GetSuperClasses()) {
	      if(this->IsSubClassOf(subClass, theSuperClass)) {
		return true;
	      }
	    }
	  }
	}
      }

      return false;
    }
  }
}
