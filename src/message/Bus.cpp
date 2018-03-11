#include <foas/message/Bus.h>


namespace foas {
  namespace message {
    Bus::Bus(std::string name, std::shared_ptr<Bus> parentBus) : mName(name), mParentBus(parentBus) {
    }

    Bus::~Bus() {
      if(mParentBus) {
	mParentBus->RemoveSubBus(mName);
      }
    }

    bool Bus::HasQueuedMessagesAvailable() {
      std::lock_guard<std::mutex> lock(mHasQueuedMessagesAvailableMutex);
      return mHasQueuedMessagesAvailable;
    }
    
    void Bus::QueueMessage(std::string topic, std::shared_ptr<Message> message) {
      std::lock_guard<std::mutex> hasLock(mHasQueuedMessagesAvailableMutex);
      mHasQueuedMessagesAvailable = true;
      
      std::lock_guard<std::mutex> queueLock(mQueuedMessagesMutex);
      mQueuedMessages[topic].push_back(message);
    }
    
    std::map<std::string, std::list<std::shared_ptr<Message>>> Bus::CollectQueuedMessages() {
      std::lock_guard<std::mutex> hasLock(mHasQueuedMessagesAvailableMutex);
      std::lock_guard<std::mutex> queueLock(mQueuedMessagesMutex);
      
      std::map<std::string, std::list<std::shared_ptr<Message>>> queuedMessages = mQueuedMessages;
      mQueuedMessages.clear();
      mHasQueuedMessagesAvailable = false;
      
      return queuedMessages;
    }
    
    void Bus::PostMessage(std::string topic, std::shared_ptr<Message> message) {
      // TODO: Iterate through all participants that are interested in 'topic' and sent them the 'message'.
    }
    
    std::shared_ptr<Bus> Bus::CreateSubBus(std::string name) {
      std::lock_guard<std::mutex> lockSubBusses(mSubBussesMutex);
      
      std::shared_ptr<Bus> subBus = std::make_shared<Bus>(name, this->shared_from_this());
      mSubBusses[name] = subBus;
      
      return subBus;
    }
    
    void Bus::RemoveSubBus(std::string name) {
      std::lock_guard<std::mutex> lockSubBusses(mSubBussesMutex);
      
      mSubBusses.erase(mSubBusses.find(name));
    }
  }
}
