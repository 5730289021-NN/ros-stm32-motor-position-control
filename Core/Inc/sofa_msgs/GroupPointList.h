#ifndef _ROS_sofa_msgs_GroupPointList_h
#define _ROS_sofa_msgs_GroupPointList_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int16MultiArray.h"
#include "geometry_msgs/Point.h"

namespace sofa_msgs
{

  class GroupPointList : public ros::Msg
  {
    public:
      typedef std_msgs::Int16 _number_type;
      _number_type number;
      typedef std_msgs::Int16MultiArray _ranges_type;
      _ranges_type ranges;
      uint32_t positions_length;
      typedef geometry_msgs::Point _positions_type;
      _positions_type st_positions;
      _positions_type * positions;

    GroupPointList():
      number(),
      ranges(),
      positions_length(0), positions(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->number.serialize(outbuffer + offset);
      offset += this->ranges.serialize(outbuffer + offset);
      *(outbuffer + offset + 0) = (this->positions_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->positions_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->positions_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->positions_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->positions_length);
      for( uint32_t i = 0; i < positions_length; i++){
      offset += this->positions[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->number.deserialize(inbuffer + offset);
      offset += this->ranges.deserialize(inbuffer + offset);
      uint32_t positions_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      positions_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      positions_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      positions_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->positions_length);
      if(positions_lengthT > positions_length)
        this->positions = (geometry_msgs::Point*)realloc(this->positions, positions_lengthT * sizeof(geometry_msgs::Point));
      positions_length = positions_lengthT;
      for( uint32_t i = 0; i < positions_length; i++){
      offset += this->st_positions.deserialize(inbuffer + offset);
        memcpy( &(this->positions[i]), &(this->st_positions), sizeof(geometry_msgs::Point));
      }
     return offset;
    }

    const char * getType(){ return "sofa_msgs/GroupPointList"; };
    const char * getMD5(){ return "a321227dd9b54e148d1acf57ba13479c"; };

  };

}
#endif
