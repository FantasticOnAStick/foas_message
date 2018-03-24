#ifndef __FOAS_MESSAGE_BUS_H__
#define __FOAS_MESSAGE_BUS_H__


#include <mutex>
#include <condition_variable>
#include <map>
#include <list>
#include <string>
#include <memory>

#include <foas/message/Message.h>
#include <foas/message/ClassManager.h>


namespace foas {
  namespace message {
    class Bus : public std::enable_shared_from_this<Bus> {
    private:
      std::string mName;
      
      std::mutex mHasQueuedMessagesAvailableMutex;
      bool mHasQueuedMessagesAvailable;
      
      std::mutex mQueuedMessagesMutex;
      std::map<std::string, std::list<std::shared_ptr<Message>>> mQueuedMessages;
      
      std::shared_ptr<Bus> mParentBus;
      std::mutex mSubBussesMutex;
      std::map<std::string, std::shared_ptr<Bus>> mSubBusses;
      
      std::shared_ptr<ClassManager> mClassManager;
      
    public:
      Bus(std::string name, std::shared_ptr<Bus> parentBus = nullptr);
      ~Bus();
      
      bool HasQueuedMessagesAvailable();
      void QueueMessage(std::string topic, std::shared_ptr<Message> message);
      std::map<std::string, std::list<std::shared_ptr<Message>>> CollectQueuedMessages();
      
      void PostMessage(std::string topic, std::shared_ptr<Message> message);
      
      std::shared_ptr<Bus> CreateSubBus(std::string name);
      void RemoveSubBus(std::string name);
      
      void SetClassManager(std::shared_ptr<ClassManager> classManager);
      std::shared_ptr<ClassManager> GetClassManager();
    };
  }
}


#endif /* __FOAS_MESSAGE_BUS_H__ */
