#ifndef _ROS_sofa_msgs_GroupPoint_h
#define _ROS_sofa_msgs_GroupPoint_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Int16.h"
#include "geometry_msgs/Point.h"

namespace sofa_msgs
{

  class GroupPoint : public ros::Msg
  {
    public:
      typedef std_msgs::Int16 _range_type;
      _range_type range;
      typedef geometry_msgs::Point _position_type;
      _position_type position;

    GroupPoint():
      range(),
      position()
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->range.serialize(outbuffer + offset);
      offset += this->position.serialize(outbuffer + offset);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->range.deserialize(inbuffer + offset);
      offset += this->position.deserialize(inbuffer + offset);
     return offset;
    }

    const char * getType(){ return "sofa_msgs/GroupPoint"; };
    const char * getMD5(){ return "1f69c893121caa2c488de6ac8bc1307b"; };

  };

}
#endif
