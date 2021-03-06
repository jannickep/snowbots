/* Auto-generated by genmsg_cpp for file /home/mark/snowbots/src/10-11/ros-pkg/sb_msgs/msg/VisionNav.msg */
#ifndef SB_MSGS_MESSAGE_VISIONNAV_H
#define SB_MSGS_MESSAGE_VISIONNAV_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace sb_msgs
{
template <class ContainerAllocator>
struct VisionNav_ {
  typedef VisionNav_<ContainerAllocator> Type;

  VisionNav_()
  : confidence(0)
  , direction(0)
  , distance(0)
  {
  }

  VisionNav_(const ContainerAllocator& _alloc)
  : confidence(0)
  , direction(0)
  , distance(0)
  {
  }

  typedef int32_t _confidence_type;
  int32_t confidence;

  typedef int32_t _direction_type;
  int32_t direction;

  typedef int32_t _distance_type;
  int32_t distance;


private:
  static const char* __s_getDataType_() { return "sb_msgs/VisionNav"; }
public:
  ROS_DEPRECATED static const std::string __s_getDataType() { return __s_getDataType_(); }

  ROS_DEPRECATED const std::string __getDataType() const { return __s_getDataType_(); }

private:
  static const char* __s_getMD5Sum_() { return "3551098c9d8ba0ab66ec155e8ee6b271"; }
public:
  ROS_DEPRECATED static const std::string __s_getMD5Sum() { return __s_getMD5Sum_(); }

  ROS_DEPRECATED const std::string __getMD5Sum() const { return __s_getMD5Sum_(); }

private:
  static const char* __s_getMessageDefinition_() { return "int32 confidence #a percentage\n\
int32 direction  \n\
int32 distance \n\
\n\
"; }
public:
  ROS_DEPRECATED static const std::string __s_getMessageDefinition() { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED const std::string __getMessageDefinition() const { return __s_getMessageDefinition_(); }

  ROS_DEPRECATED virtual uint8_t *serialize(uint8_t *write_ptr, uint32_t seq) const
  {
    ros::serialization::OStream stream(write_ptr, 1000000000);
    ros::serialization::serialize(stream, confidence);
    ros::serialization::serialize(stream, direction);
    ros::serialization::serialize(stream, distance);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint8_t *deserialize(uint8_t *read_ptr)
  {
    ros::serialization::IStream stream(read_ptr, 1000000000);
    ros::serialization::deserialize(stream, confidence);
    ros::serialization::deserialize(stream, direction);
    ros::serialization::deserialize(stream, distance);
    return stream.getData();
  }

  ROS_DEPRECATED virtual uint32_t serializationLength() const
  {
    uint32_t size = 0;
    size += ros::serialization::serializationLength(confidence);
    size += ros::serialization::serializationLength(direction);
    size += ros::serialization::serializationLength(distance);
    return size;
  }

  typedef boost::shared_ptr< ::sb_msgs::VisionNav_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::sb_msgs::VisionNav_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct VisionNav
typedef  ::sb_msgs::VisionNav_<std::allocator<void> > VisionNav;

typedef boost::shared_ptr< ::sb_msgs::VisionNav> VisionNavPtr;
typedef boost::shared_ptr< ::sb_msgs::VisionNav const> VisionNavConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::sb_msgs::VisionNav_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::sb_msgs::VisionNav_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace sb_msgs

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::sb_msgs::VisionNav_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::sb_msgs::VisionNav_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::sb_msgs::VisionNav_<ContainerAllocator> > {
  static const char* value() 
  {
    return "3551098c9d8ba0ab66ec155e8ee6b271";
  }

  static const char* value(const  ::sb_msgs::VisionNav_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0x3551098c9d8ba0abULL;
  static const uint64_t static_value2 = 0x66ec155e8ee6b271ULL;
};

template<class ContainerAllocator>
struct DataType< ::sb_msgs::VisionNav_<ContainerAllocator> > {
  static const char* value() 
  {
    return "sb_msgs/VisionNav";
  }

  static const char* value(const  ::sb_msgs::VisionNav_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::sb_msgs::VisionNav_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int32 confidence #a percentage\n\
int32 direction  \n\
int32 distance \n\
\n\
";
  }

  static const char* value(const  ::sb_msgs::VisionNav_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::sb_msgs::VisionNav_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::sb_msgs::VisionNav_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.confidence);
    stream.next(m.direction);
    stream.next(m.distance);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct VisionNav_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::sb_msgs::VisionNav_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::sb_msgs::VisionNav_<ContainerAllocator> & v) 
  {
    s << indent << "confidence: ";
    Printer<int32_t>::stream(s, indent + "  ", v.confidence);
    s << indent << "direction: ";
    Printer<int32_t>::stream(s, indent + "  ", v.direction);
    s << indent << "distance: ";
    Printer<int32_t>::stream(s, indent + "  ", v.distance);
  }
};


} // namespace message_operations
} // namespace ros

#endif // SB_MSGS_MESSAGE_VISIONNAV_H

