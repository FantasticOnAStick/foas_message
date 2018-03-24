#ifndef __FOAS_MESSAGE_MESSAGE_H__
#define __FOAS_MESSAGE_MESSAGE_H__


#include <foas/common/Property.h>


namespace foas {
  namespace message {
    class Message {
    private:
      std::shared_ptr<common::Property> mBaseProperty;
      std::string mSender;
      std::string mReceiver;
      
    public:
      Message(std::shared_ptr<common::Property> baseProperty = std::make_shared<common::Property>());
      ~Message();
      
      std::shared_ptr<common::Property> GetProperty();
      
      std::shared_ptr<common::Property> operator[](std::string key);
      std::shared_ptr<common::Property> operator[](int index);
      
      void SetSender(std::string sender);
      void SetReceiver(std::string receiver);

      std::string GetSender();
      std::string GetReceiver();
    };
  }
}


#endif /* __FOAS_MESSAGE_MESSAGE_H__ */
