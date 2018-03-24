#include <foas/message/Class.h>


namespace foas {
  namespace message {
    Class::Class(std::string name) : mName(name) {
    }

    Class::~Class() {
    }

    std::string Class::GetName() {
      return mName;
    }
    
    void Class::AddSuperClass(std::string name) {
      std::lock_guard<std::mutex> lock(mSuperClassesAccess);
      
      if(std::find(mSuperClasses.begin(), mSuperClasses.end(), name) == mSuperClasses.end()) {
	mSuperClasses.push_back(name);
      }
    }

    bool Class::HasDirectSuperClass(std::string name) {
      std::lock_guard<std::mutex> lock(mSuperClassesAccess);
      
      return std::find(mSuperClasses.begin(), mSuperClasses.end(), name) != mSuperClasses.end();
    }
    
    std::list<std::shared_ptr<Class>> Class::GetSuperClasses() {
      return mSuperClasses;
    }
  }
}
