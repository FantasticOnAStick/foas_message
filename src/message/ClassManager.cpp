#include <foas/message/ClassManager.h>


namespace foas {
  namespace message {
    std::shared_ptr<ClassManager> ClassManager::sSingleton = nullptr;
    
    
    std::shared_ptr<ClassManager> ClassManager::GetSingleton() {
      if(!sSingleton) {
	sSingleton = std::make_shared<ClassManager>();
      }
      
      return sSingleton;
    }
    
    
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

    std::shared_ptr<common::Property> ClassManager::InstantiateClass(std::string name) {
      std::shared_ptr<common::Property> instance = nullptr;
      std::shared_ptr<Class> theClass = this->GetClass(name);
      
      if(theClass) {
	instance = std::make_shared<common::Property>();
	instance->Get("class") = std::make_shared<common::Property>(theClass->GetName());
	instance->Get("content") = std::make_shared<common::Property>(common::Property::Dictionary);
      }
      
      return instance;
    }
  }
}
