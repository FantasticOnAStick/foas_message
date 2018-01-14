#ifndef __FOAS_MESSAGE_MESSAGE_H__
#define __FOAS_MESSAGE_MESSAGE_H__


#include <foas/common/Property.h>


namespace foas {
  namespace message {
    class Message {
    private:
      common::Property mBaseProperty;
      
    public:
      Message();
      ~Message();
    };
  }
}


#endif /* __FOAS_MESSAGE_MESSAGE_H__ */
