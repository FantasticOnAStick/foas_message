#include <foas/message/Message.h>


namespace foas {
  namespace message {
    Message::Message(std::shared_ptr<common::Property> baseProperty) : mBaseProperty(baseProperty), mSender(""), mReceiver("") {
    }
    
    Message::~Message() {
    }
    
    std::shared_ptr<common::Property> Message::GetProperty() {
      return mBaseProperty;
    }
    
    std::shared_ptr<common::Property> Message::operator[](std::string key) {
      return mBaseProperty->Get(key);
    }
    
    std::shared_ptr<common::Property> Message::operator[](int index) {
      return mBaseProperty->Get(index);
    }
    
    void Message::SetSender(std::string sender) {
      mSender = sender;
    }
    
    void Message::SetReceiver(std::string receiver) {
      mReceiver = receiver;
    }
    
    void Message::AddSenderPrefix(std::string prefix) {
      if(mSender != "") {
	mSender = "." + mSender;
      }

      mSender = prefix + mSender;
    }
    
    std::string Message::GetSender() {
      return mSender;
    }

    std::string Message::GetReceiver() {
      return mReceiver;
    }
  }
}
